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

#include "vtxFile.h"
#include "vtxLogManager.h"
#include "vtxMovie.h"
#include "vtxScriptObject.h"
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
			mVmCore = new csp::VmCore(false);

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
		}
		//-----------------------------------------------------------------------
		bool AS3ScriptEngine::executeCode(const char* code, const uint& len)
		{
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

					mRootObject = dynamic_cast<vtx::as3::MovieClip*>(mRoot->scriptObj());
				}
			}

			return mRootObject;
		}
		//-----------------------------------------------------------------------
		void AS3ScriptEngine::output(const String& message)
		{
			VTX_LOG("AS3: '%s'", message.c_str());
		}
		//-----------------------------------------------------------------------
	}
}
