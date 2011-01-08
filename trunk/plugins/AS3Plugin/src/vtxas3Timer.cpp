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

#include "vtxas3Timer.h"

#include "cspVmCore.h"

namespace vtx { namespace as3 {
	//-----------------------------------------------------------------------
	void Timer::ctor(double delay, int repeatCount)
	{
		mDelay = (float)delay * 0.001f;
		mRepeatCount = repeatCount;

		mCounter = 0;
		mTime = 0.0f;

		//getParentMovie()->addListener(this);
	}
	//-----------------------------------------------------------------------
	void Timer::_reset()
	{
		mCounter = 0;
		mTime = 0.0f;
	}
	//-----------------------------------------------------------------------
	void Timer::_start()
	{
		//getParentMovie()->addListener(this);
	}
	//-----------------------------------------------------------------------
	void Timer::_stop()
	{
		mTime = 0.0f;
		//getParentMovie()->removeListener(this);
	}
	//-----------------------------------------------------------------------
	void Timer::update(const float& delta_time)
	{
		// repeat limit reached
		if(mRepeatCount > 0)
		{
			if(mCounter >= mRepeatCount)
				return;
			else
				++mCounter;
		}

		mTime += delta_time;

		if(mTime >= mDelay)
		{
			MMGC_GCENTER(core()->GetGC());

			mTime = 0.0f;

			avmplus::Atom args[] = 
			{
				0, 
				CSP_CORE->toScript("timer"), 
				CSP_CORE->toScript(false), 
				CSP_CORE->toScript(true)
			};

			avmplus::ScriptObject* evt = CSP_CORE->createObject("TimerEvent", "flash.events", args);

			avmplus::Atom dispatch_args[] = 
			{
				0, 
				evt->atom()
			};

			csp::VmCore::callFunction(this, dispatchEvent, dispatch_args);

			evt->DecrementRef();
		}
	}
	//-----------------------------------------------------------------------
}}
