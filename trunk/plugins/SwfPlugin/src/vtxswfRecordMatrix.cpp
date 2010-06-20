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
#include "vtxswfRecordMatrix.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfRecordMatrix::SwfRecordMatrix()
			: mScaleX(0.0)
			, mScaleY(0.0)
			, mRotateSkew0(0.0)
			, mRotateSkew1(0.0)
			, mTranslateX(0)
			, mTranslateY(0)
			, mHasScale(false)
			, mHasRotateSkew(false)
		{}
		//-----------------------------------------------------------------------
		SwfRecordMatrix::SwfRecordMatrix(MemoryBlockReader& memoryReader)
			: mScaleX(0.0)
			, mScaleY(0.0)
			, mRotateSkew0(0.0)
			, mRotateSkew1(0.0)
			, mTranslateX(0)
			, mTranslateY(0)
			, mHasScale(false)
			, mHasRotateSkew(false)
		{
			mHasScale = memoryReader.readBooleanBit();
			if (mHasScale)
			{
				int nScaleBits = (int)memoryReader.readUnsignedBits(5);
				mScaleX   = memoryReader.readFPBits(nScaleBits);
				mScaleY   = memoryReader.readFPBits(nScaleBits);
			}
			mHasRotateSkew = memoryReader.readBooleanBit();
			if (mHasRotateSkew)
			{
				int nRotateBits = (int)memoryReader.readUnsignedBits(5);
				mRotateSkew0   = memoryReader.readFPBits(nRotateBits);
				mRotateSkew1   = memoryReader.readFPBits(nRotateBits);
			}
			int nTranslateBits = (int)memoryReader.readUnsignedBits(5);
			mTranslateX   = (int)memoryReader.readSignedBits(nTranslateBits);
			mTranslateY   = (int)memoryReader.readSignedBits(nTranslateBits);
			memoryReader.align();
		}
		//-----------------------------------------------------------------------
		SwfRecordMatrix::~SwfRecordMatrix()
		{}
		//-----------------------------------------------------------------------
	}
}
