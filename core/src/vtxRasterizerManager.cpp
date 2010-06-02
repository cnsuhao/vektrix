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

#include "vtxRasterizerManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	template<> RasterizerManager* Singleton<RasterizerManager>::sInstance = 0;
	//-----------------------------------------------------------------------
	RasterizerManager::RasterizerManager()
	{

	}
	//-----------------------------------------------------------------------
	RasterizerManager::~RasterizerManager()
	{

	}
	//-----------------------------------------------------------------------
	bool RasterizerManager::addRasterizer(Rasterizer* rasterizer)
	{
		RasterizerMap::iterator it = mRasterizers.find(rasterizer->getName());

		if(it == mRasterizers.end())
		{
			mRasterizers.insert(RasterizerMap::value_type(rasterizer->getName(), rasterizer));
			VTX_LOG("Added Rasterizer with name \"%s\".", rasterizer->getName().c_str());
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	Rasterizer* RasterizerManager::getRasterizer(const String name)
	{
		RasterizerMap::iterator it = mRasterizers.find(name);

		if(it != mRasterizers.end())
		{
			return it->second;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	bool RasterizerManager::removeRasterizer(Rasterizer* rasterizer)
	{
		RasterizerMap::iterator it = mRasterizers.find(rasterizer->getName());

		if(it != mRasterizers.end())
		{
			mRasterizers.erase(it);
			VTX_LOG("Removed Rasterizer '%s'.", rasterizer->getName().c_str());
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
}
