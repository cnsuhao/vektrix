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
	import flash.accessibility.AccessibilityProperties;
	import flash.display.IBitmapDrawable;
	import flash.events.Event;
	import flash.events.EventDispatcher;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	import flash.geom.Transform;
	//-----------------------------------------------------------------------
	[native(cls="::vtx::as3::DisplayObjectClass", instance="::vtx::as3::DisplayObject", methods="auto")]
	public class DisplayObject extends EventDispatcher implements IBitmapDrawable
	{
		const DEBUG_DISPLAYOBJECT:Boolean = true;
		//-----------------------------------------------------------------------
		private native function ctor():void;
		//-----------------------------------------------------------------------
		public function DisplayObject()
		{
			super();
			if(DEBUG_DISPLAYOBJECT) { trace("new DisplayObject()"); }

			//ctor();
		}
		///-----------------------------------------------------------------------
		/// GETTERS & SETTERS
		///-----------------------------------------------------------------------
		public function get accessibilityProperties():AccessibilityProperties
		{
			if(DEBUG_DISPLAYOBJECT) { trace("DisplayObject.get_accessibilityProperties()"); }
			return new AccessibilityProperties();
		}
		//-----------------------------------------------------------------------
		public function set accessibilityProperties(value:AccessibilityProperties):void
		{
			if(DEBUG_DISPLAYOBJECT) { trace("DisplayObject.set_accessibilityProperties(" + value + ")"); }
		}
		//-----------------------------------------------------------------------
		public function get alpha():Number
		{
			if(DEBUG_DISPLAYOBJECT) { trace("DisplayObject.get_alpha()"); }
			return 1;
		}
		//-----------------------------------------------------------------------
		public function set alpha(value:Number):void
		{
			if(DEBUG_DISPLAYOBJECT) { trace("DisplayObject.set_alpha(" + value + ")"); }
		}
		//-----------------------------------------------------------------------
		public function get blendMode():String
		{
			if(DEBUG_DISPLAYOBJECT) { trace("DisplayObject.get_blendMode()"); }
			return "";
		}
		//-----------------------------------------------------------------------
		public function set blendMode(value:String):void
		{
			if(DEBUG_DISPLAYOBJECT) { trace("DisplayObject.set_blendMode(" + value + ")"); }
		}
		//-----------------------------------------------------------------------
		public function get cacheAsBitmap():Boolean
		{
			if(DEBUG_DISPLAYOBJECT) { trace("DisplayObject.get_cacheAsBitmap()"); }
			return false;
		}
		//-----------------------------------------------------------------------
		public function set cacheAsBitmap(value:Boolean):void
		{
			if(DEBUG_DISPLAYOBJECT) { trace("DisplayObject.set_cacheAsBitmap(" + value + ")"); }
		}
		//-----------------------------------------------------------------------
		public function get filters():Array
		{
			return null;
		}
		//-----------------------------------------------------------------------
		public function set filters(value:Array):void
		{

		}
		//-----------------------------------------------------------------------
		private native function get _height():Number;
		//-----------------------------------------------------------------------
		public function get height():Number
		{
			return _height;
		}
		//-----------------------------------------------------------------------
		private native function set _height(value:Number):void;
		//-----------------------------------------------------------------------
		public function set height(value:Number):void
		{
			_height = value;
		}
		//-----------------------------------------------------------------------
		public function get loaderInfo():LoaderInfo
		{
			trace(this, "loaderInfo()")
			return null
		}
		
		public function get mask():DisplayObject
		{
			return null;
		}
		public function set mask(value:DisplayObject):void {}
		
		public function get mouseX():Number
		{
			return null;
		}
		public function get mouseY():Number
		{
			return null;
		}
		
		public function get name():String { return ""; }
		public function set name(value:String):void {}
		
		public function get opaqueBackground():Object
		{
			return null;
		}
		public function set opaqueBackground(value:Object):void {}
		
		private native function get _parent():DisplayObjectContainer;
		public function get parent():DisplayObjectContainer
		{
			return _parent;
		}
		
		private native function get _root():DisplayObject;
		public function get root():DisplayObject
		{
			if(DEBUG_DISPLAYOBJECT) { trace("DisplayObject.get.root()=" + _root); }
			return _root;
		}

		public native function get rotation():Number
		/*{ return 0; }*/
		public native function set rotation(value:Number):void
		/*{}*/
		
		public function get scale9Grid():Rectangle
		{
			return null;
		}
		public function set scale9Grid(value:Rectangle):void {}

		public native function get scaleX():Number
		/*{ return 0; };*/
		public native function set scaleX(value:Number):void
		/*{ trace("DisplayObject::scaleX =", value); }*/
		
		public native function get scaleY():Number
		/*{ return 0; };*/
		public native function set scaleY(value:Number):void
		/*{ trace("DisplayObject::scaleY =", value); };*/
		
		public function get scrollRect():Rectangle
		{
			return null;
		}
		public function set scrollRect(value:Rectangle):void {}
		
		public native function get stage():Stage
		/*{ return null; }*/
		
		public function get transform():Transform
		{
			return null;
		}
		public function set transform(value:Transform):void {}
		//-----------------------------------------------------------------------
		private native function get _visible():Boolean;
		//-----------------------------------------------------------------------
		public function get visible():Boolean
		{
			if(DEBUG_DISPLAYOBJECT) { trace("DisplayObject.get.visible()"); }
			return _visible;
		}
		//-----------------------------------------------------------------------
		private native function set _visible(value:Boolean):void;
		//-----------------------------------------------------------------------
		public function set visible(value:Boolean):void
		{
			if(DEBUG_DISPLAYOBJECT) { trace("DisplayObject.set.visible()"); }
			_visible = value;
		}
		//-----------------------------------------------------------------------

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

		///-----------------------------------------------------------------------
		/// CLASS METHODS
		///-----------------------------------------------------------------------
		override public function dispatchEvent(event:Event):Boolean
		{
			var result:Boolean = super.dispatchEvent(event);

			if(parent != null)
			{
				parent.dispatchEvent(event);
			}

			return result;
		}

		public function getBounds(targetCoordinateSpace:DisplayObject):Rectangle
		{
			return null;
		}
		public function getRect(targetCoordinateSpace:DisplayObject):Rectangle
		{
			return null;
		}
		public function globalToLocal(point:Point):Point
		{
			return null;
		}
		public function hitTestObject(obj:DisplayObject):Boolean
		{
			return null;
		}
		public function hitTestPoint(x:Number, y:Number, shapeFlag:Boolean = false):Boolean
		{
			return null;
		}
		public function localToGlobal(point:Point):Point
		{
			return null;
		}
	}
}
