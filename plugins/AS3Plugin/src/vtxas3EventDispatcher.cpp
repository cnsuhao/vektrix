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

#include "vtxas3Object.h"

#include "vtxFocusEvent.h"
#include "vtxInstance.h"
#include "vtxLogManager.h"
#include "vtxMouseEvent.h"
#include "vtxStringHelper.h"

#include "cspVmCore.h"

#include "vtxas3ScriptInterface.h"

namespace vtx { namespace as3 {
	//-----------------------------------------------------------------------
	EventDispatcher::EventDispatcher(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
		: AS3Object(vtable, prototype)
	{
		//if(!RefCount())
		//{
		//	IncrementRef();
		//}
	}
	//-----------------------------------------------------------------------
	void EventDispatcher::addEventListener(avmplus::Stringp type, avmplus::FunctionObject* function, bool useCapture, int priority, bool useWeakReference)
	{
		MMGC_GCENTER(core()->GetGC());

		/*DictionaryObject* dict = get_private_mHandlers();
		Atom listeners = dict->getStringProperty(type);

		ArrayObject* array = NULL;

		if(listeners == undefinedAtom)
		{
			array = CSP_CORE->getToplevel()->arrayClass->newArray();
			dict->setStringProperty(type, array->atom());
		}
		else
		{
			array = static_cast<ArrayObject*>(AvmCore::atomToScriptObject(listeners));
		}

		Atom arg = function->atom();
		array->push(&arg, 1);
		*/

		//String tp = CSP_CORE->stringFromAS3(type);
		//mHandlers[tp].push_back(function);
		//std::cout << "added as3 event listener: " << tp << std::endl;
		//function->IncrementRef();
	}
	//-----------------------------------------------------------------------
	bool EventDispatcher::dispatchEvent(as3::Event* event)
	{
		MMGC_GCENTER(core()->GetGC());

		DictionaryObject* dict = get_private_mHandlers();

		Atom listeners = dict->getStringProperty(event->getType());
		if(listeners != undefinedAtom)
		{
			ArrayObject* array = static_cast<ArrayObject*>(AvmCore::atomToScriptObject(listeners));
			if(array)
			{
				for(uint i=0; i<array->get_length(); ++i)
				{
					Atom func_atom = array->getUintProperty(i);
					avmplus::ScriptObject* func = AvmCore::atomToScriptObject(func_atom);

					Atom args[2] = { func->atom(), event->atom() };
					func->call(1, args);
				}

				return true;
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool EventDispatcher::hasEventListener(avmplus::Stringp type)
	{
		MMGC_GCENTER(core()->GetGC());

		DictionaryObject* dict = get_private_mHandlers();

		Atom listeners = dict->getStringProperty(type);

		return (listeners != undefinedAtom);
	}
	//-----------------------------------------------------------------------
	void EventDispatcher::removeEventListener(avmplus::Stringp type, avmplus::FunctionObject* function, bool useWeakReference)
	{
		MMGC_GCENTER(core()->GetGC());
		
		/*
		DictionaryObject* dict = get_private_mHandlers();

		Atom listeners = dict->getStringProperty(type);
		if(listeners != undefinedAtom)
		{
			ArrayObject* array = static_cast<ArrayObject*>(AvmCore::atomToScriptObject(listeners));
			if(array)
			{
				for(uint i=0; i<array->get_length(); ++i)
				{
					Atom func_atom = array->getIntProperty(i);

					if(func_atom == function->atom())
					{
						ArrayObject* args = CSP_CORE->getToplevel()->arrayClass->newArray();
						Atom atom_args[2] = { i, 1 };
						args->push(atom_args, 2);

						//array->delUintProperty(i);
						toplevel()->arrayClass->splice(array->atom(), args);
						//ArrayClass::generic_splice(toplevel(), array->atom(), args);
						//array->delUintProperty(i);
					}
				}
			}

			if(array->get_length() == 0)
			{
				dict->deleteStringProperty(type);
			}
		}
		*/

		/*
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
		*/
	}
	//-----------------------------------------------------------------------
	void EventDispatcher::eventFired(const vtx::Event& evt)
	{
		MMGC_GCENTER(core()->GetGC());

		TRY(core(), kCatchAction_ReportAsError)
		{
			VTX_DEBUG_ASSERT(evt.getType().length(), "evt.type.length == 0");
			std::cout << "dispatch: " << evt.getType() << std::endl;
			csp::ArgumentList args;
			args.push_back(CSP_CORE->scriptString(evt.getType().c_str()));
			args.push_back(CSP_CORE->scriptBoolean(false));
			args.push_back(CSP_CORE->scriptBoolean(true));

			if(evt.getCategory() == vtx::MouseEvent::CATEGORY)
			{
				const vtx::MouseEvent& mouse_evt = static_cast<const vtx::MouseEvent&>(evt);
				args.push_back(CSP_CORE->internDouble(mouse_evt.stageX)->atom());
				args.push_back(CSP_CORE->internDouble(mouse_evt.stageY)->atom());
			}

			avmplus::ScriptObject* as3_evt = CSP_CORE->createObject(evt.getCategory(), "flash.events", args);

			dispatchEvent(static_cast<as3::Event*>(as3_evt));

			as3_evt->DecrementRef();
		}
		CATCH(Exception* exception)
		{
			CSP_CORE->printException(exception);
		}
		END_CATCH
		END_TRY

		/* old
		if(evt.getCategory() == vtx::MouseEvent::CATEGORY)
		{
			const vtx::MouseEvent& mouse_evt = static_cast<const vtx::MouseEvent&>(evt);

			csp::ArgumentList args;
			args.push_back(CSP_CORE->scriptString(evt.getType().c_str()));
			args.push_back(CSP_CORE->scriptBoolean(false));
			args.push_back(CSP_CORE->scriptBoolean(true));
			args.push_back(CSP_CORE->internDouble(mouse_evt.stageX)->atom());
			args.push_back(CSP_CORE->internDouble(mouse_evt.stageY)->atom());

			avmplus::ScriptObject* evt = CSP_CORE->createObject("MouseEvent", "flash.events", args);

			//args.clear();
			//args.push_back(evt->atom());

			//csp::VmCore::callObjectFunction(this, "dispatchEvent", args);
			dispatchEvent(static_cast<as3::Event*>(evt));

			//while(evt->RefCount() > 0) evt->DecrementRef();

			evt->DecrementRef();
		}
		else if(evt.getCategory() == FocusEvent::CATEGORY)
		{
			const FocusEvent& focus_evt = static_cast<const FocusEvent&>(evt);

			csp::ArgumentList args;
			args.push_back(CSP_CORE->scriptString(evt.getType().c_str()));
			args.push_back(CSP_CORE->scriptBoolean(false));
			args.push_back(CSP_CORE->scriptBoolean(true));

			avmplus::ScriptObject* evt = CSP_CORE->createObject("FocusEvent", "flash.events", args);

			//args.clear();
			//args.push_back(evt->atom());

			//csp::VmCore::callObjectFunction(this, "dispatchEvent", args);
			dispatchEvent(static_cast<as3::Event*>(evt));

			//while(evt->RefCount() > 0) evt->DecrementRef();

			evt->DecrementRef();
		}
		*/
	}
	//-----------------------------------------------------------------------
	void EventDispatcher::setChildObject(const String& name, vtx::ScriptObject* script_object)
	{
		if(!script_object)
		{
			return;
			VTX_EXCEPT("EventDispatcher::setChildObject(NULL)");
		}

		ScriptInterface* iface = static_cast<ScriptInterface*>(script_object);


		csp::VmCore::setSlotObject(this, name, iface->getObject());
	}
	//-----------------------------------------------------------------------
	vtx::ScriptObject* EventDispatcher::getChildObject(const String& name)
	{
		AS3Object* as3_obj = static_cast<AS3Object*>(csp::VmCore::getSlotObject(this, name));
		return as3_obj->getInterface();
	}
	//-----------------------------------------------------------------------
}}
