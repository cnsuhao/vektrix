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
#include "vtxswfMemoryBlockReader.h"
#ifdef USE_ZLIB
#	include "zlib/zlib.h"
#endif

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		MemoryBlockReader::MemoryBlockReader() 
			: mOffset(0)
			, mBuffer(NULL)
			, mBufLen(0)
			, mBitBuffer(0)
			, mBitCursor(8)
			, mCompressed(false)
			, mAnsi(false)
			, mShiftJIS(false)
		{}
		//-----------------------------------------------------------------------
		MemoryBlockReader::MemoryBlockReader(unsigned char* buffer, size_t buf_len) 
			: mOffset(0)
			, mBuffer(NULL)
			, mBufLen(0)
			, mBitBuffer(0)
			, mBitCursor(8)
			, mCompressed(false)
			, mAnsi(false)
			, mShiftJIS(false)
		{
			init(buffer, buf_len);
		}
		//-----------------------------------------------------------------------
		MemoryBlockReader::~MemoryBlockReader()
		{
			if(mCompressed)
			{
				delete[] mBuffer;
				mBuffer = NULL;
			}
		}
		//-----------------------------------------------------------------------
		void MemoryBlockReader::init(unsigned char* buffer, size_t buf_len)
		{
			mBuffer = buffer;
			mBufLen = buf_len;
			mOffset = 0;
			mBitBuffer = 0;
			mBitCursor = 8;
		}
		//-----------------------------------------------------------------------
		void MemoryBlockReader::enableCompression()
		{
#ifdef USE_ZLIB
			const uint chunk_size = 1024*512;
			uint remainingBytes = mBufLen-mOffset;

			unsigned char* readBuf = new unsigned char[remainingBytes];
			readBytes(remainingBytes, readBuf);

			unsigned char* newBuffer = new unsigned char[chunk_size];
			uint inflatedBytes = zlibInflate(readBuf, remainingBytes, newBuffer, chunk_size);

			delete[] readBuf;
			mBuffer = newBuffer;
			mBufLen = inflatedBytes;
			mCompressed = true;
			mOffset = 0;
#else
			VTX_DEBUG_FAIL("Unable to decompress!");
#endif
		}
		//-----------------------------------------------------------------------
		uint MemoryBlockReader::zlibInflate(unsigned char *compr, unsigned long comprLen, unsigned char *uncompr, unsigned long uncomprLen)
		{
#ifdef USE_ZLIB
			int err;
			z_stream d_stream;

			d_stream.zalloc = (alloc_func)0;
			d_stream.zfree = (free_func)0;
			d_stream.opaque = (voidpf)0;

			d_stream.next_in  = compr;
			d_stream.avail_in = (uInt)comprLen;

			err = inflateInit(&d_stream);
			VTX_DEBUG_ASSERT(err==Z_OK, "inflateInit failed");

			for (;;)
			{
				d_stream.next_out = uncompr;            /* discard the output */
				d_stream.avail_out = (uInt)uncomprLen;
				err = inflate(&d_stream, Z_NO_FLUSH);
				if (err == Z_STREAM_END) break;
				VTX_DEBUG_ASSERT(err==Z_OK, "large inflate failed");
			}

			err = inflateEnd(&d_stream);
			VTX_DEBUG_ASSERT(err==Z_OK, "inflateEnd failed");
			return d_stream.total_out;
#else
			VTX_DEBUG_FAIL("Unable to decompress!");
			return 0;
#endif
		}
		//-----------------------------------------------------------------------
		bool MemoryBlockReader::readBooleanBit()
		{
			return (readUnsignedBits(1) == 1);
		}
		//-----------------------------------------------------------------------
		void MemoryBlockReader::readBytes( size_t len, unsigned char* pBuf )
		{
			memcpy(pBuf, mBuffer + mOffset, len);
			mOffset += len;
			align();
		}
		//-----------------------------------------------------------------------
		double MemoryBlockReader::readDouble()
		{
			unsigned char buf[8];
			readBytes(8, buf);
			return( (double)(
				(int64)buf[3] << 56 | (int64)buf[2] << 48 | (int64)buf[1] << 40 | (int64)buf[0] << 32 |
				(int64)buf[7] << 24 | (int64)buf[6] << 16 | (int64)buf[5] << 8 | (int64)buf[4])
			);
		}
		//-----------------------------------------------------------------------
		float MemoryBlockReader::readFloat16()
		{
			int bits16     = readUI16();
			int sign       = (bits16 & 0x8000) >> 15;
			int exponent16 = (bits16 & 0x7c00) >> 10;
			int mantissa16 = bits16 & 0x3ff;
			int exponent32 = 0;
			if (exponent16 != 0) {
				if (exponent16 == 0x1f) {
					exponent32 = 0xff;
				} else {
					exponent32 = exponent16 - 15 + 127;
				}
			}
			int mantissa32 = mantissa16 << 13;
			int bits32     = sign << 31;
			bits32 |= exponent32 << 23;
			bits32 |= mantissa32;
			return (float)(bits32);
		}
		//-----------------------------------------------------------------------
		long MemoryBlockReader::readSignedBits( size_t nBits )
		{
			long result = readUnsignedBits(nBits);
			if ((result & (1L << (nBits - 1))) != 0) {
				result |= (-1L << nBits);
			}
			return result;
		}
		//-----------------------------------------------------------------------
		vtx::String MemoryBlockReader::readString()
		{
			// read the string byte for byte until we get a null-byte
			vtx::String str;
			fillBitBuffer();
			while (mBitBuffer != 0) {
				str.push_back(mBitBuffer);
				fillBitBuffer();
			}
			//byte[] buffer = baos.toByteArray();
			//String encoding;
			//if (mShiftJIS) {
			//	encoding = "SJIS";
			//} else if (mAnsi) {
			//	encoding = "cp1252";
			//} else {
			//	encoding = "UTF-8";
			//}
			return str;
		}
		//-----------------------------------------------------------------------
		int MemoryBlockReader::readUI16()
		{
			fillBitBuffer();
			int result = mBitBuffer;
			fillBitBuffer();
			result |= (mBitBuffer << 8);
			align();
			return result;
		}
		//-----------------------------------------------------------------------
		long MemoryBlockReader::readUI32()
		{
			fillBitBuffer();
			long result = mBitBuffer;
			fillBitBuffer();
			result |= (mBitBuffer << 8);
			fillBitBuffer();
			result |= (mBitBuffer << 16);
			fillBitBuffer();
			result |= (mBitBuffer << 24);
			align();
			return result;
		}
		//-----------------------------------------------------------------------
		int64 MemoryBlockReader::readSI64()
		{
			fillBitBuffer();
			int64 result = mBitBuffer;
			fillBitBuffer();
			result |= ((int64)mBitBuffer << 8);
			fillBitBuffer();
			result |= ((int64)mBitBuffer << 16);
			fillBitBuffer();
			result |= ((int64)mBitBuffer << 24);
			fillBitBuffer();
			result |= ((int64)mBitBuffer << 32);
			fillBitBuffer();
			result |= ((int64)mBitBuffer << 40);
			fillBitBuffer();
			result |= ((int64)mBitBuffer << 48);
			fillBitBuffer();
			result |= ((int64)mBitBuffer << 56);
			align();
			return result;
		}
		//-----------------------------------------------------------------------
		unsigned char MemoryBlockReader::readUI8()
		{
			fillBitBuffer();
			unsigned char result = (unsigned char)mBitBuffer;
			align();
			return result;
		}
		//-----------------------------------------------------------------------
		long MemoryBlockReader::readUnsignedBits( size_t nBits )
		{
			if (nBits == 0) {
				return 0;
			}
			size_t bitsLeft = nBits;
			long result  = 0;
			while (bitsLeft > 0) {
				if (mBitCursor == 8) {
					// buffer is empty
					fillBitBuffer();
				}

				// check if bit is set
				if ((mBitBuffer & (1 << (7 - mBitCursor))) != 0) {
					// set corresponding result bit
					result |= (1L << (bitsLeft - 1));
				}
				mBitCursor++;
				bitsLeft--;
			}
			return result;
		}
		//-----------------------------------------------------------------------
		int MemoryBlockReader::readSI24()
		{
			fillBitBuffer();
			int result = mBitBuffer;
			fillBitBuffer();
			result |= mBitBuffer << 8;
			fillBitBuffer();
			result |= mBitBuffer << 16;
			if ((mBitBuffer & 0x80) != 0) {
				result |= 0xFF000000;
			}
			align();
			return result;
		}
		//-----------------------------------------------------------------------
		int MemoryBlockReader::readAbcInt()
		{
			int result = readUI8();
			if ((result & 0x00000080) == 0) {
				return result;
			}
			result = (result & 0x0000007f) | (readUI8() << 7);
			if ((result & 0x00004000) == 0) {
				return result;
			}
			result = (result & 0x00003fff) | (readUI8() << 14);
			if ((result & 0x00200000) == 0) {
				return result;
			}
			result = (result & 0x001fffff) | (readUI8() << 21);
			if ((result & 0x10000000) == 0) {
				return result;
			}
			result = (result & 0x0fffffff) | (readUI8() << 28);
			return result;
		}
		//-----------------------------------------------------------------------
		void MemoryBlockReader::fillBitBuffer()
		{
			mBitBuffer = mBuffer[mOffset++];
			VTX_DEBUG_ASSERT(mOffset <= mBufLen, "Buffer overflow detected!");
			mBitCursor = 0;
		}
		//-----------------------------------------------------------------------
	}
}
