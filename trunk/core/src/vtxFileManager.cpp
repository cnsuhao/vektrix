/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009-2010 Fuse-Software (tm)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#include "vtxFileManager.h"

#include "vtxFile.h"
#include "vtxFileParsingJob.h"
#include "vtxFileStream.h"
#include "vtxFileContainer.h"
#include "vtxLogManager.h"
#include "vtxMovieClipResource.h"
#include "vtxStringHelper.h"
#include "vtxTimeline.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	template<> FileManager* Singleton<FileManager>::sInstance = 0;
	//-----------------------------------------------------------------------
	FileManager::FileManager() 
		: mContainerFactories("FileContainer"), 
		mParserFactories("FileParser")
	{
		mContainerFactories.addFactory(new DefaultFileContainerFactory);
	}
	//-----------------------------------------------------------------------
	FileManager::~FileManager()
	{
		FileContainerMap::iterator cont_it = mContainers.begin();
		FileContainerMap::iterator cont_end = mContainers.end();
		while(cont_it != cont_end)
		{
			delete cont_it->second;
			++cont_it;
		}
	}
	//-----------------------------------------------------------------------
	void FileManager::update()
	{
#ifdef VTX_THREADING_ENABLED

		VTX_LOCK_MUTEX(mFinishedFilesMutex);

		while(mFinishedFiles.size())
		{
			File* file = mFinishedFiles.back();
			file->_loadingCompleted();
			mFinishedFiles.pop_back();
		}

#endif // VTX_THREADING_ENABLED
	}
	//-----------------------------------------------------------------------
	File* FileManager::getFile(const String& filename, const bool& threadedParsing)
	{
		// empty filename
		if(!filename.length())
		{
			VTX_WARN("Tried to load file but no filename was given");
			return NULL;
		}

		FileMap::iterator file_it = mFiles.find(filename);

		if(file_it != mFiles.end())
		{
			VTX_LOG("Reloading file '%s' from memory.", filename.c_str());

			return file_it->second;
		}

		VTX_LOCK_MUTEX(mParsingFilesMutex);
		file_it = mParsingFiles.find(filename);

		if(file_it != mParsingFiles.end())
		{
			VTX_LOG("Requested file '%s' is currently being parsed.", filename.c_str());

			return file_it->second;
		}

		// not loaded yet ---> load it
		VTX_LOG("Trying to load file '%s'...", filename.c_str());

		String file_extension = StringHelper::getFileExtension(filename);

		FileParserFactory* factory = getParserFactory(file_extension);

		if(!factory)
		{
			// no parser found
			VTX_WARN("Unable to find parser to handle a file with extension '%s'.", file_extension.c_str());
			return NULL;
		}

		FileParser* parser = factory->createObject();

		File* file = new File(filename);
		mParsingFiles.insert(std::make_pair(filename, file));

#ifdef VTX_THREADING_ENABLED
		if(threadedParsing)
		{
			FileParsingJob* job = new FileParsingJob(parser, file);
			VTX_CREATE_THREAD(thread, *job);
			mThreads.push_back(thread);
		}
		else
#endif // VTX_THREADING_ENABLED
		{
			FileStream* stream = getFileStream(filename);

			if(!stream)
			{
				// no container found
				VTX_WARN("Unable to find container to load file '%s'.", filename.c_str());
				return NULL;
			}

			parser->parse(stream, file);

			if(parser->errorsOccured())
			{
				String error = parser->getError();
				while(error.length())
				{
					VTX_WARN(error.c_str());
					error = parser->getError();
				}

				VTX_EXCEPT("An error occured while parsing the file \"%s\", see the log for details.", filename.c_str());
			}

			// TODO: implement FileStreamPtr, so we don't need to destroy instances by hand ?
			stream->close();
			delete stream;

			factory->destroyObject(parser);

			mFiles.insert(FileMap::value_type(filename, file));
			VTX_LOG("Successfully loaded '%s'.", filename.c_str());
			return file;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	FileStream* FileManager::getFileStream(const String& filename)
	{
		VTX_LOCK_MUTEX(mContainersMutex);

		FileContainerMap::iterator container_it = mContainers.begin();

		for( ; container_it != mContainers.end(); ++container_it)
		{
			FileContainer* container = container_it->second;

			if(container->hasFile(filename))
			{
				return container->openFile(filename);
			}
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	void FileManager::addParserFactory(FileParserFactory* factory)
	{
		mParserFactories.addFactory(factory);

		if(factory)
		{
			FileParser* parser = factory->createObject();

			const StringList& extensions = parser->getExtensions();

			StringList::const_iterator ext_it = extensions.begin();
			StringList::const_iterator ext_end = extensions.end();
			while(ext_it != ext_end)
			{
				const String& ext = *ext_it;
				ParserExtensionMap::iterator it = mParsersByExt.find(ext);

				if(it == mParsersByExt.end())
				{
					mParsersByExt.insert(std::make_pair(ext, factory));
					VTX_LOG("Added FileParser for extension \"%s\".", ext.c_str());
				}
				else
				{
					VTX_WARN("Tried to add FileParser for an already registered extension: \"%s\"", ext.c_str());
				}

				++ext_it;
			}

			factory->destroyObject(parser);
		}
	}
	//-----------------------------------------------------------------------
	FileParserFactory* FileManager::getParserFactory(const String extension)
	{
		ParserExtensionMap::iterator it = mParsersByExt.find(extension);

		if(it != mParsersByExt.end())
		{
			return it->second;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	void FileManager::removeParserFactory(FileParserFactory* factory)
	{
		mParserFactories.removeFactory(factory);

		if(factory)
		{
			FileParser* parser = factory->createObject();

			const StringList& extensions = parser->getExtensions();

			StringList::const_iterator ext_it = extensions.begin();
			StringList::const_iterator ext_end = extensions.end();
			while(ext_it != ext_end)
			{
				const String& ext = *ext_it;
				ParserExtensionMap::iterator it = mParsersByExt.find(ext);

				if(it != mParsersByExt.end())
				{
					mParsersByExt.erase(it);
					VTX_LOG("Removed FileParser for extension \"%s\".", ext.c_str());
				}

				++ext_it;
			}

			factory->destroyObject(parser);
		}
	}
	//-----------------------------------------------------------------------
	FileManager::ContainerManager& FileManager::getContainerManager()
	{
		return mContainerFactories;
	}
	//-----------------------------------------------------------------------
	FileContainer* FileManager::addFileContainer(const String& name, const String& type)
	{
		VTX_LOCK_MUTEX(mContainersMutex);

		FileContainerFactory* factory = mContainerFactories.getFactory(type);

		if(factory)
		{
			if(mContainers.find(name) == mContainers.end())
			{
				FileContainer* container = factory->createObject(name);
				mContainers.insert(FileContainerMap::value_type(name, container));
				return container;
			}

			VTX_EXCEPT("A container with the name '%s' already exists!", name.c_str());
			return NULL;
		}

		VTX_EXCEPT("A FileContainerFactory with the name '%s' doesn't exist!", type.c_str());
		return NULL;
	}
	//-----------------------------------------------------------------------
	void FileManager::unloadAllFiles()
	{
		VTX_LOG("Unloading files...");

		FileMap::iterator it = mFiles.begin();
		FileMap::iterator end = mFiles.end();
		while(it != end)
		{
			VTX_LOG("Unloading file %s", it->second->getFilename().c_str());
			delete it->second;
			++it;
		}
	}
	//-----------------------------------------------------------------------
}
