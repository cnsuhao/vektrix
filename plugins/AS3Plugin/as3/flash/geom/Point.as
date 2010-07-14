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
	public class Point
	{
		public function Point(x:Number = 0, y:Number = 0) {}
		
		/* attributes */
		public var x:Number;
		public var y:Number;
		
		/* getters & setters */
		public function get length():Number { return null; }

		/* methods */
		public function add(v:Point):Point { return null; }
		public function clone():Point { return null; }
		public static function distance(pt1:Point, pt2:Point):Number { return null; }
		public function equals(toCompare:Point):Boolean { return false; }
		public static function interpolate(pt1:Point, pt2:Point, f:Number):Point { return null; }
		public function normalize(thickness:Number):void {}
		public function offset(dx:Number, dy:Number):void {}
		public static function polar(len:Number, angle:Number):Point { return null; }
		public function subtract(v:Point):Point { return null; }
		public function toString():String { return ""; }
	}
}
