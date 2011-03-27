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

#include "vtxInteractiveObject.h"

#include "vtxFocusEvent.h"
#include "vtxMouseEvent.h"
#include "vtxMovie.h"
#include "vtxScriptObject.h"

#include "vtxLogManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	InteractiveObject::InteractiveObject() 
		: mHasFocus(false), 
		mMouseState(MS_OUT_UP), 
		mPrevMouseState(MS_OUT_UP)
	{

	}
	//-----------------------------------------------------------------------
	InteractiveObject::~InteractiveObject()
	{

	}
	//-----------------------------------------------------------------------
	void InteractiveObject::processEvents()
	{
		DisplayObject::processEvents();

		if(isPointInside(getParent()->getMouseAbs()))
		{
			if(mMouseState == MS_OUT_UP)
			{
				MouseEvent evt(MouseEvent::MOUSE_OVER);
				eventFired(evt);

				if(mScriptObject)
					mScriptObject->eventFired(evt);

				changeMouseState(MS_IN_UP);
			}
		}
		else
		{
			if(mMouseState == MS_IN_UP)
			{
				MouseEvent evt(MouseEvent::MOUSE_OUT);
				eventFired(evt);

				if(mScriptObject)
					mScriptObject->eventFired(evt);

				changeMouseState(MS_OUT_UP);
			}
		}
	}
	//-----------------------------------------------------------------------
	void InteractiveObject::eventFired(const Event& evt)
	{
		if(evt.getCategory() == MouseEvent::CATEGORY)
		{
			const MouseEvent& mouse_evt = static_cast<const MouseEvent&>(evt);

			if(evt.getType() == MouseEvent::MOUSE_DOWN)
			{
				if(!mHasFocus)
				{
					mHasFocus = true;
					mParentMovie->_setFocusedObject(this);

					if(mScriptObject)
					{
						FocusEvent focus_evt(FocusEvent::FOCUS_IN);
						mScriptObject->eventFired(focus_evt);
					}
				}

				if(mMouseState == MS_IN_UP)
					changeMouseState(MS_IN_DOWN);

				if(mScriptObject)
					mScriptObject->eventFired(evt);

			} // MOUSE_DOWN

			else if(evt.getType() == MouseEvent::MOUSE_UP)
			{
				if(mMouseState == MS_IN_DOWN)
					changeMouseState(MS_IN_UP);

				if(mScriptObject)
					mScriptObject->eventFired(evt);

			} // MOUSE_UP

			else if(evt.getType() == MouseEvent::MOUSE_MOVE)
			{
				if(mScriptObject)
					mScriptObject->eventFired(evt);

			} // MOUSE_MOVE

		} // MouseEvents

		else if(evt.getCategory() == FocusEvent::CATEGORY)
		{
			if(evt.getType() == FocusEvent::FOCUS_OUT)
			{
				mHasFocus = false;

				if(mScriptObject)
					mScriptObject->eventFired(evt);
			}
		}
		else
		{
			if(mScriptObject)
				mScriptObject->eventFired(evt);
		}
	}
	//-----------------------------------------------------------------------
	void InteractiveObject::changeMouseState(const MouseState& new_state)
	{
		mPrevMouseState = mMouseState;
		mMouseState = new_state;
	}
	//-----------------------------------------------------------------------
}
