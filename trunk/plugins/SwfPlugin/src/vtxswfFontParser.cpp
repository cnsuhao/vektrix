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
#include "vtxswfFontParser.h"
#include "vtxswfParser.h"

#include "vtxFontResource.h"
#include "vtxGlyphResource.h"
#include "vtxStringHelper.h"

namespace vtx { namespace swf {
	//-----------------------------------------------------------------------
	void FontParser::handleDefineFont(const TagTypes& tag_type, const uint& tag_length, SwfParser* parser)
	{
		UI16 id = parser->readU16();
		UI8 flags = parser->readU8();
		UI8 lang_code = parser->readU8();

		FontResource* font = new FontResource(StringHelper::toString(id));

		// read non-ZERO terminated strings
		String font_name = parser->readString(false);
		font->setName(font_name);

		// Offset Table
		UI16 num_glyphs = parser->readU16();
		for(UI16 i=0; i<num_glyphs; ++i)
		{
			if(flags & FF_WideOffsets)
				parser->readU32();

			else
				parser->readU16();
		}

		// Code Table Offset
		UI32 codetable_offset = 0;
		if(flags & FF_WideOffsets)
			codetable_offset = parser->readU32();
		else
			codetable_offset = parser->readU16();

		// Glyph Shapes
		for(UI16 i=0; i<num_glyphs; ++i)
		{
			// reset the glyph data
			mFlashGlyph.clear();

			// parse the flash glyph
			parser->readShape(TT_DefineShape, mFlashGlyph);

			GlyphResource* glyph = new GlyphResource(font);
			glyph->setIndex(i);
			writeGlyphContours(glyph);
			font->addGlyph(glyph);
		}

		// Code Table
		for(UI16 i=0; i<num_glyphs; ++i)
		{
			GlyphResource* glyph = font->getGlyphByIndex(i);
			glyph->setCode(parser->readU16());
		}

		// Font Layout
		if(flags & FF_HasLayout)
		{
			SI16 ascender_height = parser->readS16();
			SI16 descender_height = parser->readS16();
			SI16 leading_height = parser->readS16();

			font->setAscender(ascender_height/1024.0f);
			font->setDescender(descender_height/1024.0f);
			font->setLeading(leading_height/1024.0f);

			// Advance Table
			for(UI16 i=0; i<num_glyphs; ++i)
			{
				SI16 advance = parser->readS16();
				GlyphResource* glyph = font->getGlyphByIndex(i);
				glyph->setAdvance(advance/1024.0f);
			}

			// Bounds Table
			for(UI16 i=0; i<num_glyphs; ++i)
				parser->readRect();

			// Kerning Table
			UI16 kerning_count = parser->readU16();

			for(UI16 i=0; i<kerning_count; ++i)
				parser->readKerningRecord(flags & FF_WideCodes);
		}

		parser->getCurrentFile()->addResource(font);
	}
	//-----------------------------------------------------------------------
//#define VTX_DEBUG_GLYPHS
	//-----------------------------------------------------------------------
	void FontParser::writeGlyphContours(GlyphResource* glyph_resource)
	{
		ShapeElementList::iterator element_it = mFlashGlyph.elements.begin();
		ShapeElementList::iterator element_end = mFlashGlyph.elements.end();
		while(element_it != element_end)
		{
			// the current element
			SHAPEELEMENT& element = *element_it;
			Vector2 element_pos(element.x/1024.0f, element.y/1024.0f);
			Vector2 element_ctrl(element.cx/1024.0f, element.cy/1024.0f);

			// which type is it?
			switch(element.type)
			{
			case SET_MOVE:
				{
					ShapeElement shape_element;
					shape_element.type = ShapeElement::SID_MOVE_TO;
					shape_element.pos = element_pos;

#ifdef VTX_DEBUG_GLYPHS
					std::cout << "MOVE " << StringHelper::toString(shape_element.pos) << std::endl;
#endif

					glyph_resource->addShapeElement(shape_element);
				}
				break;

			case SET_LINE:
				{
					ShapeElement shape_element;
					shape_element.type = ShapeElement::SID_LINE_TO;
					shape_element.pos = element_pos;

#ifdef VTX_DEBUG_GLYPHS
					std::cout << "LINE " << StringHelper::toString(shape_element.pos) << std::endl;
#endif

					glyph_resource->addShapeElement(shape_element);
				}
				break;

			case SET_BEZIER:
				{
					ShapeElement shape_element;
					shape_element.type = ShapeElement::SID_CURVE_TO;
					shape_element.ctrl = element_ctrl;
					shape_element.pos = element_pos;

#ifdef VTX_DEBUG_GLYPHS
					std::cout << "CURVE " << StringHelper::toString(shape_element.ctrl) << std::endl;
					std::cout << "TO " << StringHelper::toString(shape_element.pos) << std::endl;
#endif

					glyph_resource->addShapeElement(shape_element);
				}
				break;
			}; // switch(element.type)

			++element_it;

		} // for(elements)

#ifdef VTX_DEBUG_GLYPHS
		std::cout << "END" << std::endl;
#endif
	}
	//-----------------------------------------------------------------------
}}
