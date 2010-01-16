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
#include "vtxFileParser.h"
#include "vtxFileStream.h"
#include "vtxFileContainerFactory.h"
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
		: FactoryManager<FileContainerFactory, DefaultFileContainerFactory>("FileContainer")
	{

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

		FileParserMap::iterator pars_it = mParsers.begin();
		FileParserMap::iterator pars_end = mParsers.end();
		while(pars_it != pars_end)
		{
			delete pars_it->second;
			++pars_it;
		}

		FileMap::iterator it = mLoadedFiles.begin();
		FileMap::iterator end = mLoadedFiles.end();
		while(it != end)
		{
			delete it->second;
			++it;
		}
	}
	//-----------------------------------------------------------------------
	File* FileManager::getFile(const String& filename)
	{
		FileMap::iterator file_it = mLoadedFiles.find(filename);

		if(file_it != mLoadedFiles.end())
		{
			VTX_LOG("Reloading '%s' from memory.", filename.c_str());

			return file_it->second;
		}

		// not loaded yet ---> load it
		VTX_LOG("Trying to load file '%s'...", filename.c_str());

		FileStream* stream = getFileStream(filename);

		if(!stream)
		{
			// no container found
			VTX_EXCEPT("Unable to find container to load file '%s'.", filename.c_str());
		}

		String file_extension = StringHelper::getFileExtension(filename);

		FileParser* parser = getFileParser(file_extension);

		if(!parser)
		{
			// no parser found
			VTX_EXCEPT("Unable to find parser to handle a file with extension '%s'.", file_extension.c_str());
		}

		File* file = parser->parse(stream);

		if(!file)
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

		mLoadedFiles.insert(FileMap::value_type(filename, file));

		VTX_LOG("Successfully loaded '%s'.", filename.c_str());

		return file;
	}
	//-----------------------------------------------------------------------
	FileStream* FileManager::getFileStream(const String& filename)
	{
		FileContainerMap::iterator container_it = mContainers.begin();

		for( ; container_it != mContainers.end(); container_it++)
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
	bool FileManager::addFileParser(FileParser* parser)
	{
		FileParserMap::iterator it = mParsers.find(parser->getExtension());

		if(it == mParsers.end())
		{
			mParsers.insert(FileParserMap::value_type(parser->getExtension(), parser));
			VTX_LOG("Added FileParser for extension \"%s\".", parser->getExtension().c_str());
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	FileParser* FileManager::getFileParser(const String extension)
	{
		FileParserMap::iterator it = mParsers.find(extension);

		if(it != mParsers.end())
		{
			return it->second;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	bool FileManager::removeFileParser(FileParser* parser)
	{
		FileParserMap::iterator it = mParsers.find(parser->getExtension());

		if(it != mParsers.end())
		{
			mParsers.erase(it);
			VTX_LOG("Removed FileParser for extension \"%s\".", parser->getExtension().c_str());
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	FileContainer* FileManager::addFileContainer(const String& name, const String& type)
	{
		FileContainerFactory* factory = getFactory(type);

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
}
