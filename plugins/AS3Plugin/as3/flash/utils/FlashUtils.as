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
	import avmplus.describeType;
	import avmplus.getQualifiedClassName;
	import avmplus.getQualifiedSuperclassName;
	import avmplus.FLASH10_FLAGS;

	[native(cls="::vtx::as3::FlashUtilsClass", methods="auto")]
	class FlashUtils
	{
		native static function getClass(className:String):Class
	}

	public function clearInterval(id:uint):void {}
	public function clearTimeout(id:uint):void {}
	public function describeType(value:*):XML
	{
		trace("describeType");
		return avmplus.describeType(value, FLASH10_FLAGS);
	}

	public function escapeMultiByte(value:String):String { return ""; }

	public function getDefinitionByName(name:String):Object
	{
		//trace("getDefinitionByName(", name, ")");
		var obj = FlashUtils.getClass(name) as Object;
		//obj = Domain.currentDomain.getClass(name) as Object;
		//trace("AFTER getDefinitionByName(", name, ")=", obj);
		return obj;
	}

	public function getQualifiedClassName(value:*):String
	{
		//trace("getQualifiedClassName(", value, ")");
		var name = avmplus.getQualifiedClassName(value);
		//trace("AFTER getQualifiedClassName(", value, ")=", name);
		return name;
	}

	public function getQualifiedSuperclassName(value:*):String
	{
		trace("getQualifiedSuperclassName(", value, ")");
		return avmplus.getQualifiedSuperclassName(value);
	}

	public function getTimer():int
	{
		trace("getTimer");
		//return System.getTimer();
		return 0;
	}

	public function setInterval(closure:Function, delay:Number, ... arguments):uint { return null; }
	public function setTimeout(closure:Function, delay:Number, ... arguments):uint { return null; }
	public function unescapeMultiByte(value:String):String { return ""; }
}
