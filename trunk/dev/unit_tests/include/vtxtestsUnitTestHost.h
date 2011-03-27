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

#ifndef __vtxtestsUnitTestBase_H__
#define __vtxtestsUnitTestBase_H__

#include "vtxtests.h"
#include "vtxtestsOgreBase.h"
#include "vtxtestsOISBase.h"

// plugins
#include "vtxas3Plugin.h"
#include "vtxcaiPlugin.h"
#include "vtxfreeimgPlugin.h"
#include "vtxftPlugin.h"
#include "vtxopPlugin.h"
#include "vtxopenglPlugin.h"
#include "vtxswfPlugin.h"

namespace vtx { namespace tests {
	//-----------------------------------------------------------------------
	class UnitTestHost : public OgreBase, public OISBase
	{
	public:
		UnitTestHost();

		template <class T>
		void runTest()
		{
			mActiveTest = new T(this);
			mActiveTest->started();
			mActiveTest->stopped();
			delete mActiveTest;
			mActiveTest = NULL;
		}

		// Ogre::FrameListener
		virtual bool frameStarted(const Ogre::FrameEvent& evt);
		virtual bool frameEnded(const Ogre::FrameEvent& evt);

		// Ogre::WindowEventListener
		virtual void windowResized(Ogre::RenderWindow* window);

		// OIS::KeyListener
		virtual bool keyPressed(const OIS::KeyEvent& e);
		virtual bool keyReleased(const OIS::KeyEvent& e);

		// OIS::MouseListener
		virtual bool mouseMoved(const OIS::MouseEvent& e);
		virtual bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);

	protected:
		bool mStopRequested;
		UnitTest* mActiveTest;
	};
	//-----------------------------------------------------------------------
}}

#undef get
#undef set

#endif
