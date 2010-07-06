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

#include "vtxopPlugin.h"

#include "vtxopMovableMovieFactory.h"
#include "vtxopMovableEditText.h"
#include "vtxopMovableShape.h"
#include "vtxopMovableStaticText.h"
#include "vtxopTexture.h"
#include "vtxopTextureMovieFactory.h"

#include "vtxInstanceManager.h"
#include "vtxRoot.h"

//-----------------------------------------------------------------------
#ifdef VTX_STATIC_LIB
void vektrix_OgrePlugin_startPlugin()
#else
extern "C" void vtxopExport startPlugin() throw()
#endif
{
	vtx::Root::getSingletonPtr()->registerPlugin(new vtx::ogre::OgrePlugin());
}
//-----------------------------------------------------------------------

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		OgrePlugin::OgrePlugin() 
			: instMgr(InstanceManager::getSingletonPtr())
		{
			// Generic
			mTexture = new OgreTextureFactory;
			instMgr->textures()->addFactory(mTexture);

			// Movies
			initMovableMovie();
			initTextureMovie();
		}
		//-----------------------------------------------------------------------
		OgrePlugin::~OgrePlugin()
		{
			freeMovableMovie();
			freeTextureMovie();

			// Generic
			instMgr->textures()->removeFactory(mTexture);
			delete mTexture;
		}
		//-----------------------------------------------------------------------
		void OgrePlugin::initMovableMovie()
		{
			// Instances
			mMovableEditText = new OgreMovableEditTextFactory;
			mMovableShape = new OgreMovableShapeFactory;
			mMovableStaticText = new OgreMovableStaticTextFactory;

			instMgr->addFactory(mMovableEditText);
			instMgr->addFactory(mMovableShape);
			instMgr->addFactory(mMovableStaticText);

			// Movie
			mMovableMovie = new MovableMovieFactory;
			Root::getSingletonPtr()->addFactory(mMovableMovie);
		}
		//-----------------------------------------------------------------------
		void OgrePlugin::freeMovableMovie()
		{
			// Movie
			Root::getSingletonPtr()->removeFactory(mMovableMovie);
			delete mMovableMovie;

			// Instances
			instMgr->removeFactory(mMovableEditText);
			instMgr->removeFactory(mMovableShape);
			instMgr->removeFactory(mMovableStaticText);

			delete mMovableEditText;
			delete mMovableShape;
			delete mMovableStaticText;
		}
		//-----------------------------------------------------------------------
		void OgrePlugin::initTextureMovie()
		{
			// Movie
			mTextureMovie = new TextureMovieFactory;
			Root::getSingletonPtr()->addFactory(mTextureMovie);
		}
		//-----------------------------------------------------------------------
		void OgrePlugin::freeTextureMovie()
		{
			// Movie
			Root::getSingletonPtr()->removeFactory(mTextureMovie);
			delete mTextureMovie;
		}
		//-----------------------------------------------------------------------
	}
}
