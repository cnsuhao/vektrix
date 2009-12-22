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
#include "vtxButton.h"

#include "vtxBoundingBox.h"
#include "vtxButtonResource.h"
#include "vtxButtonState.h"
#include "vtxMovie.h"
#include "vtxScriptButton.h"

#include "vtxLogManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	Button::Button(Resource* resource) 
		: DisplayObjectContainer(resource), 
		mMouseDown(false), 
		mMouseOver(false), 
		mScriptObject(NULL), 
		mUp(NULL), 
		mOver(NULL), 
		mDown(NULL)
	{
		ButtonResource* button_res = dynamic_cast<ButtonResource*>(resource);

		if(button_res)
		{
			if(button_res->getState(ButtonResource::SID_UP))
				mUp = button_res->getState(ButtonResource::SID_UP)->clone(this);
			if(button_res->getState(ButtonResource::SID_OVER))
				mOver = button_res->getState(ButtonResource::SID_OVER)->clone(this);
			if(button_res->getState(ButtonResource::SID_DOWN))
				mDown = button_res->getState(ButtonResource::SID_DOWN)->clone(this);
			//mPressed = button_res->getState(ButtonResource::SID_PRESSED)->clone();
		}
	}
	//-----------------------------------------------------------------------
	Button::~Button()
	{
		delete mDown;
		delete mOver;
		delete mUp;
	}
	//-----------------------------------------------------------------------
	const String& Button::getType() const
	{
		static String type = "Button";
		return type;
	}
	//-----------------------------------------------------------------------
	void Button::_update(const float& delta_time)
	{
		//DisplayObjectContainer::_update(delta_time);

		// DEBUGGING only, implement more beautifully
		if(isPointInside(getParent()->getMouseAbs()))
		{
			if(getParent()->isMouseDown())
			{
				if(!mMouseDown && mDown)
				{
					VTX_LOG("Button Down");
					clearLayers();
					mDown->execute();
					mMouseDown = true;
				}
			}
			else
			{
				if(mMouseDown && mOver)
				{
					VTX_LOG("Button Up");
					clearLayers();
					mOver->execute();
					mMouseDown = false;

					if(mScriptObject)
					{
						mScriptObject->buttonUp();
					}
				}
			}

			if(!mMouseOver && mOver)
			{
				VTX_LOG("Mouse In");
				clearLayers();
				mOver->execute();
				mMouseOver = true;
			}
		}
		else
		{
			if(mMouseOver && mUp)
			{
				VTX_LOG("Mouse Out");
				clearLayers();
				mUp->execute();
				mMouseOver = false;
			}
		}

		DisplayObjectContainer::_update(delta_time);

		mWorldBB.reset();

		Layers::iterator it = mLayers.begin();
		Layers::iterator end = mLayers.end();
		while(it != end)
		{
			mWorldBB.extend(it->second->_getWorldBoundingBox());
			++it;
		}
	}
	//-----------------------------------------------------------------------
	const BoundingBox& Button::getBoundingBox() const
	{
		// DEBUG
		return mBB;
	}
	//-----------------------------------------------------------------------
	void Button::_setParent(Movie* parent)
	{
		DisplayObjectContainer::_setParent(parent);

		//clearLayers();
		//mUp->execute();
	}
	//-----------------------------------------------------------------------
	void Button::setScriptObject(ScriptObject* obj)
	{
		mScriptObject = dynamic_cast<ScriptButton*>(obj);
	}
	//-----------------------------------------------------------------------
	ScriptObject* Button::getScriptObject() const
	{
		return mScriptObject;
	}
	//-----------------------------------------------------------------------
}
