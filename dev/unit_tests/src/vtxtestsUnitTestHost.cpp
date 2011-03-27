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

#include "vtxtestsUnitTestHost.h"
#include "vtxtestsUnitTest.h"

#include "OgreRenderWindow.h"
#include "OgreRoot.h"

namespace vtx { namespace tests {
	//-----------------------------------------------------------------------
	UnitTestHost::UnitTestHost() 
		: mStopRequested(false)
	{

	}
	//-----------------------------------------------------------------------
	bool UnitTestHost::frameStarted(const Ogre::FrameEvent& evt)
	{
		if(mStopRequested)
			return false;

		if(!OgreBase::frameStarted(evt))
			return false;

		if(mOISKeyboard && mOISMouse)
		{
			mOISKeyboard->capture();
			mOISMouse->capture();
		}

		return mActiveTest->frameStarted(evt);
	}
	//-----------------------------------------------------------------------
	bool UnitTestHost::frameEnded(const Ogre::FrameEvent& evt)
	{
		if(!mActiveTest->frameEnded(evt))
			return false;

		return OgreBase::frameEnded(evt);
	}
	//-----------------------------------------------------------------------
	void UnitTestHost::windowResized(Ogre::RenderWindow* window)
	{
		mActiveTest->windowResized(window);

		if(mOISMouse)
		{
			const OIS::MouseState& ms = mOISMouse->getMouseState();
			ms.width = window->getWidth();
			ms.height = window->getHeight();
		}

		OgreBase::windowResized(window);
	}
	//-----------------------------------------------------------------------
	bool UnitTestHost::keyPressed(const OIS::KeyEvent& e)
	{
		if(mOISKeyboard->isKeyDown(OIS::KC_LSHIFT) && mOISKeyboard->isKeyDown(OIS::KC_ESCAPE))
			mStopRequested = true;

		if(mActiveTest->keyPressed(e))
			return true;

		return OISBase::keyPressed(e);
	}
	//-----------------------------------------------------------------------
	bool UnitTestHost::keyReleased(const OIS::KeyEvent& e)
	{
		if(mActiveTest->keyReleased(e))
			return true;

		return OISBase::keyReleased(e);
	}
	//-----------------------------------------------------------------------
	bool UnitTestHost::mouseMoved(const OIS::MouseEvent& e)
	{
		if(mActiveTest->mouseMoved(e))
			return true;

		return OISBase::mouseMoved(e);
	}
	//-----------------------------------------------------------------------
	bool UnitTestHost::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
	{
		if(mActiveTest->mousePressed(e, id))
			return true;

		return OISBase::mousePressed(e, id);
	}
	//-----------------------------------------------------------------------
	bool UnitTestHost::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
	{
		if(mActiveTest->mouseReleased(e, id))
			return true;

		return OISBase::mouseReleased(e, id);
	}
	//-----------------------------------------------------------------------
}}
