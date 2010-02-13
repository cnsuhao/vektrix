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

#include "vtxStaticTextResource.h"
#include "vtxStringHelper.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		void SwfParser::handleDefineText(const TagTypes& type)
		{
			UI16 id = readU16();
			RECT bounds = readRect();
			MATRIX transform = readMatrix();

			UI8 glyph_bits = readU8();
			UI8 advance_bits = readU8();

			StaticTextResource* statictext = new StaticTextResource(StringHelper::toString(id));

			BoundingBox box(
				Vector2(bounds.xmin/20.0f, bounds.ymin/20.0f), 
				Vector2(bounds.xmax/20.0f, bounds.ymax/20.0f));

			statictext->setBoundingBox(box);

			StaticTextResource::GlyphStripList glyphs;
			StaticTextResource::GlyphStrip glyph_strip;

			TextRecordList records;
			while(true)
			{
				UI8 flags = readU8();

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
					text_record.font_id = readU16();
					glyph_strip.fontid = StringHelper::toString(text_record.font_id);
				}
				// has color
				if(flags & 4)
				{
					text_record.color = readColor(type == TT_DefineText2);
					glyph_strip.color = Color(
						(float)text_record.color.red/255.0f, 
						(float)text_record.color.green/255.0f, 
						(float)text_record.color.blue/255.0f, 
						(float)text_record.color.alpha/255.0f);
				}
				// has x offset
				if(flags & 1)
				{
					text_record.x = readS16();
					glyph_strip.x = text_record.x / 20.0f;
				}
				// has y offset
				if(flags & 2)
				{
					text_record.y = readS16();
					glyph_strip.y = text_record.y / 20.0f;
					glyph_strip.newline = true;
				}
				// has font -> text height
				if(flags & 8)
				{
					text_record.size = readU16();
					glyph_strip.size = text_record.size / 20.0f;
				}

				resetReadBits();

				// Glyph Entries
				UI8 glyph_count = readU8();
				for(UI8 i=0; i<glyph_count; ++i)
				{
					GLYPHENTRY entry;
					entry.index = readUBits(glyph_bits);
					entry.x_advance = readSBits(advance_bits);

					StaticTextResource::Glyph glyph;
					glyph.index = entry.index;
					glyph.x = entry.x_advance / 20.0f;

					// add glyph to strip
					glyph_strip.glyphs.push_back(glyph);
				}

				records.push_back(text_record);

				// add strip to list
				glyphs.push_back(glyph_strip);

			} // while(TextRecords)

			statictext->setGlyphStrips(glyphs);
			mCurrentFile->addResource(statictext);
		}
		//-----------------------------------------------------------------------
	}
}
