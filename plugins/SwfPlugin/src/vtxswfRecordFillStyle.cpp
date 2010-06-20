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
#include "vtxswfRecordFillStyle.h"
#include "vtxswfRecordRGBA.h"
#include "vtxswfRecordRGB.h"
#include "vtxswfRecordFocalGradient.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfRecordFillStyle::SwfRecordFillStyle()
			: mType(FST_Solid)
			, mColor(NULL)
			, mGradientMatrix(NULL)
			, mGradient(NULL)
			, mBitmapId(0)
			, mBitmapMatrix(NULL)
		{}
		//-----------------------------------------------------------------------
		SwfRecordFillStyle::SwfRecordFillStyle(MemoryBlockReader& memoryReader, bool hasAlpha)
			: mType(FST_Solid)
			, mColor(NULL)
			, mGradientMatrix(NULL)
			, mGradient(NULL)
			, mBitmapId(0)
			, mBitmapMatrix(NULL)
		{
			mType = (FillStyleType)memoryReader.readUI8();
			switch (mType)
			{
			case FST_Solid:
				if(hasAlpha)
					mColor = new SwfRecordRGBA(memoryReader);
				else
					mColor = new SwfRecordRGB(memoryReader);
				break;
			case FST_LinearGradient:
			case FST_RadialGradient:
			case FST_FocalRadialGradient:
				mGradientMatrix = new SwfRecordMatrix(memoryReader);
				if(mType == FST_FocalRadialGradient)
					mGradient = new SwfRecordFocalGradient(memoryReader);
				else
					mGradient = new SwfRecordGradient(memoryReader, hasAlpha);
				break;
			case FST_RepeatingBitmap:
			case FST_ClippedBitmap:
			case FST_NonSmoothedRepeatingBitmap:
			case FST_NonSmoothedClippedBitmap:
				mBitmapId = memoryReader.readUI16();
				mBitmapMatrix = new SwfRecordMatrix(memoryReader);
				break;
			default:
				VTX_DEBUG_FAIL("Unknown fill type");
			}
		}
		//-----------------------------------------------------------------------
		SwfRecordFillStyle::~SwfRecordFillStyle()
		{
			if(mColor)
			{
				delete mColor;
				mColor = NULL;
			}
			if(mGradientMatrix)
			{
				delete mGradientMatrix;
				mGradientMatrix = NULL;
			}
			if(mGradient)
			{
				delete mGradient;
				mGradient = NULL;
			}
			if(mBitmapMatrix)
			{
				delete mBitmapMatrix;
				mBitmapMatrix = NULL;
			}
		}
		//-----------------------------------------------------------------------
	}
}
