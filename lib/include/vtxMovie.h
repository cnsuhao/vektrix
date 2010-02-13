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
#include "vtxVector2.h"

namespace vtx
{
	/** Defines a movie instance, which was created from a File template.
	@remarks
		The Movie class represents a functional GUI instance, which is created
		based on a beforehand loaded File template. The Movie class itself is
		mostly an interface which has to be extended and implemented in external
		plugins. Instances of Movie can only be created by using the Root::createMovie
		function.
	*/
	class vtxExport Movie
	{
	public:
		virtual ~Movie();
		/** Get the unique name associated with this Movie.
		@returns
			the name of this Movie.
		*/
		const String& getName();
		/** Get the File template that was used to create this Movie.
		@returns
			pointer to the template File.
		*/
		File* getFile();
		/** Advance the Timeline of the Movie by the given delta time.
		@param
			delta_time Time that shall be added to the Timeline of the Movie.
		*/
		void addTime(float delta_time);
		/** Set the Movie's virtual mouse cursor to the given absolute position.
		@param
			x X-Coordinate of the mouse cursor in pixels, values in the range of [0 ... movie_width] are valid.
		@param
			y Y-Coordinate of the mouse cursor in pixels, values in the range of [0 ... movie_height] are valid.
		*/
		void setMouseAbs(uint x, uint y);
		/** Set the Movie's virtual mouse cursor to the given relative position.
		@param
			x X-Coordinate of the mouse cursor relative to the Movie's width, values in the range of [0.0f ... 1.0f] are valid.
		@param
			y Y-Coordinate of the mouse cursor relative to the Movie's height, values in the range of [0.0f ... 1.0f] are valid.
		*/
		void setMouseRel(float x, float y);
		/** Get the Movie's virtual mouse cursor position in absolute space.
		@returns
			Coordinates of the mouse cursor in pixels.
		*/
		const Vector2& getMouseAbs() const;
		/** Inform the Movie that a mouse button was pressed.
		*/
		void mouseDown();
		/** Inform the Movie that a mouse button was released.
		*/
		void mouseUp();
		/** Query the current status of the mouse button.
		@returns
			true if the mouse button is currently pressed, false otherwise.
		*/
		const bool& isMouseDown() const;
		/** Advance the playhead of the Movie automatically.
		*/
		void play();
		/** Stop the playhead of the Movie.
		*/
		void stop();
		/** Jump to a given frame of the Movie.
		@param
			frame Index of the frame that you want to jump to, values in the range of [0 ... frame_count] are valid.
		@returns
			true if the jump to the frame was successful, false otherwise.
		*/
		bool goto_frame(uint frame);
		/** Jump to a given point in time of the Movie.
		@param
			time Point in time that you want to jump to, values in the range of [0 ... frame_count/frame_rate] are valid.
		@returns
			true if the jump to the point in time was successful, false otherwise.
		*/
		bool goto_time(const float& time);
		/** Request an Instance by its id.
		@param
			id The id of the Instance that shall be returned.
		@returns
			an Instance with the given id.
		*/
		virtual Instance* getInstance(const String& id);
		/** Store an Instance.
		@param
			instance The Instance that shall be stored.
		*/
		virtual void releaseInstance(Instance* instance);
		/** Get the ScriptEngine that is associated with this Movie.
		@returns
			the ScriptEngine that is being used to execute script commands.
		*/
		ScriptEngine* getScriptEngine() const;
		/** Enable the debugger for this movie.
		@param
			enable Enable the debugger if true, disable otherwise.
		*/
		void enableDebugger(const bool& enable);
		/** Get the MovieDebugger that is associated with this Movie.
		@returns
			The MovieDebugger that is used to debug this movie.
		*/
		MovieDebugger* getDebugger() const;

	protected:
		Movie(const String& name, File* file, MovieFactory* creator);

		String mName;
		File* mFile;
		bool mMouseDown;
		MovieFactory* mCreator;
		RenderStrategy* mRenderStrategy;
		Vector2 mMousePosition;

		MovieDebugger* mDebugger;
		MovieClip* mMainMovieClip;
		ScriptEngine* mScriptEngine;

		Shape* mMouseArrow;
		Shape* mMouseHand;
		Shape* mMouseTextCursor;
	};
}

#endif
