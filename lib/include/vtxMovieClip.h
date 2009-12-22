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
#ifndef __vtxMovieClip_H__
#define __vtxMovieClip_H__

#include "vtxPrerequesites.h"
#include "vtxDisplayObjectContainer.h"

namespace vtx
{
	class MovieClip : public DisplayObjectContainer
	{
	public:
		MovieClip(Resource* resource);
		virtual ~MovieClip();

		const String& getType() const;

		void play();
		void stop();
		bool goto_frame(uint frame);
		bool goto_time(const float& time);

		void _update(const float& delta_time);
		const BoundingBox& getBoundingBox() const;

		virtual void _setParent(Movie* parent);

		virtual void setScriptObject(ScriptObject* obj);
		virtual ScriptObject* getScriptObject() const;

	protected:
		ScriptMovieClip* mScriptObject;
		Timeline* mTimeline;
	};
}

#endif
