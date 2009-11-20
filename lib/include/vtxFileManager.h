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
#pragma once

#include "vtxPrerequesites.h"
#include "vtxDefaultFileContainer.h"
#include "vtxDefaultFileContainerFactory.h"
#include "vtxFileContainerFactory.h"
#include "vtxFactoryManager.h"
#include "vtxSingleton.h"

namespace vtx
{
	class vtxExport FileManager : public Singleton<FileManager>, public FactoryManager<FileContainerFactory, DefaultFileContainerFactory>
	{
	public:
		typedef std::map<String, File*> FileMap;
		typedef std::map<String, FileContainer*> FileContainerMap;
		typedef std::map<String, FileParser*> FileParserMap;

		FileManager();
		virtual ~FileManager();

		File* getFile(const String& filename);
		FileStream* getFileStream(const String& filename);

		bool addFileParser(FileParser* parser);
		FileParser* getFileParser(const String extension);

		FileContainer* addFileContainer(const String& name, const String& type = DefaultFileContainer::FACTORY_NAME);

	protected:
		// map of the already loaded files
		FileMap mLoadedFiles;
		// map of registered file parsers
		FileParserMap mParsers;
		// map of containers (folders, zip files, databases, etc.)
		FileContainerMap mContainers;
	};
}
