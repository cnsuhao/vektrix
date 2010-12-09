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

#include "vtxas3ScriptInterface.h"
#include "vtxas3Object.h"

#include "cspVmCore.h"

namespace vtx { namespace as3 {
	//-----------------------------------------------------------------------
	ScriptInterface::ScriptInterface(AS3Object* as3_object) 
		: mAS3Object(as3_object)
	{

	}
	//-----------------------------------------------------------------------
	ScriptInterface::~ScriptInterface()
	{

	}
	//-----------------------------------------------------------------------
	AS3Object* ScriptInterface::getObject() const
	{
		return mAS3Object;
	}
	//-----------------------------------------------------------------------
	void ScriptInterface::eventFired(const vtx::Event& evt)
	{
		mAS3Object->eventFired(evt);
	}
	//-----------------------------------------------------------------------
	void ScriptInterface::setNativeObject(Instance* inst)
	{
		vtx::ScriptObject::setNativeObject(inst);
		mAS3Object->init(inst, this);
	}
	//-----------------------------------------------------------------------
	void ScriptInterface::setChildObject(const String& name, vtx::ScriptObject* script_object)
	{
		mAS3Object->setChildObject(name, script_object);
	}
	//-----------------------------------------------------------------------
	vtx::ScriptObject* ScriptInterface::getChildObject(const String& name)
	{
		return mAS3Object->getChildObject(name);
	}
	//-----------------------------------------------------------------------
}}
