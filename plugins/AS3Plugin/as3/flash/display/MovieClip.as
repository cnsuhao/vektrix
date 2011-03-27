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

package flash.display
{
	import flash.events.Event;
	import flash.utils.Dictionary;
	//-----------------------------------------------------------------------
	[native(cls="::vtx::as3::MovieClipClass", instance="::vtx::as3::MovieClip", methods="auto")]
	public dynamic class MovieClip extends Sprite
	{
		const DEBUG_MOVIECLIP = false;
		//-----------------------------------------------------------------------
		private var mFrameScripts:Dictionary;
		//-----------------------------------------------------------------------
		private native function ctor():void;
		//-----------------------------------------------------------------------
		public function MovieClip()
		{
			super();
			if(DEBUG_MOVIECLIP) { trace("new MovieClip()"); }

			ctor();
			mFrameScripts = new Dictionary();
		}
		///-----------------------------------------------------------------------
		/// GETTERS & SETTERS
		///-----------------------------------------------------------------------
		public native function get _currentFrame():int;
		//-----------------------------------------------------------------------
		public function get currentFrame():int
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.get_currentFrame() = " + _currentFrame); }
			return _currentFrame;
		}
		//-----------------------------------------------------------------------
		public function get currentLabel():String
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.get.currentLabel()"); }
			return "";
		}
		//-----------------------------------------------------------------------
		public function get currentLabels():Array
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.get.currentLabels()"); }
			return new Array();
		}
		//-----------------------------------------------------------------------
		public function get currentScene():Scene
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.get.currentScene()"); }
			return new Scene();
		}
		//-----------------------------------------------------------------------
		public function get enabled():Boolean
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.get.enabled()"); }
			return false;
		}
		//-----------------------------------------------------------------------
		public function set enabled(value:Boolean):void
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.set.enabled(" + value + ")"); }
		}
		//-----------------------------------------------------------------------
		public function get framesLoaded():int
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.get.framesLoaded()"); }
			return 0;
		}
		//-----------------------------------------------------------------------
		public function get scenes():Array
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.get.scenes()"); }
			return new Array();
		}
		//-----------------------------------------------------------------------
		public function get totalFrames():int
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.get.totalFrames()"); }
			return 0;
		}
		//-----------------------------------------------------------------------
		public function get trackAsMenu():Boolean
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.get.trackAsMenu()"); }
			return false;
		}
		//-----------------------------------------------------------------------
		public function set trackAsMenu(value:Boolean):void
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.set.trackAsMenu(" + value + ")"); }
		}
		///-----------------------------------------------------------------------
		/// CLASS METHODS
		///-----------------------------------------------------------------------
		public function addFrameScript(... arguments):void
		{
			for(var i:int=0; i<arguments.length; i+=2)
			{
				var frame_index:int = arguments[i];
				var script_function:Function = arguments[i+1];

				if(DEBUG_MOVIECLIP) { trace("MovieClip.addFrameScript(" + frame_index + ", " + script_function + ")"); }

				mFrameScripts[frame_index] = script_function;
			}
		}
		//-----------------------------------------------------------------------
		override public function dispatchEvent(event:Event):Boolean
		{
			if(event.type == Event.ENTER_FRAME)
			{
				var frame_script:Function = mFrameScripts[currentFrame - 1];
				if(frame_script != null)
				{
					if(DEBUG_MOVIECLIP) trace("MovieClip.callFrameScript(" + currentFrame + ")");
					frame_script();
				}
			}

			return super.dispatchEvent(event);
		}
		//-----------------------------------------------------------------------
		public function gotoAndPlay(frame:Object, scene:String = null):void
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.gotoAndPlay(" + frame + ", " + scene + ")"); }
		}
		//-----------------------------------------------------------------------
		public function gotoAndStop(frame:Object, scene:String = null):void
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.gotoAndStop(" + frame + ", " + scene + ")"); }
		}
		//-----------------------------------------------------------------------
		public function nextFrame():void
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.nextFrame()"); }
		}
		//-----------------------------------------------------------------------
		public function nextScene():void
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.nextScene()"); }
		}
		//-----------------------------------------------------------------------
		public function play():void
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.play()"); }
		}
		//-----------------------------------------------------------------------
		public function prevFrame():void
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.prevFrame()"); }
		}
		//-----------------------------------------------------------------------
		public function prevScene():void
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.prevScene()"); }
		}
		//-----------------------------------------------------------------------
		public function stop():void
		{
			if(DEBUG_MOVIECLIP) { trace("MovieClip.stop()"); }
		}
		//-----------------------------------------------------------------------
	}
}
