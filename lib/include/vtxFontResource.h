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

#ifndef __vtxFontResource_H__
#define __vtxFontResource_H__

#include "vtxPrerequesites.h"
#include "vtxResource.h"

namespace vtx
{
	/** A Resource which contains all necessary data for rendering a font */
	class vtxExport FontResource : public Resource
	{
	public:
		friend class GlyphResource;

		typedef std::vector<GlyphResource*> GlyphList;
		typedef std::map<ushort, GlyphResource*> GlyphMap;

		FontResource(const String& id);
		virtual ~FontResource();

		/** @copybrief Resource::getType */
		const String& getType() const;

		/** Set the name associated with this font */
		void setName(const String& name);
		/** Get the name associated with this font */
		const String& getName() const;

		/** Set the ascender for this font */
		void setAscender(const float& ascender);
		/** Get the ascender of this font */
		const float& getAscender() const;

		/** Set the descender for this font */
		void setDescender(const float& descender);
		/** Get the descender of this font */
		const float& getDescender() const;

		/** Set the leading for this font */
		void setLeading(const float& leading);
		/** Get the leading of this font */
		const float& getLeading() const;

		/** Add a single GlyphResource to this font */
		void addGlyph(GlyphResource* glyph);
		/** Get a GlyphResource by its index */
		GlyphResource* getGlyphByIndex(const uint& index) const;
		/** Get a GlyphResource by its unicode */
		GlyphResource* getGlyphByCode(const ushort& char_code) const;
		/** Get a list of all glyphs contained within this font */
		const GlyphList& getGlyphList() const;

	protected:
		String mName;
		float mAscender;
		float mDescender;
		float mLeading;
		GlyphList mGlyphs;
		GlyphMap mCharGlyphMap;

		// TODO: refractor this, this should happen automatically when adding glyphs
		void _notifyGlyphCode(const ushort& code, GlyphResource* glyph);
	};
}

#endif
