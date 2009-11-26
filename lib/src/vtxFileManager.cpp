/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009 Fuse-Software (tm)

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
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
			// no container found
			VTX_EXCEPT("An unknown error occured during parsing the file \"%s\".", filename.c_str());
		}

		// DEBUG / TODO: implement this more beautifully
		// how to pass the framerate from fileheader to the timeline
		// Answer: movieclips retrieve the framerate automatically from
		// their parent movie
		file->getMainMovieClip()->getTimeline()->setFrameRate(file->getHeader().fps);

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
