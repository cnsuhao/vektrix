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

#include "vtxEditTextResource.h"
#include "vtxStringHelper.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		void SwfParser::handleDefineEditText(const TagTypes& type)
		{
			UI16 id = readU16();
			RECT bounds = readRect();

			EditTextResource* edit_text = new EditTextResource(StringHelper::toString(id));

			BoundingBox box(
				Vector2(bounds.xmin/20.0f, bounds.ymin/20.0f), 
				Vector2(bounds.xmax/20.0f, bounds.ymax/20.0f));

			edit_text->setBoundingBox(box);

			resetReadBits();
			UI8 has_text =		readUBits(1);
			UI8 word_wrap =		readUBits(1);
			UI8 multi_line =	readUBits(1);
			UI8 password =		readUBits(1);
			UI8 read_only =		readUBits(1);
			UI8 has_color =		readUBits(1);
			UI8 has_max_len =	readUBits(1);
			UI8 has_font =		readUBits(1);

			resetReadBits();
			UI8 has_font_class =	readUBits(1);
			UI8 auto_size =			readUBits(1);
			UI8 has_layout =		readUBits(1);
			UI8 no_select =			readUBits(1);
			UI8 border =			readUBits(1);
			UI8 was_static =		readUBits(1);
			UI8 html_text =			readUBits(1);
			UI8 use_glyph_font =	readUBits(1);

			if(has_font)
			{
				// font id
				UI16 fontid = readU16();
			}

			if(has_font_class)
			{
				// font as3 class
				String font_class = readString();
			}

			if(has_font)
			{
				// font height
				UI16 font_size = readU16();
			}

			if(has_color)
			{
				// text color
				COLOR color = readColor(true);
			}

			if(has_max_len)
			{
				// max text length
				readU16();
			}

			if(has_layout)
			{
				readU8(); // align (left = 0, right, center, justify)
				readU16(); // left margin
				readU16(); // right margin
				readU16(); // ident
				readS16(); // leading
			}

			// variable name
			readString();

			if(has_text)
			{
				// initial text
				String html_text = readString();
				edit_text->setInitialText(StringHelper::utf8Decode(html_text));
			}

			mCurrentFile->addResource(edit_text);
		}
		//-----------------------------------------------------------------------
	}
}
