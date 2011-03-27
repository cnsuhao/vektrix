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

#include "vtxDisplayObject.h"
#include "vtxFocusEvent.h"
#include "vtxLogManager.h"
#include "vtxMouseEvent.h"
#include "vtxMovie.h"
#include "vtxScriptObject.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	DisplayObjectContainer::DisplayObjectContainer(const bool& auto_update_bbs) 
		: mAutoUpdateBBs(auto_update_bbs), 
		mNeedBoundingBoxUpdate(false), 
		mChildListChanged(false)
	{

	}
	//-----------------------------------------------------------------------
	DisplayObjectContainer::~DisplayObjectContainer()
	{
		clearLayers();
	}
	//-----------------------------------------------------------------------
	bool DisplayObjectContainer::isDisplayObjectContainer() const
	{
		return true;
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::addChild(DisplayObject* object)
	{
		uint layer = 0;

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
		mNeedBoundingBoxUpdate = true;
		mChildListChanged = true;

		LayerMap::iterator it = mLayers.find(layer);
		LayerMap::iterator end = mLayers.end();

		// layer not free
		if(it != end)
		{
			// move original object of this layer to the next layer
			addChildAt(it->second, it->first+1);

			// erase the original assignment
			mLayers.erase(it);
		}

		const String& name = object->getName();

		if(name.length())
		{
			NameMap::iterator it = mNameMap.find(name);
			if(it == mNameMap.end())
			{
				mNameMap.insert(std::make_pair(name, object));
				//mScriptObject->setChildObject(name, object->getScriptObject());
			}
			//else
			//{
			//	VTX_EXCEPT("DisplayObject with name: %s already placed at DisplayObjectContainer");
			//}
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
	DisplayObject* DisplayObjectContainer::getChildByIndex(const uint& index)
	{
		if(index >= 0 && index < mLayers.size())
		{
			LayerMap::const_iterator it = mLayers.begin();
			std::advance(it, index);
			return it->second;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	DisplayObject* DisplayObjectContainer::getChildByName(const String& name)
	{
		NameMap::iterator it = mNameMap.find(name);

		if(it != mNameMap.end())
		{
			return it->second;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	DisplayObject* DisplayObjectContainer::removeChildAt(uint layer)
	{
		mNeedBoundingBoxUpdate = true;
		mChildListChanged = true;

		LayerMap::iterator it = mLayers.find(layer);
		if(it == mLayers.end())
		{
			return NULL;
		}

		DisplayObject* child = it->second;

		if(it != mLayers.end())
		{
			if(child->getName().length())
			{
				NameMap::iterator it = mNameMap.find(child->getName());
				if(it != mNameMap.end())
				{
					mNameMap.erase(it);
				}
				else
				{
					VTX_EXCEPT("DisplayObject with name: %s placed at DisplayObjectContainer without name");
				}
			}

			if(mParentMovie)
				mParentMovie->releaseInstance(child);

			mLayers.erase(it);

			return child;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	uint DisplayObjectContainer::numChildren() const
	{
		return mLayers.size();
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::clearLayers()
	{
		mNeedBoundingBoxUpdate = true;
		mChildListChanged = true;

		LayerMap::iterator it = mLayers.begin();
		LayerMap::iterator end = mLayers.end();

		while(it != end)
		{
			DisplayObject* child = it->second;

			if(child && mParentMovie)
			{
				if(child->isDisplayObjectContainer())
				{
					DisplayObjectContainer* child_container = static_cast<DisplayObjectContainer*>(child);
					child_container->clearLayers();
				}

				mParentMovie->releaseInstance(child);
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
		for_each_const(it, LayerMap, mLayers)
		{
			if(it->second->isPointInside(coord))
				return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::processEvents()
	{
		InteractiveObject::processEvents();
		//fireEvents();

		for_each(it, LayerMap, mLayers)
			it->second->processEvents();
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::updateGraphics(const float& delta_time)
	{
		if(mNeedBoundingBoxUpdate && mAutoUpdateBBs)
		{
			BoundingBox new_bb;

			for_each(it, LayerMap, mLayers)
			{
				BoundingBox bb = it->second->getBoundingBox();
				bb.transformAffine(it->second->getMatrix());
				new_bb.extend(bb);
			}

			mTransform.setBounding(new_bb);

			mNeedBoundingBoxUpdate = false;
		}

		if(mTransform.doesNeedMatrixUpdate())
		{
			for_each(it, LayerMap, mLayers)
				it->second->needMatrixUpdate();
		}

		InteractiveObject::updateGraphics(delta_time);

		for_each(it, LayerMap, mLayers)
			it->second->updateGraphics(delta_time);
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::eventFired(const Event& evt)
	{
		// TODO: evtl. unify eventFired vs. dispatchEvent
		dispatchEvent(evt);

		if(evt.getCategory() != FocusEvent::CATEGORY)
		{
			LayerMap::iterator it = mLayers.begin();
			LayerMap::iterator end = mLayers.end();

			while(it != end)
			{
				DisplayObject* child = it->second;
				if(evt.getCategory() == MouseEvent::CATEGORY)
				{
					bool mouseInside = child->isPointInside(getParent()->getMouseAbs());
					if(mouseInside)
					{
						child->eventFired(evt);
					}
					else if(evt.getType() == MouseEvent::MOUSE_DOWN && child->hasFocus())
					{
						child->eventFired(FocusEvent(FocusEvent::FOCUS_OUT));
					}
				}
				else
				{
					child->eventFired(evt);
				}

				if(mChildListChanged)
				{
					mChildListChanged = false;
					it = mLayers.begin();
					end = mLayers.end();
				}
				else
					++it;
			}
		}

		InteractiveObject::eventFired(evt);
	}
	//-----------------------------------------------------------------------
}
