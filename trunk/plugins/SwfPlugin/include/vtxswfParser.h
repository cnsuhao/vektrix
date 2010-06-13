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

//#define DEBUG_FLASH_SHAPES
//#define DEBUG_OUTPUT_PATH "C:/vektrix_debug/"

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
			const uint& getReadPosition() const { return mReadPos; }
			File::FileHeader& getHeader() { return mHeader; }

		protected:
			bool mCompressed;
			uint mReadPos;
			char* mBuffer;

			int mBitPos;
			int mBitBuf;

			UI32 mFileLength;
			File::FileHeader mHeader;

			File* mCurrentFile;
			FileStream* mCurrentStream;

			// tag parsers
			FontParser* mFontParser;
			ImageParser* mImageParser;
			ScriptParser* mScriptParser;
			ShapeParser* mShapeParser;
			StructureParser* mStructureParser;
			TextParser* mTextParser;

			void resetData();
			bool parseHeader();
			void readTag();

			void debug_contour_element(const ContourElement& element, FILE* file);
			void debug_shape_element(const ShapeElement& element, FILE* file);

		public:
			// read basic types
			UI8 readU8();
			UI16 readU16();
			UI32 readU32();
			UI32 readUBits(UI32 n);
			SI16 readS16();
			int readSBits(UI32 n);
			void readByteBlock(char* buf, UI32 n);

			void resetReadBits();

			RECT readRect();
			COLOR readColor(const bool& alpha = false);
			MATRIX readMatrix();
			CXFORM readCxForm(const bool& alpha = false);
			String readString(const bool& zero_terminated = true);
			KERNINGRECORD readKerningRecord(const UI8& wide_codes);

			// read shapes and fill-/line-styles
			void readShape(const TagTypes& type, SHAPE& result);
			void readShapeWithStyle(const TagTypes& type, SHAPE& result);
			void readFillstyleArray(const TagTypes& type, FillstyleList& result);
			void readLinestyleArray(const TagTypes& type, LinestyleList& result);

		protected:
			void fillReadBits();
		};
		//-----------------------------------------------------------------------
		/** The FileParserFactory for creating FileParser objects */
		FactoryImpl_P0(SwfParser, FileParser);
		//-----------------------------------------------------------------------
	}
}

#endif
