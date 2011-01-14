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

#include "flash_external_ExternalInterface.h"
#include "vtxtestsUnitTestHost.h"

#include "vtxFileManager.h"
#include "vtxRoot.h"
#include "vtxScriptEngine.h"

#include "vtxopMovableMovie.h"

#include "OgreRenderWindow.h"

#define TEST flash_external_ExternalInterface

namespace vtx { namespace tests { namespace as3 {
	//-----------------------------------------------------------------------
	VTX_TEST_MEDIA_PATH(as3, flash_external_ExternalInterface);
	//-----------------------------------------------------------------------
	TEST::TEST(UnitTestHost* host) 
		: UnitTest(host), 
		mMovie(NULL)
	{
		mHost->startOgre();
		mHost->startOIS(mHost->getOgreWindow());
	}
	//-----------------------------------------------------------------------
	TEST::~TEST()
	{
		mHost->stopOIS();
		mHost->stopOgre();
	}
	//-----------------------------------------------------------------------
	void TEST::started()
	{
		// let's save some screen space, nothing is displayed anyway
		mHost->getOgreWindow()->resize(350, 150);

		mRoot = new Root;

		LogManager::getSingletonPtr()->logToCout(true);

		// load vektrix plugins
		VTX_LOAD_PLUGIN(vektrix_AS3Plugin);
		VTX_LOAD_PLUGIN(vektrix_OgrePlugin);
		VTX_LOAD_PLUGIN(vektrix_SwfPlugin);

		FileManager::getSingletonPtr()->addFileContainer(MEDIA_PATH);

		mRoot->createMovie("swf_movie", "flash_external_ExternalInterface.swf", "OgreMovableMovie", this);
	}
	//-----------------------------------------------------------------------
	void TEST::stopped()
	{
		delete mRoot;
		mRoot = NULL;
	}
	//-----------------------------------------------------------------------
	bool TEST::loadingCompleted(Movie* movie)
	{
		mMovie = (ogre::MovableMovie*)movie;
		mMovie->getScriptEngine()->setCallbackListener(this);

		// remove this listener
		return true;
	}
	//-----------------------------------------------------------------------
	ScriptParam TEST::scriptCallback(const String& callback_name, const ScriptParamList& args)
	{
		if(callback_name == "returnValuesToCpp")
		{
			VTX_LOG("%s(%s , %d , %u , %f , %s);", 
				callback_name.c_str(), 
				(args[0].boolValue() ? "true":"false"), 
				args[1].intValue(), 
				args[2].intValue(), 
				args[3].doubleValue(), 
				args[4].stringValue());
		}

		return __TIMESTAMP__;
	}
	//-----------------------------------------------------------------------
	bool TEST::frameStarted(const Ogre::FrameEvent& evt)
	{
		mRoot->update(evt.timeSinceLastFrame);

		return UnitTest::frameStarted(evt);
	}
	//-----------------------------------------------------------------------
	bool TEST::keyReleased(const OIS::KeyEvent& e)
	{
		if(e.key == OIS::KC_E && mMovie)
		{
			ScriptParamList args;
			args.push_back(true);
			args.push_back(12345);
			args.push_back(67890);
			args.push_back(54.321);
			args.push_back("hello world!");
			vtx::ScriptParam result = mMovie->getScriptEngine()->callScriptFunction("setValuesFromCpp", args);
			VTX_LOG("return value from AS3: %s", result.stringValue());
		}

		return true;
	}
	//-----------------------------------------------------------------------
}}}
