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
			: avmplus::ScriptObject(vtable, prototype)
		{

		}
		//-----------------------------------------------------------------------
		void EventDispatcher::addEventListener(avmplus::Stringp type, avmplus::FunctionObject* function, bool useCapture, int priority, bool useWeakReference)
		{
			String tp = mCore->csp2stl(type);
			mHandlers[tp].push_back(function);
			function->IncrementRef();
		}
		//-----------------------------------------------------------------------
		bool EventDispatcher::dispatchEvent(as3::Event* event)
		{
			String type = mCore->csp2stl(event->getType());

			FunctionMap::const_iterator funcs = mHandlers.find(type);
			if(funcs != mHandlers.end())
			{
				const FunctionList& functions = funcs->second;

				FunctionList::const_iterator it = functions.begin();
				FunctionList::const_iterator end = functions.end();
				while(it != end)
				{
					// call the function
					Atom args[2] = { (*it)->atom(), event->atom() };
					(*it)->call(1, args);
					++it;
				}

				return true;
			}

			return false;
		}
		//-----------------------------------------------------------------------
		void EventDispatcher::removeEventListener(avmplus::Stringp type, avmplus::FunctionObject* function, bool useWeakReference)
		{
			String stl_type = mCore->csp2stl(type);

			FunctionMap::iterator funcs = mHandlers.find(stl_type);
			if(funcs != mHandlers.end())
			{
				FunctionList& functions = funcs->second;

				FunctionList::iterator it = functions.begin();
				FunctionList::iterator end = functions.end();
				while(it != end)
				{
					if(*it == function)
					{
						(*it)->DecrementRef();
						functions.erase(it);
						return;
					}
					++it;
				}
			}

		}
		//-----------------------------------------------------------------------
		void EventDispatcher::eventFired(const vtx::Event& evt)
		{
			if(!mCore || !mScriptObject)
			{
				return;
			}

			MMGC_GCENTER(mCore->mIntCore->GetGC());

			if(evt.getCategory() == MouseEvent::CATEGORY)
			{
				const MouseEvent& mouse_evt = dynamic_cast<const MouseEvent&>(evt);

				csp::ArgumentList args;
				args.push_back(mCore->newString(evt.getType().c_str()));
				args.push_back(mCore->newBoolean(false));
				args.push_back(mCore->newBoolean(true));

				csp::ScriptObject* evt = mCore->createObject("MouseEvent", "flash.events", args);
				args.clear();
				args.push_back(evt->atom());

				dispatchEvent((as3::Event*)evt->scriptObj());
				//mScriptObject->callFunction("dispatchEvent", args);

				delete evt;
			}
			else if(evt.getCategory() == FocusEvent::CATEGORY)
			{
				const FocusEvent& focus_evt = dynamic_cast<const FocusEvent&>(evt);

				csp::ArgumentList args;
				args.push_back(mCore->newString(evt.getType().c_str()));
				args.push_back(mCore->newBoolean(false));
				args.push_back(mCore->newBoolean(true));

				csp::ScriptObject* evt = mCore->createObject("FocusEvent", "flash.events", args);
				args.clear();
				args.push_back(evt->atom());

				dispatchEvent((as3::Event*)evt->scriptObj());
				//mScriptObject->callFunction("dispatchEvent", args);

				delete evt;
			}
		}
		//-----------------------------------------------------------------------
		vtx::ScriptObject* EventDispatcher::_createChildObject(const String& name)
		{
			if(mScriptObject)
			{
				csp::ScriptObject* slot_obj = mScriptObject->createSlotObject(name);
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
