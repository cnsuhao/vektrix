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

#include "vtxPrerequisites.h"
#include "vtxVector2.h"

namespace vtx
{
	/** Defines a movie instance, which can be created by using Root::createMovie() */
	class vtxExport Movie
	{
		friend class InteractiveObject;
		friend class Root;

	protected:
		Movie(const String& name, File* file, MovieFactory* creator);
		virtual ~Movie();

	public:
		class vtxExport Listener
		{
			virtual void movieDestroyed(Movie* movie) = 0;
		};

		/** Get the unique name that is associated with this movie */
		const String& getName();

		/** Get the File template that was used to create this movie */
		File* getFile();

		/** Advance the Timeline of the movie by the given delta time */
		void addTime(float delta_time);

		/** Set the movie's virtual mouse cursor to the given absolute position */
		void setMouseAbs(uint x, uint y);

		/** Set the movie's virtual mouse cursor to the given relative position */
		void setMouseRel(float x, float y);

		/** Get the movie's virtual mouse cursor position in absolute space */
		const Vector2& getMouseAbs() const;

		/** Inform the movie that a mouse button was pressed */
		void mouseDown();

		/** Inform the movie that a mouse button was released */
		void mouseUp();

		/** Inform the movie that a keyboard button was released */
		void keyDown(const uint& keyCode, const uint& charCode);

		/** Inform the movie that a keyboard button was released */
		void keyUp(const uint& keyCode, const uint& charCode);

		/** @copybrief MovieClip::play */
		void play();

		/** @copybrief MovieClip::stop */
		void stop();

		/** @copybrief MovieClip::gotoFrame */
		bool gotoFrame(uint frame);

		/** @copybrief MovieClip::gotoTime */
		bool gotoTime(const float& time);

		/** Request an Instance by its id */
		virtual Instance* getInstance(const String& id);

		/** Request an Instance by its type */
		virtual Instance* getInstanceByType(const String& type);

		/** Release a previously used Instance */
		virtual void releaseInstance(Instance* instance);

		/** Get the ScriptEngine that is associated with this movie */
		ScriptEngine* getScriptEngine() const;

		/** Enable the debugger for this movie */
		void enableDebugger(const bool& enable);

		/** Get the MovieDebugger that is associated with this movie */
		MovieDebugger* getDebugger() const;

		/** Get the main MovieClip of this movie */
		MovieClip* getMainMovieClip() const;

		RenderStrategy* getRenderStrategy() const;

		/** Attach custom user data to this movie */
		void setUserData(void* data);
		/** Get the custom user data of this movie */
		void* getUserData() const;

	protected:
		String mName;
		File* mFile;
		MovieFactory* mCreator;
		RenderStrategy* mRenderStrategy;
		Vector2 mMousePosition;
		void* mUserData;

		InteractiveObject* mFocusedObject;
		MovieDebugger* mDebugger;
		MovieClip* mMainMovieClip;
		ScriptEngine* mScriptEngine;

		void _setFocusedObject(InteractiveObject* focused_object);

		//Shape* mMouseArrow;
		//Shape* mMouseHand;
		//Shape* mMouseTextCursor;
	};
}

#endif
