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
#include "vtxswfRecordButtonRecord.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfRecordButtonRecord::SwfRecordButtonRecord()
			: mHitState(false)
			, mDownState(false)
			, mOverState(false)
			, mUpState(false)
			, mCharacterId(0)
			, mPlaceDepth(0)
			, mPlaceMatrix(NULL)
			, mColorTransform(NULL)
			, mHasBlendMode(false)
			, mHasFilters(false)
			, mBlendMode(BM_NORMAL)
		{}
		//-----------------------------------------------------------------------
		SwfRecordButtonRecord::SwfRecordButtonRecord(MemoryBlockReader& memoryReader, bool hasColorTransform)
			: mHitState(false)
			, mDownState(false)
			, mOverState(false)
			, mUpState(false)
			, mCharacterId(0)
			, mPlaceDepth(0)
			, mPlaceMatrix(NULL)
			, mColorTransform(NULL)
			, mHasBlendMode(false)
			, mHasFilters(false)
			, mBlendMode(BM_NORMAL)
		{
			memoryReader.readUnsignedBits(2);
			mHasBlendMode   = memoryReader.readBooleanBit();
			mHasFilters     = memoryReader.readBooleanBit();
			mHitState       = memoryReader.readBooleanBit();
			mDownState      = memoryReader.readBooleanBit();
			mOverState      = memoryReader.readBooleanBit();
			mUpState        = memoryReader.readBooleanBit();
			mCharacterId    = memoryReader.readUI16();
			mPlaceDepth     = memoryReader.readUI16();
			mPlaceMatrix    = new SwfRecordMatrix(memoryReader);
			if (hasColorTransform)
			{
				mColorTransform = new SwfRecordCXformWithAlpha(memoryReader);
			}
			if (mHasFilters)
			{
				SwfRecordFilter filterReader;
				mFilters = filterReader.readFilters(memoryReader);
			}
			if (mHasBlendMode)
			{
				short code = memoryReader.readUI8();
				mBlendMode = (code == 0) ? BM_NORMAL : (BlendMode)code;
			}
		}
		//-----------------------------------------------------------------------
		SwfRecordButtonRecord::~SwfRecordButtonRecord()
		{
			if(mPlaceMatrix)
			{
				delete mPlaceMatrix;
				mPlaceMatrix = NULL;
			}
			if(mColorTransform)
			{
				delete mColorTransform;
				mColorTransform = NULL;
			}
			for(FilterList::iterator it = mFilters.begin(); it != mFilters.end(); ++it)
			{
				delete (*it);
			}
			mFilters.clear();
		}
		//-----------------------------------------------------------------------
	}
}
