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
#include "vtxswfRecordClipEventFlags.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfRecordClipEventFlags::SwfRecordClipEventFlags()
			: mKeyUp(false)
			, mKeyDown(false)
			, mMouseUp(false)
			, mMouseDown(false)
			, mmouseMove(false)
			, mUnload(false)
			, mEnterFrame(false)
			, mLoad(false)
			, mDragOver(false)
			, mRollOut(false)
			, mRollOver(false)
			, mReleaseOutside(false)
			, mRelease(false)
			, mPress(false)
			, mInitialize(false)
			, mData(false)
			, mConstruct(false)
			, mKeyPress(false)
			, mDragOut(false)
		{}
		//-----------------------------------------------------------------------
		SwfRecordClipEventFlags::SwfRecordClipEventFlags(MemoryBlockReader& memoryReader, short swfVersion)
			: mKeyUp(false)
			, mKeyDown(false)
			, mMouseUp(false)
			, mMouseDown(false)
			, mmouseMove(false)
			, mUnload(false)
			, mEnterFrame(false)
			, mLoad(false)
			, mDragOver(false)
			, mRollOut(false)
			, mRollOver(false)
			, mReleaseOutside(false)
			, mRelease(false)
			, mPress(false)
			, mInitialize(false)
			, mData(false)
			, mConstruct(false)
			, mKeyPress(false)
			, mDragOut(false)
		{
			mKeyUp            = memoryReader.readBooleanBit();
			mKeyDown          = memoryReader.readBooleanBit();
			mMouseUp          = memoryReader.readBooleanBit();
			mMouseDown        = memoryReader.readBooleanBit();
			mmouseMove        = memoryReader.readBooleanBit();
			mUnload           = memoryReader.readBooleanBit();
			mEnterFrame       = memoryReader.readBooleanBit();
			mLoad             = memoryReader.readBooleanBit();
			mDragOver         = memoryReader.readBooleanBit();
			mRollOut          = memoryReader.readBooleanBit();
			mRollOver         = memoryReader.readBooleanBit();
			mReleaseOutside   = memoryReader.readBooleanBit();
			mRelease          = memoryReader.readBooleanBit();
			mPress            = memoryReader.readBooleanBit();
			mInitialize       = memoryReader.readBooleanBit();
			mData             = memoryReader.readBooleanBit();
			if (swfVersion >= 6)
			{
				// 5 reserved bits
				memoryReader.readUnsignedBits(5);
				mConstruct   = memoryReader.readBooleanBit();
				mKeyPress    = memoryReader.readBooleanBit();
				mDragOut     = memoryReader.readBooleanBit();
				// 8 reserved bits
				memoryReader.readUnsignedBits(8);
			}
		}
		//-----------------------------------------------------------------------
		SwfRecordClipEventFlags::~SwfRecordClipEventFlags()
		{}
		//-----------------------------------------------------------------------
	}
}
