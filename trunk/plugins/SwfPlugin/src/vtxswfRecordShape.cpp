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
#include "vtxswfRecordShape.h"
#include "vtxswfRecordStyleChangeRecord.h"
#include "vtxswfRecordStraightEdgeRecord.h"
#include "vtxswfRecordCurvedEdgeRecord.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfRecordShape::SwfRecordShape()
			: mNumFillBits(0)
			, mNumLineBits(0)
		{}
		//-----------------------------------------------------------------------
		SwfRecordShape::SwfRecordShape(MemoryBlockReader& memoryReader, bool useNewLineStyle, bool hasAlpha)
			: mNumFillBits(0)
			, mNumLineBits(0)
		{
			read(memoryReader, false, false);
		}
		//-----------------------------------------------------------------------
		void SwfRecordShape::read(MemoryBlockReader& memoryReader, bool useNewLineStyle, bool hasAlpha)
		{
			mNumFillBits   = (unsigned char)memoryReader.readUnsignedBits(4);
			mNumLineBits   = (unsigned char)memoryReader.readUnsignedBits(4);
			unsigned char currentNumFillBits = mNumFillBits;
			unsigned char currentNumLineBits = mNumLineBits;
			do {
				int typeFlag = (int) memoryReader.readUnsignedBits(1);
				if (typeFlag == 0)
				{
					unsigned char flags = (unsigned char)memoryReader.readUnsignedBits(5);
					if (flags == 0)
					{
						break;
					}
					SwfRecordStyleChangeRecord* record = new SwfRecordStyleChangeRecord(
						memoryReader, flags, currentNumFillBits, currentNumLineBits, useNewLineStyle, hasAlpha);
					currentNumFillBits   = record->mNumFillBits;
					currentNumLineBits   = record->mNumLineBits;
					mShapeRecords.push_back(record);
				}
				else
				{
					int straightFlag = (int) memoryReader.readUnsignedBits(1);
					if (straightFlag == 1)
					{
						SwfRecordStraightEdgeRecord* record = new SwfRecordStraightEdgeRecord(memoryReader);
						mShapeRecords.push_back(record);
					}
					else
					{
						SwfRecordCurvedEdgeRecord* record = new SwfRecordCurvedEdgeRecord(memoryReader);
						mShapeRecords.push_back(record);
					}
				}
			} while (true);
			memoryReader.align();
		}
		//-----------------------------------------------------------------------
		SwfRecordShape::~SwfRecordShape()
		{
			for(ShapeRecordList::iterator it = mShapeRecords.begin(); it != mShapeRecords.end(); ++it)
			{
				delete (*it);
			}
			mShapeRecords.clear();
		}
		//-----------------------------------------------------------------------
	}
}
