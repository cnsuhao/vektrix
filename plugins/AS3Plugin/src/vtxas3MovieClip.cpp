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

#include "vtxas3ScriptEngine.h"

#include "vtxEvent.h"
#include "vtxMovie.h"
#include "vtxMovieClip.h"
#include "vtxStringHelper.h"

#include "cspVmCore.h"

namespace vtx { namespace as3 {
	//-----------------------------------------------------------------------
	MovieClip::MovieClip(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
		: Sprite(vtable, prototype)
	{
		//csp::VmCore::initializeAllSlots(this);
		//AS3ScriptEngine* script_engine = static_cast<AS3ScriptEngine*>(CSP_CORE->getUserData());
		////Instance* inst = script_engine->getQueuedInstance();
		//Instance* inst = script_engine->getParentMovie()->getInstanceByType("MovieClip");
		//setNativeObject(inst);
		//if(inst)
		//{
		//	inst->setScriptObject(this);
		//}
		//std::cout << "as3 movieclip" << std::endl;
		//mNativeObject->setScriptObject(this);
	}
	//-----------------------------------------------------------------------
	MovieClip::~MovieClip()
	{

	}
	//-----------------------------------------------------------------------
	void MovieClip::eventFired(const vtx::Event& evt)
	{
		if(!mMovieClip)
		{
			std::cout << ("null movieclip") << std::endl;
			return;
		}

		if(evt.getCategory() == vtx::Event::GENERIC_CATEGORY)
		{
			if(evt.getType() == vtx::Event::ENTER_FRAME)
			{
				const uint& frame = mMovieClip->getCurrentFrame();
				csp::VmCore::callObjectFunction(this, "frame" + StringHelper::toString(frame+1));
				//callFunction("frame" + StringHelper::toString(frame+1));
			}
		}
	}
	//-----------------------------------------------------------------------
	void MovieClip::setNativeObject(Instance* inst)
	{
		Sprite::setNativeObject(inst);
		mMovieClip = static_cast<vtx::MovieClip*>(inst);
	}
	//-----------------------------------------------------------------------
}}
