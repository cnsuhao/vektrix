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
	
	public class Socket extends EventDispatcher
	{
		private var _connected:Boolean = false;
		private var _endian:String = Endian.BIG_ENDIAN;
		private var _objectEncoding:uint;
		private var _timeout:uint  = 20000; //ms

		public function Socket(host:String = null, port:int = 0)
		{
		//init( "hello world" );
		}

		private function init(test:String):void
		{
		
		}

		public function get inited():String
		{
			return "";
		}

		public function get bytesAvailable():uint
		{
			return 0;
		}

		public function get connected():Boolean
		{
			return _connected;
		}

		public function get endian():String
		{
			return _endian;
		}

		public function set endian( value:String ):void
		{
			_endian = value;
		}

		public function get objectEncoding():uint
		{
			return _objectEncoding;
		}

		public function set objectEncoding( value:uint ):void
		{
			_objectEncoding = value;
		}

		public function get timeout():uint
		{
			return _timeout;
		}

		public function set timeout( value:uint ):void
		{
			_timeout = value;
		}


		public function close():void
		{

		}

		public function connect( host:String, port:int ):void
		{

		}

		public function flush():void
		{

		}

		public function readByte():int
		{
			return 0;
		}

		public function writeByte( value:int ):void
		{

		}
	}
}
