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

#include "vtxFontResource.h"
#include "vtxGlyphResource.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	FontResource::FontResource(const String& id) 
		: Resource(id), 
		mAscender(0.0f), 
		mDescender(0.0f), 
		mLeading(0.0f)
	{

	}
	//-----------------------------------------------------------------------
	FontResource::~FontResource()
	{
		GlyphList::iterator it = mGlyphs.begin();
		GlyphList::iterator end = mGlyphs.end();
		while(it != end)
		{
			delete *it;
			++it;
		}
	}
	//-----------------------------------------------------------------------
	const String& FontResource::getType() const
	{
		static String type = "Font";
		return type;
	}
	//-----------------------------------------------------------------------
	void FontResource::setName(const String& name)
	{
		mName = name;
	}
	//-----------------------------------------------------------------------
	const String& FontResource::getName() const
	{
		return mName;
	}
	//-----------------------------------------------------------------------
	void FontResource::setAscender(const float& ascender)
	{
		mAscender = ascender;
	}
	//-----------------------------------------------------------------------
	const float& FontResource::getAscender() const
	{
		return mAscender;
	}
	//-----------------------------------------------------------------------
	void FontResource::setDescender(const float& descender)
	{
		mDescender = descender;
	}
	//-----------------------------------------------------------------------
	const float& FontResource::getDescender() const
	{
		return mDescender;
	}
	//-----------------------------------------------------------------------
	void FontResource::setLeading(const float& leading)
	{
		mLeading = leading;
	}
	//-----------------------------------------------------------------------
	const float& FontResource::getLeading() const
	{
		return mLeading;
	}
	//-----------------------------------------------------------------------
	void FontResource::addGlyph(GlyphResource* glyph)
	{
		mGlyphs.push_back(glyph);

		// glyph has got a character assigned
		if(glyph->getCode())
		{
			mCharGlyphMap[glyph->getCode()] = glyph;
		}
	}
	//-----------------------------------------------------------------------
	GlyphResource* FontResource::getGlyphByIndex(const uint& index) const
	{
		if(index < 0 || index > mGlyphs.size()-1)
		{
			return NULL;
		}

		return mGlyphs.at(index);
	}
	//-----------------------------------------------------------------------
	GlyphResource* FontResource::getGlyphByCode(const ushort& char_code) const
	{
		GlyphMap::const_iterator it = mCharGlyphMap.find(char_code);
		if(it != mCharGlyphMap.end())
		{
			return it->second;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	const FontResource::GlyphList& FontResource::getGlyphList() const
	{
		return mGlyphs;
	}
	//-----------------------------------------------------------------------
	void FontResource::_notifyGlyphCode(const ushort& code, GlyphResource* glyph)
	{
		mCharGlyphMap[code] = glyph;
	}
	//-----------------------------------------------------------------------
}
