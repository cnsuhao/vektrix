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
