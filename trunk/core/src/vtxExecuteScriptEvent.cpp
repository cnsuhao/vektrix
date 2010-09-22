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

#include "vtxExecuteScriptEvent.h"
#include "vtxDisplayObjectContainer.h"
#include "vtxLogManager.h"
#include "vtxMovie.h"
#include "vtxMovieClip.h"
#include "vtxScriptEngine.h"
#include "vtxScriptResource.h"
#include "vtxStage.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	ExecuteScriptEvent::ExecuteScriptEvent(DisplayObjectContainer* container, ScriptResource* script_resource) 
		: FrameEvent(container), 
		mExecuted(false), 
		mScriptResource(script_resource)
	{

	}
	//-----------------------------------------------------------------------
	FrameEvent* ExecuteScriptEvent::clone(DisplayObjectContainer* container)
	{
		return new ExecuteScriptEvent(container, mScriptResource);
	}
	//-----------------------------------------------------------------------
	void ExecuteScriptEvent::execute()
	{
		if(mExecuted) return;
		VTX_LOG("executing frame script: %s", mScriptResource->getID().c_str());
		/**/
		Movie* parent = mObjectContainer->getParent();
		ScriptEngine* script_engine = parent->getScriptEngine();
		if(script_engine)
		{
			try
			{
				script_engine->executeCode(mScriptResource->getBuffer(), mScriptResource->getLength());
				parent->getStage()->initScriptObject();
				parent->getMainMovieClip()->initScriptObject();
				mExecuted = true;
			}
			catch(std::exception& e)
			{
				VTX_EXCEPT(e.what());
			}
		}

		/* cOOOOOOLD
		TODO: add virtual void Instance::initializeScripting() = 0;
		TODO: at DisplayObjectContainer -> initialize all children
		TODO: NEW: add "initializeSlots()" to as3::ScriptObjectBase constructor
		child objects retrieve their vtx::ScriptObjects when Instance::initScripting() is being called
		*/
		/*
		// TODO: add as3::AS3ScriptEngine::createScriptObject(Instance* instance)
		{
			mCreatingInstance = instance;
			return mVmCore->createObject(...);
		}
		inside as3::MovieClip::MovieClip(...)
		{
			this->setNativeObject(core->getCreatingInstance());
		}
		*/

		//parent->getMainMovieClip()->setScriptObject(script_engine->getRootScriptObject(parent->getMainMovieClip()));
		//parent->getMainMovieClip()->initScriptObject();
	}
	//-----------------------------------------------------------------------
}
