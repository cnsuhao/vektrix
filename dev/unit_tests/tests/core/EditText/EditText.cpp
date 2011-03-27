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

#include "EditText.h"
#include "vtxtestsUnitTestHost.h"

#include "vtxFileManager.h"
#include "vtxMovieDebugger.h"
#include "vtxRoot.h"

#include "vtxFontManager.h"

#include "vtxopMovableMovie.h"

#include "OgreRenderWindow.h"
#include "OgreSceneManager.h"

namespace vtx { namespace tests { namespace core {
	//-----------------------------------------------------------------------
	EditText::EditText(UnitTestHost* host) 
		: UnitTest(host), 
		mMovie(NULL)
	{
		mHost->startOgre();
		mHost->startOIS(mHost->getOgreWindow());
	}
	//-----------------------------------------------------------------------
	EditText::~EditText()
	{
		mHost->stopOIS();
		mHost->stopOgre();
	}
	//-----------------------------------------------------------------------
	void EditText::started()
	{
		mRoot = new Root;

		LogManager::getSingletonPtr()->logToCout(true);

		// load vektrix plugins
		VTX_LOAD_PLUGIN(vektrix_AS3Plugin);
		VTX_LOAD_PLUGIN(vektrix_CairoPlugin);
		VTX_LOAD_PLUGIN(vektrix_FreeTypePlugin);
		VTX_LOAD_PLUGIN(vektrix_OgrePlugin);
		VTX_LOAD_PLUGIN(vektrix_SwfPlugin);

		FileManager::getSingletonPtr()->addFileContainer(VTX_TEST_MEDIA_PATH(core, EditText));
		FileManager::getSingletonPtr()->addFileContainer("C:/Windows/Fonts");

		FontManager::getSingletonPtr()->loadFontFile("times.ttf");
		FontResource* font = FontManager::getSingletonPtr()->getFont("Times New Roman");

		mRoot->createMovie("swf_movie", "as3_button.swf", "OgreMovableMovie", this);

		mHost->startOgreRendering();
	}
	//-----------------------------------------------------------------------
	void EditText::stopped()
	{
		delete mRoot;
		mRoot = NULL;
	}
	//-----------------------------------------------------------------------
	bool EditText::loadingCompleted(Movie* movie)
	{
		mMovie = static_cast<ogre::MovableMovie*>(movie);

		mHost->getOgreScene()->getRootSceneNode()->attachObject(mMovie);
		mHost->getOgreCamera()->setPosition(0, 0, 500);

		int width = movie->getFile()->getHeader().width;
		int height = movie->getFile()->getHeader().height;

		mHost->getOgreWindow()->resize(width, height);

		const OIS::MouseState& ms = mHost->getOISMouse()->getMouseState();
		ms.width = mHost->getOgreWindow()->getWidth();
		ms.height = mHost->getOgreWindow()->getHeight();

		float movie_ratio = (float)width/height;
		float window_ratio = mHost->getOgreCamera()->getAspectRatio();
		if(movie_ratio > window_ratio)
		{
			// zoom to width
			mHost->getOgreCamera()->setPosition(width/2.0f, -height/2.0f, 
				(float)width*0.5f/window_ratio/tanf(mHost->getOgreCamera()->getFOVy().valueRadians()*0.5f));
		}
		else
		{
			// zoom to height
			mHost->getOgreCamera()->setPosition(width/2.0f, -height/2.0f, 
				(float)height*0.5f/tanf(mHost->getOgreCamera()->getFOVy().valueRadians()*0.5f));
		}

		const vtx::Color& bg_color = mMovie->getFile()->getHeader().bgcolor;
		mHost->getOgreViewport()->setBackgroundColour(Ogre::ColourValue(bg_color.r, bg_color.g, bg_color.b, bg_color.a));

		mMovie->enableDebugger(true);
		//movie->getDebugger()->debugBoundingBoxes(true);

		// remove this listener
		return true;
	}
	//-----------------------------------------------------------------------
	bool EditText::frameStarted(const Ogre::FrameEvent& evt)
	{
		if(mHost->getOISKeyboard()->isKeyDown(OIS::KC_1))
			mHost->getOgreCamera()->move(Ogre::Vector3(0, 0, +evt.timeSinceLastFrame * 50.0f));

		if(mHost->getOISKeyboard()->isKeyDown(OIS::KC_2))
			mHost->getOgreCamera()->move(Ogre::Vector3(0, 0, -evt.timeSinceLastFrame * 50.0f));

		mRoot->update(evt.timeSinceLastFrame);
		return UnitTest::frameStarted(evt);
	}
	//-----------------------------------------------------------------------
	bool EditText::keyPressed(const OIS::KeyEvent& e)
	{
		if(mMovie)
			mMovie->keyDown(e.key, e.text);

		return true;
	}
	//-----------------------------------------------------------------------
	bool EditText::keyReleased(const OIS::KeyEvent& e)
	{
		if(mMovie)
			mMovie->keyUp(e.key, e.text);

		return true;
	}
	//-----------------------------------------------------------------------
	bool EditText::mouseMoved(const OIS::MouseEvent& e)
	{
		if(mMovie)
			mMovie->setMouseRel(
			e.state.X.abs/(float)mHost->getOgreWindow()->getWidth(), 
			e.state.Y.abs/(float)mHost->getOgreWindow()->getHeight());

		return true;
	}
	//-----------------------------------------------------------------------
	bool EditText::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
	{
		if(mMovie)
			mMovie->mouseDown();

		return true;
	}
	//-----------------------------------------------------------------------
	bool EditText::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
	{
		if(mMovie)
			mMovie->mouseUp();

		return true;
	}
	//-----------------------------------------------------------------------
}}}
