#include "flash_package.h"

namespace vtx
{
	namespace as3
	{
		//-----------------------------------------------------------------------
		SpriteClass::SpriteClass(avmplus::VTable* cvtable) 
			: ClassClosure(cvtable)
		{
			AvmAssert(traits()->getSizeOfInstance() == sizeof(SpriteClass));
			createVanillaPrototype();
		}
		//-----------------------------------------------------------------------
		avmplus::ScriptObject* SpriteClass::createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype)
		{
			return new (core()->GetGC(), ivtable->getExtraSize()) Sprite(ivtable, prototype);
		}
		//-----------------------------------------------------------------------
		Sprite::Sprite(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
			: DisplayObjectContainer(vtable, prototype)
		{

		}
		//-----------------------------------------------------------------------
	}
}
