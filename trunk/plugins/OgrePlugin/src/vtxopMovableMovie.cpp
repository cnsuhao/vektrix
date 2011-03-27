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
#include "vtxopMovableStaticText.h"

#include "vtxogreShapeAtlasElement.h"

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
		Instance* MovableMovie::getInstanceByType(const String& type)
		{
			Instance* instance = NULL;

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
			}

			if(!instance)
				instance = Movie::getInstanceByType(type);

			if(!instance)
			{
				VTX_EXCEPT("No suitable factory for the instance type \"%s\" was found, the object with this type can not be created!!!", 
					type.c_str());
			}

			Ogre::Renderable* renderable = NULL;

			if(type == Shape::TYPE)
				renderable = static_cast<OgreMovableShape*>(instance);

			else if(type == EditText::TYPE)
				renderable = static_cast<OgreMovableEditText*>(instance);

			else if(type == StaticText::TYPE)
				renderable = static_cast<OgreMovableStaticText*>(instance);

			if(renderable)
				mRenderables.insert(std::make_pair(renderable, renderable));

			return instance;
		}
		//-----------------------------------------------------------------------
		void MovableMovie::releaseInstance(Instance* instance)
		{
			Ogre::Renderable* renderable = NULL;
			const String& type = instance->getType();

			if(type == Shape::TYPE)
				renderable = static_cast<OgreMovableShape*>(instance);

			else if(type == EditText::TYPE)
				renderable = static_cast<OgreMovableEditText*>(instance);

			else if(type == StaticText::TYPE)
				renderable = static_cast<OgreMovableStaticText*>(instance);

			if(renderable)
				mRenderables.erase(renderable);

			Movie::releaseInstance(instance);
			delete instance;
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
			for_each(it, RenderableMap, mRenderables)
				queue->addRenderable(it->second);
		}
		//-----------------------------------------------------------------------
		void MovableMovie::visitRenderables(Ogre::Renderable::Visitor* visitor, bool debugRenderables)
		{

		}
		//-----------------------------------------------------------------------
	}
}
