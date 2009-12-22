#include "flash_package.h"

#include "cspScriptObject.h"

namespace vtx
{
	namespace as3
	{
		//-----------------------------------------------------------------------
		EventHandlerClass::EventHandlerClass(avmplus::VTable* cvtable) 
			: ClassClosure(cvtable)
		{
			AvmAssert(traits()->getSizeOfInstance() == sizeof(EventHandlerClass));
			createVanillaPrototype();
		}
		//-----------------------------------------------------------------------
		avmplus::ScriptObject* EventHandlerClass::createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype)
		{
			return new (core()->GetGC(), ivtable->getExtraSize()) EventHandler(ivtable, prototype);
		}
		//-----------------------------------------------------------------------
		void EventHandlerClass::handle(avmplus::ScriptObject* evt)
		{
			std::cout << "native C++ EventHandler called" << std::endl;
			csp::ScriptObject* csp_evt = csp::ScriptObject::fromAvmplus(evt);
			if(csp_evt)
			{
				csp_evt->callFunction("debugEventDispatcher");
			}
		}
		//-----------------------------------------------------------------------
		EventHandler::EventHandler(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
			: ScriptObject(vtable, prototype)
		{

		}
		//-----------------------------------------------------------------------
	}
}
