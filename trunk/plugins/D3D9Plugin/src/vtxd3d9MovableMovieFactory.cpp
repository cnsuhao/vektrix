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

#include "vtxd3d9MovableMovieFactory.h"
#include "vtxd3d9MovableMovie.h"
#include "vtxd3d9MovableStrategy.h"

namespace vtx
{
	namespace d3d9
	{
		//-----------------------------------------------------------------------
		MovableMovieFactory::MovableMovieFactory()
		{
			mFactoryNames["EditText"] = "";
			mFactoryNames["Shape"] = "D3D9MovableShape";
			mFactoryNames["StaticText"] = "";
			mFactoryNames["Texture"] = "D3D9Texture";
		}
		//-----------------------------------------------------------------------
		MovableMovieFactory::~MovableMovieFactory()
		{

		}
		//-----------------------------------------------------------------------
		const String& MovableMovieFactory::getName() const
		{
			static String name = "D3D9MovableMovie";
			return name;
		}
		//-----------------------------------------------------------------------
		Movie* MovableMovieFactory::createObject(String name, File* file)
		{
			return new MovableMovie(name, file, this);
		}
		//-----------------------------------------------------------------------
		void MovableMovieFactory::destroyObject(Movie* instance)
		{
			delete dynamic_cast<MovableMovie*>(instance);
			instance = NULL;
		}
		//-----------------------------------------------------------------------
		vtx::RenderStrategy* MovableMovieFactory::_createRenderStrategy(File* file)
		{
			return new MovableStrategy(this, file);
		}
		//-----------------------------------------------------------------------
		MovieDebugger* MovableMovieFactory::_newDebugger(Movie* movie)
		{
			return NULL;
		}
		//-----------------------------------------------------------------------
	}
}
