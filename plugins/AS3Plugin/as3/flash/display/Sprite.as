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
	import flash.geom.Rectangle;
	import flash.media.SoundTransform;
	
	[native(cls="::vtx::as3::SpriteClass", instance="::vtx::as3::Sprite", methods="auto")]
	public class Sprite extends DisplayObjectContainer
	{
		public function Sprite()
		{
			super();
			//trace("AS3 Sprite CTOR");
		}
		
		/* getters & setters */
		public function get buttonMode():Boolean { return false; }
		public function set buttonMode(value:Boolean):void {}
		
		public function get dropTarget():DisplayObject { return null; }
		public function get graphics():Graphics { return null; }
		
		public function get hitArea():Sprite { return null; }
		public function set hitArea(value:Sprite):void {}
		
		public function get soundTransform():SoundTransform { return null; }
		public function set soundTransform(value:SoundTransform):void {}
		
		public function get useHandCursor():Boolean { return false; }
		public function set useHandCursor(value:Boolean):void {}

		/* methods */
		public function startDrag(lockCenter:Boolean = false, bounds:Rectangle = null):void {}
		public function stopDrag():void {}
	}
}
