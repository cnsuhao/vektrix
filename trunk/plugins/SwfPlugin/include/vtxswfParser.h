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

#ifndef __vtxswfParser_H__
#define __vtxswfParser_H__

#include "vtxswf.h"
#include "vtxswfContourElement.h"
#include "vtxswfParserTypes.h"
#include "vtxFile.h"
#include "vtxFileParser.h"
#include "vtxswfMemoryBlockReader.h"
#include "vtxswfImageParser.h"
#include "vtxswfShapeParser.h"
#include "vtxswfStructureParser.h"
#include "vtxswfFontParser.h"
#include "vtxswfTextParser.h"
#include "vtxswfScriptParser.h"

namespace vtx
{
	namespace swf
	{
		class SwfParser : public FileParser
		{
		public:
			SwfParser();
			virtual ~SwfParser();

			const StringList& getExtensions() const;
			void parse(FileStream* stream, File* file);

			File* getCurrentFile() const { return mCurrentFile; }
			const uint& getFileLength() const { return mFileLength; }
			File::FileHeader& getHeader() { return mHeader; }
			MemoryBlockReader& getMemoryBlock() { return mMemoryBlockReader; }

		protected:
			bool mCompressed;
			uchar* mBuffer;
			UI32 mFileLength;
			File* mCurrentFile;
			FileStream* mCurrentStream;
			MemoryBlockReader mMemoryBlockReader;
			File::FileHeader mHeader;

			// tag parsers
			ImageParser mImageParser;
			ShapeParser mShapeParser;
			StructureParser mStructureParser;
			FontParser mFontParser;
			TextParser mTextParser;
			ScriptParser mScriptParser;

			void resetData();
			bool parseHeader();
			void readTag();
		};
		//-----------------------------------------------------------------------
		/** The FileParserFactory for creating FileParser objects */
		FactoryImpl_P0(SwfParser, FileParser);
		//-----------------------------------------------------------------------
	}
}

#endif
