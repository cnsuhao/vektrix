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
	
	public class Graphics
	{
		/* methods */
		public function beginBitmapFill(bitmap:BitmapData, matrix:Matrix = null, repeat:Boolean = true, smooth:Boolean = false):void {}
		public function beginFill(color:uint, alpha:Number = 1.0):void {}
		
		public function beginGradientFill(
			type:String, colors:Array, alphas:Array, 
			ratios:Array, matrix:Matrix = null, spreadMethod:String = "pad", 
			interpolationMethod:String = "rgb", focalPointRatio:Number = 0):void {}
			
		public function clear():void {}
		public function curveTo(controlX:Number, controlY:Number, anchorX:Number, anchorY:Number):void {}
		public function drawCircle(x:Number, y:Number, radius:Number):void {}
		public function drawEllipse(x:Number, y:Number, width:Number, height:Number):void {}
		public function drawRect(x:Number, y:Number, width:Number, height:Number):void {}
		public function drawRoundRect(x:Number, y:Number, width:Number, height:Number, ellipseWidth:Number, ellipseHeight:Number = NaN):void {}
		public function endFill():void {}
		public function lineGradientStyle(type:String, colors:Array, alphas:Array, ratios:Array, matrix:Matrix = null, 
		spreadMethod:String = "pad", interpolationMethod:
		String = "rgb", focalPointRatio:Number = 0):void {}
		public function lineStyle(thickness:Number = NaN, color:uint = 0, alpha:Number = 1.0, pixelHinting:Boolean = false, 
		scaleMode:String = "normal", caps:String = null, joints:String = null, miterLimit:Number = 3):void {}
		public function lineTo(x:Number, y:Number):void {}
		public function moveTo(x:Number, y:Number):void {}
	}
}
