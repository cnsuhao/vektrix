#include "flash_package.h"

#include "vtxButton.h"

#include "cspInternalCore.h"
#include "cspVmCore.h"
#include "cspScriptObject.h"

namespace vtx
{
	namespace as3
	{
		//-----------------------------------------------------------------------
		SimpleButtonClass::SimpleButtonClass(avmplus::VTable* cvtable) 
			: ClassClosure(cvtable)
		{
			AvmAssert(traits()->getSizeOfInstance() == sizeof(SimpleButtonClass));
			createVanillaPrototype();
		}
		//-----------------------------------------------------------------------
		avmplus::ScriptObject* SimpleButtonClass::createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype)
		{
			return new (core()->GetGC(), ivtable->getExtraSize()) SimpleButton(ivtable, prototype);
		}
		//-----------------------------------------------------------------------
		SimpleButton::SimpleButton(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
			: InteractiveObject(vtable, prototype)
		{
			mCore = csp::VmCore::fromAvmplus(core());
		}
		//-----------------------------------------------------------------------
		SimpleButton::~SimpleButton()
		{
			delete csp::ScriptObject::fromAvmplus(this);
			mObject = 0;
		}
		//-----------------------------------------------------------------------
		vtx::ScriptObject* SimpleButton::getChildScriptObject(const String& name)
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

				return vtx_obj;
			}

			return NULL;
		}
		//-----------------------------------------------------------------------
		void SimpleButton::buttonUp()
		{
			if(!mObject)
			{
				mObject = csp::ScriptObject::fromAvmplus(this);
			}

			if(mCore && mObject)
			{
				csp::ArgumentList args;
				args.push_back(mCore->newString("click"));
				args.push_back(mCore->newBoolean(false));
				args.push_back(mCore->newBoolean(true));

				csp::ScriptObject* evt = mCore->createObject("MouseEvent", "flash.events", args);
				args.clear();
				args.push_back(evt->atom());

				mObject->callFunction("dispatchEvent", args);
				//vm_core->callObjectFunction(this, "dispatchEvent", args);

				delete evt;
			}
		}
		//-----------------------------------------------------------------------
		double SimpleButton::get_x()
		{
			//std::cout << "get_x" << std::endl;
			if(mButton)
			{
				return mButton->_getWorldMatrix().m[0][2];
			}

			return 0;
		}
		//-----------------------------------------------------------------------
		void SimpleButton::set_x(double val)
		{
			if(mButton)
			{
				Matrix mat = mButton->_getWorldMatrix();
				mat.m[0][2] = (float)val;
				mButton->setMatrix(mat);
			}
		}
		//-----------------------------------------------------------------------
	}
}
