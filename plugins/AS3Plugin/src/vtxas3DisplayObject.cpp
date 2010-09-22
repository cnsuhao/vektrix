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

#include "vtxas3Object.h"
#include "vtxas3Stage.h"

#include "vtxDisplayObject.h"
#include "vtxMovie.h"
#include "vtxStage.h"

namespace vtx { namespace as3 {
	//-----------------------------------------------------------------------
	DisplayObject::DisplayObject(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
		: EventDispatcher(vtable, prototype), 
		mDisplayObject(NULL)
	{

	}
	//-----------------------------------------------------------------------
	double DisplayObject::get_x()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_x()");
		return mDisplayObject->getX();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::set_x(double val)
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::set_x()");
		mDisplayObject->setX((float)val);
	}
	//-----------------------------------------------------------------------
	double DisplayObject::get_y()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_y()");
		return mDisplayObject->getY();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::set_y(double val)
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::set_y()");
		mDisplayObject->setY((float)val);
	}
	//-----------------------------------------------------------------------
	double DisplayObject::get_rotation()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_rotation()");
		return mDisplayObject->getAngle();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::set_rotation(double val)
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::set_rotation()");
		mDisplayObject->setAngle((float)val);
	}
	//-----------------------------------------------------------------------
	double DisplayObject::get_scaleX()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_scaleX()");
		return mDisplayObject->getScaleX();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::set_scaleX(double val)
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::set_scaleX()");
		mDisplayObject->setScaleX((float)val);
	}
	//-----------------------------------------------------------------------
	double DisplayObject::get_scaleY()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_scaleY()");
		return mDisplayObject->getScaleY();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::set_scaleY(double val)
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::set_scaleY()");
		mDisplayObject->setScaleY((float)val);
	}
	//-----------------------------------------------------------------------
	double DisplayObject::get_width()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_width()");
		return mDisplayObject->getWidth();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::set_width(double val)
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::set_width()");
		mDisplayObject->setWidth((float)val);
	}
	//-----------------------------------------------------------------------
	double DisplayObject::get_height()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_height()");
		return mDisplayObject->getHeight();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::set_height(double val)
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::set_height()");
		mDisplayObject->setHeight((float)val);
	}
	//-----------------------------------------------------------------------
	DisplayObjectContainer* DisplayObject::get_parent()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_parent()");

		return NULL;
// 		DisplayObjectContainer* container = static_cast<DisplayObjectContainer*>(mDisplayObject->getParentContainer()->getScriptObject());
// 		std::cout << "DisplayObject::parent() = " << container << std::endl;
// 		return container;
	}
	//-----------------------------------------------------------------------
	Stage* DisplayObject::get_stage()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_stage()");

		//std::cout << "DisplayObject::get_stage()=" << mDisplayObject->getParent()->getStage()->getScriptObject() << std::endl;
		//return static_cast<Stage*>(mDisplayObject->getParent()->getStage()->getScriptObject());
		return NULL;
	}
	//-----------------------------------------------------------------------
	void DisplayObject::set_visible(bool val)
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::set_visible()");
		mDisplayObject->setVisible(val);
	}
	//-----------------------------------------------------------------------
	bool DisplayObject::get_visible()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_visible()");
		return mDisplayObject->getVisible();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::init(Instance* inst, ScriptInterface* iface)
	{
		EventDispatcher::init(inst, iface);
		mDisplayObject = static_cast<vtx::DisplayObject*>(inst);
	}
	//-----------------------------------------------------------------------

}}
