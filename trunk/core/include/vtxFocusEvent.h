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

#ifndef __vtxFocusEvent_H__
#define __vtxFocusEvent_H__

#include "vtxPrerequesites.h"
#include "vtxEvent.h"
#include "vtxKeyCodes.h"

namespace vtx
{
	class vtxExport FocusEvent : public Event
	{
	public:
		FocusEvent(const String& type, const KeyCode& keyCode = KC_UNASSIGNED, InteractiveObject* relatedObject = NULL);
		virtual ~FocusEvent();

		static const String CATEGORY;
		static const String FOCUS_IN;
		static const String FOCUS_OUT;
		static const String KEY_FOCUS_CHANGE;
		static const String MOUSE_FOCUS_CHANGE;

		const String& getCategory() const;

		KeyCode keyCode;
		InteractiveObject* relatedObject;
	};
}

#endif
