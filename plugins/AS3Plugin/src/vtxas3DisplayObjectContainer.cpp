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

#include "cspVmCore.h"

#include "vtxDisplayObjectContainer.h"

#include "vtxas3ScriptInterface.h"

namespace vtx { namespace as3 {
	//-----------------------------------------------------------------------
	DisplayObjectContainer::DisplayObjectContainer(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
		: InteractiveObject(vtable, prototype), 
		mDisplayObjectContainer(NULL)
	{

	}
	//-----------------------------------------------------------------------
	DisplayObjectContainer::~DisplayObjectContainer()
	{

	}
	//-----------------------------------------------------------------------
	int DisplayObjectContainer::get_numChildren()
	{
		return mDisplayObjectContainer->numChildren();
	}
	//-----------------------------------------------------------------------
	DisplayObject* DisplayObjectContainer::addChild(DisplayObject* child)
	{
		MMGC_GCENTER(core()->GetGC());
		//child->IncrementRef();
		vtx::Instance* inst = child->getNativeObject();
		vtx::DisplayObject* native_child = static_cast<vtx::DisplayObject*>(inst);
		if(native_child && mDisplayObjectContainer)
		{
			mDisplayObjectContainer->addChild(native_child);
			return child;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	DisplayObject* DisplayObjectContainer::addChildAt(DisplayObject* child, int index)
	{
		vtx::DisplayObject* obj = static_cast<vtx::DisplayObject*>(child->getNativeObject());
		if(obj && mDisplayObjectContainer)
		{
			mDisplayObjectContainer->addChildAt(obj, index);
			return child;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	bool DisplayObjectContainer::contains(DisplayObject* child)
	{
		return false;
	}
	//-----------------------------------------------------------------------
	DisplayObject* DisplayObjectContainer::getChildAt(int index)
	{
		VTX_DEBUG_ASSERT(mDisplayObjectContainer, "DisplayObjectContainer::getChildAt()");

		vtx::DisplayObject* child = mDisplayObjectContainer->getChildAt(index);
		if(child)
		{
			ScriptInterface* iface = static_cast<ScriptInterface*>(child->getScriptObject());
			return static_cast<DisplayObject*>(iface->getObject());
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	DisplayObject* DisplayObjectContainer::getChildByName(avmplus::Stringp name)
	{
		MMGC_GCENTER(core()->GetGC());

		VTX_DEBUG_ASSERT(mDisplayObjectContainer, "DisplayObjectContainer::getChildByName()");

		String stl_name = CSP_CORE->stringFromAS3(name);
		vtx::DisplayObject* child = mDisplayObjectContainer->getChildByName(stl_name);

		if(child)
		{
			ScriptInterface* iface = static_cast<ScriptInterface*>(child->getScriptObject());
			return static_cast<DisplayObject*>(iface->getObject());
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	int DisplayObjectContainer::getChildIndex(DisplayObject* child)
	{
		return 0;
	}
	//-----------------------------------------------------------------------
	DisplayObject* DisplayObjectContainer::removeChild(DisplayObject* child)
	{
		return NULL;
	}
	//-----------------------------------------------------------------------
	DisplayObject* DisplayObjectContainer::removeChildAt(int index)
	{
		VTX_DEBUG_ASSERT(mDisplayObjectContainer, "DisplayObjectContainer::removeChildAt()");

		vtx::DisplayObject* child = mDisplayObjectContainer->removeChildAt(index);

		if(child)
		{
			ScriptInterface* iface = static_cast<ScriptInterface*>(child->getScriptObject());
			return static_cast<DisplayObject*>(iface->getObject());
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::setChildIndex(DisplayObject* child, int index)
	{

	}
	//-----------------------------------------------------------------------
	void DisplayObjectContainer::setNativeObject(Instance* inst)
	{
// 		InteractiveObject::setNativeObject(inst);
// 		mDisplayObjectContainer = static_cast<vtx::DisplayObjectContainer*>(inst);

		//if(!inst) return;

		//for(uint i=0; i<mDisplayObjectContainer->numChildren(); ++i)
		//{
		//	vtx::DisplayObject* child = mDisplayObjectContainer->getChildByIndex(i);
		//	if(child->getName().length())
		//	{
		//		ScriptObjectBase* obj = static_cast<ScriptObjectBase*>(child->getScriptObject());
		//		setChildObject(child->getName(), obj);
		//		//csp::VmCore::setSlotObject(this, child->getName(), obj);
		//	}
		//}
	}
	//-----------------------------------------------------------------------
}}
