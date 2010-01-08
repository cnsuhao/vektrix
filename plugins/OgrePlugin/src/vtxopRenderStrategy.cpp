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

#include "vtxopRenderStrategy.h"

#include "vtxAtlasPacker.h"
#include "vtxButton.h"
#include "vtxInstance.h"
#include "vtxInstancePool.h"
#include "vtxLogManager.h"
#include "vtxMovie.h"
#include "vtxMovieFactory.h"
#include "vtxResource.h"
#include "vtxShapeFactory.h"

#include "vtxopShape.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		RenderStrategy::RenderStrategy(vtx::MovieFactory* factory, vtx::File* file) 
			: vtx::RenderStrategy(factory, file)
		{
			mPool = new InstancePool;
			mPacker = new AtlasPacker(mFactory->getTextureFactory());

			File::ShapeResourceList shape_list = file->getShapeResourceList();
			File::ShapeResourceList::iterator it = shape_list.begin();

			for( ; it != shape_list.end(); ++it)
			{
				mPacker->addShape(*it);
			}

			mPacker->packAtlas();
			//AtlasPacker::PackResultList list = mPacker->getResultList();
			mPacker->renderAtlas();
		}
		//-----------------------------------------------------------------------
		RenderStrategy::~RenderStrategy()
		{
			delete mPacker;
			mPacker = NULL;

			delete mPool;
			mPool = NULL;
		}
		//-----------------------------------------------------------------------
		void RenderStrategy::storeInstance(vtx::Instance* inst)
		{
			mPool->push(inst);
			inst->_setParent(NULL);
		}
		//-----------------------------------------------------------------------
		vtx::Instance* RenderStrategy::shareInstance(const std::string& id, vtx::Movie* movie)
		{
			Instance* inst = mPool->pop(id);

			if(inst)
			{
				inst->_setParent(movie);
				return inst;
			}

			Resource* resource = movie->getFile()->getResource(id);

			if(!resource)
			{
				VTX_EXCEPT("Resource %s was not found.", id.c_str());
			}

			// TODO: improve this, maybe implement it in the base class and add a listener for custom handling
			if(resource->getType() == "Shape")
			{
				if(mFactory)
				{
					VTX_LOG("Movie \"%s\" CREATED Shape with id %s, using ShapeFactory %s", movie->getName().c_str(), id.c_str(), mFactory->getShapeFactory()->getName().c_str());

					OgreShape* shape_inst = dynamic_cast<OgreShape*>(mFactory->getShapeFactory()->createObject(movie, resource));
					shape_inst->_setParent(movie);

					AtlasPacker::PackResultList list = mPacker->getResultList();
					AtlasPacker::PackResultList::iterator it = list.find(id);
					if(it != list.end())
					{
						shape_inst->setAtlasQuad(it->second);
					}

					return shape_inst;
				}
			}
			else if(resource->getType() == "Button")
			{
				if(mFactory)
				{
					VTX_LOG("Movie \"%s\" CREATED Button with id %s", movie->getName().c_str(), id.c_str());

					//Button* button_inst = mFactory->getButtonFactory()->createObject(movie, resource);
					//button_inst->_setParent(movie);

					Button* button_inst = new Button(resource);
					button_inst->_setParent(movie);
					// DEBUG
					//button_inst->_setParentMovie(movie);

					return button_inst;
				}
			}

			VTX_EXCEPT("No suitable factory for the resource type \"%s\" was found, the object with the id \"%s\" can not be created!!!", resource->getType().c_str(), id.c_str());

			return NULL;
		}
		//-----------------------------------------------------------------------
	}
}
