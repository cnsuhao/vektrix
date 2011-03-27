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

#ifndef __vtxtestsUnitTest_H__
#define __vtxtestsUnitTest_H__

#include "vtxPrerequisites.h"

#include "vtxtests.h"

#include "OgreFrameListener.h"

#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

#define VTX_TEST_MEDIA_PATH(category, name) \
	(vtx::String("../../tests/") + #category + "/" + #name + "/media").c_str()

namespace vtx { namespace tests {
	//-----------------------------------------------------------------------
	class UnitTest
	{
	public:
		UnitTest(UnitTestHost* host);
		virtual ~UnitTest() {}

		virtual void started() {}
		virtual void stopped() {}

		// Ogre::FrameListener
		virtual bool frameStarted(const Ogre::FrameEvent& evt) { return true; }
		virtual bool frameEnded(const Ogre::FrameEvent& evt) { return true; }

		// Ogre::WindowEventListener
		virtual void windowResized(Ogre::RenderWindow* window) {}

		// OIS::KeyListener
		virtual bool keyPressed(const OIS::KeyEvent& e) { return false; }
		virtual bool keyReleased(const OIS::KeyEvent& e){ return false; }

		// OIS::MouseListener
		virtual bool mouseMoved(const OIS::MouseEvent& e) { return false; }
		virtual bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id) { return false; }
		virtual bool mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id) { return false; }

	protected:
		UnitTestHost* mHost;
	};
	//-----------------------------------------------------------------------
}}

#endif
