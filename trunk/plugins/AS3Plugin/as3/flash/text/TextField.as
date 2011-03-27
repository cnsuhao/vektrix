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

package flash.text
{
	import flash.display.DisplayObject;
	import flash.display.InteractiveObject;
	import flash.geom.Rectangle;

	[native(cls="::vtx::as3::TextFieldClass", instance="::vtx::as3::TextField", methods="auto")]
	public class TextField extends InteractiveObject
	{
		//-----------------------------------------------------------------------
		private native function ctor():void;
		//-----------------------------------------------------------------------
		public function TextField()
		{
			super();
			ctor();
		}
		/* getters & setters */
		public function get alwaysShowSelection():Boolean { return false; }
		public function set alwaysShowSelection(value:Boolean):void {}
		public function get antiAliasType():String { return ""; }
		public function set antiAliasType(value:String):void {}
		public function get autoSize():String { return ""; }
		public function set autoSize(value:String):void {}
		public function get background():Boolean { return false; }
		public function set background(value:Boolean):void {}
		public function get backgroundColor():uint { return null; }
		public function set backgroundColor(value:uint):void {}
		public function get border():Boolean { return false; }
		public function set border(value:Boolean):void {}
		public function get borderColor():uint { return null; }
		public function set borderColor(value:uint):void {}
		public function get bottomScrollV():int { return 0; }
		public function get caretIndex():int { return 0; }
		public function get condenseWhite():Boolean { return false; }
		public function set condenseWhite(value:Boolean):void {}
		// AIR-only public function get contextMenu():NativeMenu { return null; }
		public function get defaultTextFormat():TextFormat { return null; }
		public function set defaultTextFormat(value:TextFormat):void {}
		public function get displayAsPassword():Boolean { return false; }
		public function set displayAsPassword(value:Boolean):void {}
		public function get embedFonts():Boolean { return false; }
		public function set embedFonts(value:Boolean):void {}
		public function get gridFitType():String { return ""; }
		public function set gridFitType(value:String):void {}
		
		public native function get htmlText():String
		/*{ return ""; }*/
		public native function set htmlText(value:String):void
		/*{}*/
		
		public function get length():int { return 0; }
		public function get maxChars():int { return 0; }
		public function set maxChars(value:int):void {}
		public function get maxScrollH():int { return 0; }
		public function get maxScrollV():int { return 0; }
		public function get mouseWheelEnabled():Boolean { return false; }
		public function set mouseWheelEnabled(value:Boolean):void {}
		public function get multiline():Boolean { return false; }
		public function set multiline(value:Boolean):void {}
		public function get numLines():int { return 0; }
		public function get restrict():String { return ""; }
		public function set restrict(value:String):void {}
		public function get scrollH():int { return 0; }
		public function set scrollH(value:int):void {}
		public function get scrollV():int { return 0; }
		public function set scrollV(value:int):void {}
		public function get selectable():Boolean { return false; }
		public function set selectable(value:Boolean):void {}
		public function get selectionBeginIndex():int { return 0; }
		public function get selectionEndIndex():int { return 0; }
		public function get sharpness():Number { return 0; }
		public function set sharpness(value:Number):void {}
		public function get styleSheet():StyleSheet { return null; }
		public function set styleSheet(value:StyleSheet):void {}

		public native function get text():String;// { return ""; }
		public native function set text(value:String):void;// {}

		public function get textColor():uint { return null; }
		public function set textColor(value:uint):void {}
		public function get textHeight():Number { return 0; }
		public function get textWidth():Number { return 0; }
		public function get thickness():Number { return 0; }
		public function set thickness(value:Number):void {}
		public function get type():String { return ""; }
		public function set type(value:String):void {}
		public function get useRichTextClipboard():Boolean { return false; }
		public function set useRichTextClipboard(value:Boolean):void {}
		public function get wordWrap():Boolean { return false; }
		public function set wordWrap(value:Boolean):void {}

		/* methods */
		public function appendText(newText:String):void {}
		public function getCharBoundaries(charIndex:int):Rectangle { return null; }
		public function getCharIndexAtPoint(x:Number, y:Number):int { return 0; }
		public function getFirstCharInParagraph(charIndex:int):int { return 0; }
		public function getImageReference(id:String):DisplayObject { return null; }

		public native function getLineIndexAtPoint(x:Number, y:Number):int
		/*{ return 0; }*/

		public function getLineIndexOfChar(charIndex:int):int { return 0; }
		public function getLineLength(lineIndex:int):int { return 0; }
		public function getLineMetrics(lineIndex:int):TextLineMetrics { return null; }
		public function getLineOffset(lineIndex:int):int { return 0; }
		public function getLineText(lineIndex:int):String { return ""; }
		public function getParagraphLength(charIndex:int):int { return 0; }
		public function getTextFormat(beginIndex:int = -1, endIndex:int = -1):TextFormat { return null; }
		public function replaceSelectedText(value:String):void {}
		public function replaceText(beginIndex:int, endIndex:int, newText:String):void {}

		public native function setSelection(beginIndex:int, endIndex:int):void
		/*{}*/
		
		public function setTextFormat(format:TextFormat, beginIndex:int = -1, endIndex:int = -1):void {}
	}
}