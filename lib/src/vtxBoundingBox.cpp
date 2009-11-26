/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009 Fuse-Software (tm)

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/
#include "vtxBoundingBox.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	BoundingBox::BoundingBox() 
		: mExtent(EXTENT_NULL), 
		mMin(Vector2()), 
		mMax(Vector2())
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
	void BoundingBox::reset()
	{
		mExtent = EXTENT_NULL;
	}
	//-----------------------------------------------------------------------
	void BoundingBox::extend(const BoundingBox& bb)
	{
		if(mExtent == EXTENT_NULL)
		{
			setExtents(bb.getMin(), bb.getMax());
		}
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
	const float BoundingBox::getWidth() const
	{
		return (mMax.x - mMin.x);
	}
	//-----------------------------------------------------------------------
	const float BoundingBox::getHeight() const
	{
		return (mMax.y - mMin.y);
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
	Vector2 BoundingBox::getHalf() const
	{
		return (mMax - mMin) * 0.5f;
	}
	//-----------------------------------------------------------------------
}
