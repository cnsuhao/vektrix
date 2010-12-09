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
	import flash.system.ApplicationDomain;
	import flash.utils.ByteArray;

	public class LoaderInfo extends EventDispatcher
	{
		/* getters & setters */
		public function get actionScriptVersion():uint { return null; }
		public function get applicationDomain():ApplicationDomain { return null; }
		public function get bytes():ByteArray { return null; }
		public function get bytesLoaded():uint { return null; }
		public function get bytesTotal():uint { return null; }
		public function get childAllowsParent():Boolean { return false; }
		// AIR-only public function get childSandboxBridge():Object { return null; }
		// AIR-only public function set childSandboxBridge(value:Object):void {}
		public function get content():DisplayObject { return null; }
		public function get contentType():String { return ""; }
		public function get frameRate():Number { return 0; }
		public function get height():int { return 0; }
		public function get loader():Loader { return null; }
		public function get loaderURL():String { return ""; }
		public function get parameters():Object { return null; }
		public function get parentAllowsChild():Boolean { return false; }
		// AIR-only public function get parentSandboxBridge():Object { return null; }
		// AIR-only public function set parentSandboxBridge(value:Object):void {}
		public function get sameDomain():Boolean { return false; }
		public function get sharedEvents():EventDispatcher { return null; }
		public function get swfVersion():uint { return null; }
		public function get url():String { return ""; }
		public function get width():int { return 0; }

		/* methods */
		public static function getLoaderInfoByDefinition(object:Object):LoaderInfo { return null; }
	}
}
