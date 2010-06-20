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
#include "vtxswfTagEditText.h"
#include "vtxswfParser.h"
#include "vtxEditTextResource.h"
#include "vtxStringHelper.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfTagEditText::SwfTagEditText(uint tag_length, uchar* tag_data)
			: SwfTag(TT_DefineEditText, tag_length, tag_data)
		{}
		//-----------------------------------------------------------------------
		SwfTagEditText::~SwfTagEditText()
		{}
		//-----------------------------------------------------------------------
		void SwfTagEditText::ParseData(SwfParser* parser)
		{
			UI16 id = parser->readU16();
			RECT bounds = parser->readRect();

			EditTextResource* edit_text = new EditTextResource(StringHelper::toString(id));

			BoundingBox box(
				Vector2(bounds.xmin/20.0f, bounds.ymin/20.0f), 
				Vector2(bounds.xmax/20.0f, bounds.ymax/20.0f));

			edit_text->setBoundingBox(box);

			parser->resetReadBits();
			UI8 has_text =		parser->readUBits(1);
			UI8 word_wrap =		parser->readUBits(1);
			UI8 multi_line =	parser->readUBits(1);
			UI8 password =		parser->readUBits(1);
			UI8 read_only =		parser->readUBits(1);
			UI8 has_color =		parser->readUBits(1);
			UI8 has_max_len =	parser->readUBits(1);
			UI8 has_font =		parser->readUBits(1);

			parser->resetReadBits();
			UI8 has_font_class =	parser->readUBits(1);
			UI8 auto_size =			parser->readUBits(1);
			UI8 has_layout =		parser->readUBits(1);
			UI8 no_select =			parser->readUBits(1);
			UI8 border =			parser->readUBits(1);
			UI8 was_static =		parser->readUBits(1);
			UI8 html_text =			parser->readUBits(1);
			UI8 use_glyph_font =	parser->readUBits(1);

			if(has_font)
			{
				// font id
				UI16 fontid = parser->readU16();
			}

			if(has_font_class)
			{
				// font as3 class
				String font_class = parser->readString();
			}

			if(has_font)
			{
				// font height
				UI16 font_size = parser->readU16();
			}

			if(has_color)
			{
				// text color
				COLOR color = parser->readColor(true);
			}

			if(has_max_len)
			{
				// max text length
				parser->readU16();
			}

			if(has_layout)
			{
				parser->readU8(); // align (left = 0, right, center, justify)
				parser->readU16(); // left margin
				parser->readU16(); // right margin
				parser->readU16(); // ident
				parser->readS16(); // leading
			}

			// variable name
			parser->readString();

			if(has_text)
			{
				// initial text
				String html_text = parser->readString();
				edit_text->setInitialText(StringHelper::utf8Decode(html_text));
			}

			parser->getCurrentFile()->addResource(edit_text);
		}
		//-----------------------------------------------------------------------
	}
}
