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

#include "vtxMemoryFileStream.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	MemoryFileStream::MemoryFileStream(const String& filename, void* buffer, const uint& size, bool auto_free) 
		: FileStream(filename), 
		mAutoFree(auto_free)
	{
		mSize = size;
		mFirst = mCurrent = static_cast<uchar*>(buffer);
		mLast = mFirst + mSize;
		assert(mLast >= mFirst);
	}
	//-----------------------------------------------------------------------
	MemoryFileStream::~MemoryFileStream()
	{
		close();
	}
	//-----------------------------------------------------------------------
	void MemoryFileStream::seek(uint pos)
	{
		assert(mFirst + pos <= mLast);
		mCurrent = mFirst + pos;
	}
	//-----------------------------------------------------------------------
	uint MemoryFileStream::tell()
	{
		return mCurrent - mFirst;
	}
	//-----------------------------------------------------------------------
	uint MemoryFileStream::read(void* buf, uint count)
	{
		uint cnt = count;

		if(mCurrent + cnt > mLast)
		{
			cnt = mLast - mCurrent;
		}

		if(cnt == 0)
		{
			return 0;
		}

		assert(cnt <= count);

		memcpy(buf, mCurrent, cnt);
		mCurrent += cnt;
		return cnt;
	}
	//-----------------------------------------------------------------------
	String& MemoryFileStream::getLine()
	{
		static String line;
		return line;
	}
	//-----------------------------------------------------------------------
	bool MemoryFileStream::eof() const
	{
		return mCurrent >= mLast;
	}
	//-----------------------------------------------------------------------
	void MemoryFileStream::close()
	{
		if(mAutoFree && mFirst)
		{
			free(mFirst);
			mFirst = NULL;
		}
	}
	//-----------------------------------------------------------------------
}
