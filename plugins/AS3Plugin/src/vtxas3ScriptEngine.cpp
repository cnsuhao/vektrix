#include "vtxas3ScriptEngine.h"

#include "vtxFile.h"
#include "vtxLogManager.h"
#include "vtxMovie.h"
#include "vtxScriptMovieClip.h"
#include "vtxStringHelper.h"

#include "cspNativePackage.h"
#include "cspScriptObject.h"
#include "cspVmCore.h"

#include "shell_toplevel.h"

using namespace avmplus;
#include "FileInputStream.h"
#include "ConsoleOutputStream.h"
#include "SystemClass.h"
#include "FileClass.h"
#include "DomainClass.h"
#include "DebugCLI.h"
#include "Profiler.h"
#include "DataIO.h"
#include "ByteArrayGlue.h"
#include "DictionaryGlue.h"
#include "SamplerScript.h"
#include "JavaGlue.h"

#include "shell_toplevel.cpp"

#include "flash_package.h"

namespace vtx
{
	namespace as3
	{
		//-----------------------------------------------------------------------
		AS3ScriptEngine::AS3ScriptEngine(Movie* parent) 
			: ScriptEngine(parent), 
			mVmCore(NULL), 
			mRoot(NULL), 
			mRootObject(NULL)
		{
			mVmCore = new csp::VmCore();

			mVmCore->addListener(this);

			NativePackage(shell_toplevel, mVmCore);
			NativePackage(flash, mVmCore);

			mVmCore->initializePackages();
		}
		//-----------------------------------------------------------------------
		AS3ScriptEngine::~AS3ScriptEngine()
		{
			delete mRoot;
			delete mVmCore;
			csp::VmCore::destroyGcHeap();
		}
		//-----------------------------------------------------------------------
		bool AS3ScriptEngine::executeCode(const char* code, const uint& len)
		{
			//csp::ArgumentList args;
			//args.push_back(mVmCore->newString("click"));
			//args.push_back(mVmCore->newBoolean(false));
			//args.push_back(mVmCore->newBoolean(true));

			//csp::ScriptObject* evt = mVmCore->createObject("MouseEvent", "flash.events", args);

			//csp::ScriptObject* hndlr = mVmCore->createObject("EventHandler");

			//args.clear();
			//args.push_back(evt->atom());
			//mVmCore->callStaticFunction("EventHandler", "handle", "", args);
			////hndlr->callFunction("handle", args);

			return mVmCore->executeByteCode(code, len);
		}
		//-----------------------------------------------------------------------
		ScriptObject* AS3ScriptEngine::getRootScriptObject()
		{
			if(!mRootObject)
			{
				const String& root_class = mParent->getFile()->getHeader().script_root_class;
				if(root_class.length())
				{
					StringList vec = StringHelper::splitString(root_class, '.');

					if(vec.size() > 1)
					{
						// AS3 declaration -> [package.ClassName]
						mRoot = mVmCore->createObject(vec.at(1), vec.at(0));
					}
					else
					{
						mRoot = mVmCore->createObject(vec.at(0));
					}

					//mRoot->initializeSlots();

					mRootObject = dynamic_cast<vtx::as3::MovieClip*>(mRoot->scriptObj());

					//ScriptButton* btn = dynamic_cast<vtx::ScriptButton*>(mRoot->getSlotObject("button1")->scriptObj());
					//mRootObject->setChildScriptObject("button1", btn);
					// <DEBUG ONLY>
					//mRoot->callFunction("frame1");

					//args.clear();
					//args.push_back(evt->atom());
					//mRoot->getSlotObject("button1")->callFunction("dispatchEvent", args);
					//mRoot->getSlotObject("button1")->callFunction("dispatchEvent", args);
					//mRoot->getSlotObject("button1")->callFunction("dispatchEvent", args);
					//mRoot->getSlotObject("button1")->callFunction("dispatchEvent", args);
					// </DEBUG ONLY>
				}
			}

			return mRootObject;
		}
		//-----------------------------------------------------------------------
		void AS3ScriptEngine::output(const std::string& message)
		{
			VTX_LOG("AS3: '%s'", message.c_str());
		}
		//-----------------------------------------------------------------------
	}
}
