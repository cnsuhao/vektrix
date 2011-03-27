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

#ifndef __vtxtestsOISBase_H__
#define __vtxtestsOISBase_H__

#include "vtxtests.h"

#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

#include "OgrePrerequisites.h"

namespace vtx { namespace tests {
	//-----------------------------------------------------------------------
	class OISBase : public OIS::KeyListener, public OIS::MouseListener
	{
	public:
		OISBase();
		virtual ~OISBase() {}

		void startOIS(Ogre::RenderWindow* window);
		void startOIS(const size_t& hwnd, const int& width, const int& height);
		void stopOIS();

		// OIS::KeyListener
		virtual bool keyPressed(const OIS::KeyEvent& e) { return false; }
		virtual bool keyReleased(const OIS::KeyEvent& e) { return false; }

		// OIS::MouseListener
		virtual bool mouseMoved(const OIS::MouseEvent& e) { return false; }
		virtual bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id) { return false; }
		virtual bool mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id) { return false; }

	private:
		__getp(OIS::InputManager, OISInputManager);
		__getp(OIS::Keyboard, OISKeyboard);
		__getp(OIS::Mouse, OISMouse);
	};
	//-----------------------------------------------------------------------
}}

#endif
