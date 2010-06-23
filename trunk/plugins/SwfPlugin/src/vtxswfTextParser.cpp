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
#include "vtxswfStructParserHelper.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		void TextParser::handleDefineText(const TagTypes& tag_type, MemoryBlockReader& tag_reader, SwfParser* parser)
		{
			UI16 id = tag_reader.readUI16();

			RECT bounds;
			ParserHelper::readRect(tag_reader, bounds);

			MATRIX transform;
			ParserHelper::readMatrix(tag_reader, transform);

			UI8 glyph_bits = tag_reader.readUI8();
			UI8 advance_bits = tag_reader.readUI8();

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
				UI8 flags = tag_reader.readUI8();

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
					text_record.font_id = tag_reader.readUI16();
					glyph_strip.fontid = StringHelper::toString(text_record.font_id);
				}
				// has color
				if(flags & 4)
				{
					(tag_type == TT_DefineText2)
						? ParserHelper::readColorRGB(tag_reader, text_record.color)
						: ParserHelper::readColorRGBA(tag_reader, false, text_record.color);
					glyph_strip.color = Color(
						(float)text_record.color.red/255.0f, 
						(float)text_record.color.green/255.0f, 
						(float)text_record.color.blue/255.0f, 
						(float)text_record.color.alpha/255.0f);
				}
				// has x offset
				if(flags & 1)
				{
					text_record.x = tag_reader.readSI16();
					glyph_strip.x = text_record.x / 20.0f;
				}
				// has y offset
				if(flags & 2)
				{
					text_record.y = tag_reader.readSI16();
					glyph_strip.y = text_record.y / 20.0f;
					glyph_strip.newline = true;
				}
				// has font -> text height
				if(flags & 8)
				{
					text_record.size = tag_reader.readUI16();
					glyph_strip.size = text_record.size / 20.0f;
				}

				tag_reader.align();

				// Glyph Entries
				UI8 glyph_count = tag_reader.readUI8();
				for(UI8 i=0; i<glyph_count; ++i)
				{
					GLYPHENTRY entry;
					entry.index = tag_reader.readUnsignedBits(glyph_bits);
					entry.x_advance = tag_reader.readSignedBits(advance_bits);

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
		void TextParser::handleDefineEditText(const TagTypes& tag_type, MemoryBlockReader& tag_reader, SwfParser* parser)
		{
			UI16 id = tag_reader.readUI16();

			RECT bounds;
			ParserHelper::readRect(tag_reader, bounds);

			EditTextResource* edit_text = new EditTextResource(StringHelper::toString(id));

			BoundingBox box(
				Vector2(bounds.xmin/20.0f, bounds.ymin/20.0f), 
				Vector2(bounds.xmax/20.0f, bounds.ymax/20.0f));

			edit_text->setBoundingBox(box);

			tag_reader.align();
			UI8 has_text =		(UI8)tag_reader.readUnsignedBits(1);
			UI8 word_wrap =		(UI8)tag_reader.readUnsignedBits(1);
			UI8 multi_line =	(UI8)tag_reader.readUnsignedBits(1);
			UI8 password =		(UI8)tag_reader.readUnsignedBits(1);
			UI8 read_only =		(UI8)tag_reader.readUnsignedBits(1);
			UI8 has_color =		(UI8)tag_reader.readUnsignedBits(1);
			UI8 has_max_len =	(UI8)tag_reader.readUnsignedBits(1);
			UI8 has_font =		(UI8)tag_reader.readUnsignedBits(1);

			tag_reader.align();
			UI8 has_font_class =	(UI8)tag_reader.readUnsignedBits(1);
			UI8 auto_size =			(UI8)tag_reader.readUnsignedBits(1);
			UI8 has_layout =		(UI8)tag_reader.readUnsignedBits(1);
			UI8 no_select =			(UI8)tag_reader.readUnsignedBits(1);
			UI8 border =			(UI8)tag_reader.readUnsignedBits(1);
			UI8 was_static =		(UI8)tag_reader.readUnsignedBits(1);
			UI8 html_text =			(UI8)tag_reader.readUnsignedBits(1);
			UI8 use_glyph_font =	(UI8)tag_reader.readUnsignedBits(1);

			if(has_font)
			{
				// font id
				UI16 fontid = tag_reader.readUI16();
			}

			if(has_font_class)
			{
				// font as3 class
				String font_class = tag_reader.readString(true);
			}

			if(has_font)
			{
				// font height
				UI16 font_size = tag_reader.readUI16();
			}

			if(has_color)
			{
				// text color
				COLOR color;
				ParserHelper::readColorRGBA(tag_reader, false, color);
			}

			if(has_max_len)
			{
				// max text length
				tag_reader.readUI16();
			}

			if(has_layout)
			{
				tag_reader.readUI8();  // align (left = 0, right, center, justify)
				tag_reader.readUI16(); // left margin
				tag_reader.readUI16(); // right margin
				tag_reader.readUI16(); // ident
				tag_reader.readSI16(); // leading
			}

			// variable name
			tag_reader.readString(true);

			if(has_text)
			{
				// initial text
				String html_text = tag_reader.readString(true);
				edit_text->setInitialText(StringHelper::utf8Decode(html_text));
			}

			parser->getCurrentFile()->addResource(edit_text);
		}
		//-----------------------------------------------------------------------
	}
}
