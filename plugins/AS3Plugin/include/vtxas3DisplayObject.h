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

#ifndef __vtxas3DisplayObject_H__
#define __vtxas3DisplayObject_H__

#include "vtxas3.h"
#include "cspPrerequisites.h"

#ifdef VTX_AS3_USE_SINGLE_ABC_PACKAGE
#	include "flash.h"
#else
#	include "flash_display.h"
#endif

#include "vtxas3EventDispatcher.h"

namespace vtx { namespace as3 {
	//-----------------------------------------------------------------------
	class DisplayObject : public EventDispatcher
	{
	public:
		CSP_INST_CDTOR(DisplayObject, EventDispatcher);

		virtual void ctor();

		double get_x();
		void set_x(double val);

		double get_y();
		void set_y(double val);

		double get_rotation();
		void set_rotation(double val);

		double get_scaleX();
		void set_scaleX(double val);

		double get_scaleY();
		void set_scaleY(double val);

		double get_width();
		void set_width(double val);

		double get__height();
		void set__height(double val);

		DisplayObjectContainer* get__parent();
		DisplayObject* get__root();

		Stage* get_stage();

		void set__visible(bool val);
		bool get__visible();

		CSP_SLOTS(DisplayObject, flash_display_);

	protected:
		vtx::DisplayObject* mDisplayObject;

		virtual void init(Instance* inst, ScriptInterface* iface);
	};
	//-----------------------------------------------------------------------
	CSP_DEFINE_CLASS(DisplayObjectClass, DisplayObject, flash_display_);
	//-----------------------------------------------------------------------
}}

#endif
