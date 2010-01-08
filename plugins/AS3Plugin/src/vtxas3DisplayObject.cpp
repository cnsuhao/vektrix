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

#include "flash_package.h"

#include "cspScriptObject.h"

namespace vtx
{
	namespace as3
	{
		//-----------------------------------------------------------------------
		DisplayObjectClass::DisplayObjectClass(avmplus::VTable* cvtable) 
			: ClassClosure(cvtable)
		{
			AvmAssert(traits()->getSizeOfInstance() == sizeof(DisplayObjectClass));
			createVanillaPrototype();
		}
		//-----------------------------------------------------------------------
		avmplus::ScriptObject* DisplayObjectClass::createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype)
		{
			return new (core()->GetGC(), ivtable->getExtraSize()) DisplayObject(ivtable, prototype);
		}
		//-----------------------------------------------------------------------
		DisplayObject::DisplayObject(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
			: EventDispatcher(vtable, prototype), 
			mCaspinObject(NULL)
		{

		}
		//-----------------------------------------------------------------------
		double DisplayObject::get_x()
		{
			return 0;
		}
		//-----------------------------------------------------------------------
		void DisplayObject::set_x(double val)
		{

		}
		//-----------------------------------------------------------------------
		double DisplayObject::get_y()
		{
			return 0;
		}
		//-----------------------------------------------------------------------
		void DisplayObject::set_y(double val)
		{

		}
		//-----------------------------------------------------------------------
		double DisplayObject::get_rotation()
		{
			return 0;
		}
		//-----------------------------------------------------------------------
		void DisplayObject::set_rotation(double val)
		{

		}
		//-----------------------------------------------------------------------
		csp::ScriptObject* DisplayObject::getCaspinObject()
		{
			if(!mCaspinObject)
			{
				mCaspinObject = csp::ScriptObject::fromAvmplus(this);
			}

			return mCaspinObject;
		}
		//-----------------------------------------------------------------------
	}
}
