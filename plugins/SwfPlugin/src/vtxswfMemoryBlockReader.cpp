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
			uint chunk_size = 0x40000; // 256 kBytes

			z_stream zlib_stream;
			zlib_stream.zalloc = Z_NULL;
			zlib_stream.zfree = Z_NULL;
			zlib_stream.opaque = Z_NULL;

			zlib_stream.avail_in = 0;
			zlib_stream.next_in = Z_NULL;

			int ret = inflateInit(&zlib_stream);
			if(ret != Z_OK)
			{
				VTX_DEBUG_FAIL("ZLIB error: unknown startup error");
				return;
			}

			uint bufStart = 0;
			unsigned char* readBuf = new unsigned char[chunk_size];
			unsigned char* mNewBuffer = new unsigned char[mBufLen - mOffset];

			do 
			{
				// TODO: only read available data :S
				readBytes(chunk_size, readBuf);
				zlib_stream.avail_in = chunk_size;

				if(zlib_stream.avail_in == 0)
				{
					break;
				}
				zlib_stream.next_in = readBuf;
				do
				{
					zlib_stream.avail_out = chunk_size;
					zlib_stream.next_out = &mNewBuffer[bufStart];

					ret = inflate(&zlib_stream, Z_NO_FLUSH);
					VTX_DEBUG_ASSERT(ret != Z_STREAM_ERROR, "");
					switch(ret)
					{
					case Z_NEED_DICT:
					case Z_DATA_ERROR:
					case Z_MEM_ERROR:
						(void)inflateEnd(&zlib_stream);
						VTX_DEBUG_FAIL("ZLIB error: extraction failed");
						return;
					}

					uint written = chunk_size - zlib_stream.avail_out;
					bufStart += written;
				} while(zlib_stream.avail_out == 0);
			} while(ret != Z_STREAM_END);

			(void)inflateEnd(&zlib_stream);
			delete[] readBuf;

			mBuffer = readBuf;
			mCompressed = true;
#else
			VTX_DEBUG_FAIL("Unable to decompress!");
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
			memcpy(pBuf, mBuffer, len); mOffset += len;
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
