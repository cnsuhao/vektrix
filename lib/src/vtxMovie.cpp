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
#include "vtxInstanceFactory.h"
#include "vtxLogManager.h"
#include "vtxMovableObject.h"
#include "vtxMovieClip.h"
#include "vtxMovieDebugger.h"
#include "vtxMovieClipResource.h"
#include "vtxRenderStrategy.h"
#include "vtxResource.h"
#include "vtxRoot.h"
#include "vtxScriptEngineManager.h"
#include "vtxScriptResource.h"
#include "vtxShape.h"
#include "vtxShapeManager.h"
#include "vtxShapeResource.h"
#include "vtxStringHelper.h"
#include "vtxTextureManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	Movie::Movie(const String& name, File* file, MovieFactory* creator) 
		: mName(name), 
		mFile(file), 
		mMouseDown(false), 
		mCreator(creator), 
		mMousePosition(0.0f, 0.0f), 
		mDebugger(NULL), 
		mMainMovieClip(NULL), 
		mScriptEngine(NULL), 
		mMouseArrow(NULL), 
		mMouseHand(NULL), 
		mMouseTextCursor(NULL)
	{
		mMainMovieClip = new MovieClip(mFile->getMainMovieClip());
		mMainMovieClip->_setParent(this);

		ScriptEngineFactory* scriptEngineFactory = 
			ScriptEngineManager::getSingletonPtr()->getFactory(mFile->getScriptEngine());

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
				mMainMovieClip->setScriptObject(mScriptEngine->getRootScriptObject());
			}
		}

		//mMouseArrow = mCreator->getShapeFactory()->createObject(this, mFile->getResource("__Reserved__MouseArrow"));
		//mMouseHand = mCreator->getShapeFactory()->createObject(this, mFile->getResource("__Reserved__MouseHand"));
		//mMouseTextCursor = mCreator->getShapeFactory()->createObject(this, mFile->getResource("__Reserved__TextCursor"));

		//mMainMovieClip->addChildAt(mMouseArrow, -1);
	}
	//-----------------------------------------------------------------------
	Movie::~Movie()
	{
		delete mDebugger;

		delete mMouseTextCursor;
		delete mMouseHand;
		delete mMouseArrow;

		delete mScriptEngine;
		delete mMainMovieClip;
	}
	//-----------------------------------------------------------------------
	const String& Movie::getName()
	{
		return mName;
	}
	//-----------------------------------------------------------------------
	File* Movie::getFile()
	{
		return mFile;
	}
	//-----------------------------------------------------------------------
	void Movie::addTime(float delta_time)
	{
		if(mDebugger)
		{
			mDebugger->preDebug();
		}

		mMainMovieClip->_update(delta_time);
	}
	//-----------------------------------------------------------------------
	void Movie::setMouseAbs(uint x, uint y)
	{
		const File::FileHeader& header = mFile->getHeader();
		// clamp x
		if(x < 0) x = 0;
		else if(x > header.width) x = header.width;

		// clamp y
		if(y < 0) y = 0;
		else if(y > header.height) y = header.height;

		mMousePosition = Vector2((float)x, (float)y);
	}
	//-----------------------------------------------------------------------
	void Movie::setMouseRel(float x, float y)
	{
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
		mMouseDown = true;
	}
	//-----------------------------------------------------------------------
	void Movie::mouseUp()
	{
		mMouseDown = false;
	}
	//-----------------------------------------------------------------------
	const bool& Movie::isMouseDown() const
	{
		return mMouseDown;
	}
	//-----------------------------------------------------------------------
	void Movie::play()
	{
		mMainMovieClip->play();
	}
	//-----------------------------------------------------------------------
	void Movie::stop()
	{
		mMainMovieClip->stop();
	}
	//-----------------------------------------------------------------------
	bool Movie::goto_frame(uint frame)
	{
		return mMainMovieClip->goto_frame(frame);
	}
	//-----------------------------------------------------------------------
	bool Movie::goto_time(const float& time)
	{
		return mMainMovieClip->goto_time(time);
	}
	//-----------------------------------------------------------------------
	Instance* Movie::getInstance(const String& id)
	{
		Instance* inst = mDataPool->shareInstance(id, this);
		//VTX_LOG("SHARED instance with id %s (%s)", id.c_str(), inst->getType().c_str());
		return inst;
	}
	//-----------------------------------------------------------------------
	void Movie::releaseInstance(Instance* instance)
	{
		if(instance)
		{
			mDataPool->storeInstance(instance);
			//VTX_LOG("STORED instance with id %s (%s)", instance->getID().c_str(), instance->getType().c_str());
		}
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
	void Movie::_initialize(MovieFactory* creator_factory)
	{
		mCreator = creator_factory;
		mDataPool = mCreator->getDataPool(mFile);
	}
	//-----------------------------------------------------------------------
}
