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

package flash.system
{
	import flash.utils.*;
	
	public final class ApplicationDomain
	{
		/* Constructor */
		public function ApplicationDomain(parentDomain:ApplicationDomain = null) { }

		/* getters & setters */
		public static function get currentDomain():ApplicationDomain { return null; }
		
		public function get domainMemory():ByteArray { return null; }
		public function set domainMemory(value:ByteArray):void {}
		
		public static function get MIN_DOMAIN_MEMORY_LENGTH():uint { return null; }
		public function get parentDomain():ApplicationDomain { return null; }

		/* methods */
		public function getDefinition(name:String):Object { return null; }
		public function hasDefinition(name:String):Boolean { return false; }
	}
}
