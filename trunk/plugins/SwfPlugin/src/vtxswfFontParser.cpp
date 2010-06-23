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
#include "vtxswfStructParserHelper.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		void FontParser::handleDefineFont(const TagTypes& tag_type, MemoryBlockReader& tag_reader, SwfParser* parser)
		{
			UI16 id = tag_reader.readUI16();

			FontResource* font = new FontResource(StringHelper::toString(id));

			tag_reader.align();
			UI8 has_layout =	(UI8)tag_reader.readUnsignedBits(1);
			UI8 shift_JIS =		(UI8)tag_reader.readUnsignedBits(1);
			UI8 small_text =	(UI8)tag_reader.readUnsignedBits(1);
			UI8 ANSI =			(UI8)tag_reader.readUnsignedBits(1);
			UI8 wide_offsets =	(UI8)tag_reader.readUnsignedBits(1);
			UI8 wide_codes =	(UI8)tag_reader.readUnsignedBits(1);
			UI8 italic =		(UI8)tag_reader.readUnsignedBits(1);
			UI8 bold =			(UI8)tag_reader.readUnsignedBits(1);

			UI8 lang_code = tag_reader.readUI8();

			// read non-ZERO terminated strings
			String font_name = tag_reader.readString(false);
			font->setName(font_name);

			// Offset Table
			UI16 num_glyphs = tag_reader.readUI16();
			for(UI16 i=0; i<num_glyphs; ++i)
			{
				if(wide_offsets)
				{
					tag_reader.readUI32();
				}
				else
				{
					tag_reader.readUI16();
				}
			}

			// Code Table Offset
			UI32 codetable_offset = 0;
			if(wide_offsets)
			{
				codetable_offset = tag_reader.readUI32();
			}
			else
			{
				codetable_offset = tag_reader.readUI16();
			}

			// Glyph Shapes
			for(UI16 i=0; i<num_glyphs; ++i)
			{
				// reset the glyph data
				mFlashGlyph.clear();

				// parse the flash glyph
				//parser->readShape(TT_DefineShape, mFlashGlyph);

				GlyphResource* glyph = new GlyphResource(font);
				glyph->setIndex(i);
				writeGlyphContours(glyph);
				font->addGlyph(glyph);
			}

			// Code Table
			for(UI16 i=0; i<num_glyphs; ++i)
			{
				GlyphResource* glyph = font->getGlyphByIndex(i);
				glyph->setCode(tag_reader.readUI16());
			}

			// Font Layout
			if(has_layout)
			{
				SI16 ascender_height = tag_reader.readSI16();
				SI16 descender_height = tag_reader.readSI16();
				SI16 leading_height = tag_reader.readSI16();

				font->setAscender(ascender_height/1024.0f);
				font->setDescender(descender_height/1024.0f);
				font->setLeading(leading_height/1024.0f);

				// Advance Table
				for(UI16 i=0; i<num_glyphs; ++i)
				{
					SI16 advance = tag_reader.readSI16();
					GlyphResource* glyph = font->getGlyphByIndex(i);
					glyph->setAdvance(advance/1024.0f);
				}

				// Bounds Table
				for(UI16 i=0; i<num_glyphs; ++i)
				{
					RECT bounds;
					ParserHelper::readRect(tag_reader, bounds);
				}

				// Kerning Table
				UI16 kerning_count = tag_reader.readUI16();
				for(UI16 i=0; i<kerning_count; ++i)
				{
					KERNINGRECORD kerning;
					ParserHelper::readKerningRecord(tag_reader, false, kerning);
				}
			}
			parser->getCurrentFile()->addResource(font);
		}
		//-----------------------------------------------------------------------
		void FontParser::writeGlyphContours(GlyphResource* glyph_resource)
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
