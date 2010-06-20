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
#include "vtxswfRecordSWFHeader.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfRecordSwfHeader::SwfRecordSwfHeader()
			: mCompressed(false)
			, mVersion(0)
			, mFileLength(0)
			, mFrameSize(NULL)
			, mFrameRate(0)
			, mFrameCount(0)
		{}
		//-----------------------------------------------------------------------
		SwfRecordSwfHeader::SwfRecordSwfHeader(MemoryBlockReader& memoryReader)
			: mCompressed(false)
			, mVersion(0)
			, mFileLength(0)
			, mFrameSize(NULL)
			, mFrameRate(0)
			, mFrameCount(0)
		{
			unsigned char compressionByte = memoryReader.readUI8();

			// header starts with CWS (0x43 0x57 0x53) for compressed
			// or FWS (0x46 0x57 0x53) for uncompressed files
			if ( ((compressionByte != 0x43) && (compressionByte != 0x46)) ||
				 (memoryReader.readUI8() != 0x57) || (memoryReader.readUI8() != 0x53))
			{
				VTX_DEBUG_FAIL("Invalid swf file signature");
			}
			if (compressionByte == 0x43) {
				mCompressed = true;
			}
			mVersion      = memoryReader.readUI8();
			mFileLength   = memoryReader.readUI32();
			if (mCompressed)
			{
				//memoryReader.enableCompression();
			}
			mFrameSize = new SwfRecordRect(memoryReader);
			memoryReader.readUI8(); // ignore one byte
			mFrameRate    = memoryReader.readUI8();
			mFrameCount   = memoryReader.readUI16();
		}
		//-----------------------------------------------------------------------
		SwfRecordSwfHeader::~SwfRecordSwfHeader()
		{
			if(mFrameSize)
			{
				delete mFrameSize;
				mFrameSize = NULL;
			}
		}
		//-----------------------------------------------------------------------
	}
}
