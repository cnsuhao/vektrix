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
#include "vtxswfTag.h"
#include "vtxswfTagFont3.h"
#include "vtxFontResource.h"
#include "vtxGlyphResource.h"
#include "vtxStringHelper.h"
#include "vtxSwfParser.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfTagFont3::SwfTagFont3(uint tag_length, uchar* tag_data)
			: SwfTag(TT_DefineFont3, tag_length, tag_data)
		{}
		//-----------------------------------------------------------------------
		SwfTagFont3::~SwfTagFont3()
		{}
		//-----------------------------------------------------------------------
		void SwfTagFont3::ParseData(SwfParser* parser)
		{}
		//-----------------------------------------------------------------------
		void SwfTagFont3::writeGlyphContours(GlyphResource* glyph_resource)
		{
			Vector2 min;
			Vector2 max;

			ShapeElementList::iterator element_it = mFlashGlyph.elements.begin();
			ShapeElementList::iterator element_end = mFlashGlyph.elements.end();
			while(element_it != element_end)
			{
				// the current element
				SHAPEELEMENT& element = *element_it;
				Vector2 element_pos(element.x/1024.0f, element.y/1024.0f);
				Vector2 element_ctrl(element.cx/1024.0f, element.cy/1024.0f);

				// pos
				if(element_pos.x < min.x)
					min.x = element_pos.x;

				if(element_pos.x > max.x)
					max.x = element_pos.x;

				if(element_pos.y < min.y)
					min.y = element_pos.y;

				if(element_pos.y > max.y)
					max.y = element_pos.y;

				// ctrl
				if(element_ctrl.x < min.x)
					min.x = element_ctrl.x;

				if(element_ctrl.x > max.x)
					max.x = element_ctrl.x;

				if(element_ctrl.y < min.y)
					min.y = element_ctrl.y;

				if(element_ctrl.y > max.y)
					max.y = element_ctrl.y;

				// which type is it?
				switch(element.type)
				{
				case SET_MOVE:
					{
						ShapeElement shape_element;
						shape_element.type = ShapeElement::SID_MOVE_TO;
						shape_element.pos = element_pos;

						glyph_resource->addShapeElement(shape_element);
					}
					break;

				case SET_LINE:
					{
						ShapeElement shape_element;
						shape_element.type = ShapeElement::SID_LINE_TO;
						shape_element.pos = element_pos;

						glyph_resource->addShapeElement(shape_element);
					}
					break;

				case SET_BEZIER:
					{
						ShapeElement shape_element;
						shape_element.type = ShapeElement::SID_CURVE_TO;
						shape_element.ctrl = Vector2(element.cx/1024.0f, element.cy/1024.0f);
						shape_element.pos = element_pos;

						glyph_resource->addShapeElement(shape_element);
					}
					break;
				}; // switch(element.type)

				++element_it;

			} // for(elements)

			glyph_resource->setBoundingBox(BoundingBox(min, max));
		}
		//-----------------------------------------------------------------------
	}
}
