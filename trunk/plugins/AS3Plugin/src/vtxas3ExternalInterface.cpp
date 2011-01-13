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

#include "vtxas3ExternalInterface.h"
#include "vtxas3ScriptEngine.h"

#include "vtxScriptCallbackListener.h"

#include "cspVmCore.h"

namespace vtx { namespace as3 {
	//-----------------------------------------------------------------------
	ExternalInterfaceClass::ExternalInterfaceClass(avmplus::VTable* cvtable) 
		: ClassClosure(cvtable)
	{

	}
	//-----------------------------------------------------------------------
	bool ExternalInterfaceClass::get_available()
	{
		AS3ScriptEngine* engine = static_cast<AS3ScriptEngine*>(CSP_CORE->getUserData());
		return (engine->getCallbackListener() != 0);
	}
	//-----------------------------------------------------------------------
	void ExternalInterfaceClass::addCallback(avmplus::Stringp functionName, avmplus::FunctionObject* function)
	{
		AS3ScriptEngine* engine = static_cast<AS3ScriptEngine*>(CSP_CORE->getUserData());
		engine->addScriptFunction(CSP_CORE->toString(functionName), function);
	}
	//-----------------------------------------------------------------------
	avmplus::Atom ExternalInterfaceClass::call(avmplus::Stringp functionName, avmplus::Atom* args, uint argc)
	{
		AS3ScriptEngine* engine = static_cast<AS3ScriptEngine*>(CSP_CORE->getUserData());
		ScriptCallbackListener* listener = engine->getCallbackListener();

		if(listener)
		{
			ScriptParamList params;
			for(uint i=0; i<argc; ++i)
				params.push_back(engine->atomToParam(args[i]));

			ScriptParam result = listener->scriptCallback(CSP_CORE->toString(functionName), params);
			return engine->paramToAtom(result);
		}
		else
			return nullObjectAtom;
	}
	//-----------------------------------------------------------------------
}}
