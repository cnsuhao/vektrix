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

package flash.net
{
	import flash.events.EventDispatcher;
	
	public class SharedObject extends EventDispatcher
	{
		public function get client():Object
		{
			return null;
		}
		
		public function set client(value:Object):void
		{
			
		}
		
		public function get data():Object
		{
			return null;
		}
		
		public static function get defaultObjectEncoding():uint
		{
			return 0;
		}
		
		public function set defaultObjectEncoding(value:uint):void
		{
			
		}
		
		public function set fps(value:Number):void
		{
			
		}
		
		public function get objectEncoding():uint
		{
			return 0;
		}
		
		public function set objectEncoding(value:uint):void
		{
			
		}
		
		public function get size():uint
		{
			return 0;
		}
		
		public function clear():void
		{
			
		}
		
		public function close():void
		{
			
		}
		
		public function connect(myConnection:NetConnection, params:String = null):void
		{
			
		}
		
		public function flush(minDiskSpace:int = 0):String
		{
			
		}
		
		public static function getLocal(name:String, localPath:String = null, secure:Boolean = false):SharedObject
		{
			return null;
		}
		
		public static function getRemote(name:String, remotePath:String = null, persistence:Object = false, secure:Boolean = false):SharedObject
		{
			return null;
		}
		
		public function send(... arguments):void
		{
			
		}
		
		public function setDirty(propertyName:String):void
		{
			
		}
		
		public function setProperty(propertyName:String, value:Object = null):void
		{
			
		}
	}
}
