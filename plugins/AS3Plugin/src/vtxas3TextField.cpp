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

#include "flash_package.h"

#include "vtxEditText.h"

#include "cspInternalCore.h"
#include "cspVmCore.h"
#include "cspScriptObject.h"

namespace vtx
{
	namespace as3
	{
		//-----------------------------------------------------------------------
		TextFieldClass::TextFieldClass(avmplus::VTable* cvtable) 
			: ClassClosure(cvtable)
		{
			AvmAssert(traits()->getSizeOfInstance() == sizeof(TextFieldClass));
			createVanillaPrototype();
		}
		//-----------------------------------------------------------------------
		avmplus::ScriptObject* TextFieldClass::createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype)
		{
			return new (core()->GetGC(), ivtable->getExtraSize()) TextField(ivtable, prototype);
		}
		//-----------------------------------------------------------------------
		TextField::TextField(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
			: InteractiveObject(vtable, prototype)
		{

		}
		//-----------------------------------------------------------------------
		TextField::~TextField()
		{
			delete getCaspinObject();
		}
		//-----------------------------------------------------------------------
		void TextField::setNativeObject(Instance* inst)
		{
			InteractiveObject::setNativeObject(inst);
			mEditText = dynamic_cast<vtx::EditText*>(inst);
		}
		//-----------------------------------------------------------------------
		//void TextField::eventFired(const Event& evt)
		//{
		//	InteractiveObject::eventFired(evt);
		//}
		//-----------------------------------------------------------------------
		avmplus::Stringp TextField::get_htmlText()
		{
			csp::VmCore* core = getCaspinCore();

			if(mEditText && core)
			{
				return core->stl2cspUTF8(mEditText->getHtmlText());
			}

			return core->stl2csp("");
		}
		//-----------------------------------------------------------------------
		void TextField::set_htmlText(avmplus::Stringp htmlText)
		{
			csp::VmCore* core = getCaspinCore();

			if(mEditText && core)
			{
				mEditText->setHtmlText(core->csp2stlUTF8(htmlText));
			}
		}
		//-----------------------------------------------------------------------
		int TextField::getLineIndexAtPoint(double x, double y)
		{
			if(mEditText)
			{
				return mEditText->getLineAtPoint(Vector2((float)x, (float)y)).index;
			}

			return -1;
		}
		//-----------------------------------------------------------------------
		void TextField::setSelection(int beginIndex, int endIndex)
		{
			if(mEditText)
			{
				mEditText->setSelection(beginIndex, endIndex);
			}
		}
		//-----------------------------------------------------------------------
		vtx::ScriptObject* TextField::_createChildObject(const String& name)
		{
			csp::ScriptObject* parent_obj = csp::ScriptObject::fromAvmplus(this);
			if(parent_obj)
			{
				csp::ScriptObject* slot_obj = parent_obj->createSlotObject(name);
				if(slot_obj)
				{
					return dynamic_cast<vtx::ScriptObject*>(slot_obj->scriptObj());
				}
			}

			return NULL;
		}
		//-----------------------------------------------------------------------
	}
}
