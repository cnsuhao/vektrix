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

#include "vtxButton.h"

#include "cspInternalCore.h"
#include "cspVmCore.h"
#include "cspScriptObject.h"

namespace vtx
{
	namespace as3
	{
		//-----------------------------------------------------------------------
		SimpleButtonClass::SimpleButtonClass(avmplus::VTable* cvtable) 
			: ClassClosure(cvtable)
		{
			AvmAssert(traits()->getSizeOfInstance() == sizeof(SimpleButtonClass));
			createVanillaPrototype();
		}
		//-----------------------------------------------------------------------
		avmplus::ScriptObject* SimpleButtonClass::createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype)
		{
			return new (core()->GetGC(), ivtable->getExtraSize()) SimpleButton(ivtable, prototype);
		}
		//-----------------------------------------------------------------------
		SimpleButton::SimpleButton(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
			: InteractiveObject(vtable, prototype)
		{
			mCore = csp::VmCore::fromAvmplus(core());
		}
		//-----------------------------------------------------------------------
		SimpleButton::~SimpleButton()
		{
			delete csp::ScriptObject::fromAvmplus(this);
			mObject = 0;
		}
		//-----------------------------------------------------------------------
		vtx::ScriptObject* SimpleButton::getChildScriptObject(const String& name)
		{
			ChildMap::iterator it = mChildren.find(name);
			if(it != mChildren.end())
			{
				return it->second;
			}

			csp::ScriptObject* parent_obj = csp::ScriptObject::fromAvmplus(this);
			if(parent_obj)
			{
				csp::ScriptObject* slot_obj = parent_obj->createSlotObject(name);
				vtx::ScriptObject* vtx_obj = dynamic_cast<vtx::ScriptObject*>(slot_obj->scriptObj());
				if(vtx_obj)
				{
					mChildren.insert(std::make_pair(name, vtx_obj));
				}

				return vtx_obj;
			}

			return NULL;
		}
		//-----------------------------------------------------------------------
		void SimpleButton::buttonUp()
		{
			if(!mObject)
			{
				mObject = csp::ScriptObject::fromAvmplus(this);
			}

			if(mCore && mObject)
			{
				csp::ArgumentList args;
				args.push_back(mCore->newString("click"));
				args.push_back(mCore->newBoolean(false));
				args.push_back(mCore->newBoolean(true));

				csp::ScriptObject* evt = mCore->createObject("MouseEvent", "flash.events", args);
				args.clear();
				args.push_back(evt->atom());

				mObject->callFunction("dispatchEvent", args);

				delete evt;
			}
		}
		//-----------------------------------------------------------------------
		double SimpleButton::get_x()
		{
			if(mButton)
			{
				return mButton->getX();
			}

			return 0;
		}
		//-----------------------------------------------------------------------
		void SimpleButton::set_x(double val)
		{
			if(mButton)
			{
				mButton->setX((float)val);
			}
		}
		//-----------------------------------------------------------------------
		double SimpleButton::get_y()
		{
			if(mButton)
			{
				return mButton->getY();
			}

			return 0;
		}
		//-----------------------------------------------------------------------
		void SimpleButton::set_y(double val)
		{
			if(mButton)
			{
				mButton->setY((float)val);
			}
		}
		//-----------------------------------------------------------------------
		double SimpleButton::get_rotation()
		{
			if(mButton)
			{
				return mButton->getAngle();
			}

			return 0;
		}
		//-----------------------------------------------------------------------
		void SimpleButton::set_rotation(double val)
		{
			if(mButton)
			{
				mButton->setAngle((float)val);
			}
		}
		//-----------------------------------------------------------------------
	}
}
