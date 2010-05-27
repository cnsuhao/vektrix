/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009-2010 Fuse-Software (tm)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#include "vtxButton.h"

#include "vtxBoundingBox.h"
#include "vtxButtonResource.h"
#include "vtxButtonState.h"
#include "vtxMouseEvent.h"
#include "vtxMovie.h"
#include "vtxScriptObject.h"

#include "vtxLogManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	const String Button::TYPE = "Button";
	//-----------------------------------------------------------------------
	Button::Button() 
		: mMouseDown(false), 
		mMouseOver(true), 
		mMouseState(MS_OUT_UP), 
		mUp(NULL), 
		mOver(NULL), 
		mDown(NULL)
	{

	}
	//-----------------------------------------------------------------------
	Button::~Button()
	{
		delete mDown;
		delete mOver;
		delete mUp;
	}
	//-----------------------------------------------------------------------
	void Button::initFromResource(Resource* resource)
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
	const String& Button::getType() const
	{
		return TYPE;
	}
	//-----------------------------------------------------------------------
	void Button::_update(const float& delta_time)
	{
		DisplayObjectContainer::_update(delta_time);
		DisplayObjectContainer::updateWorldBoundingBox();

		// TODO: DEBUGGING only, implement more beautifully
		if(isPointInside(getParent()->getMouseAbs()))
		{
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
	}
	//-----------------------------------------------------------------------
	const BoundingBox& Button::getBoundingBox() const
	{
		return mBB;
	}
	//-----------------------------------------------------------------------
	void Button::_setParent(Movie* parent)
	{
		DisplayObjectContainer::_setParent(parent);

		clearLayers();

		if(parent)
		{
			mUp->execute();
		}
	}
	//-----------------------------------------------------------------------
	void Button::eventFired(const Event& evt)
	{
		DisplayObjectContainer::eventFired(evt);

		if(evt.getCategory() == MouseEvent::CATEGORY)
		{
			const MouseEvent& mouse_evt = dynamic_cast<const MouseEvent&>(evt);

			if(isPointInside(Vector2(mouse_evt.stageX, mouse_evt.stageY)))
			{
				if(evt.getType() == MouseEvent::MOUSE_DOWN)
				{
					clearLayers();
					mDown->execute();
				}
				else if(evt.getType() == MouseEvent::MOUSE_UP)
				{
					clearLayers();
					mOver->execute();
				}

				if(mScriptObject)
				{
					mScriptObject->eventFired(evt);
				}
			}
		}
	}
	//-----------------------------------------------------------------------
}
