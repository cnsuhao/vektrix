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

#include "vtxas3Object.h"
#include "vtxas3ScriptInterface.h"

#include "vtxInstance.h"
#include "vtxLogManager.h"
#include "vtxScriptEngine.h"

#include "cspVmCore.h"

namespace vtx { namespace as3 {
	//-----------------------------------------------------------------------
	AS3Object::AS3Object(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
		: avmplus::ScriptObject(vtable, prototype)
	{
		if(RefCount() == 0)
			IncrementRef();
	}
	//-----------------------------------------------------------------------
	AS3Object::~AS3Object()
	{

	}
	//-----------------------------------------------------------------------
	void AS3Object::ctor()
	{

	}
	//-----------------------------------------------------------------------
	void AS3Object::init(Instance* inst, ScriptInterface* iface)
	{
		mNativeObject = inst;
		mInterface = iface;
	}
	//-----------------------------------------------------------------------
	void AS3Object::setChildObject(const String& name, vtx::ScriptObject* script_object)
	{
		ScriptInterface* iface = static_cast<ScriptInterface*>(script_object);
		csp::VmCore::setSlotObject(this, name, iface->getObject());
	}
	//-----------------------------------------------------------------------
	vtx::ScriptObject* AS3Object::getChildObject(const String& name)
	{
		AS3Object* as3_obj = static_cast<AS3Object*>(csp::VmCore::getSlotObject(this, name));
		return as3_obj->getInterface();
	}
	//-----------------------------------------------------------------------
	AS3ScriptEngine* AS3Object::getEngine() const
	{
		return static_cast<AS3ScriptEngine*>(CSP_CORE->getUserData());
	}
	//-----------------------------------------------------------------------
	Movie* AS3Object::getParentMovie() const
	{
		return static_cast<ScriptEngine*>(CSP_CORE->getUserData())->getParentMovie();
	}
	//-----------------------------------------------------------------------
	Instance* AS3Object::getNativeObject() const
	{
		return mNativeObject;
	}
	//-----------------------------------------------------------------------
	ScriptInterface* AS3Object::getInterface() const
	{
		return mInterface;
	}
	//-----------------------------------------------------------------------
}}
