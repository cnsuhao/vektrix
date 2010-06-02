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
#include "vtxInstanceManager.h"
#include "vtxRenderStrategy.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	MovieFactory::MovieFactory() 
		: mTextureFactory(NULL)
	{
	}
	//-----------------------------------------------------------------------
	MovieFactory::~MovieFactory()
	{
		RenderStrategyMap::iterator it = mRenderStrategy.begin();
		RenderStrategyMap::iterator end = mRenderStrategy.end();
		while(it != end)
		{
			delete it->second;
			++it;
		}
	}
	//-----------------------------------------------------------------------
	RenderStrategy* MovieFactory::getRenderStrategy(File* file)
	{
		RenderStrategyMap::iterator it = mRenderStrategy.find(file->getFilename());

		if(it != mRenderStrategy.end())
		{
			return it->second;
		}

		RenderStrategy* renderStrategy = _createRenderStrategy(file);
		mRenderStrategy.insert(RenderStrategyMap::value_type(file->getFilename(), renderStrategy));

		return renderStrategy;
	}
	//-----------------------------------------------------------------------
	TextureFactory* MovieFactory::getTextureFactory()
	{
		return mTextureFactory;
	}
	//-----------------------------------------------------------------------
	InstanceFactory* MovieFactory::getFactory(const String& type)
	{
		FactoryMap::iterator it = mFactories.find(type);
		if(it != mFactories.end())
		{
			return it->second;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	void MovieFactory::_initialize()
	{
		InstanceManager* inst_mgr = InstanceManager::getSingletonPtr();

		mTextureFactory = inst_mgr->textures()->getFactory("OgreTexture");
	}
	//-----------------------------------------------------------------------
}
