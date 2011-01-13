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

#ifndef __vtxswfDataReader_H__
#define __vtxswfDataReader_H__

#include "vtxswf.h"
#include "vtxswfParserTypes.h"

namespace vtx { namespace swf {
	class DataReader
	{
	public:
		DataReader();

		void reset();

		void init(char* buffer);

		void setReadPosition(const uint& offset);
		const uint& getReadPosition() const;

		// read basic types
		void skip(const uint& len);
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

#ifdef _DEBUG
		void saveMemoryDump(const String& dumpname, const uint& length)
		{
			std::ofstream dump;
			dump.open(dumpname.c_str(), std::ios::binary | std::ios::out);
			dump.write(mBuffer + mReadPos, length);
			dump.close();
		}
#endif

	private:
		uint mReadPos;
		char* mBuffer;

		int mBitPos;
		int mBitBuf;

		void fillReadBits();
	};
}}

#endif
