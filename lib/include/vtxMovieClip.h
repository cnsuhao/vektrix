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

#include "vtxPrerequesites.h"
#include "vtxDisplayObjectContainer.h"

namespace vtx
{
	class vtxExport MovieClip : public DisplayObjectContainer
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
		ScriptMovieClip* getScriptMovieClip() const;

	protected:
		BoundingBox mBB;
		ScriptMovieClip* mScriptObject;
		Timeline* mTimeline;
	};
}

#endif
