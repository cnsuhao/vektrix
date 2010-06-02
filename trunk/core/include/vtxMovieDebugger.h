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

#ifndef __vtxMovieDebugger_H__
#define __vtxMovieDebugger_H__

#include "vtxPrerequesites.h"

namespace vtx
{
	/** A class for displaying visual debugging information about movies */
	class vtxExport MovieDebugger
	{
	public:
		MovieDebugger(Movie* parent);
		virtual ~MovieDebugger();

		/** Called before any of the other debugging informations is being called */
		virtual void preDebug() = 0;

		/** Enable or disable the debugging of bounding boxes */
		void debugBoundingBoxes(const bool& enable);
		/** Check if debugging bounding boxes is enabled */
		const bool& debuggingBoundingBoxes() const;

		/** Debug the given BoundingBox */
		void debugBoundingBox(const BoundingBox& bb);

	protected:
		bool mDebugBoundingBoxes;
		Movie* mParent;

		/** Draw a BoundingBox */
		virtual void drawBoundingBox(const BoundingBox& bb) = 0;

		/** Start a new debug line strip */
		virtual void startDebugLine() = 0;
		/** Add a point to the current debug line strip */
		virtual void debugLine(const Vector2& point) = 0;
		/** Finish the current debug line strip */
		virtual void endDebugLine() = 0;
	};
}

#endif
