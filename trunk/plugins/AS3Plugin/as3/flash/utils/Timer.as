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

package flash.utils
{
	const DEBUG_TIMER:Boolean = false;

	import flash.events.EventDispatcher;

	[native(cls="::vtx::as3::TimerClass", instance="::vtx::as3::Timer", methods="auto")]
	public class Timer extends EventDispatcher
	{
		//-----------------------------------------------------------------------
		private native function ctor(delay:Number, repeatCount:int):void;
		//-----------------------------------------------------------------------
		public function Timer(delay:Number, repeatCount:int = 0)
		{
			super();
			if(DEBUG_TIMER) { trace("new Timer(", delay, ", ", repeatCount, ")"); }

			ctor(delay, repeatCount);
		}
		//-----------------------------------------------------------------------
		private native function _reset():void;
		//-----------------------------------------------------------------------
		public function reset():void
		{
			if(DEBUG_TIMER) { trace("Timer.reset()"); }
			_reset();
		}
		//-----------------------------------------------------------------------
		private native function _start():void;
		//-----------------------------------------------------------------------
		public function start():void
		{
			if(DEBUG_TIMER) { trace("Timer.start()"); }
			_start();
		}
		//-----------------------------------------------------------------------
		private native function _stop():void;
		//-----------------------------------------------------------------------
		public function stop():void
		{
			if(DEBUG_TIMER) { trace("Timer.stop()"); }
			_stop();
		}
		//-----------------------------------------------------------------------
	}
}
