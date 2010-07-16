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

#include "vtxShapeResource.h"

#include "vtxFileManager.h"
#include "vtxFileContainer.h"
#include "vtxFileStream.h"
#include "vtxMathHelper.h"
#include "vtxShapeElement.h"
#include "vtxSubshapeResource.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	ShapeResource::ShapeResource(const String& id) 
		: Resource(id), 
		mMaximumScale(Vector2(1, 1))
	{

	}
	//-----------------------------------------------------------------------
	ShapeResource::~ShapeResource()
	{
		SubshapeList::iterator it = mSubshapes.begin();
		SubshapeList::iterator end = mSubshapes.end();
		while(it != end)
		{
			delete *it;
			++it;
		}
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
	bool ShapeResource::_checkPointInside(const Vector2& point)
	{
		SubshapeList::iterator it = mSubshapes.begin();
		SubshapeList::iterator end = mSubshapes.end();

		bool inside = false;

		while(it != end)
		{
			SubshapeResource* subshape = *it;

			ShapeElementList elem_list = subshape->getElementList();
			ShapeElementList::iterator elem_it = elem_list.begin();
			ShapeElementList::iterator elem_end = elem_list.end();

			ShapeElement& prev_element = *elem_it;
			++elem_it;

			while(elem_it != elem_end)
			{
				ShapeElement& element = *elem_it;

				if(elem_it != elem_list.begin() && 
					element.type == ShapeElement::SID_MOVE_TO)
				{
					prev_element = element;
					++elem_it;
					element = *elem_it;
				}

				const Vector2& prev_pos = prev_element.pos;
				const Vector2& curr_pos = element.pos;

				if(
					((curr_pos.y <= point.y && point.y < prev_pos.y) || 
					(prev_pos.y <= point.y && point.y < curr_pos.y)) && 
					(point.x < (prev_pos.x - curr_pos.x) * (point.y - curr_pos.y) / (prev_pos.y - curr_pos.y) + curr_pos.x)
					)
				{
					inside = !inside;
				}

				prev_element = element;
				++elem_it;
			}

			++it;
		}

		return inside;
	}
	//-----------------------------------------------------------------------
	const String& ShapeResource::getType() const
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
