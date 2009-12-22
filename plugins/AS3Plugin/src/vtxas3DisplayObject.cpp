#include "flash_package.h"

namespace vtx
{
	namespace as3
	{
		//-----------------------------------------------------------------------
		DisplayObjectClass::DisplayObjectClass(avmplus::VTable* cvtable) 
			: ClassClosure(cvtable)
		{
			AvmAssert(traits()->getSizeOfInstance() == sizeof(DisplayObjectClass));
			createVanillaPrototype();
		}
		//-----------------------------------------------------------------------
		avmplus::ScriptObject* DisplayObjectClass::createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype)
		{
			return new (core()->GetGC(), ivtable->getExtraSize()) DisplayObject(ivtable, prototype);
		}
		//-----------------------------------------------------------------------
		DisplayObject::DisplayObject(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
			: EventDispatcher(vtable, prototype)
		{
			mValue = 0;
		}
		//-----------------------------------------------------------------------
		double DisplayObject::get_x()
		{
			return mValue;
		}
		//-----------------------------------------------------------------------
		void DisplayObject::set_x(double val)
		{
			mValue = val;
		}
		//-----------------------------------------------------------------------
	}
}
