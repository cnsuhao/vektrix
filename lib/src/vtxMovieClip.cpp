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
}
