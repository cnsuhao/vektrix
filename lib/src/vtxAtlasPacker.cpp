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

#include "vtxAtlasPacker.h"

#include "vtxTexture.h"
#include "vtxLogManager.h"
#include "vtxRoot.h"
#include "vtxShapeResource.h"
#include "vtxTextureFactory.h"
#include "vtxTextureManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	template<> AtlasPacker* Singleton<AtlasPacker>::sInstance = 0;
	//-----------------------------------------------------------------------
	AtlasPacker::AtlasPacker(TextureFactory* factory, uint atlasSize) 
		: mTextureFactory(factory), 
		mSize(atlasSize)
	{

	}
	//-----------------------------------------------------------------------
	AtlasPacker::~AtlasPacker()
	{
		AtlasTextureList::iterator it = mTextures.begin();
		AtlasTextureList::iterator end = mTextures.end();
		while(it != end)
		{
			mTextureFactory->destroyObject(*it);
			++it;
		}
	}
	//-----------------------------------------------------------------------
	bool AtlasPacker::sortShape(ShapeResource* shape1, ShapeResource* shape2)
	{
		return (shape1->getArea() < shape2->getArea());
	}
	//-----------------------------------------------------------------------
	void AtlasPacker::addShape(ShapeResource* shape)
	{
		mShapes.push_back(shape);
	}
	//-----------------------------------------------------------------------
	const AtlasPacker::PackResultList& AtlasPacker::packAtlas()
	{
		mResult.clear();
		// TODO: sort shapes
		std::sort(mShapes.rbegin(), mShapes.rend(), sortShape);

		if(!mTextures.size())
		{
			//mTextures.push_back(new Texture(mSize));
			mTextures.push_back(mTextureFactory->createObject(NULL, NULL));
		}

		File::ShapeResourceList::iterator shape_it = mShapes.begin();
		for( ; shape_it != mShapes.end(); )
		{
			AtlasTextureList::iterator texture_it = mTextures.begin();
			for( ; texture_it != mTextures.end(); ++texture_it)
			{
				AtlasNode* node = (*texture_it)->packShape(*shape_it);
				if(node)
				{
					mResult.insert(PackResultList::value_type((*shape_it)->getID(), PackResult(*texture_it, node)));
					// shape was successfully packed, 
					// advance to the next one
					++shape_it;
					break;
				}
			}

			// TODO: implement code that handles full textures

			// no texture was found that would accept the shape, 
			// create a new, empty texture
			//mTextures.push_back(new Texture(mSize));
			//mTextures.push_back(texture_factory->createObject(mSize));
		}

		//std::sort(mShapes.rbegin(), mShapes.rend());
		return mResult;
	}
	//-----------------------------------------------------------------------
	void AtlasPacker::renderAtlas()
	{
		AtlasTextureList::iterator it = mTextures.begin();
		for( ; it != mTextures.end(); ++it)
		{
			(*it)->renderAllShapes();
		}
	}
	//-----------------------------------------------------------------------
	void AtlasPacker::clearAtlas()
	{
		AtlasTextureList::iterator it = mTextures.begin();
		for( ; it != mTextures.end(); ++it)
		{
			(*it)->clear();
		}
	}
	//-----------------------------------------------------------------------
	void AtlasPacker::destroyAtlas()
	{
		AtlasTextureList::iterator it = mTextures.begin();
		for( ; it != mTextures.end(); ++it)
		{
			delete *it;
		}

		mTextures.clear();
	}
	//-----------------------------------------------------------------------
	const AtlasPacker::PackResultList& AtlasPacker::getResultList()
	{
		return mResult;
	}
	//-----------------------------------------------------------------------
	void AtlasPacker::setSize(uint size)
	{
		mSize = size;
	}
	//-----------------------------------------------------------------------
	const uint& AtlasPacker::getSize() const
	{
		return mSize;
	}
	//-----------------------------------------------------------------------
}
