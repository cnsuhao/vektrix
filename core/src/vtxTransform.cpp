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

#include "vtxTransform.h"
#include "vtxDisplayObjectContainer.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	Transform::Transform() 
		: mParentContainer(NULL), 
		mAngle(0.0f), 
		mScale(1.0f, 1.0f), 
		mLayer(0), 
		mWorldZOrder(0), 
		mNeedColorUpdate(true), 
		mNeedMatrixUpdate(true), 
		mNeedMatrixCompose(false)
	{

	}
	//-----------------------------------------------------------------------
	Transform::~Transform()
	{

	}
	//-----------------------------------------------------------------------
	void Transform::setParentContainer(DisplayObjectContainer* parent)
	{
		mParentContainer = parent;
	}
	//-----------------------------------------------------------------------
	void Transform::setX(const float& x)
	{
		mPosition.x = x;
		needMatrixCompose();
		needMatrixUpdate();
	}
	//-----------------------------------------------------------------------
	const float& Transform::getX() const
	{
		return mPosition.x;
	}
	//-----------------------------------------------------------------------
	void Transform::setY(const float& y)
	{
		mPosition.y = y;
		needMatrixCompose();
		needMatrixUpdate();
	}
	//-----------------------------------------------------------------------
	const float& Transform::getY() const
	{
		return mPosition.y;
	}
	//-----------------------------------------------------------------------
	void Transform::setAngle(const float& angle)
	{
		mAngle = angle;
		needMatrixCompose();
		needMatrixUpdate();
	}
	//-----------------------------------------------------------------------
	const float& Transform::getAngle() const
	{
		return mAngle;
	}
	//-----------------------------------------------------------------------
	void Transform::setScaleX(const float& scale)
	{
		mScale.x = scale;
		needMatrixCompose();
		needMatrixUpdate();
	}
	//-----------------------------------------------------------------------
	const float& Transform::getScaleX() const
	{
		return mScale.x;
	}
	//-----------------------------------------------------------------------
	void Transform::setScaleY(const float& scale)
	{
		mScale.y = scale;
		needMatrixCompose();
		needMatrixUpdate();
	}
	//-----------------------------------------------------------------------
	const float& Transform::getScaleY() const
	{
		return mScale.y;
	}
	//-----------------------------------------------------------------------
	void Transform::setWidth(const float& width)
	{

	}
	//-----------------------------------------------------------------------
	const float Transform::getWidth() const
	{
		return mBounding.getWidth() * mScale.x;
	}
	//-----------------------------------------------------------------------
	void Transform::setHeight(const float& width)
	{

	}
	//-----------------------------------------------------------------------
	const float Transform::getHeight() const
	{
		return mBounding.getHeight() * mScale.y;
	}
	//-----------------------------------------------------------------------
	void Transform::setLayer(const uint& layer)
	{
		mLayer = layer;
	}
	//-----------------------------------------------------------------------
	const uint& Transform::getLayer() const
	{
		return mLayer;
	}
	//-----------------------------------------------------------------------
	void Transform::setColor(const CXForm& cx)
	{
		mCxForm = cx;
		needColorUpdate();
	}
	//-----------------------------------------------------------------------
	const CXForm& Transform::getColor() const
	{
		return mCxForm;
	}
	//-----------------------------------------------------------------------
	void Transform::setMatrix(const Matrix& m)
	{
		mMatrix = m;

		decomposeMatrix();
		// TODO: check robustness of matrix decomposition
		needMatrixCompose();
		needMatrixUpdate();
	}
	//-----------------------------------------------------------------------
	const Matrix& Transform::getMatrix() const
	{
		return mMatrix;
	}
	//-----------------------------------------------------------------------
	void Transform::setBounding(const BoundingBox& bb)
	{
		mBounding = bb;
	}
	//-----------------------------------------------------------------------
	const BoundingBox& Transform::getBounding() const
	{
		return mBounding;
	}
	//-----------------------------------------------------------------------
	void Transform::needColorUpdate()
	{
		mNeedColorUpdate = true;
	}
	//-----------------------------------------------------------------------
	void Transform::needMatrixUpdate()
	{
		mNeedMatrixUpdate = true;
	}
	//-----------------------------------------------------------------------
	void Transform::update()
	{
		if(mNeedMatrixCompose)
		{
			composeMatrix();
		}

		if(mNeedMatrixUpdate)
		{
			updateMatrix();
		}
	}
	//-----------------------------------------------------------------------
	BoundingBox& Transform::getWorldBounding()
	{
		return mWorldBounding;
	}
	//-----------------------------------------------------------------------
	const CXForm& Transform::getWorldColor() const
	{
		return mWorldColor;
	}
	//-----------------------------------------------------------------------
	const Matrix& Transform::getWorldMatrix() const
	{
		return mWorldMatrix;
	}
	//-----------------------------------------------------------------------
	const uint& Transform::getZOrder()
	{
		mWorldZOrder = 0;

		if(mParentContainer)
		{
			mWorldZOrder = mParentContainer->getZOrder();

			const DisplayObjectContainer::LayerMap& layers = mParentContainer->getLayers();
			DisplayObjectContainer::LayerMap::const_iterator it = layers.begin();
			DisplayObjectContainer::LayerMap::const_iterator end = layers.end();

			while(it != end && it->first <= mLayer)
			{
				++mWorldZOrder;
				++it;
			}
			//for(uint i=0; i <= mLayer; ++i)
			//{
			//	MovableObject* obj = mParentContainer->getChildAt(i);
			//	if(obj)
			//	{
			//		++mWorldZOrder;
			//	}
			//}
		}

		return mWorldZOrder;
	}
	//-----------------------------------------------------------------------
	void Transform::updateMatrix()
	{
		if(mParentContainer)
		{
			mWorldMatrix = mParentContainer->getWorldMatrix() * mMatrix;
		}
		else
		{
			mWorldMatrix = mMatrix;
		}

		mWorldBounding = mBounding;
		mWorldBounding.transformAffine(mWorldMatrix);

		mNeedMatrixUpdate = false;
	}
	//-----------------------------------------------------------------------
	void Transform::needMatrixCompose()
	{
		mNeedMatrixCompose = true;
	}
	//-----------------------------------------------------------------------
	void Transform::composeMatrix()
	{
		float rad = mAngle / 180.0f * (float)M_PI;

		mMatrix = 
			Matrix(
			1, 0, mPosition.x, 
			0, 1, mPosition.y) * 

			Matrix(
			cos(rad), -sin(rad), 0, 
			sin(rad), cos(rad), 0) * 

			Matrix(
			mScale.x, 0, 0, 
			0, mScale.y, 0);

		mNeedMatrixCompose = false;
	}
	//-----------------------------------------------------------------------
	void Transform::decomposeMatrix()
	{
		mAngle = mMatrix.getRotation();
		mPosition = mMatrix.getTransformation();
		mScale = mMatrix.getScale();
		//Matrix rot_scale_mat = mMatrix;
		//rot_scale_mat.m[0][2] = rot_scale_mat.m[1][2] = 0;

		//Vector2 v1(1, 0);
		//Vector2 v2(1, 0);

		//v2 = rot_scale_mat.transformAffine(v2);
		//v2.normalize();

		//mAngle = acosf(v1.dotProduct(v2)) * 180.0f / (float)M_PI;

		//v1 = Vector2(1, 1);
		//v2 = Vector2(1, 1);

		//v1.normalize();
		//v2.normalize();

		//v1 = rot_scale_mat.transformAffine(v1);
		//v2 = rot_scale_mat.transformAffine(v2);

		//v2.normalize();

		//mScale = v1 / v2;

		//mPosition.x = mMatrix.m[0][2];
		//mPosition.y = mMatrix.m[1][2];
	}
	//-----------------------------------------------------------------------
}
