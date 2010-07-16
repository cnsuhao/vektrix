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

#ifndef __vtxcaiRasterizer_H__
#define __vtxcaiRasterizer_H__

#include "vtxcai.h"
#include "vtxRastarizer.h"
#include "vtxRect.h"

#include "cairo.h"

namespace vtx { namespace cai {
	//-----------------------------------------------------------------------
	class CairoRasterizer : public Rasterizer
	{
	public:
		CairoRasterizer();
		virtual ~CairoRasterizer();

		void startPaint(const Rect& rect, const Vector2& offset, const Vector2& scale, Texture* texture);

		void setColorFill(const Color& color);
		void setMaterialFill(MaterialResource* material);

		void drawShapeElements(const ShapeElementList& elements);

		void finishPaint();

		const String& getName() const;

	protected:
		cairo_t* mCairo;
		cairo_surface_t* mSurface;
		cairo_pattern_t* mCairoPattern;

		Rect mRect;
		Texture* mTexture;
		Vector2 mOffset;
		Vector2 mScale;
	};
	//-----------------------------------------------------------------------
}}

#endif
