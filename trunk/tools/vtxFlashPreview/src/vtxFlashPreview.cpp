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

#include "vtxFlashPreview.h"
#include "vtxFrameListener.h"
#include "vtxKeyboardListener.h"
#include "vtxMovieListener.h"
#include "vtxMouseListener.h"

#include "vtxFileManager.h"
#include "vtxRoot.h"

// vektrix plugins
#include "vtxas3Plugin.h"
#include "vtxcaiPlugin.h"
#include "vtxcurlPlugin.h"
#include "vtxfreeimgPlugin.h"
#include "vtxopPlugin.h"
#include "vtxswfPlugin.h"

#undef new
#include "vtxopMovableMovie.h"

#include "OgreRenderSystem.h"
#include "OgreRenderWindow.h"
#include "OgreRoot.h"

#include "OgreD3D9Plugin.h"
#include "OgreGLPlugin.h"

__namespace3(vtx, tools, FlashPreview)
//-----------------------------------------------------------------------
FlashPreview::FlashPreview() 
: mWindow(NULL), 
mMouse(NULL), 
mKeyboard(NULL)
{

}
//-----------------------------------------------------------------------
int FlashPreview::start(int argc, char** argv)
{
	if(argc < 2)
	{
		std::cout << "ERROR: no input file provided..." << std::endl;
		std::cin.get();
		return 1;
	}

	VTX_MEM_DEBUG_ENABLE();
	//VTX_MEM_DEBUG_BREAK(15068);

	mFilename = argv[1];

	startOgre();
	startOIS();
	startVektrix();

	mFrameListener = new FrameListener(this);
	mOgreRoot->addFrameListener(mFrameListener);

	mKeyboardListener = new KeyboardListener(this);
	mKeyboard->setEventCallback(mKeyboardListener);

	mMouseListener = new MouseListener(this);
	mMouse->setEventCallback(mMouseListener);

	mMovieListener = new MovieListener(this);
	mMovie = (vtx::ogre::MovableMovie*)vtx::Root::getSingletonPtr()->createMovie(
		"preview_movie", mFilename, "OgreMovableMovie", mMovieListener);
	mMovie->play();

	mMovieNode->attachObject(static_cast<vtx::ogre::MovableMovie*>(mMovie));
	mMovieNode->setPosition(0, 0, -500);

	// start the ogre rendering
	mOgreRoot->startRendering();

	delete mFrameListener;
	delete mKeyboardListener;
	delete mMouseListener;
	delete mMovieListener;

	stopVektrix();
	stopOgre();
	stopOIS();

	return 0;
}
//-----------------------------------------------------------------------
void FlashPreview::update()
{
	if(mKeyboard && mMouse)
	{
		mKeyboard->capture();
		mMouse->capture();
	}
}
//-----------------------------------------------------------------------
bool FlashPreview::leaveRequested()
{
	// exit on SHIFT + ESC or if the window has been closed
	return 
		(mKeyboard && mKeyboard->isKeyDown(OIS::KC_LSHIFT) && mKeyboard->isKeyDown(OIS::KC_ESCAPE)) || 
		(mWindow && mWindow->isClosed());
}
//-----------------------------------------------------------------------
void FlashPreview::resizeWindow(const int& width, const int& height)
{
	mWindow->resize(width, height);

	const OIS::MouseState& ms = mMouse->getMouseState();
	ms.width = mWindow->getWidth();
	ms.height = mWindow->getHeight();

	float movie_ratio = (float)width/height;
	float window_ratio = mCamera->getAspectRatio();
	if(movie_ratio > window_ratio)
	{
		// zoom to width
		mMovieNode->setPosition(-width/2.0f, height/2.0f, 
			-(float)width*0.5f/window_ratio/tanf(mCamera->getFOVy().valueRadians()*0.5f));
	}
	else
	{
		// zoom to height
		mMovieNode->setPosition(-width/2.0f, height/2.0f, 
			-(float)height*0.5f/tanf(mCamera->getFOVy().valueRadians()*0.5f));
	}

	const vtx::Color& bg_color = mMovie->getFile()->getHeader().bgcolor;
	mViewport->setBackgroundColour(Ogre::ColourValue(bg_color.r, bg_color.g, bg_color.b, bg_color.a));
}
//-----------------------------------------------------------------------
void FlashPreview::mouseMoved(const uint& x, const uint& y)
{
	mMovie->setMouseRel(x/(float)mWindow->getWidth(), y/(float)mWindow->getHeight());
}
//-----------------------------------------------------------------------
void FlashPreview::mouseDown()
{
	mMovie->mouseDown();
}
//-----------------------------------------------------------------------
void FlashPreview::mouseUp()
{
	mMovie->mouseUp();
}
//-----------------------------------------------------------------------
void FlashPreview::keyDown(const uint& key_code, const uint& text)
{
	mMovie->keyDown(key_code, text);
}
//-----------------------------------------------------------------------
void FlashPreview::keyUp(const uint& key_code, const uint& text)
{
	mMovie->keyUp(key_code, text);
}
//-----------------------------------------------------------------------
void FlashPreview::startVektrix()
{
	mVtxRoot = new vtx::Root();

	vtx::LogManager::getSingletonPtr()->logToCout(true);

	// vektrix plugins
	VTX_LOAD_PLUGIN(vektrix_AS3Plugin);
	VTX_LOAD_PLUGIN(vektrix_CairoPlugin);
	VTX_LOAD_PLUGIN(vektrix_cURLPlugin);
	VTX_LOAD_PLUGIN(vektrix_FreeImgPlugin);
	VTX_LOAD_PLUGIN(vektrix_OgrePlugin);
	VTX_LOAD_PLUGIN(vektrix_SwfPlugin);

	String cwd = "";
	uint slash = mFilename.find_last_of('\\');

	if(slash != String::npos)
	{
		cwd = mFilename.substr(0, slash);
	}
	else if((slash = mFilename.find_last_of('/')) != String::npos)
	{
		cwd = mFilename.substr(0, slash);
	}

	// HDD access
	vtx::FileManager::getSingletonPtr()->addFileContainer("");
	vtx::FileManager::getSingletonPtr()->addFileContainer(cwd);

	// web access
	vtx::FileManager::getSingletonPtr()->addFileContainer("", "WebFileContainer");
}
//-----------------------------------------------------------------------
void FlashPreview::stopVektrix()
{
	delete mVtxRoot;
}
//-----------------------------------------------------------------------
void FlashPreview::startOgre()
{
	mOgreRoot = new Ogre::Root("", "ogre.cfg", "Ogre.log");

	// ogre plugins
	Ogre::D3D9Plugin* d3d9_plugin = new Ogre::D3D9Plugin();
	Ogre::Root::getSingleton().installPlugin(d3d9_plugin);

	if(!mOgreRoot->restoreConfig())
		if(!mOgreRoot->showConfigDialog())
		{
			delete mOgreRoot;
			exit(1);
		}

		// override floating point mode
		Ogre::RenderSystem* render_system = mOgreRoot->getRenderSystem();
		if(render_system->getName() == "Direct3D9 Rendering Subsystem")
			render_system->setConfigOption("Floating-point mode", "Consistent");

		mWindow = mOgreRoot->initialise(true, "vtxFlashPreview - " + mFilename);

		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

		mSceneMgr = mOgreRoot->createSceneManager(Ogre::ST_GENERIC);

		mCamera = mSceneMgr->createCamera("MainCamera");
		mCamera->setAutoAspectRatio(true);
		mCamera->setNearClipDistance(1);

		mViewport = mWindow->addViewport(mCamera);
		mViewport->setBackgroundColour(Ogre::ColourValue::White);

		mMovieNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
}
//-----------------------------------------------------------------------
void FlashPreview::stopOgre()
{
	delete mOgreRoot;
}
//-----------------------------------------------------------------------
void FlashPreview::startOIS()
{
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
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
	mInputManager = OIS::InputManager::createInputSystem(pl);
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));

	// tell OIS about the window's dimensions
	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = mWindow->getWidth();
	ms.height = mWindow->getHeight();
}
//-----------------------------------------------------------------------
void FlashPreview::stopOIS()
{
	mInputManager->destroyInputObject(mMouse);
	mInputManager->destroyInputObject(mKeyboard);
	OIS::InputManager::destroyInputSystem(mInputManager);
}
//-----------------------------------------------------------------------
}}}
