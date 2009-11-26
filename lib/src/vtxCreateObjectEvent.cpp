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
#include "vtxCreateObjectEvent.h"

#include "vtxDisplayObjectContainer.h"
#include "vtxFile.h"
#include "vtxMovableObject.h"
#include "vtxMovie.h"

#include "vtxLogManager.h"
#include "vtxShapeResource.h"

#include "vtxStringHelper.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	CreateObjectEvent::CreateObjectEvent(DisplayObjectContainer* object_container, 
		const String& id, const uint& layer, const Matrix& matrix, const CXForm& cxform, const String& name) 
		: FrameEvent(object_container), 
		mID(id), 
		mLayer(layer), 
		mMatrix(matrix), 
		mCXForm(cxform), 
		mName(name)
	{
		//ShapeResource* shape = dynamic_cast<ShapeResource*>(mObjectContainer->getParent()->getFile()->getResource(mID));

		//if(shape)
		//{
		//	shape->_injectScale(mMatrix.getScale());
		//}
	}
	//-----------------------------------------------------------------------
	FrameEvent* CreateObjectEvent::clone(DisplayObjectContainer* container)
	{
		return new CreateObjectEvent(container, mID, mLayer, mMatrix, mCXForm, mName);
	}
	//-----------------------------------------------------------------------
	void CreateObjectEvent::execute(void)
	{
		mObject = dynamic_cast<MovableObject*>(mObjectContainer->getParent()->getInstance(mID));

		if(!mObject)
		{
			VTX_EXCEPT("%s: CreateObjectEvent requested an object (id: \"%s\") that is not a MovableObject.", 
				mObjectContainer->getParent()->getFile()->getFilename().c_str(), mID.c_str());
		}

		mObject->setParentContainer(mObjectContainer);
		mObject->setMatrix(mMatrix);
		mObject->setCXForm(mCXForm);
		mObjectContainer->addChildAt(mObject, mLayer);

		if(mName.length())
		{
			mObject->_initScriptObject(mName);
		}
	}
	//-----------------------------------------------------------------------
}
