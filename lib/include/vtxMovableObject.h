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

#ifndef __vtxMovableObject_H__
#define __vtxMovableObject_H__

#include "vtxPrerequesites.h"
#include "vtxInstance.h"
#include "vtxTransform.h"

namespace vtx
{
	class vtxExport MovableObject : public Instance
	{
	public:
		MovableObject(Resource* resource);
		virtual ~MovableObject();

		virtual void setX(const float& x);
		virtual const float& getX() const;

		virtual void setY(const float& y);
		virtual const float& getY() const;

		virtual void setAngle(const float& angle);
		virtual const float& getAngle() const;

		virtual void setMatrix(const Matrix& m);
		virtual const Matrix& getMatrix() const;

		virtual void setCXForm(const CXForm& cx);

		void setParentContainer(DisplayObjectContainer* parent);

		virtual const BoundingBox& getBoundingBox() const = 0;
		virtual bool isPointInside(const Vector2& coord) = 0;

		const Matrix& getWorldMatrix();
		const BoundingBox& getWorldBoundingBox();

		void needColorUpdate();
		void needMatrixUpdate();

		virtual void _update(const float& delta_time = 0.0f);

		Transform& getTransform();

	protected:
		Transform mTransform;
		DisplayObjectContainer* mParentContainer;
	};
}

#endif
