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
	class vtxExport FontResource : public Resource
	{
	public:
		friend class GlyphResource;

		typedef std::vector<GlyphResource*> GlyphList;
		typedef std::map<ushort, GlyphResource*> GlyphMap;

		FontResource(const String& id);
		virtual ~FontResource();

		const String& getType() const;

		void setName(const String& name);
		const String& getName() const;

		void addGlyph(GlyphResource* glyph);
		GlyphResource* getGlyphByIndex(const uint& index) const;
		GlyphResource* getGlyphByCode(const ushort& char_code) const;
		const GlyphList& getGlyphList() const;

	protected:
		String mName;
		GlyphList mGlyphs;
		GlyphMap mCharGlyphMap;

		void _notifyGlyphCode(const ushort& code, GlyphResource* glyph);
	};
}

#endif
