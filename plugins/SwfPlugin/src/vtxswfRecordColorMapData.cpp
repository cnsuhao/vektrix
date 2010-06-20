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
#include "vtxswfRecordColorMapData.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfRecordColorMapData::SwfRecordColorMapData()
		{}
		//-----------------------------------------------------------------------
		SwfRecordColorMapData::SwfRecordColorMapData(MemoryBlockReader& memoryReader, short colorTableSize, int width, int height)
		{
			for (int i = 0; i < colorTableSize; i++)
			{
				mColorTableRGB.push_back(new SwfRecordRGB(memoryReader));
			}
			int imageDataSize = (width + getScanlinePadLength(width)) * height;
			for (int i = 0; i < imageDataSize; i++)
			{
				mColorMapPixelData.push_back((short)memoryReader.readUI8());
			}
		}
		//-----------------------------------------------------------------------
		int SwfRecordColorMapData::getScanlinePadLength(int width)
		{
			int pad = 0;
			if ((width & 3) != 0)
				pad = 4 - (width & 3);
			return pad;
		}
		//-----------------------------------------------------------------------
		SwfRecordColorMapData::~SwfRecordColorMapData()
		{
			for(RGBRecordList::iterator it = mColorTableRGB.begin(); it != mColorTableRGB.end(); ++it)
			{
				delete (*it);
			}
			mColorTableRGB.clear();
			mColorMapPixelData.clear();
		}
		//-----------------------------------------------------------------------
	}
}
