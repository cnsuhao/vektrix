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

#ifndef __vtxswfMemoryBlockReader_H__
#define __vtxswfMemoryBlockReader_H__

#include "vtxswf.h"
#include "vtxswfParserTypes.h"

namespace vtx
{
	namespace swf
	{
		class MemoryBlockReader
		{
		public:
			MemoryBlockReader();
			MemoryBlockReader(unsigned char* buffer, size_t buf_len);
			virtual ~MemoryBlockReader();

			void init(unsigned char* buffer, size_t buf_len);

			void setANSI(bool ansi) { mAnsi = ansi; }
			bool isANSI() { return mAnsi; }
			void setShiftJIS(bool shift_jis) { mShiftJIS = shift_jis; }
			bool isShiftJIS() { return mShiftJIS; }

			void align() { mBitCursor = 8; }
			int available() { if(mCompressed) return 0; return mBufLen - mOffset; }
			void enableCompression();
			void move(size_t delta) { mOffset += delta; }
			size_t getOffset() { return mOffset; }
			uchar* getBufferCurrentPtr() { return &mBuffer[mOffset]; }

			float readFloat16();
			float readFloat() { return ((float)readSI32()); }
			double readDouble();

			float readFP16() { return (readSI16() / 256.0f); }
			float readFP32() { return (readSI32() / 65536.0f); }
			float readFPBits(size_t nBits) { return (readSignedBits(nBits) / 65536.0f); }

			char readSI8() { return (char)readUI8(); }
			short readSI16() { return (short)readUI16(); }
			int readSI24();
			int readSI32() { return (int)readUI32(); }
			int64 readSI64();

			unsigned char readUI8();
			unsigned short readUI16();
			unsigned int readUI32();

			bool readBooleanBit();
			long readSignedBits(size_t nBits);
			long readUnsignedBits(size_t nBits);
			void readBytes(size_t len, unsigned char* pBuf);

			String readString(bool zero_terminated);
			int readAbcInt();
			void fillBitBuffer();

		protected:
			uint zlibInflate(unsigned char *compr, unsigned long comprLen, unsigned char *uncompr, unsigned long uncomprLen);

		protected:
			bool mCompressed;
			bool mAnsi;
			bool mShiftJIS;

			unsigned char* mBuffer;
			size_t mBufLen;
			size_t mOffset;

			unsigned char mBitBuffer;
			size_t mBitCursor;
		};
	}
}

#endif // __vtxswfMemoryBlockReader_H__
