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

#include "vtxDisplayObject.h"
#include "vtxDisplayObjectContainer.h"
#include "vtxLogManager.h"
#include "vtxMovie.h"
#include "vtxMovieDebugger.h"
#include "vtxScriptObject.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	DisplayObject::DisplayObject() 
		: mParentContainer(NULL)
	{

	}
	//-----------------------------------------------------------------------
	DisplayObject::~DisplayObject()
	{

	}
	//-----------------------------------------------------------------------
	bool DisplayObject::isDisplayObject() const
	{
		return true;
	}
	//-----------------------------------------------------------------------
	void DisplayObject::setX(const float& x)
	{
		mTransform.setX(x);
	}
	//-----------------------------------------------------------------------
	const float& DisplayObject::getX() const
	{
		return mTransform.getX();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::setY(const float& y)
	{
		mTransform.setY(y);
	}
	//-----------------------------------------------------------------------
	const float& DisplayObject::getY() const
	{
		return mTransform.getY();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::setAngle(const float& angle)
	{
		mTransform.setAngle(angle);
	}
	//-----------------------------------------------------------------------
	const float& DisplayObject::getAngle() const
	{
		return mTransform.getAngle();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::setScaleX(const float& scale)
	{
		mTransform.setScaleX(scale);
	}
	//-----------------------------------------------------------------------
	const float& DisplayObject::getScaleX() const
	{
		return mTransform.getScaleX();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::setScaleY(const float& scale)
	{
		mTransform.setScaleY(scale);
	}
	//-----------------------------------------------------------------------
	const float& DisplayObject::getScaleY() const
	{
		return mTransform.getScaleY();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::setLayer(const uint& layer)
	{
		mTransform.setLayer(layer);
	}
	//-----------------------------------------------------------------------
	const uint& DisplayObject::getLayer() const
	{
		return mTransform.getLayer();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::setCXForm(const CXForm& cx)
	{
		mTransform.setColor(cx);
	}
	//-----------------------------------------------------------------------
	void DisplayObject::setMatrix(const Matrix& m)
	{
		mTransform.setMatrix(m);
	}
	//-----------------------------------------------------------------------
	const Matrix& DisplayObject::getMatrix() const
	{
		return mTransform.getMatrix();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::setWidth(const float& width)
	{
		mTransform.setWidth(width);
	}
	//-----------------------------------------------------------------------
	float DisplayObject::getWidth() const
	{
		return mTransform.getWidth();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::setHeight(const float& height)
	{
		mTransform.setHeight(height);
	}
	//-----------------------------------------------------------------------
	float DisplayObject::getHeight() const
	{
		return mTransform.getHeight();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::setVisible(const bool& visible)
	{
		// TODO: implement this
	}
	//-----------------------------------------------------------------------
	bool DisplayObject::getVisible() const
	{
		// TODO: implement this
		return true;
	}
	//-----------------------------------------------------------------------
	void DisplayObject::setBoundingBox(const BoundingBox& bb)
	{
		mTransform.setBounding(bb);
	}
	//-----------------------------------------------------------------------
	const BoundingBox& DisplayObject::getBoundingBox() const
	{
		return mTransform.getBounding();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::setParentContainer(DisplayObjectContainer* parent)
	{
		mParentContainer = parent;
		mTransform.setParentContainer(parent);
		mTransform.setBounding(getBoundingBox());
		_update(0);
	}
	//-----------------------------------------------------------------------
	DisplayObjectContainer* DisplayObject::getParentContainer() const
	{
		return mParentContainer;
	}
	//-----------------------------------------------------------------------
	const BoundingBox& DisplayObject::getWorldBoundingBox()
	{
		return mTransform.getWorldBounding();
	}
	//-----------------------------------------------------------------------
	const Matrix& DisplayObject::getWorldMatrix()
	{
		return mTransform.getWorldMatrix();
	}
	//-----------------------------------------------------------------------
	const uint& DisplayObject::getZOrder()
	{
		return mTransform.getZOrder();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::needColorUpdate()
	{
		mTransform.needColorUpdate();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::needMatrixUpdate()
	{
		mTransform.needMatrixUpdate();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::_update(const float& delta_time)
	{
		mTransform.update();

		if(mParentMovie)
		{
			MovieDebugger* debugger = mParentMovie->getDebugger();
			if(debugger)
			{
				debugger->debugBoundingBox(mTransform.getWorldBounding());
			}
		}
	}
	//-----------------------------------------------------------------------
	Transform& DisplayObject::getTransform()
	{
		return mTransform;
	}
	//-----------------------------------------------------------------------
	/*void DisplayObject::initScriptObject()
	{
		//if(mParentContainer && mName.length())
		//{
		//	mParentContainer->getScriptObject()->setChildObject(mName, mScriptObject);
		//}

		Instance::initScriptObject();
	}*/
	//-----------------------------------------------------------------------
}
