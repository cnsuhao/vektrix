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

#include "vtxFocusEvent.h"
#include "vtxMouseEvent.h"

#include "cspInternalCore.h"
#include "cspScriptObject.h"
#include "cspVmCore.h"

#include "vtxInstance.h"

namespace vtx
{
	namespace as3
	{
		//-----------------------------------------------------------------------
		EventDispatcherClass::EventDispatcherClass(avmplus::VTable* cvtable) 
			: ClassClosure(cvtable)
		{
			AvmAssert(traits()->getSizeOfInstance() == sizeof(EventDispatcherClass));
			createVanillaPrototype();
		}
		//-----------------------------------------------------------------------
		avmplus::ScriptObject* EventDispatcherClass::createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype)
		{
			return new (core()->GetGC(), ivtable->getExtraSize()) EventDispatcher(ivtable, prototype);
		}
		//-----------------------------------------------------------------------
		EventDispatcher::EventDispatcher(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
			: avmplus::ScriptObject(vtable, prototype), 
			mNativeObject(NULL)
		{

		}
		//-----------------------------------------------------------------------
		void EventDispatcher::addEventListener(avmplus::Stringp type, avmplus::FunctionObject* function, bool useCapture, int priority, bool useWeakReference)
		{
			csp::VmCore* core = getCaspinCore();

			String tp = core->csp2stl(type);
			mHandlers[tp].push_back(function);
		}
		//-----------------------------------------------------------------------
		bool EventDispatcher::dispatchEvent(as3::Event* event)
		{
			csp::VmCore* core = getCaspinCore();

			String type = core->csp2stl(event->getType());

			//std::cout << "As3 dispatch event" << std::endl;

			FunctionMap::const_iterator funcs = mHandlers.find(type);
			if(funcs != mHandlers.end())
			{
				const FunctionList& functions = funcs->second;

				FunctionList::const_iterator it = functions.begin();
				FunctionList::const_iterator end = functions.end();
				while(it != end)
				{
					Atom args[2] = { (*it)->atom(), event->atom() };
					(*it)->call(1, args);
					++it;
				}

				return true;
			}

			return false;
		}
		//-----------------------------------------------------------------------
		void EventDispatcher::setNativeObject(Instance* inst)
		{
			mNativeObject = inst;
		}
		//-----------------------------------------------------------------------
		void EventDispatcher::eventFired(const vtx::Event& evt)
		{
			csp::VmCore* core = getCaspinCore();
			csp::ScriptObject* object = getCaspinObject();

			if(!core || !object)
			{
				return;
			}

			if(evt.getCategory() == MouseEvent::CATEGORY)
			{
				const MouseEvent& mouse_evt = dynamic_cast<const MouseEvent&>(evt);

				csp::ArgumentList args;
				args.push_back(core->newString(evt.getType().c_str()));
				args.push_back(core->newBoolean(false));
				args.push_back(core->newBoolean(true));

				csp::ScriptObject* evt = core->createObject("MouseEvent", "flash.events", args);
				args.clear();
				args.push_back(evt->atom());

				object->callFunction("dispatchEvent", args);

				delete evt;
			}
			else if(evt.getCategory() == FocusEvent::CATEGORY)
			{
				const FocusEvent& focus_evt = dynamic_cast<const FocusEvent&>(evt);

				csp::ArgumentList args;
				args.push_back(core->newString(evt.getType().c_str()));
				args.push_back(core->newBoolean(false));
				args.push_back(core->newBoolean(true));

				csp::ScriptObject* evt = core->createObject("FocusEvent", "flash.events", args);
				args.clear();
				args.push_back(evt->atom());

				object->callFunction("dispatchEvent", args);

				delete evt;
			}
		}
		//-----------------------------------------------------------------------
	}
}
