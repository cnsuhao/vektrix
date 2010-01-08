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

#ifndef __vtxMovie_H__
#define __vtxMovie_H__

#include "vtxPrerequesites.h"
#include "vtxInstancePool.h"
#include "vtxVector2.h"

namespace vtx
{
	class vtxExport Movie
	{
	public:
		friend class MovieFactory;
		friend class Root;

		virtual ~Movie();

		const String& getName();
		File* getFile();

		void addTime(float delta_time);

		void setMouseAbs(uint x, uint y);
		void setMouseRel(float x, float y);

		const Vector2& getMouseAbs() const;

		void mouseDown();
		void mouseUp();

		const bool& isMouseDown() const;

		// timeline functions
		void play();
		void stop();
		bool goto_frame(uint frame);
		bool goto_time(const float& time);

		virtual Instance* getInstance(const String& id);
		virtual void releaseInstance(Instance* instance);

		ScriptEngine* getScriptEngine() const;

		void enableDebugger(const bool& enable);
		MovieDebugger* getDebugger() const;

	protected:
		Movie(const String& name, File* file, MovieFactory* creator);

		String mName;
		File* mFile;
		bool mMouseDown;
		MovieFactory* mCreator;
		RenderStrategy* mDataPool;
		Vector2 mMousePosition;

		MovieDebugger* mDebugger;
		MovieClip* mMainMovieClip;
		ScriptEngine* mScriptEngine;

		Shape* mMouseArrow;
		Shape* mMouseHand;
		Shape* mMouseTextCursor;

		void _initialize(MovieFactory* creator_factory);
	};
}

#endif
