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
		: mHasFocus(false)
	{

	}
	//-----------------------------------------------------------------------
	InteractiveObject::~InteractiveObject()
	{

	}
	//-----------------------------------------------------------------------
	void InteractiveObject::eventFired(const Event& evt)
	{
		if(evt.getCategory() == MouseEvent::CATEGORY)
		{
			const MouseEvent& mouse_evt = dynamic_cast<const MouseEvent&>(evt);

			if(evt.getType() == MouseEvent::MOUSE_DOWN)
			{
				if(isPointInside(Vector2(mouse_evt.stageX, mouse_evt.stageY)))
				{
					if(!mHasFocus)
					{
						FocusEvent focus_evt(FocusEvent::FOCUS_IN);
						focus_evt.relatedObject = this;

						eventFired(focus_evt);
						mHasFocus = true;

						mParentMovie->_setFocusedObject(this);
					}
				}
				else if(mHasFocus)
				{
					FocusEvent focus_evt(FocusEvent::FOCUS_OUT);
					focus_evt.relatedObject = this;

					eventFired(focus_evt);
					mHasFocus = false;
				}
			} // MOUSE_DOWN
		}
	}
	//-----------------------------------------------------------------------
}