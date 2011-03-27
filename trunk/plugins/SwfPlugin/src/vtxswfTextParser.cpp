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

#include "vtxswfTextParser.h"
#include "vtxswfParser.h"

#include "vtxEditTextResource.h"
#include "vtxStaticTextResource.h"
#include "vtxStringHelper.h"

namespace vtx { namespace swf {
	//-----------------------------------------------------------------------
	void TextParser::handleDefineText(const TagTypes& tag_type, const uint& tag_length, SwfParser* parser)
	{
		UI16 id = parser->readU16();
		RECT bounds = parser->readRect();
		MATRIX transform = parser->readMatrix();

		UI8 glyph_bits = parser->readU8();
		UI8 advance_bits = parser->readU8();

		StaticTextResource* statictext = new StaticTextResource(StringHelper::toString(id));

		BoundingBox box(
			Vector2(bounds.xmin/20.0f, bounds.ymin/20.0f), 
			Vector2(bounds.xmax/20.0f, bounds.ymax/20.0f));

		statictext->setBoundingBox(box);

		GlyphStripList glyphs;
		GlyphStrip glyph_strip;

		TextRecordList records;
		while(true)
		{
			UI8 flags = parser->readU8();

			// end of records
			if(!flags)
			{
				break;
			}

			TEXTRECORD text_record;

			// clear glyphs
			glyph_strip.glyphs.clear();
			glyph_strip.newline = false;

			// has font
			if(flags & 8)
			{
				text_record.font_id = parser->readU16();
				glyph_strip.fontid = StringHelper::toString(text_record.font_id);
			}
			// has color
			if(flags & 4)
			{
				text_record.color = parser->readRGBA(tag_type == TT_DefineText2);
				glyph_strip.color = Color(
					text_record.color.red/255.0f, 
					text_record.color.green/255.0f, 
					text_record.color.blue/255.0f, 
					text_record.color.alpha/255.0f);
			}
			// has x offset
			if(flags & 1)
			{
				text_record.x = parser->readS16();
				glyph_strip.x = text_record.x / 20.0f;
			}
			// has y offset
			if(flags & 2)
			{
				text_record.y = parser->readS16();
				float new_y = text_record.y / 20.0f;

				// needs a line break ?
				if(new_y > glyph_strip.y + glyph_strip.size)
				{
					glyph_strip.newline = true;
				}

				glyph_strip.y = new_y;
			}
			// has font -> text height
			if(flags & 8)
			{
				text_record.size = parser->readU16();
				glyph_strip.size = text_record.size / 20.0f;
			}

			parser->resetReadBits();

			// Glyph Entries
			UI8 glyph_count = parser->readU8();
			for(UI8 i=0; i<glyph_count; ++i)
			{
				GLYPHENTRY entry;
				entry.index = parser->readUBits(glyph_bits);
				entry.x_advance = parser->readSBits(advance_bits);

				GlyphStrip::Glyph glyph;
				glyph.index = entry.index;
				glyph.x_advance = entry.x_advance / 20.0f;

				// add glyph to strip
				glyph_strip.glyphs.push_back(glyph);
			}

			records.push_back(text_record);

			// add strip to list
			glyphs.push_back(glyph_strip);

		} // while(TextRecords)

		statictext->setGlyphStrips(glyphs);
		parser->getCurrentFile()->addResource(statictext);
	}
	//-----------------------------------------------------------------------
	void TextParser::handleDefineEditText(const TagTypes& tag_type, const uint& tag_length, SwfParser* parser)
	{
		UI16 id = parser->readU16();
		RECT bounds = parser->readRect();

		EditTextResource* edit_text = new EditTextResource(StringHelper::toString(id));

		BoundingBox box(
			Vector2(bounds.xmin/20.0f, bounds.ymin/20.0f), 
			Vector2(bounds.xmax/20.0f, bounds.ymax/20.0f));

		edit_text->setBoundingBox(box);

		UI16 flags = parser->readU16();

		if(flags & ETF_HasFont)
		{
			// font id
			UI16 fontid = parser->readU16();
		}

		if(flags & ETF_HasFontClass)
		{
			// font as3 class
			String font_class = parser->readString();
		}

		if(flags & ETF_HasFont)
		{
			// font height
			UI16 font_size = parser->readU16();
			edit_text->setFontSize(font_size/20.0f);
		}

		if(flags & ETF_HasTextColor)
		{
			// text color
			RGBA color = parser->readRGBA(true);
			edit_text->setDefaultColor(Color(
				color.red/255.0f, 
				color.green/255.0f, 
				color.blue/255.0f, 
				color.alpha/255.0f));
		}

		if(flags & ETF_HasMaxLength)
		{
			// max text length
			parser->readU16();
		}

		if(flags & ETF_HasLayout)
		{
			parser->readU8(); // align (left = 0, right, center, justify)
			parser->readU16(); // left margin
			parser->readU16(); // right margin
			parser->readU16(); // ident
			parser->readS16(); // leading
		}

		// variable name
		parser->readString();

		if(flags & ETF_HasText)
		{
			// initial text
			String html_text = parser->readString();
			edit_text->setInitialText(StringHelper::utf8Decode(html_text));
		}

		parser->getCurrentFile()->addResource(edit_text);
	}
	//-----------------------------------------------------------------------
}}
