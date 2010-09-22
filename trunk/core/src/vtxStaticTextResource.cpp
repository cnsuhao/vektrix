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

#include "vtxStaticTextResource.h"
#include "vtxFile.h"
#include "vtxFontResource.h"
#include "vtxGlyphResource.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	StaticTextResource::StaticTextResource(const String& id) 
		: Resource(id)
	{

	}
	//-----------------------------------------------------------------------
	StaticTextResource::~StaticTextResource()
	{

	}
	//-----------------------------------------------------------------------
	const String& StaticTextResource::getType() const
	{
		static String type = "StaticText";
		return type;
	}
	//-----------------------------------------------------------------------
	WString StaticTextResource::getText() const
	{
		WString text;

		GlyphStripList::const_iterator it = mGlyphStrips.begin();
		GlyphStripList::const_iterator end = mGlyphStrips.end();
		while(it != end)
		{
			const GlyphStrip& strip = *it;
			FontResource* font = static_cast<FontResource*>(mParent->getResource(strip.fontid, "Font"));
			if(!font)
			{
				++it;
				continue;
			}

			GlyphStrip::GlyphList::const_iterator glyph_it = strip.glyphs.begin();
			GlyphStrip::GlyphList::const_iterator glyph_end = strip.glyphs.end();
			while(glyph_it != glyph_end)
			{
				const GlyphStrip::Glyph& glyph = *glyph_it;

				GlyphResource* glyph_res = font->getGlyphByIndex(glyph.index);
				text.append(1, glyph_res->getCode());
				++glyph_it;
			}

			++it;
		}

		return text;
	}
	//-----------------------------------------------------------------------
	void StaticTextResource::setBoundingBox(const BoundingBox& bb)
	{
		mBoundingBox = bb;
	}
	//-----------------------------------------------------------------------
	const BoundingBox& StaticTextResource::getBoundingBox() const
	{
		return mBoundingBox;
	}
	//-----------------------------------------------------------------------
	void StaticTextResource::setGlyphStrips(const GlyphStripList& glyphstrips)
	{
		mGlyphStrips = glyphstrips;
	}
	//-----------------------------------------------------------------------
	const GlyphStripList& StaticTextResource::getGlyphStrips() const
	{
		return mGlyphStrips;
	}
	//-----------------------------------------------------------------------
}