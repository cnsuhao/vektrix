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

package flash.events
{
	const DEBUG_EVENTDISPATCHER = false;

	import flash.events.IEventDispatcher;
	import flash.utils.Dictionary;
	
	[native(cls="::vtx::as3::EventDispatcherClass", instance="::vtx::as3::EventDispatcher", methods="auto")]
	public class EventDispatcher implements IEventDispatcher
	{
		//-----------------------------------------------------------------------
		private var mTarget:IEventDispatcher;
		private var mHandlers:Dictionary;
		//-----------------------------------------------------------------------
		private native function ctor(target:IEventDispatcher = null):void;
		//-----------------------------------------------------------------------
		public function EventDispatcher(target:IEventDispatcher = null)
		{
			super();
			if(DEBUG_EVENTDISPATCHER) { trace("new EventDispatcher(" + target + ")"); }

			ctor(target);

			mTarget = target;

			if(mTarget == null)
			{
				mHandlers = new Dictionary();
			}
		}
		//-----------------------------------------------------------------------
		public function addEventListener(type:String, listener:Function, useCapture:Boolean = false, priority:int = 0, useWeakReference:Boolean = false):void
		{
			if(DEBUG_EVENTDISPATCHER) { trace("EventDispatcher.addEventListener(" + [type,listener,useCapture,priority,useWeakReference].join(", ") + ")"); }

			if(mTarget != null)
			{
				mTarget.addEventListener(type, listener, useCapture, priority, useWeakReference);
				return;
			}

			if(mHandlers[type] == null)
			{
				mHandlers[type] = new Array();
			}
			
			// only add listener if not already present
			if(mHandlers[type].indexOf(listener) < 0)
			{
				mHandlers[type].push(listener);
			}
		};
		//-----------------------------------------------------------------------
		public function dispatchEvent(event:Event):Boolean
		{
			if(DEBUG_EVENTDISPATCHER) { trace("EventDispatcher.addEventListener(" + event + ")" ); }

			if(mTarget != null)
			{
				return mTarget.dispatchEvent(event);
			}

			event.currentTarget = this;
			event.target = this;

			var listeners:Array = mHandlers[event.type];

			if(listeners != null)
			{
				for(var i:uint = 0; i<listeners.length; ++i)
				{
					listeners[i].call(listeners[i], event);
				}
			}

			return true;
		}
		//-----------------------------------------------------------------------
		public function hasEventListener(type:String):Boolean
		{
            if(DEBUG_EVENTDISPATCHER) { trace("EventDispatcher.hasEventListener(" + type + ")"); }

			if(mTarget != null)
			{
				return mTarget.hasEventListener(type);
			}

			return (mHandlers[type] != null);
		}
		//-----------------------------------------------------------------------
		public function removeEventListener(type:String, listener:Function, useCapture:Boolean = false):void
		{
            if(DEBUG_EVENTDISPATCHER) { trace("EventDispatcher.removeEventListener(" + [type,listener,useCapture].join(", ") + ")"); }

			if(mTarget != null)
			{
				mTarget.removeEventListener(type, listener, useCapture);
				return;
			}

			var listeners:Array = mHandlers[type];

			if(listeners == null)
				return;

			var index:int = listeners.indexOf(listener);

			if(index < 0)
				return;

			if(listeners.length > 1)
			{
				listeners.splice(index, 1);
			}
			else
			{
				// the last listener for this type has been removed, 
				// we can free the listener array for this type
				mHandlers[type] = null;
			}
		}
		//-----------------------------------------------------------------------
		public function willTrigger(type:String):Boolean
		{
			if(DEBUG_EVENTDISPATCHER) { trace("EventDispatcher.willTrigger(" + type + ")"); }

			if(mTarget != null)
			{
				return mTarget.willTrigger(type);
			}

			return true;
		}
		//-----------------------------------------------------------------------
	}
}
