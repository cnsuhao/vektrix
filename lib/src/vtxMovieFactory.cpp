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
