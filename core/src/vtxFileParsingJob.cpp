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

#include "vtxFileParsingJob.h"
#include "vtxFile.h"
#include "vtxFileManager.h"
#include "vtxFileStream.h"

#include "vtxThreadingDefines.h"
#include "vtxThreadingHeaders.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	FileParsingJob::FileParsingJob(FileParser* parser, File* file) 
		: mParser(parser), 
		mFile(file)
	{

	}
	//-----------------------------------------------------------------------
	FileParsingJob::~FileParsingJob()
	{

	}
	//-----------------------------------------------------------------------
	void FileParsingJob::start()
	{
		FileManager* file_mgr = FileManager::getSingletonPtr();

		const String& filename = mFile->getFilename();
		FileStream* stream = file_mgr->getFileStream(filename);

		if(!stream)
		{
			// no container found
			VTX_WARN("Unable to find container to load file '%s'.", filename.c_str());
			return;
		}

		mParser->parse(stream, mFile);

		if(mParser->errorsOccured())
		{
			String error = mParser->getError();
			while(error.length())
			{
				VTX_WARN(error.c_str());
				error = mParser->getError();
			}

			VTX_EXCEPT("An error occured while parsing the file \"%s\", see the log for details.", filename.c_str());
		}

		// TODO: implement FileStreamPtr, so we don't need to destroy instances by hand ?
		stream->close();
		delete stream;

		// TODO: use factory ???
		delete mParser;
	}
	//-----------------------------------------------------------------------
}
