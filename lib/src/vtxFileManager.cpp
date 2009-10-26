/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/vektrix

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
#include "vtxStringHelper.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	template<> FileManager* Singleton<FileManager>::sInstance = 0;
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
			// no container found
			VTX_EXCEPT("Unable to find parser to handle a file with extension '%s'.", file_extension.c_str());
		}

		//File* file = new File(filename);

		File* file = parser->parse(stream);

		if(!file)
		{
			// no container found
			VTX_EXCEPT("An unknown error occured during parsing the file \"%s\".", filename.c_str());
		}

		file->startedLoading();

		// DEBUG / TODO: implement this more beautifully
		// how to pass the framerate from fileheader to the timeline
		file->getTimeline().setFrameRate(file->getHeader().fps);

		//XMLParser movie_parser(file);

		////std::list<String> test = {"baba", "gaga"};
		////String test[] = {"baba", "gaga"};

		//String hdrDH[] = 
		//{
		//	"vectrix|header|"
		//};
		//movie_parser.addDataHandler(hdrDH, size_of(hdrDH), new HeaderDataHandler);

		//String rscsDH[] = 
		//{
		//	"vectrix|resources|image|", 
		//	"vectrix|resources|material|", 
		//	"vectrix|resources|sound|", 
		//	"vectrix|resources|shape|", 
		//	"vectrix|resources|button|", 
		//	"vectrix|resources|movieclip|"
		//};
		//movie_parser.addDataHandler(rscsDH, size_of(rscsDH), new ResourcesDataHandler);

		//String tmlnDH[] = 
		//{
		//	"vectrix|timeline|", 
		//	"vectrix|timeline|keyframe|", 
		//	"vectrix|timeline|keyframe|event|"
		//};
		//movie_parser.addDataHandler(tmlnDH, size_of(tmlnDH), new TimelineDataHandler);

		//movie_parser.parse(stream);

		// TODO: implement FileStreamPtr, so we don't need to destroy instances by hand ?
		stream->close();

		mLoadedFiles.insert(FileMap::value_type(filename, file));

		file->finishedLoading();

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
		//FactoryMap::iterator factory_it = mFactories.find(type);
		FileContainerFactory* factory = getFactory(type);

		if(factory)
		{
			if(mContainers.find(name) == mContainers.end())
			{
				FileContainer* temp = factory->createObject(name);
				mContainers.insert(FileContainerMap::value_type(name, temp));
				return temp;
			}

			// LOG: name already exists
			VTX_EXCEPT("A movie with the name '%s' already exists!", name.c_str());
			return NULL;
		}

		VTX_EXCEPT("A FileContainerFactory with the name '%s' doesn't exist!", type.c_str());
		return NULL;
	}
	//-----------------------------------------------------------------------
}
