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

#include "vtxEventListener.h"
#include "vtxFileEvent.h"
#include "vtxFileParsingJob.h"
#include "vtxFileStream.h"
#include "vtxFileContainer.h"
#include "vtxLogManager.h"
#include "vtxMovieClipResource.h"
#include "vtxRoot.h"
#include "vtxStringHelper.h"
#include "vtxThreadJobQueue.h"
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
#ifdef VTX_THREADED_LOADING_ENABLED

		if(VTX_TRY_MUTEX_LOCK(mMutex))
		{
#endif
			while(mFinishedFiles.size())
			{
				const FinishedFile& finished_file = mFinishedFiles.back();
				File* file = finished_file.second;

				VTX_LOG("Calling file listeners for %s", file->getFilename().c_str());

				// loading succeeded
				if(finished_file.first)
				{
					file->_loadingCompleted();
				}
				// loading failed
				else
				{
					file->_loadingFailed();
					delete file;
				}

				mFinishedFiles.pop_back();
			}

#ifdef VTX_THREADED_LOADING_ENABLED
			VTX_MANUAL_MUTEX_UNLOCK(mMutex);
		}
#endif
	}
	//-----------------------------------------------------------------------
	bool FileManager::doesFileExist(const String& filename)
	{
		VTX_LOCK_MUTEX(mContainersMutex);

		FileContainerMap::iterator container_it = mContainers.begin();

		for( ; container_it != mContainers.end(); ++container_it)
		{
			if(container_it->second->hasFile(filename))
			{
				return true;
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	File* FileManager::getFile(const String& filename, const bool& threadedParsing, EventListener* listener)
	{
		// empty filename
		if(!filename.length())
		{
			VTX_WARN("Tried to load file but no filename was given");
			return NULL;
		}

#ifdef VTX_THREADED_LOADING_ENABLED
		VTX_LOCK_MUTEX(mMutex);
#endif

		FileMap::iterator file_it = mReadyFiles.find(filename);

		if(file_it != mReadyFiles.end())
		{
			//VTX_DEBUG("Reloading file '%s' from memory.", filename.c_str());

			if(listener)
			{
				file_it->second->addListener(listener);

				FileEvent evt(FileEvent::LOADING_COMPLETED, file_it->second);
				listener->eventFired(evt);
			}

			return file_it->second;
		}

#ifdef VTX_THREADED_LOADING_ENABLED

		file_it = mParsingFiles.find(filename);

		if(file_it != mParsingFiles.end())
		{
			//VTX_LOG("Requested file '%s' is currently being parsed.", filename.c_str());

			if(listener)
			{
				file_it->second->addListener(listener);
			}

			return file_it->second;
		}

#endif // VTX_THREADED_LOADING_ENABLED

		// not loaded yet ---> load it
		VTX_LOG("Trying to load file '%s'...", filename.c_str());

		String file_extension = StringHelper::getFileExtension(filename);

		FileParserFactory* factory = getParserFactory(file_extension);

		if(!factory)
		{
			// no parser found
			VTX_WARN("Unable to find a parser to handle a file with extension '%s'.", file_extension.c_str());
			return NULL;
		}

		FileParser* parser = factory->createObject();

		File* file = new File(filename);
		FileParsingJob* job = new FileParsingJob(parser, file);

		if(listener)
		{
			file->addListener(listener);
		}

		if(threadedParsing)
		{
#ifdef VTX_THREADED_LOADING_ENABLED
			mParsingFiles.insert(std::make_pair(filename, file));
			Root::getSingletonPtr()->getMainJobQueue()->queueJob(job);
#else
			VTX_WARN("Requested threaded loading but vektrix was compiled without threading support.");
			job->start();
			delete job;
#endif
		}
		else
		{
			job->start();
			delete job;
		}

		return file;
	}
	//-----------------------------------------------------------------------
	bool FileManager::addFile(File* file)
	{
		FileMap::const_iterator it = mReadyFiles.find(file->getFilename());
		if(it == mReadyFiles.end())
		{
			mReadyFiles.insert(std::make_pair(file->getFilename(), file));
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool FileManager::removeFile(File* file)
	{
		FileMap::const_iterator it = mReadyFiles.find(file->getFilename());
		if(it != mReadyFiles.end())
		{
			mReadyFiles.erase(it);
			return true;
		}

		return false;
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
			ParserExtensionMap::iterator it = mParsersByExt.begin();
			ParserExtensionMap::iterator end = mParsersByExt.end();
			while(it != end)
			{
				if(it->second == factory)
				{
					VTX_LOG("Removed FileParser for extension \"%s\".", it->first.c_str());

					mParsersByExt.erase(it);
					it = mParsersByExt.begin();
					end = mParsersByExt.end();
					continue;
				}

				++it;
			}
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
			String uri = type + "://" + name;
			if(mContainers.find(uri) == mContainers.end())
			{
				FileContainer* container = factory->createObject(name);
				mContainers.insert(FileContainerMap::value_type(uri, container));
				return container;
			}

			VTX_EXCEPT("A container with the URI '%s' already exists!", uri.c_str());
			return NULL;
		}

		VTX_EXCEPT("A FileContainerFactory with the name '%s' doesn't exist!", type.c_str());
		return NULL;
	}
	//-----------------------------------------------------------------------
	void FileManager::unloadAllFiles()
	{
#ifdef VTX_THREADED_LOADING_ENABLED

		// make sure that all file listeners have been informed before continuing the shutdown
		update();

#endif // VTX_THREADED_LOADING_ENABLED

		VTX_LOG("Unloading files...");

		FileMap::iterator it = mReadyFiles.begin();
		FileMap::iterator end = mReadyFiles.end();
		while(it != end)
		{
			VTX_LOG("Unloading file %s", it->second->getFilename().c_str());
			delete it->second;
			++it;
		}
	}
	//-----------------------------------------------------------------------
	void FileManager::_finishedParsing(File* file)
	{
#ifdef VTX_THREADED_LOADING_ENABLED
		VTX_LOCK_MUTEX(mMutex);

		FileMap::iterator it = mParsingFiles.find(file->getFilename());
		if(it != mParsingFiles.end())
		{
			mParsingFiles.erase(it);
		}
#endif

		mFinishedFiles.push_back(FinishedFile(true, file));
		mReadyFiles.insert(FileMap::value_type(file->getFilename(), file));
	}
	//-----------------------------------------------------------------------
	void FileManager::_failedParsing(File* file)
	{
#ifdef VTX_THREADED_LOADING_ENABLED
		VTX_LOCK_MUTEX(mMutex);

		FileMap::iterator it = mParsingFiles.find(file->getFilename());
		if(it != mParsingFiles.end())
		{
			mParsingFiles.erase(it);
		}
#endif

		mFinishedFiles.push_back(FinishedFile(false, file));
	}
	//-----------------------------------------------------------------------
}
