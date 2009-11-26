/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009 Fuse-Software (tm)

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/
#include "vtxTimeline.h"

#include "vtxDisplayObjectContainer.h"
#include "vtxKeyframe.h"
#include "vtxLogManager.h"
//#include "vtxMovie.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	Timeline::Timeline(void) 
		: mPlaying(false), 
		mPosition(0.0f), 
		mFrameRate(12), 
		mCurrentFrame(0), 
		mObjectContainer(NULL)
	{

	}
	//-----------------------------------------------------------------------
	Timeline::~Timeline(void)
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
	Timeline* Timeline::clone(DisplayObjectContainer* container)
	{
		Timeline* clonedTimeline = new Timeline;
		clonedTimeline->mFrameRate = mFrameRate;
		clonedTimeline->mObjectContainer = container;

		KeyframeList::iterator it = mKeyframes.begin();

		for( ; it != mKeyframes.end(); ++it)
		{
			Keyframe* frame = (*it)->clone(container);
			clonedTimeline->mKeyframes.push_back(frame);
		}

		return clonedTimeline;
	}
	//-----------------------------------------------------------------------
	void Timeline::addKeyframe(Keyframe* frame)
	{
		// TODO: add Keyframe with indices
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
		if(!mPlaying || (mKeyframes.size() < 2 && mCurrentFrame == 1))
		{
			return;
		}

		mPosition += delta_time;

		// the frame index which is about to be displayed
		uint frame = (uint)(mPosition * mFrameRate);

		Keyframe* currentFrame = mKeyframes.at(mCurrentFrame);
		if(frame >= currentFrame->getIndex())
		{
			currentFrame->execute();
			++mCurrentFrame;
		}

		if(mCurrentFrame == mKeyframes.size() && mKeyframes.size() > 1)
		{
			mObjectContainer->clearLayers();

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
