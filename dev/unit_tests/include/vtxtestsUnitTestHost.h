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

#include "vtxPrerequisites.h"

#include "vtxtests.h"

#include "OgrePrerequisites.h"

#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

#define Get(type, name) \
	public: const type& get##name() const \
	{ return m##name; }

#define GetPtr(type, name) \
	public: type* get##name() const \
	{ return m##name; }

#define Set(type, name) \
	public: void set##name(const type& val) \
	{ m##name = val; }

#define SetPtr(type, name) \
	public: void set##name(type* val) \
	{ m##name = val; }


#define get(type, name) \
	protected: type m##name; \
	Get(type, name)

#define getp(type, name) \
	protected: type* m##name; \
	GetPtr(type, name)

#define set(type, name) \
	protected: type m##name; \
	Set(type, name)

#define setp(type, name) \
	protected: type* m##name; \
	SetPtr(type, name)

#define getset(type, name) \
	protected: type m##name; \
	Get(type, name) \
	Set(type, name)

#define getsetp(type, name) \
	protected: type* m##name; \
	GetPtr(type, name) \
	SetPtr(type, name)

namespace vtx { namespace tests {
	//-----------------------------------------------------------------------
	class UnitTestHost
	{
	public:
		UnitTestHost();

		template <class T>
		void runTest()
		{
			mActiveTest = new T(this);
			startTesting();
			delete mActiveTest;
			mActiveTest = NULL;
		}

		void startOgre();
		void startOIS(Ogre::RenderWindow* window);
		void startOIS(const size_t& hwnd, const int& width, const int& height);

		void stopOgre();
		void stopOIS();

	protected:
		void startTesting();

		UnitTest* mActiveTest;

		// Ogre
		Ogre::Camera* mOgreCamera;
		getp(Ogre::RenderWindow, OgreWindow);
		getp(Ogre::Root, OgreRoot);
		Ogre::SceneManager* mOgreScene;
		Ogre::Viewport* mOgreViewport;

		// OIS
		OIS::InputManager* mOISInputManager;
		getsetp(OIS::Keyboard, OISKeyboard);
		getp(OIS::Mouse, OISMouse);

		// vektrix
		vtx::Root* mVektrixRoot;
	};
	//-----------------------------------------------------------------------
}}

#undef get
#undef set

#endif
