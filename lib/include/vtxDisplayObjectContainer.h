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

#ifndef __vtxDisplayObjectContainer_H__
#define __vtxDisplayObjectContainer_H__

#include "vtxPrerequesites.h"
#include "vtxInteractiveObject.h"

namespace vtx
{
	class vtxExport DisplayObjectContainer : public InteractiveObject
	{
	public:
		typedef std::map<uint, MovableObject*> Layers;

		DisplayObjectContainer(Resource* resource);
		virtual ~DisplayObjectContainer();

		void addChild(MovableObject* object);
		bool addChildAt(MovableObject* object, uint layer);
		MovableObject* getChildAt(uint layer);
		bool removeChildAt(uint layer);
		void clearLayers();

		bool isPointInside(const Vector2& coord);

		virtual void setX(const float& x);
		virtual void setY(const float& y);
		virtual void setAngle(const float& angle);
		virtual void setMatrix(const Matrix& m);

		virtual void _update(const float& delta_time = 0.0f);

	protected:
		Layers mLayers;

		void childrenNeedMatrixUpdate();
	};
}

#endif
