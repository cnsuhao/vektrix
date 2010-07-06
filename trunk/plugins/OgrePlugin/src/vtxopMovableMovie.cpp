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

#include "vtxopMovableMovie.h"
#include "vtxopMovableMovieFactory.h"
#include "vtxopMovableEditText.h"
#include "vtxopMovableShape.h"

#include "vtxFileManager.h"
#include "vtxInstance.h"
#include "vtxInstancePool.h"
#include "vtxLogManager.h"
#include "vtxResource.h"

#include "vtxButton.h"
#include "vtxMovieClip.h"
#include "vtxShape.h"
#include "vtxShapeResource.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		MovableMovie::MovableMovie(const String& name, MovieFactory* creator) 
			: Movie(name, creator)
		{
			mAAB.setInfinite();
			mFactory = static_cast<MovableMovieFactory*>(creator);
		}
		//-----------------------------------------------------------------------
		MovableMovie::~MovableMovie()
		{
			destroy();
		}
		//-----------------------------------------------------------------------
		AtlasPacker* MovableMovie::getPacker() const
		{
			return mFactory->getPacker();
		}
		//-----------------------------------------------------------------------
		Instance* MovableMovie::getInstance(Resource* resource)
		{
			if(resource->getType() == Button::TYPE)
			{
				Button* button = new Button();
				button->_setParent(this);
				button->initFromResource(resource);
				return button;
			}
			else if(resource->getType() == MovieClip::TYPE)
			{
				MovieClip* movieclip = new MovieClip();
				movieclip->_setParent(this);
				movieclip->initFromResource(resource);
				return movieclip;
			}

			if(resource->getType() == Shape::TYPE)
			{
				ShapeResource* shape = static_cast<ShapeResource*>(resource);
				if(!mFactory->getPacker()->containsElement(shape))
				{
					mFactory->getPacker()->addElement(shape);
					mFactory->getPacker()->packAtlas();
					mFactory->getPacker()->renderAtlas();
				}
			}

			Instance* instance = mFactory->getInstancePool()->pop(resource->getType());

			// instance received from instance pool
			if(instance)
			{
				instance->_setParent(this);
				instance->initFromResource(resource);
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
					instance = factory->createObject();
					instance->_setParent(this);
					instance->initFromResource(resource);

					if(instance->getType() == EditText::TYPE)
					{
						OgreMovableEditText* edit_text = static_cast<OgreMovableEditText*>(instance);
						//edit_text->setAtlasList(mPacker->getResultList());
						//edit_text->setPacker(mPacker);
						mFactory->getPacker()->addListener(edit_text);
					}
					if(instance->getType() == Shape::TYPE)
					{
						OgreMovableShape* shape = static_cast<OgreMovableShape*>(instance);
						mFactory->getPacker()->addListener(shape);
					}

					//VTX_LOG("\"%s\": CREATED %s with id %s, using Factory %s", 
					//	movie->getName().c_str(), inst->getType().c_str(), id.c_str(), factory->getName().c_str());
				}
			}

			if(!instance)
			{
				VTX_EXCEPT("No suitable factory for the resource type \"%s\" was found, the object with the id \"%s\" can not be created!!!", 
					resource->getType().c_str(), resource->getID().c_str());
			}

			Ogre::Renderable* renderable = dynamic_cast<Ogre::Renderable*>(instance);
			if(renderable)
			{
				RenderableMap::iterator it = mRenderables.find(renderable);
				if(it == mRenderables.end())
				{
					mRenderables.insert(std::make_pair(renderable, renderable));
				}
			}

			return instance;
		}
		//-----------------------------------------------------------------------
		Instance* MovableMovie::getInstanceByType(const String& type)
		{
			Instance* instance = mFactory->getInstancePool()->pop(type);

			// instance received from instance pool
			if(instance)
			{
				instance->_setParent(this);
			}
			// no instance available, create a new one
			else
			{
				if(type == Button::TYPE)
				{
					Button* button = new Button();
					button->_setParent(this);
					return button;
				}
				else if(type == MovieClip::TYPE)
				{
					MovieClip* movieclip = new MovieClip();
					movieclip->_setParent(this);
					return movieclip;
				}

				if(!mFactory)
				{
					VTX_WARN("MovieFactory not available");
					return NULL;
				}

				InstanceFactory* factory = mFactory->getFactory(type);
				if(factory)
				{
					instance = factory->createObject();
					instance->_setParent(this);

					//VTX_LOG("\"%s\": CREATED %s with id %s, using Factory %s", 
					//	movie->getName().c_str(), inst->getType().c_str(), id.c_str(), factory->getName().c_str());
				}
			}

			if(!instance)
			{
				VTX_EXCEPT("No suitable factory for the instance type \"%s\" was found, the object with this type can not be created!!!", 
					type.c_str());
			}

			Ogre::Renderable* renderable = dynamic_cast<Ogre::Renderable*>(instance);
			if(renderable)
			{
				RenderableMap::iterator it = mRenderables.find(renderable);
				if(it == mRenderables.end())
				{
					mRenderables.insert(std::make_pair(renderable, renderable));
				}
			}

			return instance;
		}
		//-----------------------------------------------------------------------
		void MovableMovie::releaseInstance(Instance* instance)
		{
			Ogre::Renderable* renderable = dynamic_cast<Ogre::Renderable*>(instance);
			if(renderable)
			{
				RenderableMap::iterator it = mRenderables.find(renderable);
				if(it != mRenderables.end())
				{
					mRenderables.erase(it);
				}
			}

			if(instance->getType() == MovieClip::TYPE || instance->getType() == Button::TYPE)
			{
				DisplayObjectContainer* cont = static_cast<DisplayObjectContainer*>(instance);
				cont->clearLayers();

				delete instance;
				return;
			}

			mFactory->getInstancePool()->push(instance);
			instance->_setParent(NULL);

			//vtx::Movie::releaseInstance(instance);
		}
		//-----------------------------------------------------------------------
		const Ogre::String& MovableMovie::getMovableType() const
		{
			static Ogre::String temp = "myType";
			return temp;
		}
		//-----------------------------------------------------------------------
		const Ogre::AxisAlignedBox& MovableMovie::getBoundingBox() const
		{
			return mAAB;
		}
		//-----------------------------------------------------------------------
		Ogre::Real MovableMovie::getBoundingRadius() const
		{
			return 1.0f;
		}
		//-----------------------------------------------------------------------
		void MovableMovie::_updateRenderQueue(Ogre::RenderQueue* queue)
		{
			RenderableMap::iterator it = mRenderables.begin();
			RenderableMap::iterator end = mRenderables.end();

			while(it != end)
			{
				queue->addRenderable(it->second);
				++it;
			}
		}
		//-----------------------------------------------------------------------
		void MovableMovie::visitRenderables(Ogre::Renderable::Visitor* visitor, bool debugRenderables)
		{

		}
		//-----------------------------------------------------------------------
	}
}
