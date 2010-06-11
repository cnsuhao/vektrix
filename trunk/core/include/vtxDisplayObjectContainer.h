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

#include "vtxPrerequisites.h"
#include "vtxInteractiveObject.h"

namespace vtx
{
	/** Base class for everything visual that can itself contain other visual objects */
	class vtxExport DisplayObjectContainer : public InteractiveObject
	{
	public:
		typedef std::map<uint, DisplayObject*> LayerMap;

		DisplayObjectContainer();
		virtual ~DisplayObjectContainer();

		/** Add a child object at the topmost available layer */
		void addChild(DisplayObject* object);
		/** Add a child object at the given layer */
		bool addChildAt(DisplayObject* object, uint layer);
		/** Get the child object located at the given layer */
		DisplayObject* getChildAt(uint layer);
		/** Remove a child object from the given layer */
		bool removeChildAt(uint layer);
		/** Remove all objects from all layers */
		void clearLayers();

		const LayerMap& getLayers() const;

		/** Implementation for DisplayObject::isPointInside */
		bool isPointInside(const Vector2& coord);

		/** @copybrief DisplayObject::setX */
		virtual void setX(const float& x);
		/** @copybrief DisplayObject::setY */
		virtual void setY(const float& y);

		/** @copybrief DisplayObject::setAngle */
		virtual void setAngle(const float& angle);

		/** @copybrief DisplayObject::setScaleX */
		virtual void setScaleX(const float& scale);
		/** @copybrief DisplayObject::setScaleY */
		virtual void setScaleY(const float& scale);

		/** @copybrief DisplayObject::setMatrix */
		virtual void setMatrix(const Matrix& m);

		/** @copybrief DisplayObject::_update */
		virtual void _update(const float& delta_time = 0.0f);

		// inherited from EventListener
		virtual void eventFired(const Event& evt);

	protected:
		LayerMap mLayers;

		/** Update the world BoundingBox of this container */
		void updateWorldBoundingBox();
		/** Notify the children of this container about Matrix changes */
		void childrenNeedMatrixUpdate();
	};
}

#endif
