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

#ifndef __vtx_tests_as3_flash_external_ExternalInterface_H__
#define __vtx_tests_as3_flash_external_ExternalInterface_H__

#include "vtxtestsUnitTest.h"

#include "vtxMovie.h"
#include "vtxScriptCallbackListener.h"

#include "vtxop.h"

namespace vtx { namespace tests { namespace as3 {
	//-----------------------------------------------------------------------
	class flash_external_ExternalInterface : public UnitTest, public Movie::Listener, public ScriptCallbackListener
	{
	public:
		flash_external_ExternalInterface(UnitTestHost* host);
		virtual ~flash_external_ExternalInterface();

		virtual void started();
		virtual void stopped();

		// vtx::Movie::Listener
		virtual bool loadingCompleted(Movie* movie);

		// vtx::ScriptCallbackListener
		virtual ScriptParam scriptCallback(const String& callback_name, const ScriptParamList& args);

		// Ogre
		virtual bool frameStarted(const Ogre::FrameEvent& evt);

		// OIS
		virtual bool keyReleased(const OIS::KeyEvent& e);

	protected:
		Root* mRoot;
		ogre::MovableMovie* mMovie;
	};
	//-----------------------------------------------------------------------
}}}

#endif
