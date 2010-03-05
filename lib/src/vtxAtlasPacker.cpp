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

#include "vtxAtlasElement.h"
#include "vtxTexture.h"
#include "vtxLogManager.h"
#include "vtxRoot.h"
#include "vtxStringHelper.h"

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
	bool AtlasPacker::sortElement(AtlasElement* elem1, AtlasElement* elem2)
	{
		const uint area1 = elem1->getPackableWidth() * elem1->getPackableHeight();
		const uint area2 = elem2->getPackableWidth() * elem2->getPackableHeight();
		return (area1 < area2);
	}
	//-----------------------------------------------------------------------
	void AtlasPacker::addElement(AtlasElement* element)
	{
		mElements.push_back(element);
	}
	//-----------------------------------------------------------------------
	const AtlasPacker::PackResultList& AtlasPacker::packAtlas()
	{
		clearAtlas();

		// sort shapes
		std::sort(mElements.rbegin(), mElements.rend(), sortElement);

		if(!mTextures.size())
		{
			mTextures.push_back(mTextureFactory->createObject());
		}

		AtlasElementList::iterator elem_it = mElements.begin();
		AtlasElementList::iterator elem_end = mElements.end();
		while(elem_it != elem_end)
		{
			AtlasTextureList::iterator tex_it = mTextures.begin();
			AtlasTextureList::iterator tex_end = mTextures.end();
			while(tex_it != tex_end)
			{
				AtlasNode* node = (*tex_it)->packElement(*elem_it);
				if(node)
				{
					mResult.insert(PackResultList::value_type((*elem_it)->getPackID(), PackResult(*tex_it, node)));
					// element was successfully packed, 
					// advance to the next element
					++elem_it;
					break;
				}

				++tex_it;

			} // while(textures)

			// TODO: implement code that handles full textures

			// no texture was found that would accept the shape, 
			// create a new, empty texture
			//mTextures.push_back(new Texture(mSize));
			//mTextures.push_back(texture_factory->createObject(mSize));

		} // while(elements)

		//std::sort(mShapes.rbegin(), mShapes.rend());

		uint packed_size = mTextures.front()->getPackedSize();
		VTX_LOG("Texture atlas packed containing %d pixels (%s)", 
			packed_size, StringHelper::formatByteUnit(packed_size * 4).c_str());

		ListenerMap::iterator listener_it = mListeners.begin();
		ListenerMap::iterator listener_end = mListeners.end();
		while(listener_it != listener_end)
		{
			listener_it->second->packed(mResult);
			++listener_it;
		}

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
		mResult.clear();

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
	bool AtlasPacker::addListener(Listener* listener)
	{
		ListenerMap::iterator it = mListeners.find(listener);
		if(it == mListeners.end())
		{
			mListeners.insert(std::make_pair(listener, listener));
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool AtlasPacker::removeListener(Listener* listener)
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
}
