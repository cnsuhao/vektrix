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

#include "vtxtestsOgreBase.h"

#include "OgreRenderWindow.h"
#include "OgreRoot.h"

#include "OgreD3D9Plugin.h"
#include "OgreGLPlugin.h"

namespace vtx { namespace tests {
	//-----------------------------------------------------------------------
	OgreBase::OgreBase() 
		: mOgreRoot(NULL)
	{

	}
	//-----------------------------------------------------------------------
	void OgreBase::startOgre()
	{
		// disable ogre cout logging
		(new Ogre::LogManager())->createLog("ogre.log", true, false, false);

		mOgreRoot = new Ogre::Root("", "ogre.cfg", "ogre.log");

		// ogre plugins
		Ogre::D3D9Plugin* d3d9_plugin = new Ogre::D3D9Plugin();
		Ogre::Root::getSingleton().installPlugin(d3d9_plugin);

		// load settings from ogre.cfg
		if(!mOgreRoot->restoreConfig())
			if(!mOgreRoot->showConfigDialog())
				delete mOgreRoot;

		// override floating point mode
		Ogre::RenderSystem* render_system = mOgreRoot->getRenderSystem();
		if(render_system->getName() == "Direct3D9 Rendering Subsystem")
			render_system->setConfigOption("Floating-point mode", "Consistent");

		mOgreWindow = mOgreRoot->initialise(true, "vektrix unit test - press SHIFT + ESC to exit");

		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

		mOgreScene = mOgreRoot->createSceneManager(Ogre::ST_GENERIC);

		mOgreCamera = mOgreScene->createCamera("MainCamera");
		mOgreCamera->setAutoAspectRatio(true);
		mOgreCamera->setNearClipDistance(1);

		mOgreViewport = mOgreWindow->addViewport(mOgreCamera);
		mOgreViewport->setBackgroundColour(Ogre::ColourValue(0.4f, 0.4f, 0.4f));

		// register Ogre listener
		mOgreRoot->addFrameListener(this);

		Ogre::WindowEventUtilities::addWindowEventListener(mOgreWindow, this);
	}
	//-----------------------------------------------------------------------
	void OgreBase::startOgreRendering()
	{
		mOgreRoot->startRendering();
	}
	//-----------------------------------------------------------------------
	void OgreBase::stopOgre()
	{
		delete mOgreRoot;
		mOgreRoot = NULL;
	}
	//-----------------------------------------------------------------------
	bool OgreBase::frameStarted(const Ogre::FrameEvent& evt)
	{
		if(!mOgreWindow)
			return true;

		return !mOgreWindow->isClosed();
	}
	//-----------------------------------------------------------------------
}}
