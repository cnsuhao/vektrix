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

#ifndef __vtxTextLineElement_H__
#define __vtxTextLineElement_H__

#include "vtxPrerequesites.h"
#include "vtxGlyphStrip.h"

namespace vtx
{
	/** Represents a single line element, such as a word or an image */
	class TextLineElement
	{
	public:
		enum ElementType
		{
			ET_Word = 0, 
			ET_Image, 
			ET_FontChange, 
			ET_ParagraphChange
		};

		TextLineElement()
		{
			parentHTML = NULL;
			reset();
		}

		/** Reset all attributes of this element */
		void reset()
		{
			// IMAGE
			image_shape.clear();

			// WORD
			color = Color();
			width = x = 0.0f;
			glyphs.clear();

			// ALIGN_CHANGE
			align = HtmlElement::AlignLeft;

			// FONT_CHANGE
			height = 0.0f;
			font = NULL;
		}

		ElementType type;

		/// get the parent HtmlElement of the DOM tree, from which this LineElement was generated
		HtmlElement* parentHTML;

		// IMAGE
		String image_shape;

		// WORD
		Color color;
		float width, x;
		GlyphStrip::GlyphList glyphs;

		// ALIGN_CHANGE
		HtmlElement::Alignment align;

		// FONT_CHANGE
		float height;
		FontResource* font;
	};
}

#endif
