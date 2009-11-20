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

#include "vtxLogManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	ButtonResource::ButtonResource(const String& id) 
		: Resource(id), 
		mUp(NULL), 
		mOver(NULL), 
		mDown(NULL), 
		mHitArea(NULL)
	{

	}
	//-----------------------------------------------------------------------
	const String& ButtonResource::getType(void) const
	{
		static String type = "Button";
		return type;
	}
	//-----------------------------------------------------------------------
	void ButtonResource::setState(ButtonState* state, const StateID& id)
	{
		switch(id)
		{
		case SID_UP:
			{
				mUp = state;
			}
			break;

		case SID_OVER:
			{
				mOver = state;
			}
		    break;

		case SID_DOWN:
			{
				mDown = state;
			}
			break;

		case SID_HIT_AREA:
			{
				mHitArea = state;
			}
			break;

		default:
			{
				VTX_WARN("Tried to add ButtonState with unknown StateID!");
			}
		    break;
		}
	}
	//-----------------------------------------------------------------------
	ButtonState* ButtonResource::getState(const StateID& id)
	{
		switch(id)
		{
		case SID_UP:
			{
				return mUp;
			}
			break;

		case SID_OVER:
			{
				return mOver;
			}
			break;

		case SID_DOWN:
			{
				return mDown;
			}
			break;

		case SID_HIT_AREA:
			{
				return mHitArea;
			}
		    break;

		default:
			{
				return NULL;
			}
		    break;
		}
	}
	//-----------------------------------------------------------------------
}

