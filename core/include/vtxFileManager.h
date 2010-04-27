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

#ifndef __vtxFileManager_H__
#define __vtxFileManager_H__

#include "vtxPrerequesites.h"
#include "vtxDefaultFileContainer.h"
#include "vtxFactoryManager.h"
#include "vtxSingleton.h"

namespace vtx
{
	/** The manager that keeps track of File definitions, FileParser instances and FileContainer resources */
	class vtxExport FileManager : public Singleton<FileManager>, public FactoryManager<FileContainerFactory>
	{
		friend class Root;

	public:
		typedef std::map<String, File*> FileMap;
		typedef std::map<String, FileContainer*> FileContainerMap;
		typedef std::map<String, FileParser*> FileParserMap;

		/** Request to load a File by filename */
		File* getFile(const String& filename);
		/** Open a new FileStream */
		FileStream* getFileStream(const String& filename);

		/** Register a FileParser instance to the manager */
		void addFileParser(FileParser* parser);
		/** Get a FileParser instance by its associated file extension */
		FileParser* getFileParser(const String extension);
		/** Remove a FileParser instance from the manager */
		void removeFileParser(FileParser* parser);

		/** Add a FileContainer resource location */
		FileContainer* addFileContainer(const String& name, const String& type = DefaultFileContainer::FACTORY_NAME);

		/** Unload all currently loaded File definitions */
		void unloadAllFiles();

	protected:
		// map of the already loaded files
		FileMap mLoadedFiles;
		// map of registered file parsers
		FileParserMap mParsers;
		// map of containers (folders, zip files, databases, etc)
		FileContainerMap mContainers;

		FileManager();
		virtual ~FileManager();
	};
}

#endif
