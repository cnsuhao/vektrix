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

package flash.utils
{
	public class ByteArray
	{
		/* Constructor */
		public function ByteArray() {}
		
		/* getters & setters */
		public function get bytesAvailable():uint { return null; }
		
		public static function get defaultObjectEncoding():uint { return null; }
		public function set defaultObjectEncoding(value:uint):void {}
		
		public function get endian():String { return ""; }
		public function set endian(value:String):void {}
		
		public function get length():uint { return null; }
		public function set length(value:uint):void {}
		
		public function get objectEncoding():uint { return null; }
		public function set objectEncoding(value:uint):void {}
		
		public function get position():uint { return null; }
		public function set position(value:uint):void {}

		/* methods */
		public function compress(algorithm:String):void {}
		public function readBoolean():Boolean { return false; }
		public function readByte():int { return 0; }
		public function readBytes(bytes:ByteArray, offset:uint = 0, length:uint = 0):void {}
		public function readDouble():Number { return 0; }
		public function readFloat():Number { return 0; }
		public function readInt():int { return 0; }
		public function readMultiByte(length:uint, charSet:String):String { return ""; }
		public function readObject():* { return null; }
		public function readShort():int { return 0; }
		public function readUnsignedByte():uint { return null; }
		public function readUnsignedInt():uint { return null; }
		public function readUnsignedShort():uint { return null; }
		public function readUTF():String { return ""; }
		public function readUTFBytes(length:uint):String { return ""; }
		public function toString():String { return ""; }
		public function uncompress(algorithm:String):void {}
		public function writeBoolean(value:Boolean):void {}
		public function writeByte(value:int):void {}
		public function writeBytes(bytes:ByteArray, offset:uint = 0, length:uint = 0):void {}
		public function writeDouble(value:Number):void {}
		public function writeFloat(value:Number):void {}
		public function writeInt(value:int):void {}
		public function writeMultiByte(value:String, charSet:String):void {}
		public function writeObject(object:*):void {}
		public function writeShort(value:int):void {}
		public function writeUnsignedInt(value:uint):void {}
		public function writeUTF(value:String):void {}
		public function writeUTFBytes(value:String):void {}
	}
}
