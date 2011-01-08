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

#include "vtxas3FlashUtils.h"

#include "cspVmCore.h"

using namespace avmplus;

namespace vtx { namespace as3 {
	//-----------------------------------------------------------------------
	FlashUtilsClass::FlashUtilsClass(avmplus::VTable* cvtable) 
		: ClassClosure(cvtable)
	{
		AvmAssert(traits()->getSizeOfInstance() == sizeof(FlashUtilsClass));
		createVanillaPrototype();
	}
	//-----------------------------------------------------------------------
	ClassClosure* FlashUtilsClass::getClass(Stringp name)
	{
		MMGC_GCENTER(name->core()->GetGC());

		csp::VmCore* core = CSP_CORE_EX(name->core());
		Toplevel* tplvl = core->getToplevel();

		TRY(core, kCatchAction_ReportAsError)
		{
			if(name == NULL)
			{
				tplvl->throwArgumentError(kNullArgumentError, core->toErrorString("name"));
			}

			int dot = name->lastIndexOf(core->cachedChars[(int)':']);

			Namespace* ns;
			Stringp className;
			if(dot >= 0)
			{
				Stringp uri = core->internString(name->substring(0, dot-1));
				ns = core->internNamespace(core->newNamespace(uri, Namespace::NS_Public, core->getAPI(NULL)));
				className = core->internString(name->substring(dot+1, name->length()));
			}
			else
			{
				ns = core->findPublicNamespace();
				className = core->internString(name);
			}

			Multiname multiname(ns, className);

			ScriptObject *container = finddef(multiname, core->getDomainEnv());
			if(!container)
			{
				tplvl->throwTypeError(kClassNotFoundError, core->toErrorString(&multiname));
			}

			Atom atom = tplvl->getproperty(container->atom(), &multiname, container->vtable);

			if(!AvmCore::istype(atom, core->traits.class_itraits))
			{
				tplvl->throwTypeError(kClassNotFoundError, core->toErrorString(&multiname));
			}

			return (ClassClosure*)AvmCore::atomToScriptObject(atom);
		}
		CATCH(Exception* exception)
		{
			core->printException(exception);
		}
		END_CATCH
		END_TRY

		return NULL;
	}
	//-----------------------------------------------------------------------
	avmplus::ScriptObject* FlashUtilsClass::finddef(const Multiname& multiname, DomainEnv* domainEnv)
	{
		Toplevel* tplvl = domainEnv->toplevel();
		csp::VmCore* core = CSP_CORE_EX(tplvl->core());

		ScriptEnv* script = (ScriptEnv*)core->getDomainEnv()->getScriptInit(multiname);

		if(script == (ScriptEnv*)BIND_AMBIGUOUS)
			tplvl->throwReferenceError(kAmbiguousBindingError, multiname);

		if(script == (ScriptEnv*)BIND_NONE)
			tplvl->throwReferenceError(kUndefinedVarError, multiname);

		if(script->global == NULL)
		{
			script->initGlobal();
			script->coerceEnter(script->global->atom());
		}

		return script->global;
	}
	//-----------------------------------------------------------------------
}}
