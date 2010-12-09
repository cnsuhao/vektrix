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

#include "vtxInstance.h"
#include "vtxMovie.h"
#include "vtxResource.h"
#include "vtxScriptEngine.h"
#include "vtxScriptObject.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	Instance::Instance() 
		: mParentMovie(NULL), 
		mResource(NULL), 
		mScriptObject(NULL)
	{

	}
	//-----------------------------------------------------------------------
	Instance::~Instance()
	{
		if(mScriptObject)
		{
			mScriptObject->destroy();
			mScriptObject = NULL;
		}
	}
	//-----------------------------------------------------------------------
	bool Instance::isDisplayObject() const
	{
		return false;
	}
	//-----------------------------------------------------------------------
	bool Instance::isDisplayObjectContainer() const
	{
		return false;
	}
	//-----------------------------------------------------------------------
	void Instance::_setParent(Movie* parent)
	{
		mParentMovie = parent;
	}
	//-----------------------------------------------------------------------
	Movie* Instance::getParent() const
	{
		return mParentMovie;
	}
	//-----------------------------------------------------------------------
	Resource* Instance::getResource() const
	{
		return mResource;
	}
	//-----------------------------------------------------------------------
	void Instance::setName(const String& name)
	{
		mName = name;
	}
	//-----------------------------------------------------------------------
	const String& Instance::getName() const
	{
		return mName;
	}
	//-----------------------------------------------------------------------
	void Instance::setScriptObject(ScriptObject* obj)
	{
		// remove native object from original script object
		//if(obj)
		//{
		//	Instance* inst = obj->getNativeObject();
		//	if(inst)
		//	{
		//		inst->setScriptObject(NULL);
		//	}
		//	obj->setNativeObject(NULL);
		//}

		//if(mScriptObject)
		//{
		//	mScriptObject->destroy();
		//	mScriptObject = NULL;
		//}

		mScriptObject = obj;

		if(mScriptObject)
		{
			mScriptObject->setNativeObject(this);
		}
	}
	//-----------------------------------------------------------------------
	ScriptObject* Instance::getScriptObject() const
	{
		return mScriptObject;
	}
	//-----------------------------------------------------------------------
	void Instance::initScriptObject()
	{
		ScriptEngine* script_engine = mParentMovie->getScriptEngine();
		if(script_engine)
		{
			//script_engine->createScriptObject(this);
			setScriptObject(script_engine->createScriptObject(this));
		}
	}
	//-----------------------------------------------------------------------
}
