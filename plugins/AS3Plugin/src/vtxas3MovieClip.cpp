#include "flash_package.h"

#include "cspScriptObject.h"

namespace vtx
{
	namespace as3
	{
		//-----------------------------------------------------------------------
		MovieClipClass::MovieClipClass(avmplus::VTable* cvtable) 
			: ClassClosure(cvtable)
		{
			AvmAssert(traits()->getSizeOfInstance() == sizeof(MovieClipClass));
			createVanillaPrototype();
		}
		//-----------------------------------------------------------------------
		avmplus::ScriptObject* MovieClipClass::createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype)
		{
			return new (core()->GetGC(), ivtable->getExtraSize()) MovieClip(ivtable, prototype);
		}
		//-----------------------------------------------------------------------
		MovieClip::MovieClip(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
			: Sprite(vtable, prototype)
		{

		}
		//-----------------------------------------------------------------------
		MovieClip::~MovieClip()
		{
			delete csp::ScriptObject::fromAvmplus(this);
		}
		//-----------------------------------------------------------------------
		vtx::ScriptObject* MovieClip::getChildScriptObject(const String& name)
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

				// DEBUG
				parent_obj->callFunction("frame1");

				return vtx_obj;
			}

			return NULL;
		}
		//-----------------------------------------------------------------------
	}
}
