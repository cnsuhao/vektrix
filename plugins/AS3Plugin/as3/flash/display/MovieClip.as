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
	[native(cls="::vtx::as3::MovieClipClass", instance="::vtx::as3::MovieClip", methods="auto")]
	public dynamic class MovieClip extends Sprite
	{
		/* getters & setters */
		public function get currentFrame():int { return 0; }
		public function get currentLabel():String { return ""; }
		public function get currentLabels():Array { return null; }
		public function get currentScene():Scene { return null; }
		public function get enabled():Boolean { return false; }
		public function set enabled(value:Boolean):void {}
		public function get framesLoaded():int { return 0; }
		public function get scenes():Array { return null; }
		public function get totalFrames():int { return 0; }
		public function get trackAsMenu():Boolean { return false; }
		public function set trackAsMenu(value:Boolean):void {}

		/* methods */
		public function addFrameScript(... frame_scripts) {}
		public function gotoAndPlay(frame:Object, scene:String = null):void {}
		public function gotoAndStop(frame:Object, scene:String = null):void {}
		public function nextFrame():void {}
		public function nextScene():void {}
		public function play():void {}
		public function prevFrame():void {}
		public function prevScene():void {}
		public function stop():void {}
	}
}
