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

#include "vtxMovableObject.h"
#include "vtxDisplayObjectContainer.h"
#include "vtxLogManager.h"
#include "vtxMovie.h"
#include "vtxMovieDebugger.h"
#include "vtxScriptObject.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	MovableObject::MovableObject(Resource* resource) 
		: Instance(resource), 
		mParentContainer(NULL)
	{

	}
	//-----------------------------------------------------------------------
	MovableObject::~MovableObject()
	{

	}
	//-----------------------------------------------------------------------
	void MovableObject::setX(const float& x)
	{
		mTransform.setX(x);
	}
	//-----------------------------------------------------------------------
	const float& MovableObject::getX() const
	{
		return mTransform.getX();
	}
	//-----------------------------------------------------------------------
	void MovableObject::setY(const float& y)
	{
		mTransform.setY(y);
	}
	//-----------------------------------------------------------------------
	const float& MovableObject::getY() const
	{
		return mTransform.getY();
	}
	//-----------------------------------------------------------------------
	void MovableObject::setAngle(const float& angle)
	{
		mTransform.setAngle(angle);
	}
	//-----------------------------------------------------------------------
	const float& MovableObject::getAngle() const
	{
		return mTransform.getAngle();
	}
	//-----------------------------------------------------------------------
	void MovableObject::setMatrix(const Matrix& m)
	{
		mTransform.setMatrix(m);
	}
	//-----------------------------------------------------------------------
	const Matrix& MovableObject::getMatrix() const
	{
		return mTransform.getMatrix();
	}
	//-----------------------------------------------------------------------
	void MovableObject::setCXForm(const CXForm& cx)
	{
		mTransform.setColor(cx);
	}
	//-----------------------------------------------------------------------
	void MovableObject::setParentContainer(DisplayObjectContainer* parent)
	{
		mParentContainer = parent;
		mTransform.setBounding(getBoundingBox());
		_update(0);
	}
	//-----------------------------------------------------------------------
	const Matrix& MovableObject::getWorldMatrix()
	{
		return mTransform.getWorldMatrix();
	}
	//-----------------------------------------------------------------------
	const BoundingBox& MovableObject::getWorldBoundingBox()
	{
		return mTransform.getWorldBounding();
	}
	//-----------------------------------------------------------------------
	void MovableObject::needColorUpdate()
	{
		mTransform.needColorUpdate();
	}
	//-----------------------------------------------------------------------
	void MovableObject::needMatrixUpdate()
	{
		mTransform.needMatrixUpdate();
	}
	//-----------------------------------------------------------------------
	void MovableObject::_update(const float& delta_time)
	{
		mTransform.update(mParentContainer);

		MovieDebugger* debugger = mParentMovie->getDebugger();
		if(debugger)
		{
			debugger->debugObjectBoundingBox(mTransform.getWorldBounding());
		}
	}
	//-----------------------------------------------------------------------
	Transform& MovableObject::getTransform()
	{
		return mTransform;
	}
	//-----------------------------------------------------------------------
}
