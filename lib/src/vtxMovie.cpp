/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009 Fuse-Software (tm)

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
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
		mMouseArrow(NULL), 
		mMouseHand(NULL), 
		mMouseTextCursor(NULL)
	{
		mMainMovieClip = new MovieClip(mFile->getMainMovieClip());
		mMainMovieClip->_setParent(this);

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
		//mTimeline->addTime(delta_time);
		mMainMovieClip->_update(delta_time);

		if(mDebugger)
		{
			mDebugger->preDebug();
		}
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

		//VTX_LOG("setMousePosition %u %u", x, y);
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
		VTX_LOG("SHARED instance with id %s (%s)", id.c_str(), inst->getType().c_str());
		return inst;
	}
	//-----------------------------------------------------------------------
	void Movie::releaseInstance(Instance* instance)
	{
		if(instance)
		{
			mDataPool->storeInstance(instance);
			VTX_LOG("STORED instance with id %s (%s)", instance->getID().c_str(), instance->getType().c_str());
		}
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
	void Movie::_initialize(RenderStrategy* dataPool)
	{
		mDataPool = dataPool;
	}
	//-----------------------------------------------------------------------
	void Movie::_setCreator(MovieFactory* factory)
	{
		mCreator = factory;
	}
	//-----------------------------------------------------------------------
}
