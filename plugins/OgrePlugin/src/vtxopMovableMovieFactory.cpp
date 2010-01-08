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

#include "vtxopMovableMovieDebugger.h"
#include "vtxopMovableMovie.h"
#include "vtxopRenderStrategy.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		const std::string& MovableMovieFactory::getName() const
		{
			static std::string name = "OgreMovableMovie";
			return name;
		}
		//-----------------------------------------------------------------------
		vtx::Movie* MovableMovieFactory::createObject(std::string name, vtx::File* file)
		{
			return new MovableMovie(name, file, this);
		}
		//-----------------------------------------------------------------------
		void MovableMovieFactory::destroyObject(vtx::Movie* instance)
		{
			delete instance;
			instance = NULL;
		}
		//-----------------------------------------------------------------------
		const std::string& MovableMovieFactory::_getButtonFactoryName() const
		{
			static std::string name = "BLUBBLBUB";
			return name;
		}
		//-----------------------------------------------------------------------
		const std::string& MovableMovieFactory::_getShapeFactoryName() const
		{
			static std::string name = "OgreShape";
			return name;
		}
		//-----------------------------------------------------------------------
		const std::string& MovableMovieFactory::_getTextureFactoryName() const
		{
			static std::string name = "OgreTexture";
			return name;
		}
		//-----------------------------------------------------------------------
		vtx::RenderStrategy* MovableMovieFactory::_createDataPool(File* file)
		{
			return new ogre::RenderStrategy(this, file);
		}
		//-----------------------------------------------------------------------
		MovieDebugger* MovableMovieFactory::_newDebugger(Movie* movie)
		{
			return new MovableMovieDebugger(movie);
		}
		//-----------------------------------------------------------------------
	}
}
