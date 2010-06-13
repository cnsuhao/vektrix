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

#include "vtxopMovableStrategy.h"

#include "vtxAtlasPacker.h"
#include "vtxButton.h"
#include "vtxEditTextResource.h"
#include "vtxFontResource.h"
#include "vtxGlyphResource.h"
#include "vtxInstance.h"
#include "vtxInstancePool.h"
#include "vtxLogManager.h"
#include "vtxMovie.h"
#include "vtxMovieClip.h"
#include "vtxMovieFactory.h"
#include "vtxResource.h"
#include "vtxShape.h"
#include "vtxShapeResource.h"
#include "vtxStaticTextResource.h"

#include "vtxopMovableEditText.h"
#include "vtxopMovableShape.h"
#include "vtxopMovableStaticText.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		MovableRenderStrategy::MovableRenderStrategy(MovieFactory* factory, File* file) 
			: RenderStrategy(factory, file)
		{
			mPool = new InstancePool();
			mPacker = new AtlasPacker(mFactory->getTextureFactory());

			const ResourceList& shape_list = file->getResourcesByType("Shape");
			ResourceList::const_iterator shape_it = shape_list.begin();
			ResourceList::const_iterator shape_end = shape_list.end();

			// add shapes
			while(shape_it != shape_end)
			{
				ShapeResource* shape = dynamic_cast<ShapeResource*>(*shape_it);
				if(shape)
				{
					mPacker->addElement(shape);
				}

				++shape_it;
			}

			const ResourceList& font_list = file->getResourcesByType("Font");
			ResourceList::const_iterator font_it = font_list.begin();
			ResourceList::const_iterator font_end = font_list.end();

			// add glyphs
			while(font_it != font_end)
			{
				FontResource* font = dynamic_cast<FontResource*>(*font_it);
				if(font)
				{
					const FontResource::GlyphList& glyphs = font->getGlyphList();
					FontResource::GlyphList::const_iterator glyph_it = glyphs.begin();
					FontResource::GlyphList::const_iterator glyph_end = glyphs.end();

					while(glyph_it != glyph_end)
					{
						mPacker->addElement(*glyph_it);
						++glyph_it;
					}
				}

				++font_it;
			}

			mPacker->packAtlas();

			file->addListener(this);
		}
		//-----------------------------------------------------------------------
		MovableRenderStrategy::~MovableRenderStrategy()
		{
			delete mPacker;
			mPacker = NULL;

			delete mPool;
			mPool = NULL;
		}
		//-----------------------------------------------------------------------
		void MovableRenderStrategy::storeInstance(Instance* inst)
		{
			mPool->push(inst);
			inst->_setParent(NULL);
		}
		//-----------------------------------------------------------------------
		Instance* MovableRenderStrategy::shareInstance(const String& id, Movie* movie)
		{
			File* file = movie->getFile();
			Resource* resource = file->getResource(id);

			if(!resource)
			{
				VTX_WARN("Resource %s was not found.", id.c_str());
				return NULL;
			}

			if(resource->getType() == Button::TYPE)
			{
				Button* button = new Button();
				button->_setParent(movie);
				button->initFromResource(resource);
				return button;
			}
			else if(resource->getType() == MovieClip::TYPE)
			{
				MovieClip* movieclip = new MovieClip();
				movieclip->_setParent(movie);
				movieclip->initFromResource(resource);
				return movieclip;
			}

			Instance* inst = mPool->pop(resource->getType());

			// instance received from instance pool
			if(inst)
			{
				inst->_setParent(movie);
				inst->initFromResource(resource);
			}
			// no instance available, create a new one
			else
			{
				if(!mFactory)
				{
					VTX_WARN("MovieFactory not available");
					return NULL;
				}

				InstanceFactory* factory = mFactory->getFactory(resource->getType());
				if(factory)
				{
					inst = factory->createObject();
					inst->_setParent(movie);
					inst->initFromResource(resource);

					//VTX_LOG("\"%s\": CREATED %s with id %s, using Factory %s", 
					//	movie->getName().c_str(), inst->getType().c_str(), id.c_str(), factory->getName().c_str());
				}
			}

			if(!inst)
			{
				VTX_EXCEPT("No suitable factory for the resource type \"%s\" was found, the object with the id \"%s\" can not be created!!!", 
					resource->getType().c_str(), id.c_str());
			}

			return inst;
		}
		//-----------------------------------------------------------------------
		Instance* MovableRenderStrategy::shareInstanceByType(const String& type, Movie* movie)
		{
			Instance* inst = mPool->pop(type);

			if(inst)
			{
				inst->_setParent(movie);
				return inst;
			}

			InstanceFactory* factory = mFactory->getFactory(type);
			if(factory)
			{
				inst = factory->createObject();
				inst->_setParent(movie);

				//VTX_LOG("\"%s\": CREATED %s using Factory %s", 
				//	movie->getName().c_str(), inst->getType().c_str(), factory->getName().c_str());

				if(inst->getType() == EditText::TYPE)
				{
					OgreMovableEditText* edit_text = dynamic_cast<OgreMovableEditText*>(inst);
					//edit_text->setAtlasList(mPacker->getResultList());
					//edit_text->setPacker(mPacker);
					mPacker->addListener(edit_text);
				}

				return inst;
			}

			return NULL;
		}
		//-----------------------------------------------------------------------
		void MovableRenderStrategy::resourceAdded(Resource* resource, const File::ResourceGroupType& group)
		{
			if(resource->getType() == "Shape")
			{
				ShapeResource* shape = dynamic_cast<ShapeResource*>(resource);
				if(shape)
				{
					mPacker->addElement(shape);
					mPacker->packAtlas();
				}
			}
		}
		//-----------------------------------------------------------------------
		AtlasPacker* MovableRenderStrategy::getPacker() const
		{
			return mPacker;
		}
		//-----------------------------------------------------------------------
	}
}
