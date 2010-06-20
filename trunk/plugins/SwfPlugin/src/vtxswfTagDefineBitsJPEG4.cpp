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
#include "vtxswfTag.h"
#include "vtxswfTagDefineBitsJPEG4.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfTagDefineBitsJPEG4::SwfTagDefineBitsJPEG4(uint tag_length, uchar* tag_data)
			: SwfTag(TT_DefineBitsJPEG4, tag_length, tag_data)
			, mCharacterId(0)
			, mDeblockParam(0)
			, mJpegData(NULL)
			, mBitmapAlphaData(NULL)
		{}
		//-----------------------------------------------------------------------
		SwfTagDefineBitsJPEG4::~SwfTagDefineBitsJPEG4()
		{
			if(mJpegData)
			{
				delete[] mJpegData;
				mJpegData = NULL;
			}
			if(mBitmapAlphaData)
			{
				delete[] mBitmapAlphaData;
				mBitmapAlphaData = NULL;
			}
		}
		//-----------------------------------------------------------------------
		void SwfTagDefineBitsJPEG4::ParseData(SwfParser* parser)
		{
			mCharacterId = mBlockReader.readUI16();
			int alphaDataOffset = (int)mBlockReader.readUI32();
			mDeblockParam = mBlockReader.readUI16();
			mJpegData = new uchar[alphaDataOffset];
			mBlockReader.readBytes(alphaDataOffset, mJpegData);
			int alphaDataSize = mTagLength - 8 - alphaDataOffset;
			mBitmapAlphaData = new uchar[alphaDataSize];
			mBlockReader.readBytes(alphaDataSize, mBitmapAlphaData);
		}
		//-----------------------------------------------------------------------
	}
}
