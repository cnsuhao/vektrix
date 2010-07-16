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

#ifndef __vtxRastarizer_H__
#define __vtxRastarizer_H__

#include "vtxPrerequisites.h"
#include "vtxShapeElement.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** An abstract interface describing a rasterizer which paints elements to textures */
	class vtxExport Rasterizer
	{
	public:
		Rasterizer();
		virtual ~Rasterizer();

		/** Start the painting of an element */
		virtual void startPaint(
			const Rect& rect, 
			const Vector2& offset, const Vector2& scale, 
			Texture* texture) = 0;

		/** Set a simple RGBA Color fillstyle for the current outline */
		virtual void setColorFill(const Color& color) = 0;

		/** Set a fillstyle based on the given MaterialResource */
		virtual void setMaterialFill(MaterialResource* material) = 0;

		/** Draw a shape from the given shape elements */
		virtual void drawShapeElements(const ShapeElementList& elements) = 0;

		/** Finish the painting of the current element */
		virtual void finishPaint() = 0;

		/** Get the unique name of this rasterizer */
		virtual const String& getName() const = 0;
	};
	//-----------------------------------------------------------------------
}

#endif
