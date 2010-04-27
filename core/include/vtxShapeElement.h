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

#ifndef __vtxShapeElement_H__
#define __vtxShapeElement_H__

#include "vtxPrerequesites.h"
#include "vtxVector2.h"

namespace vtx
{
	/** Represents a single element of a vector based shape outline */
	class ShapeElement
	{
	public:
		enum ShapeElementID
		{
			SID_MOVE_TO = 0, 
			SID_LINE_TO, 
			SID_CURVE_TO
		};

		ShapeElement() 
			: type(SID_MOVE_TO)
		{

		}

		ShapeElement(const ShapeElementID& type, 
			const float& x, const float& y, 
			const float& cx = 0.0f, const float& cy = 0.0f) 
			: type(type), 
			pos(x, y), 
			ctrl(cx, cy)
		{

		}

		// contour identifier { CID_BEGIN | CID_END | CID_LINE | CID_BEZIER }
		ShapeElementID type;

		// texture coordinates
		Vector2 texcoord;

		// current location
		Vector2 pos;

		// control point
		Vector2 ctrl;
	};
	typedef std::vector<ShapeElement> ShapeElementList;
}

#endif
