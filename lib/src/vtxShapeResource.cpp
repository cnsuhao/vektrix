/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/vektrix

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
#include "vtxShapeResource.h"

#include "vtxFileManager.h"
#include "vtxFileContainerFactory.h"
#include "vtxFileStream.h"
#include "vtxMathHelper.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	ShapeResource::ShapeResource(const String& id, const String& file) 
		: Resource(id), 
		mFilename(file), 
		mMaximumScale(Vector2(1, 1))
	{

	}
	//-----------------------------------------------------------------------
	bool ShapeResource::operator<(const ShapeResource& shape) const
	{
		return getArea() < shape.getArea();
	}
	//-----------------------------------------------------------------------
	bool ShapeResource::operator>(const ShapeResource& shape) const
	{
		return getArea() > shape.getArea();
	}
	//-----------------------------------------------------------------------
	const String& ShapeResource::getType(void) const
	{
		static String type = "Shape";
		return type;
	}
	//-----------------------------------------------------------------------
	const float ShapeResource::getArea() const
	{
		return getWidth() * getHeight();
	}
	//-----------------------------------------------------------------------
	const float ShapeResource::getWidth() const
	{
		return mBoundingBox.getWidth();
	}
	//-----------------------------------------------------------------------
	const float ShapeResource::getHeight() const
	{
		return mBoundingBox.getHeight();
	}
	//-----------------------------------------------------------------------
	const float ShapeResource::getMaximumWidth() const
	{
		return mMaximumScale.x * getWidth();
	}
	//-----------------------------------------------------------------------
	const float ShapeResource::getMaximumHeight() const
	{
		return mMaximumScale.y * getHeight();
	}
	//-----------------------------------------------------------------------
	const uint ShapeResource::getMaximumWidth_PoT() const
	{
		return MathHelper::findClosestPowerOfTwo(getMaximumWidth());
	}
	//-----------------------------------------------------------------------
	const uint ShapeResource::getMaximumHeight_PoT() const
	{
		return MathHelper::findClosestPowerOfTwo(getMaximumHeight());
	}
	//-----------------------------------------------------------------------
	void ShapeResource::setBoundingBox(const BoundingBox& bb)
	{
		mBoundingBox = bb;
	}
	//-----------------------------------------------------------------------
	const BoundingBox& ShapeResource::getBoundingBox() const
	{
		return mBoundingBox;
	}
	//-----------------------------------------------------------------------
	void ShapeResource::addSubshapeResource(SubshapeResource* res)
	{
		mSubshapes.push_back(res);
	}
	//-----------------------------------------------------------------------
	const ShapeResource::SubshapeList& ShapeResource::getSubshapeList() const
	{
		return mSubshapes;
	}
	//-----------------------------------------------------------------------
	void ShapeResource::_injectScale(const Vector2& scale)
	{
		if(scale.x > mMaximumScale.x)
		{
			mMaximumScale.x = scale.x;
		}

		if(scale.y > mMaximumScale.y)
		{
			mMaximumScale.y = scale.y;
		}
	}
	//-----------------------------------------------------------------------
}
