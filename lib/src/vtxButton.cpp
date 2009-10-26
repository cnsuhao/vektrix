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
#include "vtxButton.h"

#include "vtxBoundingBox.h"
#include "vtxButtonResource.h"
#include "vtxButtonState.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	Button::Button(Resource* resource) 
		: MovableObject(resource)
	{
		ButtonResource* button_res = dynamic_cast<ButtonResource*>(resource);

		if(button_res)
		{
			mDefault = button_res->getState(ButtonResource::SID_DEFAULT)->clone();
			mOver = button_res->getState(ButtonResource::SID_OVER)->clone();
			mPressed = button_res->getState(ButtonResource::SID_PRESSED)->clone();
		}
	}
	//-----------------------------------------------------------------------
	const String& Button::getType() const
	{
		static String type = "Button";
		return type;
	}
	//-----------------------------------------------------------------------
	void Button::_setParentMovie(Movie* parent)
	{
		mDefault->_setParentMovie(parent);
		mOver->_setParentMovie(parent);
		mPressed->_setParentMovie(parent);
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	DefaultButton::DefaultButton(Resource* resource) 
		: Button(resource)
	{

	}
	//-----------------------------------------------------------------------
	void DefaultButton::setMatrix(const Matrix& m)
	{

	}
	//-----------------------------------------------------------------------
	void DefaultButton::setCXForm(const CXForm& cx)
	{

	}
	//-----------------------------------------------------------------------
	BoundingBox& DefaultButton::getWorldBoundingBox() const
	{
		static BoundingBox bb;
		return bb;
	}
	//-----------------------------------------------------------------------
}
