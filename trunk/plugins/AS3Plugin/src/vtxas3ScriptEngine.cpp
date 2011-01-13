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

#include "vtxas3ScriptEngine.h"
//#include "vtxas3MovieClip.h"

#include "vtxswfScriptResource.h"

#include "vtxButton.h"
#include "vtxEditText.h"
#include "vtxFile.h"
#include "vtxLogManager.h"
#include "vtxMovie.h"
#include "vtxMovieClip.h"
#include "vtxResource.h"
#include "vtxScriptObject.h"
#include "vtxStage.h"
#include "vtxStaticText.h"
#include "vtxStringHelper.h"

#include "cspNativePackage.h"
#include "cspSystem.h"
#include "cspVmCore.h"

// TODO: remove this hack
#ifdef __FlashGlue_H__
#undef __FlashGlue_H__
#endif

#include "flash_package.h"

#include "vtxas3ScriptInterface.h"

using namespace avmplus;

namespace vtx { namespace as3 {
	//-----------------------------------------------------------------------
	AS3ScriptEngine::AS3ScriptEngine(Movie* parent) 
		: ScriptEngine(parent), 
		mVmCore(NULL), 
		mRootObject(NULL), 
		mScriptResource(NULL), 
		mQueuedInstance(NULL)
	{
		CSP_CREATE_VMCORE(mVmCore);
		mVmCore->setUserData(this);

		mVmCore->addListener(this);

		NativePackage(mVmCore, avmplus::NativeID, caspin_base);

#ifdef  VTX_AS3_USE_SINGLE_ABC_PACKAGE

		NativePackage(mVmCore, avmplus::NativeID, flash);

#else

		NativePackage(mVmCore, flash::accessibility,	flash_accessibility);
		NativePackage(mVmCore, flash::events,			flash_events);
		NativePackage(mVmCore, flash::display,			flash_display);
		NativePackage(mVmCore, flash::filters,			flash_filters);
		NativePackage(mVmCore, flash::geom,				flash_geom);
		NativePackage(mVmCore, flash::media,			flash_media);
		NativePackage(mVmCore, flash::net,				flash_net);
		NativePackage(mVmCore, flash::system,			flash_system);
		NativePackage(mVmCore, flash::text,				flash_text);
		NativePackage(mVmCore, flash::ui,				flash_ui);
		NativePackage(mVmCore, flash::utils,			flash_utils);
		NativePackage(mVmCore, vektrix,					vektrix);

#endif

		mVmCore->initializePackages();
	}
	//-----------------------------------------------------------------------
	AS3ScriptEngine::~AS3ScriptEngine()
	{
		CSP_DESTROY_VMCORE(mVmCore);
	}
	//-----------------------------------------------------------------------
	bool AS3ScriptEngine::executeCode(ScriptResource* resource)
	{
		if(resource->getScriptType() != swf::ScriptResource::SCRIPT_TYPE || mScriptResource)
		{
			return false;
		}

		mScriptResource = static_cast<swf::ScriptResource*>(resource);
		
		return mVmCore->executeByteCode(mScriptResource->getBuffer(), mScriptResource->getBufferSize());
	}
	//-----------------------------------------------------------------------
	ScriptParam AS3ScriptEngine::callScriptFunction(const String& function_name, const ScriptParamList& args)
	{
		TRY(mVmCore, kCatchAction_ReportAsError)
		{
			MMGC_GCENTER(mVmCore->GetGC());
			static avmplus::Atom params[16];

			FunctionMap::iterator it = mCallableFunctions.find(function_name);
			if(it != mCallableFunctions.end())
			{
				params[0] = it->second->atom();

				for(uint i=0; i<args.size(); ++i)
					params[i+1] = paramToAtom(args[i]);

				avmplus::Atom result = it->second->call(args.size(), params);
				return atomToParam(result);
			}
		}
		CATCH(Exception* exception)
		{
			mVmCore->printException(exception);
		}
		END_CATCH;
		END_TRY;

		return ScriptParam::Null;
	}
	//-----------------------------------------------------------------------
	ScriptObject* AS3ScriptEngine::getRootScriptObject(vtx::MovieClip* movieclip)
	{
		VTX_EXCEPT("Deprecated function called!");
		return NULL;
	}
	//-----------------------------------------------------------------------
	ScriptObject* AS3ScriptEngine::createScriptObject(Instance* instance)
	{
		MMGC_GCENTER(mVmCore->GetGC());

		TRY(mVmCore, kCatchAction_ReportAsError)
		{
			AS3Object* script_object = NULL;
			Resource* resource = instance->getResource();

			mQueuedInstance = instance;

			if(mScriptResource && resource)
			{
				if(mScriptResource->hasSymbol(resource->getID()))
				{
					const StringPair class_def = mScriptResource->getSymbol(resource->getID());
					std::cout << "-----------------------------------------------------------" << std::endl;
					VTX_LOG("Creating script object: %s -> %s", class_def.second.c_str(), class_def.first.c_str());
					std::cout << "-----------------------------------------------------------" << std::endl;
					script_object = static_cast<AS3Object*>(mVmCore->createObject(class_def.second, class_def.first));
				}
			}

			if(!script_object)
			{
				std::cout << "-----------------------------------------------------------" << std::endl;
				std::cout << "Creating script object: " << instance->getType() << std::endl;
				std::cout << "-----------------------------------------------------------" << std::endl;

				if(instance->getType() == vtx::Stage::TYPE)
					script_object = static_cast<AS3Object*>(mVmCore->createObject("Stage", "flash.display"));

				else if(instance->getType() == vtx::MovieClip::TYPE)
					script_object = static_cast<AS3Object*>(mVmCore->createObject("MovieClip", "flash.display"));

				else if(instance->getType() == vtx::EditText::TYPE)
					script_object = static_cast<AS3Object*>(mVmCore->createObject("TextField", "flash.text"));

				else if(instance->getType() == vtx::StaticText::TYPE)
					script_object = static_cast<AS3Object*>(mVmCore->createObject("StaticText", "flash.text"));

				else if(instance->getType() == vtx::Button::TYPE)
					script_object = static_cast<AS3Object*>(mVmCore->createObject("SimpleButton", "flash.display"));
			}

			mVmCore->stickyObject(script_object->atom());

			mQueuedInstance = NULL;

			if(!script_object)
				return NULL;

			if(!instance->getScriptObject())
			{
				ScriptInterface* iface = new ScriptInterface(script_object);
				instance->setScriptObject(iface);
			}

			return instance->getScriptObject();
		}
		CATCH(Exception* exception)
		{
			mVmCore->printException(exception);
		}
		END_CATCH;
		END_TRY;

		return NULL;
	}
	//-----------------------------------------------------------------------
	void AS3ScriptEngine::destroyScriptObject(ScriptObject* script_object)
	{

	}
	//-----------------------------------------------------------------------
	Instance* AS3ScriptEngine::getQueuedInstance()
	{
		Instance* result = mQueuedInstance;
		mQueuedInstance = NULL;
		return result;
	}
	//-----------------------------------------------------------------------
	void AS3ScriptEngine::output(const String& message)
	{
		VTX_LOG("ActionScript3: '%s'", message.c_str());
	}
	//-----------------------------------------------------------------------
	void AS3ScriptEngine::addScriptFunction(const String& function_name, avmplus::FunctionObject* function)
	{
		FunctionMap::iterator it = mCallableFunctions.find(function_name);
		if(it == mCallableFunctions.end())
		{
			mVmCore->stickyObject(function->atom());
			mCallableFunctions.insert(std::make_pair(function_name, function));
			return;
		}

		// remove previously added function
		if(!function)
		{
			mVmCore->unstickyObject(it->second->atom());
			mCallableFunctions.erase(it);
		}
	}
	//-----------------------------------------------------------------------
	ScriptParam AS3ScriptEngine::atomToParam(avmplus::Atom atom)
	{
		if(csp::VmCore::isBoolean(atom))
			return csp::VmCore::atomToBool(atom); // bool

		else if(csp::VmCore::isNumber(atom))
			if(csp::VmCore::isDouble(atom))
				return csp::VmCore::atomToDouble(atom); // double
			else
				return csp::VmCore::integer(atom); // int

		else if(mVmCore->isString(atom))
			return mVmCore->toString(csp::VmCore::atomToString(atom)); // String

		return ScriptParam::Null;
	}
	//-----------------------------------------------------------------------
	avmplus::Atom AS3ScriptEngine::paramToAtom(ScriptParam param)
	{
		switch(param.type())
		{
		case SPT_bool:
			return mVmCore->toScript(param.boolValue());
			break;

		case SPT_double:
			return mVmCore->toScript(param.doubleValue());
			break;

		case SPT_int:
			return mVmCore->toScript(param.intValue());
			break;

		case SPT_string:
			return mVmCore->toScript(param.stringValue());
			break;
		}

		return nullObjectAtom;
	}
	//-----------------------------------------------------------------------
}}
