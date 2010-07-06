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

#include "vtxMovie.h"

#include "vtxAtlasPacker.h"
#include "vtxButton.h"
#include "vtxFile.h"
#include "vtxFileManager.h"
#include "vtxInstanceManager.h"
#include "vtxKeyboardEvent.h"
#include "vtxKeyCodes.h"
#include "vtxLogManager.h"
#include "vtxMouseEvent.h"
#include "vtxDisplayObject.h"
#include "vtxMovieClip.h"
#include "vtxMovieDebugger.h"
#include "vtxMovieClipResource.h"
#include "vtxResource.h"
#include "vtxRoot.h"
#include "vtxScriptObject.h"
#include "vtxScriptResource.h"
#include "vtxShape.h"
#include "vtxShapeResource.h"
#include "vtxStringHelper.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	Movie::Movie(const String& name, MovieFactory* creator) 
		: mName(name), 
		mFile(NULL), 
		mCreator(creator), 
		mMousePosition(0.0f, 0.0f), 
		mUserData(NULL), 
		mFocusedObject(NULL), 
		mDebugger(NULL), 
		mMainMovieClip(NULL), 
		mScriptEngine(NULL)
	{

	}
	//-----------------------------------------------------------------------
	Movie::~Movie()
	{

	}
	//-----------------------------------------------------------------------
	const String& Movie::getName()
	{
		return mName;
	}
	//-----------------------------------------------------------------------
	File* Movie::getFile()
	{
		VTX_DEBUG_ASSERT(mFile, "call to Movie::getFile() but mFile was NULL");
		return mFile;
	}
	//-----------------------------------------------------------------------
	void Movie::addTime(float delta_time)
	{
		if(mDebugger)
		{
			mDebugger->preDebug();
		}

		if(mMainMovieClip)
		{
			mMainMovieClip->_update(delta_time);
		}
	}
	//-----------------------------------------------------------------------
	void Movie::setMouseAbs(uint x, uint y)
	{
		if(!mFile)
		{
			return;
		}

		const File::FileHeader& header = mFile->getHeader();
		// clamp x
		if(x < 0) x = 0;
		else if(x > header.width) x = header.width;

		// clamp y
		if(y < 0) y = 0;
		else if(y > header.height) y = header.height;

		mMousePosition = Vector2((float)x, (float)y);

		if(mMainMovieClip)
		{
			MouseEvent evt(MouseEvent::MOUSE_MOVE);
			evt.stageX = mMousePosition.x;
			evt.stageY = mMousePosition.y;
			mMainMovieClip->eventFired(evt);
		}
	}
	//-----------------------------------------------------------------------
	void Movie::setMouseRel(float x, float y)
	{
		if(!mFile)
		{
			return;
		}

		// clamp x
		if(x < 0.0f) x = 0.0f;
		else if(x > 1.0f) x = 1.0f;

		// clamp y
		if(y < 0.0f) y = 0.0f;
		else if(y > 1.0f) y = 1.0f;

		setMouseAbs((uint)(x * mFile->getHeader().width), (uint)(y * mFile->getHeader().height));
	}
	//-----------------------------------------------------------------------
	const Vector2& Movie::getMouseAbs() const
	{
		return mMousePosition;
	}
	//-----------------------------------------------------------------------
	void Movie::mouseDown()
	{
		if(mMainMovieClip)
		{
			MouseEvent evt(MouseEvent::MOUSE_DOWN);
			evt.stageX = mMousePosition.x;
			evt.stageY = mMousePosition.y;
			mMainMovieClip->eventFired(evt);
		}
	}
	//-----------------------------------------------------------------------
	void Movie::mouseUp()
	{
		if(mMainMovieClip)
		{
			MouseEvent evt(MouseEvent::MOUSE_UP);
			evt.stageX = mMousePosition.x;
			evt.stageY = mMousePosition.y;
			mMainMovieClip->eventFired(evt);
		}
	}
	//-----------------------------------------------------------------------
	void Movie::keyDown(const uint& keyCode, const uint& charCode)
	{
		if(mMainMovieClip)
		{
			mMainMovieClip->eventFired(KeyboardEvent(KeyboardEvent::KEY_DOWN, (KeyCode)keyCode, charCode));
		}
	}
	//-----------------------------------------------------------------------
	void Movie::keyUp(const uint& keyCode, const uint& charCode)
	{
		if(mMainMovieClip)
		{
			mMainMovieClip->eventFired(KeyboardEvent(KeyboardEvent::KEY_UP, (KeyCode)keyCode, charCode));
		}
	}
	//-----------------------------------------------------------------------
	void Movie::play()
	{
		if(mMainMovieClip)
		{
			mMainMovieClip->play();
		}
	}
	//-----------------------------------------------------------------------
	void Movie::stop()
	{
		mMainMovieClip->stop();
	}
	//-----------------------------------------------------------------------
	bool Movie::gotoFrame(uint frame)
	{
		return mMainMovieClip->gotoFrame(frame);
	}
	//-----------------------------------------------------------------------
	bool Movie::gotoTime(const float& time)
	{
		return mMainMovieClip->gotoTime(time);
	}
	//-----------------------------------------------------------------------
	ScriptEngine* Movie::getScriptEngine() const
	{
		return mScriptEngine;
	}
	//-----------------------------------------------------------------------
	void Movie::enableDebugger(const bool& enable)
	{
		if(enable && !mDebugger)
		{
			mDebugger = mCreator->_newDebugger(this);
		}
		else if(mDebugger)
		{
			delete mDebugger;
			mDebugger = NULL;
		}
	}
	//-----------------------------------------------------------------------
	MovieDebugger* Movie::getDebugger() const
	{
		return mDebugger;
	}
	//-----------------------------------------------------------------------
	MovieClip* Movie::getMainMovieClip() const
	{
		return mMainMovieClip;
	}
	//-----------------------------------------------------------------------
	bool Movie::addListener(Movie::Listener* listener)
	{
		if(mListeners.find(listener) == mListeners.end())
		{
			mListeners.insert(std::make_pair(listener, listener));
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool Movie::removeListener(Movie::Listener* listener)
	{
		ListenerMap::iterator it = mListeners.find(listener);
		if(it != mListeners.end())
		{
			mListeners.erase(it);
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	void Movie::setUserData(void* data)
	{
		mUserData = data;
	}
	//-----------------------------------------------------------------------
	void* Movie::getUserData() const
	{
		return mUserData;
	}
	//-----------------------------------------------------------------------
	void Movie::_setFocusedObject(InteractiveObject* focused_object)
	{
		mFocusedObject = focused_object;
	}
	//-----------------------------------------------------------------------
	void Movie::loadingCompleted(File* file)
	{
		if(mFile)
		{
			VTX_EXCEPT("Movie \"%s\" was already initialized with file \"%s\", ignoring second attempt to initialize with file \"%s\"", 
				mName.c_str(), mFile->getFilename().c_str(), file->getFilename().c_str());
			return;
		}

		mFile = file;

		mMainMovieClip = new MovieClip();
		mMainMovieClip->_setParent(this);
		mMainMovieClip->initFromResource(mFile->getMainMovieClip());

		ScriptEngineFactory* scriptEngineFactory = 
			InstanceManager::getSingletonPtr()->scriptEngines()->getFactory(mFile->getScriptEngine());

		// create script VM if available
		if(scriptEngineFactory)
		{
			mScriptEngine = scriptEngineFactory->createObject(this);
		}

		ScriptResource* script = dynamic_cast<ScriptResource*>(mFile->getResource("Script"));
		if(mScriptEngine && script)
		{
			if(mScriptEngine->executeCode(script->getBuffer(), script->getLength()))
			{
				ScriptObject* root_scriptobject = mScriptEngine->getRootScriptObject();
				if(root_scriptobject)
				{
					mMainMovieClip->setScriptObject(root_scriptobject);
				}
			}
		}

		std::vector<Listener*> remove_listeners;

		ListenerMap::iterator it = mListeners.begin();
		ListenerMap::iterator end = mListeners.end();
		while(it != end)
		{
			if(it->second->loadingCompleted(this))
			{
				// remove this listener
				remove_listeners.push_back(it->second);
			}
			++it;
		}

		for(uint i=0; i<remove_listeners.size(); ++i)
		{
			removeListener(remove_listeners.at(i));
		}
	}
	//-----------------------------------------------------------------------
	void Movie::loadingFailed(File* file)
	{
		bool destroy = false;

		ListenerMap::iterator it = mListeners.begin();
		ListenerMap::iterator end = mListeners.end();
		while(it != end)
		{
			destroy = destroy || it->second->loadingFailed(this);
			++it;
		}

		if(destroy)
		{
			Root::getSingletonPtr()->destroyMovie(this);
		}
	}
	//-----------------------------------------------------------------------
	void Movie::destroy()
	{
		// TODO: pure virtual call fix/hack, what to do here ?
		if(mFile)
		{
			mFile->removeListener(this);
		}

		delete mDebugger;
		delete mScriptEngine;
		delete mMainMovieClip;
	}
	//-----------------------------------------------------------------------
}
