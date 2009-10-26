/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/vektrix

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
#include "vtxCanvas.h"

#include "vtxLogManager.h"
#include "vtxMovableObject.h"
#include "vtxMovie.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	Canvas::Canvas(Movie* parent) 
		: mParent(parent)
	{

	}
	//-----------------------------------------------------------------------
	bool Canvas::setObjectToLayer(uint layer, MovableObject* object)
	{
		mLayers.insert(CanvasLayers::value_type(0, NULL));

		CanvasLayers::iterator it = mLayers.find(layer);

		if(it != mLayers.end())
		{
			// target layer is not free
			VTX_EXCEPT("Target Layer %u is not free.", layer);
			return false;
		}

		uint old_layer = object->getLayer();

		it = mLayers.find(old_layer);

		if(it != mLayers.end())
		{
			if(it->second == object)
			{
				mLayers.erase(it);
			}
		}

		mLayers.insert(CanvasLayers::value_type(layer, object));

		return true;
	}
	//-----------------------------------------------------------------------
	MovableObject* Canvas::getObjectFromLayer(uint layer)
	{
		CanvasLayers::iterator it = mLayers.find(layer);

		if(it != mLayers.end())
		{
			return it->second;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	bool Canvas::removeObjectFromLayer(uint layer)
	{
		CanvasLayers::iterator it = mLayers.find(layer);

		if(it != mLayers.end())
		{
			mLayers.erase(it);
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	void Canvas::clearLayers()
	{
		CanvasLayers::iterator it = mLayers.begin();

		for( ; it != mLayers.end(); ++it)
		{
			if(it->second)
			{
				mParent->releaseInstance(it->second);
			}
		}

		mLayers.clear();
	}
	//-----------------------------------------------------------------------

}
