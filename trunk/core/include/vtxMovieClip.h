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

#ifndef __vtxMovieClip_H__
#define __vtxMovieClip_H__

#include "vtxPrerequisites.h"
#include "vtxDisplayObjectContainer.h"

namespace vtx
{
	/** Represents an object container which also provides a Timeline for modifying the contained objects */
	class vtxExport MovieClip : public DisplayObjectContainer
	{
	public:
		static const String TYPE;

		MovieClip();
		virtual ~MovieClip();

		virtual void initFromResource(Resource* resource);

		const String& getType() const;

		/** @copybrief Timeline::play */
		void play();
		/** @copybrief Timeline::stop */
		void stop();
		/** @copybrief Timeline::goto_frame */
		bool gotoFrame(uint frame);
		/** @copybrief Timeline::gotoTime */
		bool gotoTime(const float& time);

		uint getCurrentFrame() const;

		/** @copybrief DisplayObjectContainer::_update */
		void _update(const float& delta_time);
		/** @copybrief DisplayObject::getBoundingBox */
		const BoundingBox& getBoundingBox() const;

	protected:
		BoundingBox mBB;
		Timeline* mTimeline;
	};
}

#endif
