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
#include "vtxswfRecordMorphLineStyle2.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfRecordMorphLineStyle2::SwfRecordMorphLineStyle2()
			: SwfRecordMorphLineStyleTag()
			, SwfRecordEnhancedStrokeStyle()
			, mStartWidth(0)
			, mEndWidth(0)
			, mStartColor(NULL)
			, mEndColor(NULL)
			, mFillStyle(NULL)
		{}
		//-----------------------------------------------------------------------
		SwfRecordMorphLineStyle2::SwfRecordMorphLineStyle2(MemoryBlockReader& memoryReader)
			: SwfRecordMorphLineStyleTag()
			, SwfRecordEnhancedStrokeStyle()
			, mStartWidth(0)
			, mEndWidth(0)
			, mStartColor(NULL)
			, mEndColor(NULL)
			, mFillStyle(NULL)
		{
			mStartWidth      = memoryReader.readUI16();
			mEndWidth        = memoryReader.readUI16();
			mStartCapStyle	 = (CapStyle)memoryReader.readUnsignedBits(2);
			mJointStyle		 = (JointStyle)memoryReader.readUnsignedBits(2);
			bool hasFill	 = memoryReader.readBooleanBit();
			bool noHScale	 = memoryReader.readBooleanBit();
			bool noVScale	 = memoryReader.readBooleanBit();
			mScaleStroke = (ScaleStrokeMethod)((short)(noHScale ? 0 : 2) | (noVScale ? 0 : 1));
			mPixelHinting = (memoryReader.readBooleanBit());
			memoryReader.readUnsignedBits(5);
			mClose = !memoryReader.readBooleanBit();
			mEndCapStyle = (CapStyle)memoryReader.readUnsignedBits(2);
			if (mJointStyle == JS_MITER)
				mMiterLimit = memoryReader.readFP16();
			if (hasFill)
			{
				mFillStyle = new SwfRecordMorphFillStyle(memoryReader);
			}
			else
			{
				mStartColor   = new SwfRecordRGBA(memoryReader);
				mEndColor     = new SwfRecordRGBA(memoryReader);
			}
		}
		//-----------------------------------------------------------------------
		SwfRecordMorphLineStyle2::~SwfRecordMorphLineStyle2()
		{
			if(mStartColor)
			{
				delete mStartColor;
				mStartColor = NULL;
			}
			if(mEndColor)
			{
				delete mEndColor;
				mEndColor = NULL;
			}
			if(mFillStyle)
			{
				delete mFillStyle;
				mFillStyle = NULL;
			}
		}
		//-----------------------------------------------------------------------
	}
}
