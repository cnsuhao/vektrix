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
	import flash.display.InteractiveObject;
	
	[native(cls="::vtx::as3::MouseEventClass", instance="::vtx::as3::MouseEvent", methods="auto")]
	public class MouseEvent extends Event 
	{
		private var mLocalX:Number;
		private var mLocalY:Number;
		
		public static const CLICK:String = "click";
		public static const DOUBLE_CLICK:String = "doubleClick";
		public static const MOUSE_DOWN:String = "mouseDown";
		public static const MOUSE_MOVE:String = "mouseMove";
		public static const MOUSE_OUT:String = "mouseOut";
		public static const MOUSE_OVER:String = "mouseOver";
		public static const MOUSE_UP:String = "mouseUp";
		public static const MOUSE_WHEEL:String = "mouseWheel";
		public static const ROLL_OUT:String = "rollOut";
		public static const ROLL_OVER:String = "rollOver";
		
		public function MouseEvent(
			type:String, 
			bubbles:Boolean = true, 
			cancelable:Boolean = false, 
			localX:Number = 0, 
			localY:Number = 0, 
			relatedObject:InteractiveObject = null, 
			ctrlKey:Boolean = false, 
			altKey:Boolean = false, 
			shiftKey:Boolean = false, 
			buttonDown:Boolean = false, 
			delta:int = 0, 
			commandKey:Boolean = false, 
			controlKey:Boolean = false, 
			clickCount:int = 0)
		{
			super(type, bubbles, cancelable);
			
			mLocalX = localX;
			mLocalY = localY;
		}
		
		public function get stageX():Number
		{
			return mLocalX;
		}
		
		public function get stageY():Number
		{
			return mLocalY;
		}
		
		override public function toString():String
		{
			return "[MouseEvent type=\"" + 
				mType + 
				"\" bubbles=" + 
				mBubbles + 
				" cancelable=" + 
				mCancelable + 
				" eventPhase=TODO localX=TODO localY=TODO stageX=TODO stageY=TODO relatedObject=TODO ctrlKey=TODO altKey=TODO shiftKey=TODO buttonDown=TODO delta=TODO]";
		}
	}
}
