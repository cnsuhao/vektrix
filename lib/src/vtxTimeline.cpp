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

#include "vtxTimeline.h"

#include "vtxDisplayObjectContainer.h"
#include "vtxKeyframe.h"
#include "vtxLogManager.h"
#include "vtxMovieClip.h"
#include "vtxScriptMovieClip.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	Timeline::Timeline() 
		: mPlaying(false), 
		mPosition(0.0f), 
		mFrameRate(12), 
		mCurrentFrame(0), 
		mParentMovieClip(NULL)
	{

	}
	//-----------------------------------------------------------------------
	Timeline::~Timeline()
	{
		KeyframeList::iterator it = mKeyframes.begin();
		KeyframeList::iterator end = mKeyframes.end();
		while(it != end)
		{
			delete *it;
			++it;
		}
	}
	//-----------------------------------------------------------------------
	Timeline* Timeline::clone(MovieClip* movieclip)
	{
		Timeline* clonedTimeline = new Timeline;
		clonedTimeline->mFrameRate = mFrameRate;
		clonedTimeline->mParentMovieClip = movieclip;

		KeyframeList::iterator it = mKeyframes.begin();

		for( ; it != mKeyframes.end(); ++it)
		{
			Keyframe* frame = (*it)->clone(movieclip);
			clonedTimeline->mKeyframes.push_back(frame);
		}

		return clonedTimeline;
	}
	//-----------------------------------------------------------------------
	void Timeline::addKeyframe(Keyframe* frame)
	{
		mKeyframes.push_back(frame);
	}
	//-----------------------------------------------------------------------
	void Timeline::clear()
	{
		mPlaying = false;
		mPosition = 0.0f;
		mKeyframes.clear();
	}
	//-----------------------------------------------------------------------
	void Timeline::addTime(float delta_time)
	{
		if(!mPlaying || (mKeyframes.size() < 2 && mCurrentFrame == 1) || !mKeyframes.size())
		{
			return;
		}

		// TODO: rework Timeline::goto commands & keyframe handling, etc.
		// >> mainly the initialization
		mPosition += delta_time;

		// the frame index which is about to be displayed
		uint frame = (uint)(mPosition * mFrameRate);

		Keyframe* currentFrame = mKeyframes.at(mCurrentFrame);
		if(frame >= currentFrame->getIndex())
		{
			currentFrame->execute();

			if(mParentMovieClip)
			{
				ScriptMovieClip* movieclip = mParentMovieClip->getScriptMovieClip();
				if(movieclip)
				{
					movieclip->frameEntered(mCurrentFrame);
				}
			}

			++mCurrentFrame;
		}

		if(mCurrentFrame == mKeyframes.size() && mKeyframes.size() > 1)
		{
			mParentMovieClip->clearLayers();

			mCurrentFrame = 0;
			mPosition = 1.0f / (float)mFrameRate;
			addTime(0);
		}
	}
	//-----------------------------------------------------------------------
	void Timeline::setFrameRate(const uint& framerate)
	{
		mFrameRate = framerate;
	}
	//-----------------------------------------------------------------------
	void Timeline::play()
	{
		mPlaying = true;
	}
	//-----------------------------------------------------------------------
	void Timeline::stop()
	{
		mPlaying = false;
	}
	//-----------------------------------------------------------------------
	bool Timeline::goto_frame(uint frame)
	{
		mPosition = (float)frame / (float)mFrameRate;
		mCurrentFrame = 0;
		mPlaying = true;

		if(!mKeyframes.size())
		{
			return false;
		}

		if(mKeyframes.back()->getIndex() < frame)
		{
			return false;
		}

		KeyframeList::iterator it = mKeyframes.begin();

		for( ; it != mKeyframes.end(); ++it)
		{
			if((*it)->getIndex() <= frame)
			{
				(*it)->execute();
			}
			else
			{
				return true;
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool Timeline::goto_time(float time)
	{
		return false;
	}
	//-----------------------------------------------------------------------
}
