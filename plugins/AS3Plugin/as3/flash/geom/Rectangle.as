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

package flash.geom
{
	public class Rectangle
	{
		public function Rectangle(x:Number = 0, y:Number = 0, width:Number = 0, height:Number = 0) {}
		
		/* getters & setters */
		public function get bottom():Number { return null; }
		public function set bottom(value:Number):void {}
		public function get bottomRight():Point { return null; }
		public function set bottomRight(value:Point):void {}
		public function get left():Number { return null; }
		public function set left(value:Number):void {}
		public function get right():Number { return null; }
		public function set right(value:Number):void {}
		public function get size():Point { return null; }
		public function set size(value:Point):void {}
		public function get top():Number { return null; }
		public function set top(value:Number):void {}
		public function get topLeft():Point { return null; }
		public function set topLeft(value:Point):void {}

		/* methods */
		public function clone():Rectangle { return null; }
		public function contains(x:Number, y:Number):Boolean { return false; }
		public function containsPoint(point:Point):Boolean { return false; }
		public function containsRect(rect:Rectangle):Boolean { return false; }
		public function equals(toCompare:Rectangle):Boolean { return false; }
		public function inflate(dx:Number, dy:Number):void {}
		public function inflatePoint(point:Point):void {}
		public function intersection(toIntersect:Rectangle):Rectangle { return null; }
		public function intersects(toIntersect:Rectangle):Boolean { return false; }
		public function isEmpty():Boolean { return false; }
		public function offset(dx:Number, dy:Number):void {}
		public function offsetPoint(point:Point):void {}
		public function setEmpty():void {}
		public function toString():String { return ""; }
		public function union(toUnion:Rectangle):Rectangle { return null; }
	}
}
