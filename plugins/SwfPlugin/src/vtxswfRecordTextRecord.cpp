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
#include "vtxswfRecordTextRecord.h"
#include "vtxswfRecordRGB.h"
#include "vtxswfRecordRGBA.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfRecordTextRecord::SwfRecordTextRecord()
			: mHasXOffset(0)
			, mXOffset(0)
			, mHasYOffset(0)
			, mYOffset(0)
			, mHasFont(0)
			, mFontId(0)
			, mTextHeight(0)
			, mHasColor(false)
			, mTextColor(NULL)
		{}
		//-----------------------------------------------------------------------
		SwfRecordTextRecord::SwfRecordTextRecord(MemoryBlockReader& memoryReader, short glyphBits, short advanceBits, bool hasAlpha)
			: mHasXOffset(0)
			, mXOffset(0)
			, mHasYOffset(0)
			, mYOffset(0)
			, mHasFont(0)
			, mFontId(0)
			, mTextHeight(0)
			, mHasColor(false)
			, mTextColor(NULL)
		{
			memoryReader.readUnsignedBits(4); // ignore first 4 bits
			mHasFont        = memoryReader.readBooleanBit();
			mHasColor       = memoryReader.readBooleanBit();
			mHasYOffset     = memoryReader.readBooleanBit();
			mHasXOffset     = memoryReader.readBooleanBit();
			if (mHasFont)
			{
				mFontId = memoryReader.readUI16();
			}
			if (mHasColor)
			{
				if(hasAlpha)
					mTextColor = new SwfRecordRGBA(memoryReader);
				else
					mTextColor = new SwfRecordRGB(memoryReader);
			}
			if (mHasXOffset)
			{
				mXOffset = memoryReader.readSI16();
			}
			if (mHasYOffset) {
				mYOffset = memoryReader.readSI16();
			}
			if (mHasFont) {
				mTextHeight = memoryReader.readUI16();
			}
			int glyphCount = memoryReader.readUI8();
			for (int i = 0; i < glyphCount; i++)
			{
				mGlyphEntries.push_back(new SwfRecordGlyphEntry(memoryReader, glyphBits, advanceBits));
			}
			memoryReader.align();
		}
		//-----------------------------------------------------------------------
		SwfRecordTextRecord::~SwfRecordTextRecord()
		{
			if(mTextColor)
			{
				delete mTextColor;
				mTextColor = NULL;
			}
			for( GlyphEntryList::iterator it = mGlyphEntries.begin(); it != mGlyphEntries.end(); ++it )
			{
				delete (*it);
			}
			mGlyphEntries.clear();
		}
		//-----------------------------------------------------------------------
	}
}
