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

#include "vtxas3EventDispatcher.h"
#include "vtxas3Event.h"
#include "vtxas3Object.h"

#include "vtxFileEvent.h"
#include "vtxFocusEvent.h"
#include "vtxInstance.h"
#include "vtxLogManager.h"
#include "vtxMouseEvent.h"
#include "vtxStringHelper.h"

#include "cspVmCore.h"

#include "vtxas3ScriptInterface.h"

using namespace avmplus;

namespace vtx { namespace as3 {
	//-----------------------------------------------------------------------
	EventDispatcher::EventDispatcher(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
		: AS3Object(vtable, prototype)
	{
		MMGC_GCENTER(core()->GetGC());
		dispatchEvent = CSP_CORE->getMethodEnv(this, "dispatchEvent");
	}
	//-----------------------------------------------------------------------
	void EventDispatcher::ctor(avmplus::ScriptObject* target)
	{
		AS3Object::ctor();
	}
	//-----------------------------------------------------------------------
	const String& EventDispatcher::getMappedVektrixType() const
	{
		static String type = "NONE";
		VTX_DEBUG_ASSERT(true, "error");
		return type;
	}
	//-----------------------------------------------------------------------
	void EventDispatcher::eventFired(const vtx::Event& evt)
	{
		MMGC_GCENTER(core()->GetGC());

		if(evt.getType().length() == 0 || evt.getCategory() == FileEvent::CATEGORY) return;

		TRY(core(), kCatchAction_ReportAsError)
		{
			VTX_DEBUG_ASSERT(evt.getType().length(), "evt.type.length == 0");

			uint num_args = 3;
			Atom* evt_args = new Atom[16];
			evt_args[1] = CSP_CORE->toScript(evt.getType());
			evt_args[2] = CSP_CORE->toScript(false);
			evt_args[3] = CSP_CORE->toScript(true);

			if(evt.getCategory() == vtx::MouseEvent::CATEGORY)
			{
				const vtx::MouseEvent& mouse_evt = static_cast<const vtx::MouseEvent&>(evt);
				evt_args[4] = CSP_CORE->toScript(mouse_evt.stageX);
				evt_args[5] = CSP_CORE->toScript(mouse_evt.stageY);
				num_args = 5;
			}

			if(evt.getType() == vtx::Event::ENTER_FRAME)
				VTX_LOG("ENTER_FRAME dispatched from %u", (uint)this);

			Event* as3_evt = static_cast<Event*>(CSP_CORE->createObject(evt.getCategory(), "flash.events", num_args, evt_args));
			delete[] evt_args;

			//as3_evt->setCurrentTarget(this);
			//as3_evt->setTarget(this);

			// call the AS3 "dispatch" method
			Atom dispatch_args[] = { atom(), as3_evt->atom() };
			csp::VmCore::callFunction(this, dispatchEvent, dispatch_args);

			if(as3_evt->RefCount() > 0)
				as3_evt->DecrementRef();
		}
		CATCH(Exception* exception)
		{
			CSP_CORE->printException(exception);
		}
		END_CATCH
		END_TRY
	}
	//-----------------------------------------------------------------------
}}
