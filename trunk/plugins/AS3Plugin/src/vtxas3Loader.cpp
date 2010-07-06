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

#include "vtxFileManager.h"
#include "vtxMovie.h"
#include "vtxMovieClip.h"
#include "vtxMovieClipResource.h"

#include "cspScriptObject.h"
#include "cspVmCore.h"

namespace vtx
{
	namespace as3
	{
		//-----------------------------------------------------------------------
		LoaderClass::LoaderClass(avmplus::VTable* cvtable) 
			: ClassClosure(cvtable)
		{
			AvmAssert(traits()->getSizeOfInstance() == sizeof(LoaderClass));
			createVanillaPrototype();
		}
		//-----------------------------------------------------------------------
		avmplus::ScriptObject* LoaderClass::createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype)
		{
			return new (core()->GetGC(), ivtable->getExtraSize()) Loader(ivtable, prototype);
		}
		//-----------------------------------------------------------------------
		Loader::Loader(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
			: DisplayObjectContainer(vtable, prototype)
		{
			earlyInit(this, true);

			Movie* movie = static_cast<Movie*>(mCore->getUserData());
			Instance* inst = movie->getInstanceByType(vtx::MovieClip::TYPE);
			inst->setScriptObject(this);
		}
		//-----------------------------------------------------------------------
		Loader::~Loader()
		{
			DecrementRef();
			delete mScriptObject;
		}
		//-----------------------------------------------------------------------
		void Loader::load(URLRequest* request, LoaderContext* context)
		{
			String url = mCore->csp2stl(request->getURL());
			FileManager::getSingletonPtr()->getFile(url, true, this);
		}
		//-----------------------------------------------------------------------
		void Loader::eventFired(const vtx::Event& evt)
		{

		}
		//-----------------------------------------------------------------------
		void Loader::_setNativeObject(Instance* inst)
		{
			DisplayObjectContainer::_setNativeObject(inst);
		}
		//-----------------------------------------------------------------------
		void Loader::loadingCompleted(File* file)
		{
			std::cout << "FINISHED URLREQUEST" << std::endl;

			Movie* movie = static_cast<Movie*>(mCore->getUserData());
			vtx::MovieClip* mc = static_cast<vtx::MovieClip*>(movie->getInstance(file->getMainMovieClip()));
			mDisplayObjectContainer->addChild(mc);
			mc->play();
		}
		//-----------------------------------------------------------------------
		void Loader::loadingFailed(File* file)
		{

		}
		//-----------------------------------------------------------------------
	}
}
