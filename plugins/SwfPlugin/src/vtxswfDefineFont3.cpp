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
#include "vtxswfParser.h"

#include "vtxFontResource.h"
#include "vtxGlyphResource.h"
#include "vtxStringHelper.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		KERNINGRECORD SwfParser::readKerningRecord(const UI8& wide_codes)
		{
			KERNINGRECORD record;

			if(wide_codes)
			{
				record.left_char_code = readU16();
				record.right_char_code = readU16();
			}
			else
			{
				record.left_char_code = readU8();
				record.right_char_code = readU8();
			}

			record.adjustment = readS16();

			return record;
		}
		//-----------------------------------------------------------------------
		void SwfParser::handleDefineFont3()
		{
			// DEBUG
			//mDebugFile = 0;

			UI16 id = readU16();

			FontResource* font = new FontResource(StringHelper::toString(id));

			resetReadBits();
			UI8 has_layout =	readUBits(1);
			UI8 shift_JIS =		readUBits(1);
			UI8 small_text =	readUBits(1);
			UI8 ANSI =			readUBits(1);
			UI8 wide_offsets =	readUBits(1);
			UI8 wide_codes =	readUBits(1);
			UI8 italic =		readUBits(1);
			UI8 bold =			readUBits(1);

			UI8 lang_code = readU8();

			// read non-ZERO terminated strings
			String font_name = readString(false);
			font->setName(font_name);

			// Offset Table
			UI16 num_glyphs = readU16();
			for(UI16 i=0; i<num_glyphs; ++i)
			{
				if(wide_offsets)
				{
					readU32();
				}
				else
				{
					readU16();
				}
			}

			// Code Table Offset
			UI32 codetable_offset = 0;
			if(wide_offsets)
			{
				codetable_offset = readU32();
			}
			else
			{
				codetable_offset = readU16();
			}

			// Glyph Shapes
			for(UI16 i=0; i<num_glyphs; ++i)
			{
				//char filename[512];
				//sprintf_s(filename, "%sfont_%d_glyph_%d.txt", DEBUG_OUTPUT_PATH, id, i);
				//mDebugFile = fopen(filename, "w");

				// clear all lists
				// -> FLASH
				mFlashShape.clear();

				// -> VEKTRIX
				mChunkLists.clear();
				mSubShapeList.clear();

				// parse the flash shape
				readShape(TT_DefineShape, mFlashShape);

				GlyphResource* glyph = new GlyphResource(font);
				glyph->setIndex(i);
				writeGlyphContours(glyph);
				font->addGlyph(glyph);

				//fclose(mDebugFile);
			}

			// Code Table
			for(UI16 i=0; i<num_glyphs; ++i)
			{
				GlyphResource* glyph = font->getGlyphByIndex(i);
				glyph->setCode(readU16());
			}

			// Font Layout
			if(has_layout)
			{
				SI16 ascender_height = readS16();
				SI16 descender_height = readS16();
				SI16 leading_height = readS16();

				// Advance Table
				for(UI16 i=0; i<num_glyphs; ++i)
				{
					SI16 advance = readS16();
					GlyphResource* glyph = font->getGlyphByIndex(i);
					glyph->setAdvance(advance/1024.0f);
				}

				// Bounds Table
				for(UI16 i=0; i<num_glyphs; ++i)
				{
					readRect();
				}

				// Kerning Table
				UI16 kerning_count = readU16();
				for(UI16 i=0; i<kerning_count; ++i)
				{
					readKerningRecord(wide_codes);
				}
			}

			mCurrentFile->addResource(font);
		}
		//-----------------------------------------------------------------------
		void SwfParser::writeGlyphContours(GlyphResource* glyph_resource)
		{
			Vector2 min;
			Vector2 max;

			ShapeElementList::iterator element_it = mFlashShape.elements.begin();
			ShapeElementList::iterator element_end = mFlashShape.elements.end();
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

				// what type is it?
				switch(element.type)
				{
				case SET_MOVE:
					{
						ShapeElement shape_element;
						shape_element.type = ShapeElement::SID_MOVE_TO;
						shape_element.pos = element_pos;

						glyph_resource->addShapeElement(shape_element);
						//debug_shape_element(shape_element, mDebugFile);
					}
					break;

				case SET_LINE:
					{
						ShapeElement shape_element;
						shape_element.type = ShapeElement::SID_LINE_TO;
						shape_element.pos = element_pos;

						glyph_resource->addShapeElement(shape_element);
						//debug_shape_element(shape_element, mDebugFile);
					}
					break;

				case SET_BEZIER:
					{
						ShapeElement shape_element;
						shape_element.type = ShapeElement::SID_CURVE_TO;
						shape_element.ctrl = Vector2(element.cx/1024.0f, element.cy/1024.0f);
						shape_element.pos = element_pos;

						glyph_resource->addShapeElement(shape_element);
						//debug_shape_element(shape_element, mDebugFile);
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
