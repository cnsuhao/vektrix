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

#ifndef __vtxGlyphResource_H__
#define __vtxGlyphResource_H__

#include "vtxPrerequisites.h"
#include "vtxBoundingBox.h"
#include "vtxShapeElement.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** A Resource which contains information about a single glyph contained within a FontResource */
	class vtxExport GlyphResource
	{
	public:
		GlyphResource(FontResource* parent);
		virtual ~GlyphResource();

		/** Set the index for this glyph */
		void setIndex(const uint& index);
		/** Get the index of this glyph */
		const uint& getIndex() const;

		/** Set the unicode for this glyph */
		void setCode(const ushort& code);
		/** Get the unicode of this glyph */
		const ushort& getCode() const;

		/** Set the vertical advance value for this glyph */
		const float& getAdvance() const;
		/** Get the vertical advance value of this glyph */
		void setAdvance(const float& advance);

		/** Add a ShapeElement to the outline of this glyph */
		void addShapeElement(ShapeElement element, const bool& auto_extend_bb = true);
		/** Get a list of all contained shape elements */
		const ShapeElementList& getElementList() const;

		/** Set the BoundingBox for this glyph */
		void setBoundingBox(const BoundingBox& bb);
		/** Get the BoundingBox of this glyph */
		const BoundingBox& getBoundingBox() const;

		/** Get the FontResource that this glyph belongs to */
		FontResource* getParentFont() const;

	protected:
		uint mIndex;
		ushort mCode;
		float mAdvance;
		BoundingBox mBoundingBox;
		FontResource* mParent;
		ShapeElementList mShapeElements;
	};
	//-----------------------------------------------------------------------
}

#endif
