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

#ifndef __vtxFlashPreview_H__
#define __vtxFlashPreview_H__

#include "vtxPrerequisites.h"
#define NO_MEM_DBG
#include "OgrePrerequisites.h"

namespace OIS
{
	class InputManager;
	class Keyboard;
	class Mouse;
}

namespace vtx { namespace tools { namespace FlashPreview {
	//-----------------------------------------------------------------------
	class FrameListener;
	class KeyboardListener;
	class MovieListener;
	class MouseListener;

	class FlashPreview
	{
	public:
		FlashPreview();

		int start(int argc, char** argv);
		void update();

		bool leaveRequested();
		void resizeWindow(const int& width, const int& height);

		void mouseMoved(const uint& x, const uint& y);
		void mouseDown();
		void mouseUp();

		void keyDown(const uint& key_code, const uint& text);
		void keyUp(const uint& key_code, const uint& text);

	private:
		String mFilename;
		FrameListener* mFrameListener;
		KeyboardListener* mKeyboardListener;
		MovieListener* mMovieListener;
		MouseListener* mMouseListener;

		// vektrix
		Root* mVtxRoot;
		Movie* mMovie;

		// Ogre
		Ogre::Camera* mCamera;
		Ogre::RenderWindow* mWindow;
		Ogre::Root* mOgreRoot;
		Ogre::SceneManager* mSceneMgr;
		Ogre::SceneNode* mMovieNode;
		Ogre::Viewport* mViewport;

		// OIS
		OIS::InputManager* mInputManager;
		OIS::Keyboard* mKeyboard;
		OIS::Mouse* mMouse;

		void startVektrix();
		void stopVektrix();

		void startOgre();
		void stopOgre();

		void startOIS();
		void stopOIS();
	};
	//-----------------------------------------------------------------------
}}}

#endif
