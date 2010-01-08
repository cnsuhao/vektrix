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
            return {};
        }
        
        public function get eventPhase():uint
        {
            return 0;
        }
        
        public function get target():Object
        {
            return {};
        }
        
        public function get type():String
        {
            return mType;
        }
        
        
        public function clone():Event
        {
            return new Event( "" );
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
            return "";
        }
        
    }
    
    public interface IEventDispatcher
    {
        function addEventListener(type:String, listener:Function, useCapture:Boolean = false, priority:int = 0, useWeakReference:Boolean = false):void;
        function dispatchEvent(event:Event):Boolean;
        function hasEventListener(type:String):Boolean;
        function removeEventListener(type:String, listener:Function, useCapture:Boolean = false):void;
        function willTrigger(type:String):Boolean;
    }
    
    /*
    */
    [native(cls="::vtx::as3::EventDispatcherClass", instance="::vtx::as3::EventDispatcher", methods="auto")]
    public class EventDispatcher implements IEventDispatcher
    {
        private var mListeners : Array;
        
        public function EventDispatcher(target:IEventDispatcher = null)
        {
            mListeners = new Array();
        }
        
        public function addEventListener(type:String, listener:Function, useCapture:Boolean = false, priority:int = 0, useWeakReference:Boolean = false):void
        {
			mListeners.push(listener);
        }
        
        //public native function dispatchEvent(event:Event):Boolean;
        public function dispatchEvent(event:Event):Boolean
        {
			for each(var listener:Function in mListeners)
			{
				event.setEventDispatcher(this);
				//print("calling " + listener);
				listener(event);
			}

			return false;
        }
        
        public function hasEventListener(type:String):Boolean
        {
			print(type);
            return false;
        }
        
        public function removeEventListener(type:String, listener:Function, useCapture:Boolean = false):void
        {
            
        }
        
        public function willTrigger(type:String):Boolean
        {
            return false;
        }
        
        
    }
    
    /*
    */
    public class NetStatusEvent extends Event
    {
        public static const NET_STATUS:String = "netStatus";
        
        private var _info:Object;
        
        public function NetStatusEvent(type:String, bubbles:Boolean = false, cancelable:Boolean = false, info:Object = null)
        {
            super( type, bubbles, cancelable );
            _info = info;
        }
        
        public function get info():Object
        {
            return _info;
        }
        
        public function set info(value:Object):void
        {
            _info = value;
        }
        
        override public function clone():Event
        {
            return new NetStatusEvent( type, bubbles, cancelable, info );
        }
        
        override public function toString():String
        {
            return formatToString( "NetStatusEvent", "type", "bubbles", "cancelable", "info" );
        }
    }
    
    /*
    */
    public class MouseEvent extends Event 
	{
		public static const CLICK:String = "click";
		
		public function MouseEvent(type:String, bubbles:Boolean, cancelable:Boolean)
		{
            super(type, bubbles, cancelable);
        }
	}
}

