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
#include "vtxMovableObject.h"
#include "vtxDisplayObjectContainer.h"
#include "vtxMovie.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	MovableObject::MovableObject(Resource* resource) 
		: Instance(resource), 
		mNeedsUpdate(true), 
		mParentContainer(NULL)
	{

	}
	//-----------------------------------------------------------------------
	void MovableObject::setMatrix(const Matrix& m)
	{
		mMatrix = m;

		mNeedsUpdate = true;

		// TODO: remove this
		_update();
	}
	//-----------------------------------------------------------------------
	void MovableObject::setCXForm(const CXForm& cx)
	{
		mCXForm = cx;

		mNeedsUpdate = true;

		// TODO: remove this
		_update();
	}
	//-----------------------------------------------------------------------
	const Matrix& MovableObject::_getWorldMatrix() const
	{
		return mWorldMatrix;
	}
	//-----------------------------------------------------------------------
	void MovableObject::_update(const float& delta_time)
	{
		if(mParentContainer)
		{
			mWorldMatrix = mParentContainer->_getWorldMatrix() * mMatrix;
		}
		else
		{
			mWorldMatrix = mMatrix;
		}
	}
	//-----------------------------------------------------------------------
	////-----------------------------------------------------------------------
	//void MovableObject::setLayer(uint layer)
	//{
	//	if(mParentMovie->setObjectToLayer(layer, this))
	//	{
	//		mLayer = layer;
	//	}
	//}
	////-----------------------------------------------------------------------
	//uint MovableObject::getLayer()
	//{
	//	return mLayer;
	//}
	////-----------------------------------------------------------------------
}
