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
#pragma once

#include "vtxPrerequesites.h"
#include "vtxVector2.h"

namespace vtx
{
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
		void extend(const BoundingBox& bb);

		const float getWidth() const;
		const float getHeight() const;

		const Vector2& getMin() const;
		const Vector2& getMax() const;

		const float& getMinX() const;
		const float& getMaxX() const;

		const float& getMinY() const;
		const float& getMaxY() const;

		Vector2 getHalf() const;

	protected:
		Extent mExtent;
		Vector2 mMax, mMin;
	};
}
