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
	import flash.display.*;
	import flash.geom.*;
	import flash.text.*;

	[native(cls="::vtx::as3::StageClass", instance="::vtx::as3::Stage", methods="auto")]
	public class Stage extends DisplayObjectContainer
	{
		/* getters & setters */
		public function get align():String { return ""; }
		public function set align(value:String):void {}
		public function get displayState():String { return ""; }
		public function set displayState(value:String):void {}
		public function get focus():InteractiveObject { return null; }
		public function set focus(value:InteractiveObject):void {}
		public function get frameRate():Number { return null; }
		public function set frameRate(value:Number):void {}
		public function get fullScreenHeight():uint { return null; }
		public function get fullScreenSourceRect():Rectangle { return null; }
		public function set fullScreenSourceRect(value:Rectangle):void {}
		public function get fullScreenWidth():uint { return null; }
		override public function get height():Number { return null; }
		override public function set height(value:Number):void {}
		override public function get mouseChildren():Boolean { return false; }
		override public function set mouseChildren(value:Boolean):void {}
		// AIR-only public function get nativeWindow():NativeWindow { return null; }
		//override public function get numChildren():int { return 0; }
		public function get quality():String { return ""; }
		public function set quality(value:String):void {}
		public function get scaleMode():String { return ""; }
		public function set scaleMode(value:String):void {}
		public function get showDefaultContextMenu():Boolean { return false; }
		public function set showDefaultContextMenu(value:Boolean):void {}
		public function get stageFocusRect():Boolean { return false; }
		public function set stageFocusRect(value:Boolean):void {}
		public native function get stageHeight():int
		public function set stageHeight(value:int):void {}
		public native function get stageWidth():int
		public function set stageWidth(value:int):void {}
		override public function get tabChildren():Boolean { return false; }
		override public function set tabChildren(value:Boolean):void {}
		override public function get textSnapshot():TextSnapshot { return null; }
		override public function get width():Number { return null; }
		override public function set width(value:Number):void {}

		/* methods */
		public function assignFocus(objectToFocus:InteractiveObject, direction:String):void {}
		public function invalidate():void {}
		public function isFocusInaccessible():Boolean { return false; }
	}
}
