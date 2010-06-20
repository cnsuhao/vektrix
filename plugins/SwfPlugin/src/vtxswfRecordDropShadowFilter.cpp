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
#include "vtxswfRecordDropShadowFilter.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfRecordDropShadowFilter::SwfRecordDropShadowFilter()
			: SwfRecordFilter(FT_DROP_SHADOW)
			, mColor(NULL)
			, mX(0.0)
			, mY(0.0)
			, mAngle(0.0)
			, mDistance(0.0)
			, mStrength(0.0)
			, mQuality(0)
			, mInner(false)
			, mKnockout(false)
			, mHideObject(false)
		{}
		//-----------------------------------------------------------------------
		SwfRecordDropShadowFilter::SwfRecordDropShadowFilter(MemoryBlockReader& memoryReader)
			: SwfRecordFilter(FT_DROP_SHADOW)
			, mColor(NULL)
			, mX(0.0)
			, mY(0.0)
			, mAngle(0.0)
			, mDistance(0.0)
			, mStrength(0.0)
			, mQuality(0)
			, mInner(false)
			, mKnockout(false)
			, mHideObject(false)
		{
			mColor        = new SwfRecordRGBA(memoryReader);
			mX            = memoryReader.readFP32();
			mY            = memoryReader.readFP32();
			mAngle        = memoryReader.readFP32();
			mDistance     = memoryReader.readFP32();
			mStrength     = memoryReader.readFP16();
			mInner        = memoryReader.readBooleanBit();
			mKnockout     = memoryReader.readBooleanBit();
			mHideObject   = !memoryReader.readBooleanBit();
			mQuality      = (int) memoryReader.readUnsignedBits(5);
		}
		//-----------------------------------------------------------------------
		SwfRecordDropShadowFilter::~SwfRecordDropShadowFilter()
		{
			if(mColor)
			{
				delete mColor;
				mColor = NULL;
			}
		}
		//-----------------------------------------------------------------------
	}
}
