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

#include "vtxBoundingBox.h"

#include "vtxMatrix.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	BoundingBox::BoundingBox() 
		: mExtent(EXTENT_NULL)
	{

	}
	//-----------------------------------------------------------------------
	BoundingBox::BoundingBox(const Vector2& min, const Vector2& max) 
		: mExtent(EXTENT_NULL), 
		mMin(min), 
		mMax(max)
	{

	}
	//-----------------------------------------------------------------------
	BoundingBox::BoundingBox(const float& xmin, const float& ymin, const float& xmax, const float& ymax) 
		: mExtent(EXTENT_NULL), 
		mMin(xmin, ymin), 
		mMax(xmax, ymax)
	{

	}
	//-----------------------------------------------------------------------
	void BoundingBox::reset()
	{
		mExtent = EXTENT_NULL;
	}
	//-----------------------------------------------------------------------
	void BoundingBox::extend(const BoundingBox& bb)
	{
		if(mExtent == EXTENT_NULL)
			setExtents(bb.getMin(), bb.getMax());

		else
		{
			mExtent = EXTENT_FINITE;
			mMin.x = (bb.getMinX() < mMin.x) ? bb.getMinX() : mMin.x;
			mMin.y = (bb.getMinY() < mMin.y) ? bb.getMinY() : mMin.y;

			mMax.x = (bb.getMaxX() > mMax.x) ? bb.getMaxX() : mMax.x;
			mMax.y = (bb.getMaxY() > mMax.y) ? bb.getMaxY() : mMax.y;
		}
	}
	//-----------------------------------------------------------------------
	void BoundingBox::extend(const Vector2& vec)
	{
		if(mExtent == EXTENT_NULL)
			setExtents(vec, vec);

		else
		{
			mExtent = EXTENT_FINITE;
			mMin.x = (vec.x < mMin.x) ? vec.x : mMin.x;
			mMin.y = (vec.y < mMin.y) ? vec.y : mMin.y;

			mMax.x = (vec.x > mMax.x) ? vec.x : mMax.x;
			mMax.y = (vec.y > mMax.y) ? vec.y : mMax.y;
		}
	}
	//-----------------------------------------------------------------------
	void BoundingBox::transformAffine(const Matrix& m)
	{
		if(mExtent != EXTENT_FINITE)
			return;

		Vector2 half = getHalf();
		Vector2 center = m.transformAffine(getCenter());
		Vector2 newHalfSize(
			fabs(m.m[0][0]) * half.x + fabs(m.m[0][1]) * half.y, 
			fabs(m.m[1][0]) * half.x + fabs(m.m[1][1]) * half.y);

		setExtents(center - newHalfSize, center + newHalfSize);
	}
	//-----------------------------------------------------------------------
	float BoundingBox::getWidth() const
	{
		return abs(mMax.x - mMin.x);
	}
	//-----------------------------------------------------------------------
	float BoundingBox::getHeight() const
	{
		return abs(mMax.y - mMin.y);
	}
	//-----------------------------------------------------------------------
	const Vector2& BoundingBox::getMin() const
	{
		return mMin;
	}
	//-----------------------------------------------------------------------
	const Vector2& BoundingBox::getMax() const
	{
		return mMax;
	}
	//-----------------------------------------------------------------------
	const float& BoundingBox::getMinX() const
	{
		return mMin.x;
	}
	//-----------------------------------------------------------------------
	const float& BoundingBox::getMaxX() const
	{
		return mMax.x;
	}
	//-----------------------------------------------------------------------
	const float& BoundingBox::getMinY() const
	{
		return mMin.y;
	}
	//-----------------------------------------------------------------------
	const float& BoundingBox::getMaxY() const
	{
		return mMax.y;
	}
	//-----------------------------------------------------------------------
	Vector2 BoundingBox::getCenter() const
	{
		return Vector2(
			(mMax.x + mMin.x) * 0.5f,
			(mMax.y + mMin.y) * 0.5f);
	}
	//-----------------------------------------------------------------------
	Vector2 BoundingBox::getHalf() const
	{
		return (mMax - mMin) * 0.5f;
	}
	//-----------------------------------------------------------------------
}
