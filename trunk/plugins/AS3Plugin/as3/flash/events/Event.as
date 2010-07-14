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
	[native(cls="::vtx::as3::EventClass", instance="::vtx::as3::Event", methods="auto")]
	public class Event
	{
		public static const ACTIVATE:String = "activate";
		public static const ADDED:String = "added";
		public static const ADDED_TO_STAGE:String = "addedToStage";
		public static const CANCEL:String = "cancel";
		public static const CHANGE:String = "change";
		public static const CLEAR:String = "clear";
		public static const CLOSE:String = "close";
		public static const CLOSING:String = "closing"; //AIR
		public static const COMPLETE:String = "complete";
		public static const CONNECT:String = "connect";
		public static const COPY:String = "copy";
		public static const CUT:String = "cut";
		public static const DEACTIVATE:String = "deactivate";
		public static const DISPLAYING:String = "displaying";
		public static const ENTER_FRAME:String = "enterFrame";
		public static const EXIT_FRAME:String = "exitFrame";
		public static const EXITING:String = "exiting"; //AIR
		public static const FRAME_CONSTRUCTED:String = "frameConstructed";
		public static const FULLSCREEN:String = "fullScreen";
		public static const HTML_BOUNDS_CHANGE:String = "htmlBoundsChange"; //AIR
		public static const HTML_DOM_INITIALIZE:String = "htmlDOMInitialize"; //AIR
		public static const HTML_RENDER:String = "htmlRender"; //AIR
		public static const ID3:String = "id3";
		public static const INIT:String = "init";
		public static const LOCATION_CHANGE:String = "locationChange"; //AIR
		public static const MOUSE_LEAVE:String = "mouseLeave";
		public static const NETWORK_CHANGE:String = "networkChange"; //AIR
		public static const OPEN:String = "open";
		public static const PASTE:String = "paste";
		public static const REMOVED:String = "removed";
		public static const REMOVED_FROM_STAGE:String = "removedFromStage";
		public static const RENDER:String = "render";
		public static const RESIZE:String = "resize";
		public static const SAMPLE_DATA:String = "sampleData";
		public static const SCROLL:String = "scroll";
		public static const SELECT:String = "select";
		public static const SELECT_ALL:String = "selectAll";
		public static const SOUND_COMPLETE:String = "soundComplete";
		public static const TAB_CHILDREN_CHANGE:String = "tabChildrenChange";
		public static const TAB_ENABLED_CHANGE:String = "tabEnabledChange";
		public static const TAB_INDEX_CHANGE:String = "tabIndexChange";
		public static const UNLOAD:String = "unload";
		public static const USER_IDLE:String = "userIdle"; //AIR
		public static const USER_PRESENT:String = "userPresent"; //AIR
		
		protected var mType:String;
		protected var mBubbles:Boolean;
		protected var mCancelable:Boolean;
		protected var mEventDispatcher:EventDispatcher;
		
		public function Event(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			mType = type;
			mBubbles = bubbles;
			mCancelable = cancelable;
			mEventDispatcher = null;
		}
		
		public function setEventDispatcher(disp:EventDispatcher)
		{
			mEventDispatcher = disp;
		}
		
		public function debugEventDispatcher()
		{
			trace(mEventDispatcher);
		}

		public function get bubbles():Boolean
		{
			return mBubbles;
		}
		
		public function get cancelable():Boolean
		{
			return mCancelable;
		}
		
		public function get currentTarget():Object
		{
			return new Object();
		}
		
		public function get eventPhase():uint
		{
			return 0;
		}
		
		public function get target():Object
		{
			return new Object();
		}
		
		public function get type():String
		{
			return mType;
		}
		
		
		public function clone():Event
		{
			return new Event("");
		}
		
		public function formatToString(className:String, ... arguments):String
		{
			return "";
		}
		
		public function isDefaultPrevented():Boolean
		{
			return false;
		}
		
		public function preventDefault():void
		{
			
		}
		
		public function stopImmediatePropagation():void
		{
			
		}
		
		public function stopPropagation():void
		{
			
		}
		
		public function toString():String
		{
			return "[Event type=\"" + 
				mType + 
				"bubbles=" + 
				mBubbles + 
				" cancelable=" + 
				mCancelable + 
				"]";
		}
		
	}
}
