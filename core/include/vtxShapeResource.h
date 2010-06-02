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

#ifndef __vtxShapeResource_H__
#define __vtxShapeResource_H__

#include "vtxPrerequesites.h"
#include "vtxAtlasElement.h"
#include "vtxBoundingBox.h"
#include "vtxResource.h"

namespace vtx
{
	/** A Resource which contains all necessary data for creating a Shape instance */
	class vtxExport ShapeResource : public Resource, public AtlasElement
	{
	public:
		typedef std::vector<SubshapeResource*> SubshapeList;

		ShapeResource(const String& id);
		virtual ~ShapeResource();

		bool operator<(const ShapeResource& shape) const;
		bool operator>(const ShapeResource& shape) const;

		/** Check if a given point is located inside the boundaries of this shape */
		bool _checkPointInside(const Vector2& point);

		/** @copybrief Resource::getType */
		const String& getType() const;

		/** Get the area that the local BoundingBox of this shape occupies */
		const float getArea() const;

		/** Get the width of this shape */
		const float getWidth() const;
		/** Get the height of this shape */
		const float getHeight() const;

		// TODO: replace this by a "maximum scale" property

		/** Get the maximum width of this shape */
		const float getMaximumWidth() const;
		/** Get the maximum height of this shape */
		const float getMaximumHeight() const;

		/** Get the maximum power-of-two width of this shape */
		const uint getMaximumWidth_PoT() const;
		/** Get the maximum power-of-two height of this shape */
		const uint getMaximumHeight_PoT() const;

		/** Set the BoundingBox for this shape */
		void setBoundingBox(const BoundingBox& bb);
		/** Get the BoundingBox of this shape */
		const BoundingBox& getBoundingBox() const;

		/** Add a SubshapeResource to this shape */
		void addSubshapeResource(SubshapeResource* res);
		/** Get a list of all contained subshapes */
		const SubshapeList& getSubshapeList() const;

		/** Notify this shape about a scale value at which it was used */
		void _injectScale(const Vector2& scale);

		// AtlasElement
		/** @copybrief AtlasElement::getPackID */
		const String getPackID();
		/** @copybrief AtlasElement::getPackableWidth */
		const uint getPackableWidth();
		/** @copybrief AtlasElement::getPackableHeight */
		const uint getPackableHeight();

	protected:
		BoundingBox mBoundingBox;
		Vector2 mMaximumScale;
		SubshapeList mSubshapes;
	};
}

#endif
