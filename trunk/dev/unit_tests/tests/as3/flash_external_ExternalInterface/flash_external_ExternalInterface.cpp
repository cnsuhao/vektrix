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

namespace vtx { namespace tests { namespace as3 {
	//-----------------------------------------------------------------------
	flash_external_ExternalInterface::flash_external_ExternalInterface(UnitTestHost* host) 
		: UnitTest(host), 
		mMovie(NULL)
	{
		mHost->startOgre();
		mHost->startOIS(mHost->getOgreWindow());
	}
	//-----------------------------------------------------------------------
	flash_external_ExternalInterface::~flash_external_ExternalInterface()
	{
		mHost->stopOIS();
		mHost->stopOgre();
	}
	//-----------------------------------------------------------------------
	void flash_external_ExternalInterface::started()
	{
		// let's save some screen space, nothing is displayed anyway
		mHost->getOgreWindow()->resize(350, 150);

		mRoot = new Root;

		LogManager::getSingletonPtr()->logToCout(true);

		// load vektrix plugins
		VTX_LOAD_PLUGIN(vektrix_AS3Plugin);
		VTX_LOAD_PLUGIN(vektrix_OgrePlugin);
		VTX_LOAD_PLUGIN(vektrix_SwfPlugin);

		FileManager::getSingletonPtr()->addFileContainer(VTX_TEST_MEDIA_PATH(as3, flash_external_ExternalInterface));

		mRoot->createMovie("swf_movie", "flash_external_ExternalInterface.swf", "OgreMovableMovie", this);

		mHost->startOgreRendering();
	}
	//-----------------------------------------------------------------------
	void flash_external_ExternalInterface::stopped()
	{
		delete mRoot;
		mRoot = NULL;
	}
	//-----------------------------------------------------------------------
	bool flash_external_ExternalInterface::loadingCompleted(Movie* movie)
	{
		mMovie = (ogre::MovableMovie*)movie;
		mMovie->getScriptEngine()->setCallbackListener(this);

		VTX_LOG("Press \"F1\" to execute an ActionScript 3 function from C++ via the ExternalInterface classes");

		// remove this listener
		return true;
	}
	//-----------------------------------------------------------------------
	ScriptParam flash_external_ExternalInterface::scriptCallback(const String& callback_name, const ScriptParamList& args)
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
	bool flash_external_ExternalInterface::frameStarted(const Ogre::FrameEvent& evt)
	{
		mRoot->update(evt.timeSinceLastFrame);
		return UnitTest::frameStarted(evt);
	}
	//-----------------------------------------------------------------------
	bool flash_external_ExternalInterface::keyReleased(const OIS::KeyEvent& e)
	{
		if(e.key == OIS::KC_F1 && mMovie)
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
