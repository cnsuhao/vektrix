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
#include "vtxMoveObjectEvent.h"

#include "vtxDisplayObjectContainer.h"
#include "vtxFile.h"
#include "vtxLogManager.h"
#include "vtxMovableObject.h"
#include "vtxMovie.h"
#include "vtxShapeResource.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	MoveObjectEvent::MoveObjectEvent(const uint& layer, const Matrix& matrix, const CXForm& cxform) 
		: mLayer(layer), 
		mMatrix(matrix), 
		mCXForm(cxform)
	{

	}
	//-----------------------------------------------------------------------
	FrameEvent* MoveObjectEvent::clone()
	{
		MoveObjectEvent* clonedEvent = new MoveObjectEvent(mLayer, mMatrix, mCXForm);
		//clonedEvent->mParentMovie = parent;

		return clonedEvent;
	}
	//-----------------------------------------------------------------------
	void MoveObjectEvent::execute(void)
	{
		mObject = mObjectContainer->getChildAt(mLayer);
		mObject->setMatrix(mMatrix);
		mObject->setCXForm(mCXForm);
		//mObject->setLayer(mLayer);

		//VTX_LOG("MoveObjectEvent");
	}
	//-----------------------------------------------------------------------
	void MoveObjectEvent::setObjectContainer(DisplayObjectContainer* container)
	{
		FrameEvent::setObjectContainer(container);

		//ShapeResource* shape = dynamic_cast<ShapeResource*>(parent->getFile()->getResource(mID));

		//if(shape)
		//{
		//	shape->_injectScale(mMatrix.getScale());
		//}
	}
	//-----------------------------------------------------------------------
}
