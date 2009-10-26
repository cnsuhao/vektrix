/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/vektrix

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
#include "vtxInstanceFactory.h"
#include "vtxLogManager.h"
#include "vtxMovableObject.h"
#include "vtxRenderStrategy.h"
#include "vtxResource.h"
#include "vtxRoot.h"
#include "vtxShapeManager.h"
#include "vtxStringHelper.h"
#include "vtxTextureManager.h"
#include "vtxTimeline.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	Movie::Movie(const String& name, File* file, MovieFactory* creator) 
		: mName(name), 
		mFile(file), 
		mCreator(creator), 
		mMousePosition(0.0f, 0.0f)
	{
		mTimeline = mFile->getTimeline().clone(this);
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
		return mFile;
	}
	//-----------------------------------------------------------------------
	void Movie::addTime(float delta_time)
	{
		mTimeline.addTime(delta_time);
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

		setMouseAbs(x * mFile->getHeader().width, y * mFile->getHeader().height);
	}
	//-----------------------------------------------------------------------
	void Movie::play()
	{
		mTimeline.play();
	}
	//-----------------------------------------------------------------------
	void Movie::stop()
	{
		mTimeline.stop();
	}
	//-----------------------------------------------------------------------
	bool Movie::goto_frame(uint frame)
	{
		return mTimeline.goto_frame(frame);
	}
	//-----------------------------------------------------------------------
	bool Movie::goto_time(float time)
	{
		return mTimeline.goto_time(time);
	}
	//-----------------------------------------------------------------------
	Instance* Movie::getInstance(const String& id)
	{
		Instance* inst = mDataPool->shareInstance(id, this);
		//VTX_LOG("SHARED instance with id %s", id.c_str());
		return inst;
	}
	//-----------------------------------------------------------------------
	void Movie::releaseInstance(Instance* instance)
	{
		if(instance)
		{
			mDataPool->storeInstance(instance);
			//VTX_LOG("STORED instance with id %s", instance->getID().c_str());
		}
	}
	//-----------------------------------------------------------------------
	bool Movie::setObjectToLayer(uint layer, MovableObject* object)
	{
		mLayers.insert(CanvasLayers::value_type(0, NULL));

		CanvasLayers::iterator it = mLayers.find(layer);

		if(it != mLayers.end())
		{
			// target layer is not free
			VTX_EXCEPT("Movie \"%s\": Target Layer %u is not free.", mName.c_str(), layer);
			return false;
		}

		uint old_layer = object->getLayer();

		it = mLayers.find(old_layer);

		if(it != mLayers.end())
		{
			if(it->second == object)
			{
				mLayers.erase(it);
			}
		}

		mLayers.insert(CanvasLayers::value_type(layer, object));

		return true;
	}
	//-----------------------------------------------------------------------
	MovableObject* Movie::getObjectFromLayer(uint layer)
	{
		CanvasLayers::iterator it = mLayers.find(layer);

		if(it != mLayers.end())
		{
			return it->second;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	bool Movie::removeObjectFromLayer(uint layer)
	{
		CanvasLayers::iterator it = mLayers.find(layer);

		if(it != mLayers.end())
		{
			mLayers.erase(it);
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	void Movie::clearLayers()
	{
		CanvasLayers::iterator it = mLayers.begin();

		for( ; it != mLayers.end(); ++it)
		{
			if(it->second)
			{
				releaseInstance(it->second);
			}
		}

		mLayers.clear();
	}
	//-----------------------------------------------------------------------
	//void Movie::_initialize(File* file)
	//{
	//	mFile = file;
	//	//mTimeline = Timeline(mFile->getTimeline(), this);
	//	mTimeline = mFile->getTimeline().clone(this);
	//}
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
