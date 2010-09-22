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

#include "vtxMovieClip.h"

#include "vtxBoundingBox.h"
#include "vtxFile.h"
#include "vtxMovie.h"
#include "vtxMovieClipResource.h"
#include "vtxTimeline.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	const String MovieClip::TYPE = "MovieClip";
	//-----------------------------------------------------------------------
	MovieClip::MovieClip() 
		: mTimeline(NULL)
	{

	}
	//-----------------------------------------------------------------------
	MovieClip::~MovieClip()
	{
		delete mTimeline;
	}
	//-----------------------------------------------------------------------
	void MovieClip::initFromResource(Resource* resource)
	{
		if(resource->getType() == "MovieClip")
		{
			MovieClipResource* movieclip_res = static_cast<MovieClipResource*>(resource);

			delete mTimeline;

			mTimeline = movieclip_res->getTimeline()->clone(this);
			mTimeline->setFrameRate(mParentMovie->getFile()->getHeader().fps);
		}

		DisplayObjectContainer::initFromResource(resource);
	}
	//-----------------------------------------------------------------------
	const String& MovieClip::getType() const
	{
		return TYPE;
	}
	//-----------------------------------------------------------------------
	void MovieClip::play()
	{
		if(mTimeline)
		{
			mTimeline->play();
		}
	}
	//-----------------------------------------------------------------------
	void MovieClip::stop()
	{
		if(mTimeline)
		{
			mTimeline->stop();
		}
	}
	//-----------------------------------------------------------------------
	bool MovieClip::gotoFrame(uint frame)
	{
		if(mTimeline)
		{
			return mTimeline->gotoFrame(frame);
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool MovieClip::gotoTime(const float& time)
	{
		if(mTimeline)
		{
			return mTimeline->gotoTime(time);
		}

		return false;
	}
	//-----------------------------------------------------------------------
	uint MovieClip::getCurrentFrame() const
	{
		if(mTimeline)
		{
			return mTimeline->getCurrentFrame();
		}

		return 0;
	}
	//-----------------------------------------------------------------------
	void MovieClip::_update(const float& delta_time)
	{
		DisplayObjectContainer::_update(delta_time);

		if(mTimeline)
		{
			mTimeline->addTime(delta_time);
		}
	}
	//-----------------------------------------------------------------------
}
