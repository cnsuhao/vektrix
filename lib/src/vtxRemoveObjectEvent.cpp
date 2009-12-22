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
#include "vtxRemoveObjectEvent.h"

#include "vtxDisplayObjectContainer.h"
#include "vtxLogManager.h"
#include "vtxMovie.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	RemoveObjectEvent::RemoveObjectEvent(DisplayObjectContainer* object_container, const uint& layer) 
		: FrameEvent(object_container), 
		mLayer(layer)
	{

	}
	//-----------------------------------------------------------------------
	FrameEvent* RemoveObjectEvent::clone(DisplayObjectContainer* container)
	{
		return new RemoveObjectEvent(container, mLayer);
	}
	//-----------------------------------------------------------------------
	void RemoveObjectEvent::execute()
	{
		Instance* inst = (Instance*)mObjectContainer->getChildAt(mLayer);

		mObjectContainer->removeChildAt(mLayer);

		if(inst)
		{
			mObjectContainer->getParent()->releaseInstance(inst);
		}
		else
		{
			VTX_WARN("Can't release Instance from layer %u, layer is empty!", mLayer);
		}
	}
	//-----------------------------------------------------------------------
}
