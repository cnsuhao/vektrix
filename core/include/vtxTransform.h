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

#ifndef __vtxTransform_H__
#define __vtxTransform_H__

#include "vtxPrerequisites.h"
#include "vtxBoundingBox.h"
#include "vtxCXForm.h"
#include "vtxMatrix.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** This class combines transformation, color and bounding attributes */
	class vtxExport Transform
	{
	public:
		Transform();
		virtual ~Transform();

		/** Set the DisplayObjectContainer that will be used for world-transformation calculations */
		void setParentContainer(DisplayObjectContainer* parent);

		/** Set the x-coordinate for this object */
		void setX(const float& x);
		/** Get the x-coordinate of this object */
		const float& getX() const;

		/** Set the y-coordinate for this object */
		void setY(const float& y);
		/** Get the y-coordinate of this object */
		const float& getY() const;

		/** Set the rotation for this object */
		void setAngle(const float& angle);
		/** Get the rotation of this object */
		const float& getAngle() const;

		/** Set the x-scale for this object */
		void setScaleX(const float& scale);
		/** Get the x-scale of this object */
		const float& getScaleX() const;

		/** Set the y-scale for this object */
		void setScaleY(const float& scale);
		/** Get the y-scale of this object */
		const float& getScaleY() const;

		/** Set the width for this object */
		void setWidth(const float& width);
		/** Get the width of this object */
		const float getWidth() const;

		/** Set the height for this object */
		void setHeight(const float& height);
		/** Get the height of this object */
		const float getHeight() const;

		/** Set the layer for this object */
		void setLayer(const uint& layer);
		/** Get the layer of this object */
		const uint& getLayer() const;

		/** Set the color transformation for this object */
		void setColor(const CXForm& cx);
		/** Get the color transformation of this object */
		const CXForm& getColor() const;

		/** Set the matrix for this object */
		void setMatrix(const Matrix& m);
		/** Get the matrix of this object */
		const Matrix& getMatrix() const;

		/** Set the bounding box for this object */
		void setBounding(const BoundingBox& bb);
		/** Get the bounding box of this object */
		const BoundingBox& getBounding() const;

		/** Inform the object that the color transformation needs to be updated */
		void needColorUpdate();

		/** Inform the object that the matrix needs to be updated */
		void needMatrixUpdate();

		const bool& doesNeedMatrixUpdate() const;

		/** Perform color / matrix updates if necessary */
		void update();

		/** Get the world bounding box that has been calculated */
		BoundingBox& getWorldBounding();
		/** Get the world color that has been calculated */
		const CXForm& getWorldColor() const;
		/** Get the world matrix that has been calculated */
		const Matrix& getWorldMatrix() const;
		/** Get the world Z order that has been calculated */
		const uint& getZOrder();

	protected:
		DisplayObjectContainer* mParentContainer;

		float mAngle;
		Vector2 mPosition;
		Vector2 mScale;
		uint mLayer;

		CXForm mCxForm;
		Matrix mMatrix;
		BoundingBox mBounding;

		bool mNeedColorUpdate;
		bool mNeedMatrixUpdate;
		bool mNeedMatrixCompose;

		BoundingBox mWorldBounding;
		CXForm mWorldColor;
		Matrix mWorldMatrix;
		uint mWorldZOrder;

		/** Update the world matrix and bounding box */
		void updateMatrix();

		/** Inform the transform that a update of the world matrix is necessary */
		void needMatrixCompose();
		/** Compose the local matrix out of the x, y, angle, etc attributes */
		void composeMatrix();
		/** Decompose the local matrix back to the seperate x, y, angle, etc attributes */
		void decomposeMatrix();
	};
	//-----------------------------------------------------------------------
}

#endif
