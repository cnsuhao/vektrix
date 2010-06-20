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
#include "vtxswfRecordSoundInfo.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfRecordSoundInfo::SwfRecordSoundInfo()
			: mSyncStop(false)
			, mSyncNoMultiple(false)
			, mInPoint(0)
			, mOutPoint(0)
			, mLoopCount(0)
			, mHasEnvelope(false)
			, mHasLoops(false)
			, mHasOutPoint(false)
			, mHasInPoint(false)
		{}
		//-----------------------------------------------------------------------
		SwfRecordSoundInfo::SwfRecordSoundInfo(MemoryBlockReader& memoryReader)
			: mSyncStop(false)
			, mSyncNoMultiple(false)
			, mInPoint(0)
			, mOutPoint(0)
			, mLoopCount(0)
			, mHasEnvelope(false)
			, mHasLoops(false)
			, mHasOutPoint(false)
			, mHasInPoint(false)
		{
			memoryReader.readUnsignedBits(2); // 2 reserved bits
			mSyncStop         = memoryReader.readBooleanBit();
			mSyncNoMultiple   = memoryReader.readBooleanBit();
			mHasEnvelope      = memoryReader.readBooleanBit();
			mHasLoops         = memoryReader.readBooleanBit();
			mHasOutPoint      = memoryReader.readBooleanBit();
			mHasInPoint       = memoryReader.readBooleanBit();
			if (mHasInPoint)
				mInPoint = memoryReader.readUI32();
			if (mHasOutPoint)
				mOutPoint = memoryReader.readUI32();
			if (mHasLoops)
				mLoopCount = memoryReader.readUI16();
			if (mHasEnvelope)
			{
				unsigned char envPoints = memoryReader.readUI8();
				for (int i = 0; i < envPoints; i++)
				{
					mEnvelopeRecords.push_back(new SwfRecordSoundEnvelope(memoryReader));
				}
			}
		}
		//-----------------------------------------------------------------------
		SwfRecordSoundInfo::~SwfRecordSoundInfo()
		{
			for(SoundEnvelopeList::iterator it = mEnvelopeRecords.begin(); it != mEnvelopeRecords.end(); ++it)
			{
				delete (*it);
			}
			mEnvelopeRecords.clear();
		}
		//-----------------------------------------------------------------------
	}
}
