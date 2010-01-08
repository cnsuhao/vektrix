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

#ifndef __vtxas3SimpleButton_H__
#define __vtxas3SimpleButton_H__

#include "cspPrerequesites.h"

#include "vtxScriptButton.h"

namespace vtx
{
	namespace as3
	{
		class SimpleButtonClass : public avmplus::ClassClosure
		{
		public:
			SimpleButtonClass(avmplus::VTable* cvtable);
			avmplus::ScriptObject* createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype);

			DECLARE_SLOTS_SimpleButtonClass;
		};

		class SimpleButton : public InteractiveObject, public vtx::ScriptButton
		{
		public:
			SimpleButton(avmplus::VTable* vtable, avmplus::ScriptObject* prototype);
			virtual ~SimpleButton();

			vtx::ScriptObject* getChildScriptObject(const String& name);

			void buttonUp();

			virtual double get_x();
			virtual void set_x(double val);

			virtual double get_y();
			virtual void set_y(double val);

			virtual double get_rotation();
			virtual void set_rotation(double val);

			DECLARE_SLOTS_SimpleButton;

		protected:
			csp::VmCore* mCore;
			csp::ScriptObject* mObject;
		};
	}
}

#endif
