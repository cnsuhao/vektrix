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

#include "vtxas3DisplayObject.h"

#include "vtxas3Object.h"
#include "vtxas3Stage.h"
#include "vtxas3ScriptInterface.h"

#include "vtxMovieClip.h"
#include "vtxMovie.h"
#include "vtxStage.h"

#include "cspVmCore.h"

namespace vtx { namespace as3 {
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
		if(!mDisplayObject) return;
		mDisplayObject->setX((float)val);
	}
	//-----------------------------------------------------------------------
	double DisplayObject::get_y()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_y()");
		if(!mDisplayObject) return 0;
		return mDisplayObject->getY();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::set_y(double val)
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::set_y()");
		if(!mDisplayObject) return;
		mDisplayObject->setY((float)val);
	}
	//-----------------------------------------------------------------------
	double DisplayObject::get_rotation()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_rotation()");
		if(!mDisplayObject) return 0;
		return mDisplayObject->getAngle();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::set_rotation(double val)
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::set_rotation()");
		if(!mDisplayObject) return;
		mDisplayObject->setAngle((float)val);
	}
	//-----------------------------------------------------------------------
	double DisplayObject::get_scaleX()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_scaleX()");
		if(!mDisplayObject) return 0;
		return mDisplayObject->getScaleX();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::set_scaleX(double val)
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::set_scaleX()");
		if(!mDisplayObject) return;
		mDisplayObject->setScaleX((float)val);
	}
	//-----------------------------------------------------------------------
	double DisplayObject::get_scaleY()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_scaleY()");
		if(!mDisplayObject) return 0;
		return mDisplayObject->getScaleY();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::set_scaleY(double val)
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::set_scaleY()");
		if(!mDisplayObject) return;
		mDisplayObject->setScaleY((float)val);
	}
	//-----------------------------------------------------------------------
	double DisplayObject::get_width()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_width()");
		if(!mDisplayObject) return 0;
		return mDisplayObject->getWidth();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::set_width(double val)
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::set_width()");
		if(!mDisplayObject) return;
		mDisplayObject->setWidth((float)val);
	}
	//-----------------------------------------------------------------------
	double DisplayObject::get__height()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_height()");
		if(!mDisplayObject) return 0;
		return mDisplayObject->getHeight();
	}
	//-----------------------------------------------------------------------
	void DisplayObject::set__height(double val)
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject(NULL)::set_height()");
		if(!mDisplayObject) return;
		mDisplayObject->setHeight((float)val);
	}
	//-----------------------------------------------------------------------
	DisplayObjectContainer* DisplayObject::get__parent()
	{
		VTX_DEBUG_WARNING(mDisplayObject, "DisplayObject(NULL)::get_parent()");
		if(!mDisplayObject)
		{
			CSP_CORE->console << implToString() << "\n";
			return NULL;
		}

		vtx::DisplayObjectContainer* parent = mDisplayObject->getParentContainer();
		if(parent)
		{
			VTX_DEBUG_WARNING(parent, "DisplayObject::get_parent()");
			AS3Object* object = static_cast<ScriptInterface*>(parent->getScriptObject())->getObject();
			return static_cast<DisplayObjectContainer*>(object);
		}

		return NULL;
		//return NULL;
// 		DisplayObjectContainer* container = static_cast<DisplayObjectContainer*>(mDisplayObject->getParentContainer()->getScriptObject());
// 		std::cout << "DisplayObject::parent() = " << container << std::endl;
// 		return container;
	}
	//-----------------------------------------------------------------------
	DisplayObject* DisplayObject::get__root()
	{
		ScriptInterface* iface = static_cast<ScriptInterface*>(getParentMovie()->getMainMovieClip()->getScriptObject());
		return static_cast<DisplayObject*>(iface->getObject());
	}
	//-----------------------------------------------------------------------
	Stage* DisplayObject::get_stage()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_stage()");
		ScriptInterface* iface = static_cast<ScriptInterface*>(mDisplayObject->getStage()->getScriptObject());
		Stage* stage = static_cast<Stage*>(iface->getObject());
		return stage;
		//std::cout << "DisplayObject::get_stage()=" << mDisplayObject->getParent()->getStage()->getScriptObject() << std::endl;
		//return static_cast<Stage*>(mDisplayObject->getParent()->getStage()->getScriptObject());
		//return NULL;
	}
	//-----------------------------------------------------------------------
	void DisplayObject::set__visible(bool val)
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::set_visible()");
		if(!mDisplayObject) return;
		mDisplayObject->setVisible(val);
	}
	//-----------------------------------------------------------------------
	bool DisplayObject::get__visible()
	{
		VTX_DEBUG_ASSERT(mDisplayObject, "DisplayObject::get_visible()");
		if(!mDisplayObject) return false;
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
