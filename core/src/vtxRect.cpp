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

#include "vtxRect.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	Rect::Rect() 
		: left(0), 
		top(0), 
		right(0), 
		bottom(0)
	{

	}
	//-----------------------------------------------------------------------
	Rect::Rect(uint l, uint t, uint r, uint b) 
		: left(l), 
		top(t), 
		right(r), 
		bottom(b)
	{

	}
	//-----------------------------------------------------------------------
	const RectF Rect::relativeTo(const uint& width, const uint& height) const
	{
		return RectF((float)left/width, (float)top/height, 
			(float)right/width, (float)bottom/height);
	}
	//-----------------------------------------------------------------------
	uint Rect::w() const
	{
		return right - left;
	}
	//-----------------------------------------------------------------------
	uint Rect::h() const
	{
		return bottom - top;
	}
	//-----------------------------------------------------------------------
	void Rect::contract(const uint& units)
	{
		left += units;
		top += units;
		right -= units;
		bottom -= units;
	}
	//-----------------------------------------------------------------------
	Rect Rect::contractedCopy(const uint& units) const
	{
		Rect result(left, top, right, bottom);
		result.contract(units);
		return result;
	}
	//-----------------------------------------------------------------------
	RectF::RectF() 
		: left(0), 
		top(0), 
		right(0), 
		bottom(0)
	{

	}
	//-----------------------------------------------------------------------
	RectF::RectF(float l, float t, float r, float b) 
		: left(l), 
		top(t), 
		right(r), 
		bottom(b)
	{

	}
	//-----------------------------------------------------------------------
	float RectF::w() const
	{
		return right - left;
	}
	//-----------------------------------------------------------------------
	float RectF::h() const
	{
		return bottom - top;
	}
	//-----------------------------------------------------------------------
}
