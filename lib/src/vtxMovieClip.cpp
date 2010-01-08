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
#include "vtxScriptMovieClip.h"
#include "vtxTimeline.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	MovieClip::MovieClip(Resource* resource) 
		: DisplayObjectContainer(resource), 
		mScriptObject(NULL), 
		mTimeline(NULL)
	{

	}
	//-----------------------------------------------------------------------
	MovieClip::~MovieClip()
	{
		delete mTimeline;
	}
	//-----------------------------------------------------------------------
	const String& MovieClip::getType() const
	{
		static String type = "MovieClip";
		return type;
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
	bool MovieClip::goto_frame(uint frame)
	{
		if(mTimeline)
		{
			return mTimeline->goto_frame(frame);
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool MovieClip::goto_time(const float& time)
	{
		if(mTimeline)
		{
			return mTimeline->goto_time(time);
		}

		return false;
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
	const BoundingBox& MovieClip::getBoundingBox() const
	{
		// TODO
		static BoundingBox bb;
		return bb;
	}
	//-----------------------------------------------------------------------
	void MovieClip::_setParent(Movie* parent)
	{
		DisplayObjectContainer::_setParent(parent);

		MovieClipResource* movieclip_res = dynamic_cast<MovieClipResource*>(mResource);

		if(movieclip_res)
		{
			if(mTimeline)
			{
				delete mTimeline;
			}

			mTimeline = movieclip_res->getTimeline()->clone(this);
			mTimeline->setFrameRate(mParentMovie->getFile()->getHeader().fps);
		}
	}
	//-----------------------------------------------------------------------
	void MovieClip::setScriptObject(ScriptObject* obj)
	{
		mScriptObject = dynamic_cast<ScriptMovieClip*>(obj);
	}
	//-----------------------------------------------------------------------
	ScriptObject* MovieClip::getScriptObject() const
	{
		return mScriptObject;
	}
	//-----------------------------------------------------------------------
	ScriptMovieClip* MovieClip::getScriptMovieClip() const
	{
		return mScriptObject;
	}
	//-----------------------------------------------------------------------
}
