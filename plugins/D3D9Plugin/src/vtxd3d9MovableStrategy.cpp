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

#include "vtxd3d9MovableStrategy.h"
#include "vtxd3d9MovableShape.h"

#include "vtxAtlasPacker.h"
#include "vtxButton.h"
#include "vtxFile.h"
#include "vtxInstance.h"
#include "vtxInstancePool.h"
#include "vtxLogManager.h"
#include "vtxMovie.h"
#include "vtxMovieFactory.h"
#include "vtxMovieClip.h"
#include "vtxShapeResource.h"
#include "vtxResource.h"

#include "vtxShape.h"

namespace vtx
{
	namespace d3d9
	{
		//-----------------------------------------------------------------------
		MovableStrategy::MovableStrategy(vtx::MovieFactory *factory, vtx::File *file) 
			: vtx::RenderStrategy(factory, file)
		{
			mPool = new InstancePool;
			mPacker = new AtlasPacker(mFactory->getTextureFactory());

			const File::ResourceList shape_list = file->getResourcesByType("Shape");
			File::ResourceList::const_iterator shape_it = shape_list.begin();
			File::ResourceList::const_iterator shape_end = shape_list.end();

			// add shapes
			while(shape_it != shape_end)
			{
				ShapeResource* shape = dynamic_cast<vtx::ShapeResource*>(*shape_it);
				if(shape)
				{
					mPacker->addElement(shape);
				}

				++shape_it;
			}

			mPacker->packAtlas();
		}
		//-----------------------------------------------------------------------
		MovableStrategy::~MovableStrategy()
		{
			delete mPacker;
			mPacker = NULL;

			delete mPool;
			mPool = NULL;
		}
		//-----------------------------------------------------------------------
		void MovableStrategy::storeInstance(vtx::Instance* inst)
		{
			mPool->push(inst);
			inst->_setParent(NULL);
		}
		//-----------------------------------------------------------------------
		vtx::Instance* MovableStrategy::shareInstance(const String& id, vtx::Movie* movie)
		{
			Instance* inst = mPool->pop(id);

			if(inst)
			{
				inst->_setParent(movie);
				return inst;
			}

			File* file = movie->getFile();
			Resource* resource = file->getResource(id);

			if(!resource)
			{
				VTX_EXCEPT("Resource %s was not found.", id.c_str());
			}

			if(resource->getType() == "Shape")
			{
				VTX_LOG("\"%s\": CREATED Shape with id %s, using Factory %s", 
					movie->getName().c_str(), id.c_str(), mFactory->getShapeFactory()->getName().c_str());

				ShapeFactory* shape_factory = mFactory->getShapeFactory();
				D3D9MovableShape* inst = dynamic_cast<D3D9MovableShape*>(shape_factory->createObject(resource));
				inst->_setParent(movie);

				AtlasPacker::PackResultList list = mPacker->getResultList();
				AtlasPacker::PackResultList::iterator it = list.find(id);
				if(it != list.end())
				{
					inst->setAtlasQuad(it->second);
				}

				return inst;
			}
			else if(resource->getType() == "Button")
			{
				VTX_LOG("\"%s\": CREATED Button with id %s", movie->getName().c_str(), id.c_str());

				Button* button_inst = new Button(resource);
				button_inst->_setParent(movie);
				return button_inst;
			}
			else if(resource->getType() == "MovieClip")
			{
				VTX_LOG("\"%s\": CREATED MovieClip with id %s", movie->getName().c_str(), id.c_str());

				MovieClip* movieclip_inst = new MovieClip(resource);
				movieclip_inst->_setParent(movie);
				return movieclip_inst;
			}

			return NULL;
		}
		//-----------------------------------------------------------------------
	}
}
