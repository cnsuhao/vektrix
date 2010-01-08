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
#include "vtxopShape.h"

#include "vtxInstance.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		MovableMovie::MovableMovie(const std::string& name, vtx::File* file, MovieFactory* creator) 
			: vtx::Movie(name, file, creator)
		{
			mAAB.setInfinite();
		}
		//-----------------------------------------------------------------------
		MovableMovie::~MovableMovie()
		{

		}
		//-----------------------------------------------------------------------
		vtx::Instance* MovableMovie::getInstance(const std::string& id)
		{
			vtx::Instance* instance = vtx::Movie::getInstance(id);

			if(instance->getType() == "Shape")
			{
				ShapeList::iterator it = mShapes.find((OgreShape*)instance);

				if(it == mShapes.end())
				{
					mShapes.insert(ShapeList::value_type((OgreShape*)instance, 0));
				}
			}

			return instance;
		}
		//-----------------------------------------------------------------------
		void MovableMovie::releaseInstance(vtx::Instance* instance)
		{
			if(instance->getType() == "Shape")
			{
				ShapeList::iterator it = mShapes.find((OgreShape*)instance);

				if(it != mShapes.end())
				{
					mShapes.erase(it);
				}
			}

			vtx::Movie::releaseInstance(instance);
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
			ShapeList::iterator it = mShapes.begin();

			for( ; it != mShapes.end(); ++it)
			{
				Ogre::Renderable* rend = dynamic_cast<Ogre::Renderable*>(it->first);
				queue->addRenderable(rend);
			}
		}
		//-----------------------------------------------------------------------
		void MovableMovie::visitRenderables(Ogre::Renderable::Visitor* visitor, bool debugRenderables)
		{

		}
		//-----------------------------------------------------------------------
	}
}
