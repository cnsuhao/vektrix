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

#include "vtxEditText.h"
#include "vtxMovie.h"

#include "cspVmCore.h"

#include "vtxLogManager.h"

namespace vtx { namespace as3 {
	//-----------------------------------------------------------------------
	TextField::TextField(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
		: InteractiveObject(vtable, prototype)
	{
		Movie* movie = static_cast<Movie*>(CSP_CORE->getUserData());
		Instance* inst = movie->getInstanceByType(EditText::TYPE);
		inst->setScriptObject(this);
	}
	//-----------------------------------------------------------------------
	TextField::~TextField()
	{

	}
	//-----------------------------------------------------------------------
	avmplus::Stringp TextField::get_htmlText()
	{
		if(mEditText)
		{
			return CSP_CORE->utfStringToAS3(mEditText->getHtmlText());
		}

		return CSP_CORE->stringToAS3("");
	}
	//-----------------------------------------------------------------------
	void TextField::set_htmlText(avmplus::Stringp htmlText)
	{
		if(mEditText)
		{
			mEditText->setHtmlText(CSP_CORE->utfStringFromAS3(htmlText));
		}
	}
	//-----------------------------------------------------------------------
	int TextField::getLineIndexAtPoint(double x, double y)
	{
		if(mEditText)
		{
			return mEditText->getLineAtPoint(Vector2((float)x, (float)y)).index;
		}

		return -1;
	}
	//-----------------------------------------------------------------------
	void TextField::setSelection(int beginIndex, int endIndex)
	{
		if(mEditText)
		{
			mEditText->setSelection(beginIndex, endIndex);
		}
	}
	//-----------------------------------------------------------------------
	void TextField::setNativeObject(Instance* inst)
	{
		Instance* instance = getNativeObject();
		if(instance)
		{
			Movie* movie = static_cast<Movie*>(CSP_CORE->getUserData());
			vtx::DisplayObject* displ = static_cast<vtx::DisplayObject*>(instance);
			if(displ)
			{
				vtx::DisplayObjectContainer* cont = displ->getParentContainer();
				if(cont)
				{
					cont->removeChildAt(displ->getLayer());
				}
				else
				{
					movie->releaseInstance(instance);
				}
			}
		}

		InteractiveObject::setNativeObject(inst);
		mEditText = static_cast<vtx::EditText*>(inst);
	}
	//-----------------------------------------------------------------------
}}
