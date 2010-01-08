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

#include "vtxPrerequesites.h"
#include "vtxBoundingBox.h"
#include "vtxCXForm.h"
#include "vtxMatrix.h"

namespace vtx
{
	class vtxExport Transform
	{
	public:
		Transform();
		virtual ~Transform();

		void setX(const float& x);
		const float& getX() const;

		void setY(const float& y);
		const float& getY() const;

		void setAngle(const float& angle);
		const float& getAngle() const;

		void setColor(const CXForm& cx);
		const CXForm& getColor() const;

		void setMatrix(const Matrix& m);
		const Matrix& getMatrix() const;

		void setBounding(const BoundingBox& bb);
		const BoundingBox& getBounding() const;

		void needColorUpdate();
		void needMatrixUpdate();

		void update(DisplayObjectContainer* parent);

		BoundingBox& getWorldBounding();
		const CXForm& getWorldColor();
		const Matrix& getWorldMatrix();

	protected:
		float mAngle;
		Vector2 mPosition;
		Vector2 mScale;

		CXForm mCxForm;
		Matrix mMatrix;
		BoundingBox mBounding;

		bool mNeedColorUpdate;
		bool mNeedMatrixUpdate;
		bool mNeedMatrixCompose;

		BoundingBox mWorldBounding;
		CXForm mWorldColor;
		Matrix mWorldMatrix;

		void updateMatrix(DisplayObjectContainer* parent);

		void needMatrixCompose();
		void composeMatrix();
		void decomposeMatrix();
	};
}

#endif
