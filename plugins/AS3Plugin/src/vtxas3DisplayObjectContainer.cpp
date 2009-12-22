#include "flash_package.h"

namespace vtx
{
	namespace as3
	{
		//-----------------------------------------------------------------------
		DisplayObjectContainerClass::DisplayObjectContainerClass(avmplus::VTable* cvtable) 
			: ClassClosure(cvtable)
		{
			AvmAssert(traits()->getSizeOfInstance() == sizeof(DisplayObjectContainerClass));
			createVanillaPrototype();
		}
		//-----------------------------------------------------------------------
		avmplus::ScriptObject* DisplayObjectContainerClass::createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype)
		{
			return new (core()->GetGC(), ivtable->getExtraSize()) DisplayObjectContainer(ivtable, prototype);
		}
		//-----------------------------------------------------------------------
		DisplayObjectContainer::DisplayObjectContainer(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
			: InteractiveObject(vtable, prototype)
		{

		}
		//-----------------------------------------------------------------------
	}
}
