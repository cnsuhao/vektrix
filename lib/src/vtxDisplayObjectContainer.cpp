/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009 Fuse-Software (tm)

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/
#include "vtxDisplayObjectContainer.h"

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
		//// DEBUG
		//if(!getParent())
		//{
		//	VTX_LOG("DisplayObjectContainer got no parent at shutdown!");
		//}

		clearLayers();
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::addChild(MovableObject* object)
	{
		uint layer = 1;

		if(mLayers.size())
		{
			Layers::iterator it = --mLayers.end();
			layer = (++it)->first;
		}

		addChildAt(object, layer);
	}
	//-----------------------------------------------------------------------
	bool DisplayObjectContainer::addChildAt(MovableObject* object, uint layer)
	{
		//mLayers.insert(Layers::value_type(0, NULL));

		Layers::iterator it = mLayers.find(layer);

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

		mLayers.insert(Layers::value_type(layer, object));

		return true;
	}
	//-----------------------------------------------------------------------
	MovableObject* DisplayObjectContainer::getChildAt(uint layer)
	{
		Layers::iterator it = mLayers.find(layer);

		if(it != mLayers.end())
		{
			return it->second;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	bool DisplayObjectContainer::removeChildAt(uint layer)
	{
		Layers::iterator it = mLayers.find(layer);

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
		Layers::iterator it = mLayers.begin();
		Layers::iterator end = mLayers.end();

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
	void DisplayObjectContainer::_update(const float& delta_time)
	{
		InteractiveObject::_update(delta_time);

		Layers::iterator it = mLayers.begin();
		Layers::iterator end = mLayers.end();

		while(it != end)
		{
			it->second->_update(delta_time);
			++it;
		}
	}
	//-----------------------------------------------------------------------
}
