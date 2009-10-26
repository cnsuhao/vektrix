/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/vektrix

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
#include "vtxopRenderStrategy.h"

#include "vtxAtlasPacker.h"
#include "vtxButton.h"
#include "vtxButtonFactory.h"
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
					VTX_LOG("Movie \"%s\" CREATED Button with id %s, using ButtonFactory %s", movie->getName().c_str(), id.c_str(), mFactory->getButtonFactory()->getName().c_str());

					Button* button_inst = mFactory->getButtonFactory()->createObject(movie, resource);
					button_inst->_setParent(movie);

					return button_inst;
				}
			}

			VTX_EXCEPT("No suitable factory for the resource type \"%s\" was found, the object with the id \"%s\" can not be created!!!", resource->getType().c_str(), id.c_str());

			return NULL;
		}
		//-----------------------------------------------------------------------
	}
}
