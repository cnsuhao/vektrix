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

#include "vtxDisplayObject.h"

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
			mDisplayObject(NULL)
		{

		}
		//-----------------------------------------------------------------------
		void DisplayObject::setNativeObject(Instance* inst)
		{
			EventDispatcher::setNativeObject(inst);
			mDisplayObject = dynamic_cast<vtx::DisplayObject*>(inst);
		}
		//-----------------------------------------------------------------------
		double DisplayObject::get_x()
		{
			if(mDisplayObject)
			{
				return mDisplayObject->getX();
			}

			return 0;
		}
		//-----------------------------------------------------------------------
		void DisplayObject::set_x(double val)
		{
			if(mDisplayObject)
			{
				mDisplayObject->setX((float)val);
			}
		}
		//-----------------------------------------------------------------------
		double DisplayObject::get_y()
		{
			if(mDisplayObject)
			{
				return mDisplayObject->getY();
			}

			return 0;
		}
		//-----------------------------------------------------------------------
		void DisplayObject::set_y(double val)
		{
			if(mDisplayObject)
			{
				mDisplayObject->setY((float)val);
			}
		}
		//-----------------------------------------------------------------------
		double DisplayObject::get_rotation()
		{
			if(mDisplayObject)
			{
				return mDisplayObject->getAngle();
			}

			return 0;
		}
		//-----------------------------------------------------------------------
		void DisplayObject::set_rotation(double val)
		{
			if(mDisplayObject)
			{
				mDisplayObject->setAngle((float)val);
			}
		}
		//-----------------------------------------------------------------------
		double DisplayObject::get_scaleX()
		{
			if(mDisplayObject)
			{
				return mDisplayObject->getScaleX();
			}

			return 0;
		}
		//-----------------------------------------------------------------------
		void DisplayObject::set_scaleX(double val)
		{
			if(mDisplayObject)
			{
				mDisplayObject->setScaleX((float)val);
			}
		}
		//-----------------------------------------------------------------------
		double DisplayObject::get_scaleY()
		{
			if(mDisplayObject)
			{
				return mDisplayObject->getScaleY();
			}

			return 0;
		}
		//-----------------------------------------------------------------------
		void DisplayObject::set_scaleY(double val)
		{
			if(mDisplayObject)
			{
				mDisplayObject->setScaleY((float)val);
			}
		}
		//-----------------------------------------------------------------------
	}
}
