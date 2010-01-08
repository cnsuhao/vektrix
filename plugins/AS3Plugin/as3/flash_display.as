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
    import flash.events.EventDispatcher;
    
    public final class ActionScriptVersion
    {
        
    }
    
    public class BitmapData implements IBitmapDrawable
    {
        
    }
    
    public final class BitmapDataChannel
    {
        
    }
    
    public final class BlendMode
    {
        
    }
    
    public final class CapsStyle
    {
        
    }
    
    public final class ColorCorrection
    {
        
    }
    
    public final class ColorCorrectionSupport
    {
        
    }
    
    /*
    */
    [native(cls="::vtx::as3::DisplayObjectClass", instance="::vtx::as3::DisplayObject", methods="auto")]
    public class DisplayObject extends EventDispatcher implements IBitmapDrawable
    {
        public native function get x():Number;
		public native function set x(value:Number):void;

        public native function get y():Number;
		public native function set y(value:Number):void;

        public native function get rotation():Number;
		public native function set rotation(value:Number):void;
    }
    
    public class AVM1Movie extends DisplayObject
    {
        
    }
    
    public class Bitmap extends DisplayObject
    {
        
    }
    
    public final class FocusDirection
    {
        
    }
    
    public final class FrameLabel
    {
        
    }
    
    public final class GradientType
    {
        
    }
    
    public final class Graphics
    {
        
    }
    
    public final class GraphicsBitmapFill implements IGraphicsFill, IGraphicsData
    {
        
    }
    
    public final class GraphicsEndFill implements IGraphicsFill, IGraphicsData
    {
        
    }
    
    public final class GraphicsGradientFill implements IGraphicsFill, IGraphicsData
    {
        
    }
    
    public final class GraphicsPath implements IGraphicsPath, IGraphicsData
    {
        
    }
    
    public final class GraphicsPathCommand
    {
        
    }
    
    public final class GraphicsPathWinding
    {
        
    }
    
    public final class GraphicsShaderFill implements IGraphicsFill, IGraphicsData
    {
        
    }
    
    public final class GraphicsSolidFill implements IGraphicsFill, IGraphicsData
    {
        
    }
    
    public final class GraphicsStroke implements IGraphicsStroke, IGraphicsData
    {
        
    }
    
    public final class GraphicsTrianglePath implements IGraphicsPath, IGraphicsData
    {
        
    }
    
    public interface IBitmapDrawable
    {
        
    }
    
    public interface IDrawCommand
    {
        
    }
    
    public interface IGraphicsData
    {
        
    }
    
    public interface IGraphicsFill
    {
        
    }
    
    public interface IGraphicsPath
    {
        
    }
    
    public interface IGraphicsStroke
    {
        
    }
    
    [native(cls="::vtx::as3::InteractiveObjectClass", instance="::vtx::as3::InteractiveObject", methods="auto")]
    public class InteractiveObject extends DisplayObject
    {

    }
    
    [native(cls="::vtx::as3::DisplayObjectContainerClass", instance="::vtx::as3::DisplayObjectContainer", methods="auto")]
    public class DisplayObjectContainer extends InteractiveObject
    {

    }
    
    public final class InterpolationMethod
    {
        
    }
    
    public final class JointStyle
    {
        
    }
    
    public final class LineScaleMode
    {
        
    }
    
    public class Loader extends DisplayObjectContainer
    {
        
    }
    
    public class LoaderInfo extends EventDispatcher
    {
        
    }
    
    public final class MorphShape extends DisplayObject
    {
        
    }
    
    public class NativeMenu extends EventDispatcher
    {
        
    }
    
    public class NativeMenuItem extends EventDispatcher
    {
        
    }
    
    public class NativeWindow extends EventDispatcher
    {
        
    }
    
    public final class NativeWindowDisplayState
    {
        
    }
    
    public class NativeWindowInitOptions
    {
        
    }
    
    public final class NativeWindowResize
    {
        
    }
    
    public final class NativeWindowSystemChrome
    {
        
    }
    
    public final class NativeWindowType
    {
        
    }
    
    public final class PixelSnapping
    {
        
    }
    
    public final class Scene
    {
        
    }
    
    public final class Screen extends EventDispatcher
    {
        
    }
    
    public class Shader
    {
        
    }
    
    public final dynamic class ShaderData
    {
        
    }
    
    public final dynamic class ShaderInput
    {
        
    }
    
    public class ShaderJob extends EventDispatcher
    {
        
    }
    
    public final dynamic class ShaderParameter
    {
        
    }
    
    public final class ShaderParameterType
    {
        
    }
    
    public final class ShaderPrecision
    {
        
    }
    
    public class Shape extends DisplayObject
    {
        
    }
    
    [native(cls="::vtx::as3::SimpleButtonClass", instance="::vtx::as3::SimpleButton", methods="auto")]
    public class SimpleButton extends InteractiveObject
    {

    }
    
    public final class SpreadMethod
    {
        
    }
    
    [native(cls="::vtx::as3::SpriteClass", instance="::vtx::as3::Sprite", methods="auto")]
    public class Sprite extends DisplayObjectContainer
    {

    }
    
    [native(cls="::vtx::as3::MovieClipClass", instance="::vtx::as3::MovieClip", methods="auto")]
    public dynamic class MovieClip extends Sprite
    {
		public function addFrameScript(index:int, script:Object)
		{
			//print("MovieClip addFrameScript");
		}
    }
    
    public class Stage extends DisplayObjectContainer
    {
        
    }
    
    public final class StageAlign
    {
        
    }
    
    public final class StageDisplayState
    {
        
    }
    
    public final class StageQuality
    {
        
    }
    
    public final class StageScaleMode
    {
        
    }
    
    public final class SWFVersion
    {
        
    }
    
    public final class TriangleCulling
    {
        
    }
    
}

