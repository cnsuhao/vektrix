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

#include "vtxRoot.h"
#include "vtxShapeManager.h"
#include "vtxTextureManager.h"

#include "vtxopMovableMovieFactory.h"
#include "vtxopTextureMovieFactory.h"

#include "vtxopShapeFactory.h"
#include "vtxopTextureFactory.h"

//-----------------------------------------------------------------------
#ifdef VTX_STATIC_LIB
	void vektrix_OgrePlugin_startPlugin()
#else
	extern "C" void vtxopExport startPlugin() throw()
#endif
{
	vtx::Root::getSingletonPtr()->_addPlugin(new vtx::ogre::OgrePlugin());
}
//-----------------------------------------------------------------------

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		OgrePlugin::OgrePlugin() 
			: mShapeFactory(new OgreShapeFactory), 
			mTextureFactory(new OgreTextureFactory), 
			mMovableMovie(new MovableMovieFactory), 
			mTextureMovie(new TextureMovieFactory)
		{
			// InstanceFactories
			vtx::ShapeManager::getSingletonPtr()->addFactory(mShapeFactory);
			vtx::TextureManager::getSingletonPtr()->addFactory(mTextureFactory);

			// MovieFactories
			vtx::Root::getSingletonPtr()->addFactory(mMovableMovie);
			vtx::Root::getSingletonPtr()->addFactory(mTextureMovie);
		}
		//-----------------------------------------------------------------------
		OgrePlugin::~OgrePlugin()
		{
			// MovieFactories
			vtx::Root::getSingletonPtr()->removeFactory(mMovableMovie);
			vtx::Root::getSingletonPtr()->removeFactory(mTextureMovie);

			// InstanceFactories
			vtx::ShapeManager::getSingletonPtr()->removeFactory(mShapeFactory);
			vtx::TextureManager::getSingletonPtr()->removeFactory(mTextureFactory);

			delete mMovableMovie;
			delete mTextureMovie;

			delete mShapeFactory;
			delete mTextureFactory;
		}
		//-----------------------------------------------------------------------
	}
}
