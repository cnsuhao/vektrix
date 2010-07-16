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

#include "vtxas3ScriptObjectBase.h"

#include "vtxFocusEvent.h"
#include "vtxInstance.h"
#include "vtxLogManager.h"
#include "vtxMouseEvent.h"

#include "cspVmCore.h"

namespace vtx { namespace as3 {
	//-----------------------------------------------------------------------
	EventDispatcher::EventDispatcher(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
		: ScriptObjectBase(vtable, prototype)
	{
		if(!RefCount())
		{
			IncrementRef();
		}
	}
	//-----------------------------------------------------------------------
	void EventDispatcher::addEventListener(avmplus::Stringp type, avmplus::FunctionObject* function, bool useCapture, int priority, bool useWeakReference)
	{
		MMGC_GCENTER(core()->GetGC());
		String tp = CSP_CORE->stringFromAS3(type);
		mHandlers[tp].push_back(function);
		function->IncrementRef();
	}
	//-----------------------------------------------------------------------
	bool EventDispatcher::dispatchEvent(as3::Event* event)
	{
		MMGC_GCENTER(core()->GetGC());
		String type = CSP_CORE->stringFromAS3(event->getType());

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
	bool EventDispatcher::hasEventListener(avmplus::Stringp type)
	{
		MMGC_GCENTER(core()->GetGC());
		String stl_type = CSP_CORE->stringFromAS3(type);

		return (mHandlers.find(stl_type) != mHandlers.end());
	}
	//-----------------------------------------------------------------------
	void EventDispatcher::removeEventListener(avmplus::Stringp type, avmplus::FunctionObject* function, bool useWeakReference)
	{
		MMGC_GCENTER(core()->GetGC());
		String stl_type = CSP_CORE->stringFromAS3(type);

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
		MMGC_GCENTER(core()->GetGC());

		if(evt.getCategory() == MouseEvent::CATEGORY)
		{
			const MouseEvent& mouse_evt = static_cast<const MouseEvent&>(evt);

			csp::ArgumentList args;
			args.push_back(CSP_CORE->newString(evt.getType().c_str()));
			args.push_back(CSP_CORE->newBoolean(false));
			args.push_back(CSP_CORE->newBoolean(true));

			avmplus::ScriptObject* evt = CSP_CORE->createObject("MouseEvent", "flash.events", args);

			dispatchEvent((as3::Event*)evt);

			delete evt;
		}
		else if(evt.getCategory() == FocusEvent::CATEGORY)
		{
			const FocusEvent& focus_evt = static_cast<const FocusEvent&>(evt);

			csp::ArgumentList args;
			args.push_back(CSP_CORE->newString(evt.getType().c_str()));
			args.push_back(CSP_CORE->newBoolean(false));
			args.push_back(CSP_CORE->newBoolean(true));

			avmplus::ScriptObject* evt = CSP_CORE->createObject("FocusEvent", "flash.events", args);

			dispatchEvent((as3::Event*)evt);

			delete evt;
		}
	}
	//-----------------------------------------------------------------------
	void EventDispatcher::setChildObject(const String& name, vtx::ScriptObject* script_object)
	{
		if(!script_object)
		{
			VTX_EXCEPT("EventDispatcher::setChildObject(NULL)");
		}

		csp::VmCore::setSlotObject(this, name, static_cast<ScriptObjectBase*>(script_object));
	}
	//-----------------------------------------------------------------------
}}
