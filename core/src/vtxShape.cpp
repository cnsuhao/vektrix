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

#include "vtxShape.h"
#include "vtxBoundingBox.h"
#include "vtxShapeResource.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	const String Shape::TYPE = "Shape";
	//-----------------------------------------------------------------------
	Shape::Shape()
	{

	}
	//-----------------------------------------------------------------------
	Shape::~Shape()
	{

	}
	//-----------------------------------------------------------------------
	void Shape::initFromResource(Resource* resource)
	{
		mShapeResource = dynamic_cast<ShapeResource*>(resource);

		if(mShapeResource)
		{
			setBoundingBox(mShapeResource->getBoundingBox());
		}
	}
	//-----------------------------------------------------------------------
	const String& Shape::getType() const
	{
		return TYPE;
	}
	//-----------------------------------------------------------------------
	bool Shape::isPointInside(const Vector2& coord)
	{
		if(coord.x >= mTransform.getWorldBounding().getMinX() && 
			coord.x <= mTransform.getWorldBounding().getMaxX() && 
			coord.y >= mTransform.getWorldBounding().getMinY() && 
			coord.y <= mTransform.getWorldBounding().getMaxY())
		{
			// point inside WorldBB
			return mShapeResource->_checkPointInside(
				mTransform.getWorldMatrix().transformInverse(coord));
		}

		return false;
	}
	//-----------------------------------------------------------------------
	void Shape::eventFired(const Event& evt)
	{

	}
	//-----------------------------------------------------------------------
}
