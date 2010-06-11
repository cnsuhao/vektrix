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

#ifndef __vtxRect_H__
#define __vtxRect_H__

#include "vtxPrerequisites.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** Represents a 2D rectangle using natural numbers */
	class vtxExport Rect
	{
	public:
		Rect();
		Rect(uint l, uint t, uint r, uint b);

		/** Calculate the coordinates of this rectangle relative to the given width and height */
		const RectF relativeTo(const uint& width, const uint& height) const;

		/** Get the width of the rectangle */
		uint w() const;
		/** Get the height of the rectangle */
		uint h() const;

		/** Contract the rectangle by the given amount */
		void contract(const uint& units);
		/** Calculates a copy of this rectangle which is contracted by the given amount */
		Rect contractedCopy(const uint& units) const;

		uint left, top, right, bottom;
	};
	//-----------------------------------------------------------------------
	/** Represents a 2D rectangle using real numbers */
	class vtxExport RectF
	{
	public:
		RectF();
		RectF(float l, float t, float r, float b);

		/** Get the width of the rectangle */
		float w() const;
		/** Get the height of the rectangle */
		float h() const;

		float left, top, right, bottom;
	};
	//-----------------------------------------------------------------------
}

#endif
