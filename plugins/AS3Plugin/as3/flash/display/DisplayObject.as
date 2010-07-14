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
	import flash.accessibility.*;
	import flash.display.IBitmapDrawable;
	import flash.events.EventDispatcher;
	import flash.geom.*;
	
	[native(cls="::vtx::as3::DisplayObjectClass", instance="::vtx::as3::DisplayObject", methods="auto")]
	public class DisplayObject extends EventDispatcher implements IBitmapDrawable
	{
		/* getters & setters */
		public function get accessibilityProperties():AccessibilityProperties { return null; }
		public function set accessibilityProperties(value:AccessibilityProperties):void {}

		public function get alpha():Number { return null; }
		public function set alpha(value:Number):void {}

		public function get blendMode():String { return ""; }
		public function set blendMode(value:String):void {}
		
		public function get cacheAsBitmap():Boolean { return false; }
		public function set cacheAsBitmap(value:Boolean):void {}
		
		public function get filters():Array { return null; }
		public function set filters(value:Array):void {}

		public native function get height():Number
		/*{ return 0; }*/
		public native function set height(value:Number):void
		/*{}*/

		public function get loaderInfo():LoaderInfo { return null; }
		
		public function get mask():DisplayObject { return null; }
		public function set mask(value:DisplayObject):void {}
		
		public function get mouseX():Number { return null; }
		public function get mouseY():Number { return null; }
		
		public function get name():String { return ""; }
		public function set name(value:String):void {}
		
		public function get opaqueBackground():Object { return null; }
		public function set opaqueBackground(value:Object):void {}
		
		public function get parent():DisplayObjectContainer
		{
			trace("DisplayObject::parent()");
			return null;
		}
		
		public function get root():DisplayObject { return null; }

		public native function get rotation():Number
		/*{ return 0; }*/
		public native function set rotation(value:Number):void
		/*{}*/
		
		public function get scale9Grid():Rectangle { return null; }
		public function set scale9Grid(value:Rectangle):void {}

		public native function get scaleX():Number
		/*{ return 0; };*/
		public native function set scaleX(value:Number):void
		/*{ trace("DisplayObject::scaleX =", value); }*/
		
		public native function get scaleY():Number
		/*{ return 0; };*/
		public native function set scaleY(value:Number):void
		/*{ trace("DisplayObject::scaleY =", value); };*/
		
		public function get scrollRect():Rectangle { return null; }
		public function set scrollRect(value:Rectangle):void {}
		
		public function get stage():Stage { return null; }
		
		public function get transform():Transform { return null; }
		public function set transform(value:Transform):void {}

		public native function get visible():Boolean
		/*{ return false; }*/
		public native function set visible(value:Boolean):void
		/*{}*/

		public native function get width():Number
		/*{ return 0; }*/
		public native function set width(value:Number):void
		/*{}*/
				
		public native function get x():Number
		/*{ return 0; }*/
		public native function set x(value:Number):void
		/*{}*/
		
		public native function get y():Number
		/*{ return 0; }*/
		public native function set y(value:Number):void
		/*{}*/

		/* methods */
		public function getBounds(targetCoordinateSpace:DisplayObject):Rectangle { return null; }
		public function getRect(targetCoordinateSpace:DisplayObject):Rectangle { return null; }
		public function globalToLocal(point:Point):Point { return null; }
		public function hitTestObject(obj:DisplayObject):Boolean { return false; }
		public function hitTestPoint(x:Number, y:Number, shapeFlag:Boolean = false):Boolean { return false; }
		public function localToGlobal(point:Point):Point { return null; }
	}
}
