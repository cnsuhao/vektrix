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
#include "vtxButtonResource.h"

#include "vtxButtonState.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	ButtonResource::ButtonResource(const String& id) 
		: Resource(id)
	{
		mStates[0] = NULL;
		mStates[1] = NULL;
		mStates[2] = NULL;
		mStates[3] = NULL;
	}
	//-----------------------------------------------------------------------
	ButtonResource::~ButtonResource()
	{
		delete mStates[0];

		if(mStates[1] != mStates[0])
			delete mStates[1];

		if(mStates[2] != mStates[0] && 
			mStates[2] != mStates[1])
			delete mStates[2];

		if(mStates[3] != mStates[0] && 
			mStates[3] != mStates[1] && 
			mStates[3] != mStates[2])
			delete mStates[3];
	}
	//-----------------------------------------------------------------------
	const String& ButtonResource::getType() const
	{
		static String type = "Button";
		return type;
	}
	//-----------------------------------------------------------------------
	void ButtonResource::setState(ButtonState* state, const StateID& id)
	{
		mStates[id] = state;
	}
	//-----------------------------------------------------------------------
	ButtonState* ButtonResource::getState(const StateID& id)
	{
		return mStates[id];
	}
	//-----------------------------------------------------------------------
}

