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

#include "vtxtestsOISBase.h"

#include "OgreRenderWindow.h"

namespace vtx { namespace tests {
	//-----------------------------------------------------------------------
	OISBase::OISBase() 
		: mOISInputManager(NULL)
	{

	}
	//-----------------------------------------------------------------------
	void OISBase::startOIS(Ogre::RenderWindow* window)
	{
		size_t hwnd = 0;
		window->getCustomAttribute("WINDOW", &hwnd);

		startOIS(hwnd, window->getWidth(), window->getHeight());
	}
	//-----------------------------------------------------------------------
	void OISBase::startOIS(const size_t& hwnd, const int& width, const int& height)
	{
		OIS::ParamList pl;
		std::ostringstream windowHndStr;

		windowHndStr << hwnd;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

#if defined OIS_WIN32_PLATFORM
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
		pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
		pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
		pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
		pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif

		// setup the manager, keyboard and mouse to handle input
		mOISInputManager = OIS::InputManager::createInputSystem(pl);
		mOISKeyboard = static_cast<OIS::Keyboard*>(mOISInputManager->createInputObject(OIS::OISKeyboard, true));
		mOISMouse = static_cast<OIS::Mouse*>(mOISInputManager->createInputObject(OIS::OISMouse, true));

		// tell OIS about the window's dimensions
		const OIS::MouseState &ms = mOISMouse->getMouseState();
		ms.width = width;
		ms.height = height;

		// register OIS listeners
		mOISKeyboard->setEventCallback(this);
		mOISMouse->setEventCallback(this);
	}
	//-----------------------------------------------------------------------
	void OISBase::stopOIS()
	{
		mOISInputManager->destroyInputObject(mOISMouse);
		mOISInputManager->destroyInputObject(mOISKeyboard);
		OIS::InputManager::destroyInputSystem(mOISInputManager);

		mOISMouse = NULL;
		mOISKeyboard = NULL;
		mOISInputManager = NULL;
	}
	//-----------------------------------------------------------------------
}}
