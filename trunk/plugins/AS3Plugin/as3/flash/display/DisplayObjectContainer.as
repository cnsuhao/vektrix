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
	import flash.geom.*;
	import flash.text.*;
	
	[native(cls="::vtx::as3::DisplayObjectContainerClass", instance="::vtx::as3::DisplayObjectContainer", methods="auto")]
	public class DisplayObjectContainer extends InteractiveObject
	{
		/* Constructor */
		public function DisplayObjectContainer() {}
		
		/* getters & setters */
		public function get mouseChildren():Boolean { return false; }
		public function set mouseChildren(value:Boolean):void {}
		
		public function get numChildren():int { return 0; }
		
		public function get tabChildren():Boolean { return false; }
		public function set tabChildren(value:Boolean):void {}
		
		public function get textSnapshot():TextSnapshot { return null; }

		/* methods */
		public native function addChild(child:DisplayObject):DisplayObject
		/*{ return null; }*/

		public function addChildAt(child:DisplayObject, index:int):DisplayObject { return null; }
		public function areInaccessibleObjectsUnderPoint(point:Point):Boolean { return false; }
		public function contains(child:DisplayObject):Boolean { return false; }
		public function getChildAt(index:int):DisplayObject { return null; }
		
		public native function getChildByName(name:String):DisplayObject
		
		public function getChildIndex(child:DisplayObject):int { return 0; }
		public function getObjectsUnderPoint(point:Point):Array { return null; }
		public function removeChild(child:DisplayObject):DisplayObject { return null; }
		public function removeChildAt(index:int):DisplayObject { return null; }
		public function setChildIndex(child:DisplayObject, index:int):void {}
		public function swapChildren(child1:DisplayObject, child2:DisplayObject):void {}
		public function swapChildrenAt(index1:int, index2:int):void {}
	}
}
