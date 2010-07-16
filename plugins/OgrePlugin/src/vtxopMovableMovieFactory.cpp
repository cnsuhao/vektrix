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

#include "vtxopMovableMovieFactory.h"
#include "vtxopMovableMovie.h"
#include "vtxopMovableMovieDebugger.h"

#include "vtxogreGlyphAtlasElement.h"
#include "vtxogreShapeAtlasElement.h"

#include "vtxAtlasPacker.h"
#include "vtxFileManager.h"
#include "vtxFontResource.h"
#include "vtxGlyphResource.h"
#include "vtxInstanceManager.h"
#include "vtxInstancePool.h"
#include "vtxShapeResource.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		MovableMovieFactory::MovableMovieFactory()
		{
			InstanceManager* inst_mgr = InstanceManager::getSingletonPtr();

			mFactories[EditText::TYPE] = inst_mgr->getFactory("OgreMovableEditText");
			mFactories[Shape::TYPE] = inst_mgr->getFactory("OgreMovableShape");
			mFactories[StaticText::TYPE] = inst_mgr->getFactory("OgreMovableStaticText");

			TextureFactory* texture_factory = inst_mgr->textures()->getFactory("OgreTexture");

			mPacker = new AtlasPacker(texture_factory);
			mPool = new InstancePool();
		}
		//-----------------------------------------------------------------------
		MovableMovieFactory::~MovableMovieFactory()
		{
			delete mPool;
			mPool = NULL;

			delete mPacker;
			mPacker = NULL;
		}
		//-----------------------------------------------------------------------
		const String& MovableMovieFactory::getName() const
		{
			static String name = "OgreMovableMovie";
			return name;
		}
		//-----------------------------------------------------------------------
		Movie* MovableMovieFactory::createObject(String name)
		{
			MovableMovie* movie = new MovableMovie(name, this);
			movie->addListener(this);
			return movie; 
		}
		//-----------------------------------------------------------------------
		void MovableMovieFactory::destroyObject(Movie* instance)
		{
			delete static_cast<MovableMovie*>(instance);
			instance = NULL;
		}
		//-----------------------------------------------------------------------
		AtlasPacker* MovableMovieFactory::getPacker() const
		{
			return mPacker;
		}
		//-----------------------------------------------------------------------
		InstancePool* MovableMovieFactory::getInstancePool() const
		{
			return mPool;
		}
		//-----------------------------------------------------------------------
		MovieDebugger* MovableMovieFactory::_newDebugger(Movie* movie)
		{
			return new MovableMovieDebugger(movie);
		}
		//-----------------------------------------------------------------------
		bool MovableMovieFactory::loadingCompleted(Movie* movie)
		{
			const File* file = movie->getFile();
			std::cout << "packing file: " << file->getFilename() << std::endl;

			const ResourceList& shape_list = file->getResourcesByType("Shape");
			ResourceList::const_iterator shape_it = shape_list.begin();
			ResourceList::const_iterator shape_end = shape_list.end();

			// add shapes
			while(shape_it != shape_end)
			{
				ShapeResource* shape = static_cast<ShapeResource*>(*shape_it);
				if(shape)
				{
					mPacker->addElement(new ShapeAtlasElement(shape));
				}

				++shape_it;
			}

			const ResourceList& font_list = file->getResourcesByType("Font");
			ResourceList::const_iterator font_it = font_list.begin();
			ResourceList::const_iterator font_end = font_list.end();

			// add glyphs
			while(font_it != font_end)
			{
				FontResource* font = static_cast<FontResource*>(*font_it);
				if(font)
				{
					const FontResource::GlyphList& glyphs = font->getGlyphList();
					FontResource::GlyphList::const_iterator glyph_it = glyphs.begin();
					FontResource::GlyphList::const_iterator glyph_end = glyphs.end();

					while(glyph_it != glyph_end)
					{
						mPacker->addElement(new GlyphAtlasElement(*glyph_it));
						++glyph_it;
					}
				}

				++font_it;
			}

			mPacker->packAtlas();

			// stop listening to this movie
			return true;
		}
		//-----------------------------------------------------------------------
	}
}
