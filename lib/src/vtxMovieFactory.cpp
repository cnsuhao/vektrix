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
#include "vtxMovieFactory.h"

#include "vtxFile.h"
#include "vtxRenderStrategy.h"
#include "vtxShapeManager.h"
#include "vtxTextureManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	MovieFactory::MovieFactory() 
		: mShapeFactory(NULL), 
		mTextureFactory(NULL)
	{
	}
	//-----------------------------------------------------------------------
	MovieFactory::~MovieFactory()
	{
		DataPoolMap::iterator it = mDataPools.begin();
		DataPoolMap::iterator end = mDataPools.end();
		while(it != end)
		{
			delete it->second;
			++it;
		}
	}
	//-----------------------------------------------------------------------
	RenderStrategy* MovieFactory::getDataPool(File* file)
	{
		DataPoolMap::iterator it = mDataPools.find(file->getFilename());

		if(it != mDataPools.end())
		{
			return it->second;
		}

		RenderStrategy* dataPool = _createDataPool(file);
		mDataPools.insert(DataPoolMap::value_type(file->getFilename(), dataPool));

		return dataPool;
	}
	//-----------------------------------------------------------------------
	ShapeFactory* MovieFactory::getShapeFactory()
	{
		return mShapeFactory;
	}
	//-----------------------------------------------------------------------
	TextureFactory* MovieFactory::getTextureFactory()
	{
		return mTextureFactory;
	}
	//-----------------------------------------------------------------------
	void MovieFactory::_initialize()
	{
		mShapeFactory = ShapeManager::getSingletonPtr()->getFactory(_getShapeFactoryName());
		mTextureFactory = TextureManager::getSingletonPtr()->getFactory(_getTextureFactoryName());
	}
	//-----------------------------------------------------------------------
}
