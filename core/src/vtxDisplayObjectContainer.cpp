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

#include "vtxDisplayObjectContainer.h"

#include "vtxFocusEvent.h"
#include "vtxLogManager.h"
#include "vtxMovie.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	DisplayObjectContainer::DisplayObjectContainer(Resource* resource) 
		: InteractiveObject(resource)
	{

	}
	//-----------------------------------------------------------------------
	DisplayObjectContainer::~DisplayObjectContainer()
	{
		clearLayers();
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::addChild(DisplayObject* object)
	{
		uint layer = 1;

		if(mLayers.size())
		{
			LayerMap::iterator it = --mLayers.end();
			layer = it->first + 1;
		}

		addChildAt(object, layer);
	}
	//-----------------------------------------------------------------------
	bool DisplayObjectContainer::addChildAt(DisplayObject* object, uint layer)
	{
		//mLayers.insert(Layers::value_type(0, NULL));

		LayerMap::iterator it = mLayers.find(layer);

		if(it != mLayers.end())
		{
			// target layer is not free
			VTX_EXCEPT("Movie \"%s\": Target Layer %u is not free.", "TODO", layer);
			return false;
		}

		//uint old_layer = object->getLayer();

		//it = mLayers.find(old_layer);

		//if(it != mLayers.end())
		//{
		//	if(it->second == object)
		//	{
		//		mLayers.erase(it);
		//	}
		//}

		mLayers.insert(LayerMap::value_type(layer, object));
		object->setParentContainer(this);
		object->setLayer(layer);

		return true;
	}
	//-----------------------------------------------------------------------
	DisplayObject* DisplayObjectContainer::getChildAt(uint layer)
	{
		LayerMap::iterator it = mLayers.find(layer);

		if(it != mLayers.end())
		{
			return it->second;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	bool DisplayObjectContainer::removeChildAt(uint layer)
	{
		LayerMap::iterator it = mLayers.find(layer);

		if(it != mLayers.end())
		{
			if(mParentMovie)
			{
				mParentMovie->releaseInstance(it->second);
			}

			mLayers.erase(it);
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::clearLayers()
	{
		LayerMap::iterator it = mLayers.begin();
		LayerMap::iterator end = mLayers.end();

		while(it != end)
		{
			if(it->second && mParentMovie)
			{
				DisplayObjectContainer* child = dynamic_cast<DisplayObjectContainer*>(it->second);
				if(child)
				{
					child->clearLayers();
				}

				mParentMovie->releaseInstance(it->second);
			}

			++it;
		}

		mLayers.clear();
	}
	//-----------------------------------------------------------------------
	const DisplayObjectContainer::LayerMap& DisplayObjectContainer::getLayers() const
	{
		return mLayers;
	}
	//-----------------------------------------------------------------------
	bool DisplayObjectContainer::isPointInside(const Vector2& coord)
	{
		LayerMap::iterator it = mLayers.begin();
		LayerMap::iterator end = mLayers.end();

		while(it != end)
		{
			if(it->second->isPointInside(coord))
			{
				return true;
			}

			++it;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::setX(const float& x)
	{
		InteractiveObject::setX(x);
		childrenNeedMatrixUpdate();
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::setY(const float& y)
	{
		InteractiveObject::setY(y);
		childrenNeedMatrixUpdate();
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::setAngle(const float& angle)
	{
		InteractiveObject::setAngle(angle);
		childrenNeedMatrixUpdate();
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::setScaleX(const float& scale)
	{
		InteractiveObject::setScaleX(scale);
		childrenNeedMatrixUpdate();
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::setScaleY(const float& scale)
	{
		InteractiveObject::setScaleY(scale);
		childrenNeedMatrixUpdate();
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::setMatrix(const Matrix& m)
	{
		InteractiveObject::setMatrix(m);
		childrenNeedMatrixUpdate();
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::_update(const float& delta_time)
	{
		InteractiveObject::_update(delta_time);

		LayerMap::iterator it = mLayers.begin();
		LayerMap::iterator end = mLayers.end();

		while(it != end)
		{
			it->second->_update(delta_time);
			++it;
		}
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::eventFired(const Event& evt)
	{
		InteractiveObject::eventFired(evt);

		// TODO: not all events should be relayed to children ?
		if(evt.getCategory() != FocusEvent::CATEGORY)
		{
			LayerMap::iterator it = mLayers.begin();
			LayerMap::iterator end = mLayers.end();

			while(it != end)
			{
				it->second->eventFired(evt);
				++it;
			}
		}
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::updateWorldBoundingBox()
	{
		// TODO: only update bounding box when transformation occured
		mTransform.getWorldBounding().reset();

		LayerMap::iterator it = mLayers.begin();
		LayerMap::iterator end = mLayers.end();

		while(it != end)
		{
			// TODO: only update bounding box when transformation occured
			mTransform.getWorldBounding().extend(it->second->getWorldBoundingBox());
			++it;
		}
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::childrenNeedMatrixUpdate()
	{
		LayerMap::iterator it = mLayers.begin();
		LayerMap::iterator end = mLayers.end();

		while(it != end)
		{
			it->second->needMatrixUpdate();
			++it;
		}
	}
	//-----------------------------------------------------------------------
}
