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

#ifndef __vtxBoundingBox_H__
#define __vtxBoundingBox_H__

#include "vtxPrerequisites.h"
#include "vtxVector2.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** An axis-aligned bounding box */
	class vtxExport BoundingBox
	{
	public:
		enum Extent
		{
			EXTENT_NULL,
			EXTENT_FINITE,
			EXTENT_INFINITE
		};

		BoundingBox();
		BoundingBox(const Vector2& min, const Vector2& max);
		BoundingBox(
			const float& xmin, 
			const float& ymin, 
			const float& xmax, 
			const float& ymax);

		BoundingBox& operator=(const BoundingBox& bb)
		{
			setExtents(bb.getMin(), bb.getMax());
			return *this;
		}

		inline BoundingBox operator + (const Vector2& vec) const
		{
			return BoundingBox(
				Vector2(mMin.x+vec.x, mMin.y+vec.y), 
				Vector2(mMax.x+vec.x, mMax.y+vec.y));
		}

		inline void setExtents(const Vector2& min, const Vector2& max)
		{
			mExtent = EXTENT_FINITE;
			mMin = min;
			mMax = max;
		}

		void reset();
		/** Extend the boundaries of this box by the ones of another */
		void extend(const BoundingBox& bb);

		/** Transform the box using the given affine matrix */
		void transformAffine(const Matrix& m);

		/** Get the width of the box */
		float getWidth() const;
		/** Get the height of the box */
		float getHeight() const;

		/** Get the minimum coordinates */
		const Vector2& getMin() const;
		/** Get the maximum coordinates */
		const Vector2& getMax() const;

		/** Get the minimum x-coordinate */
		const float& getMinX() const;
		/** Get the maximum x-coordinate */
		const float& getMaxX() const;

		/** Get the minimum y-coordinate */
		const float& getMinY() const;
		/** Get the maximum y-coordinate */
		const float& getMaxY() const;

		/** Get the center of the box */
		Vector2 getCenter() const;
		/** Get the halved dimensions of the box */
		Vector2 getHalf() const;

	protected:
		Extent mExtent;
		Vector2 mMax, mMin;
	};
	//-----------------------------------------------------------------------
}

#endif
