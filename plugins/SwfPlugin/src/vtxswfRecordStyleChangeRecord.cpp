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
#include "vtxswfRecordStyleChangeRecord.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfRecordStyleChangeRecord::SwfRecordStyleChangeRecord()
			: mMoveToX(0)
			, mMoveToY(0)
			, mFillStyle0(0)
			, mFillStyle1(0)
			, mLineStyle(0)
			, mFillStyles(NULL)
			, mLineStyles(NULL)
			, mNumFillBits(0)
			, mNumLineBits(0)
			, mHasNewStyles(false)
			, mHasLineStyle(false)
			, mHasFillStyle1(false)
			, mHasFillStyle0(false)
			, mHasMoveTo(false)
		{}
		//-----------------------------------------------------------------------
		SwfRecordStyleChangeRecord::SwfRecordStyleChangeRecord(MemoryBlockReader& memoryReader, unsigned char flags,
			unsigned char numFillBits, unsigned char numLineBits, bool useNewLineStyle, bool hasAlpha)
			: mMoveToX(0)
			, mMoveToY(0)
			, mFillStyle0(0)
			, mFillStyle1(0)
			, mLineStyle(0)
			, mFillStyles(NULL)
			, mLineStyles(NULL)
			, mNumFillBits(0)
			, mNumLineBits(0)
			, mHasNewStyles(false)
			, mHasLineStyle(false)
			, mHasFillStyle1(false)
			, mHasFillStyle0(false)
			, mHasMoveTo(false)
		{
			mHasNewStyles    = ((flags & 16) != 0);
			mHasLineStyle    = ((flags & 8) != 0);
			mHasFillStyle1   = ((flags & 4) != 0);
			mHasFillStyle0   = ((flags & 2) != 0);
			mHasMoveTo       = ((flags & 1) != 0);
			if (mHasMoveTo) {
				int moveBits = (int)memoryReader.readUnsignedBits(5);
				mMoveToX   = (int)memoryReader.readSignedBits(moveBits);
				mMoveToY   = (int)memoryReader.readSignedBits(moveBits);
			}
			if (mHasFillStyle0)
				mFillStyle0 = (int)memoryReader.readUnsignedBits(numFillBits);
			if (mHasFillStyle1)
				mFillStyle1 = (int)memoryReader.readUnsignedBits(numFillBits);
			if (mHasLineStyle)
				mLineStyle = (int)memoryReader.readUnsignedBits(numLineBits);
			if (mHasNewStyles)
			{
				mFillStyles = new SwfRecordFillStyleArray(memoryReader, hasAlpha);
				if (useNewLineStyle)
					mLineStyles = new SwfRecordLineStyleArray(memoryReader);
				else
					mLineStyles = new SwfRecordLineStyleArray(memoryReader, hasAlpha);
				mNumFillBits   = (unsigned char)memoryReader.readUnsignedBits(4);
				mNumLineBits   = (unsigned char)memoryReader.readUnsignedBits(4);
			}
			else
			{
				mNumFillBits   = numFillBits;
				mNumLineBits   = numLineBits;
			}
		}
		//-----------------------------------------------------------------------
		SwfRecordStyleChangeRecord::~SwfRecordStyleChangeRecord()
		{
			if(mFillStyles)
			{
				delete mFillStyles;
				mFillStyles = NULL;
			}
			if(mLineStyles)
			{
				delete mLineStyles;
				mLineStyles = NULL;
			}
		}
		//-----------------------------------------------------------------------
	}
}
