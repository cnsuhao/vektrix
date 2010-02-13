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

#ifndef __vtxMovieFactory_H__
#define __vtxMovieFactory_H__

#include "vtxPrerequesites.h"
#include "vtxFactory.h"

namespace vtx
{
	class vtxExport MovieFactory : public Factory<Movie, String, File*>
	{
	public:
		friend class Movie;
		friend class Root;
		// <"MovieDefinitionName", RenderStrategyPtr>
		typedef std::map<String, RenderStrategy*> RenderStrategyMap;

		MovieFactory();
		virtual ~MovieFactory();

		RenderStrategy* getRenderStrategy(File* file);

		EditTextFactory* getEditTextFactory();
		ShapeFactory* getShapeFactory();
		StaticTextFactory* getStaticTextFactory();
		TextureFactory* getTextureFactory();

	protected:
		// map of all RenderStrategies, with the respective filename as key
		RenderStrategyMap mRenderStrategy;

		// map of the used factories <InstanceType, FactoryName>
		StringMap mFactoryNames;

		// factories
		EditTextFactory* mEditTextFactory;
		ShapeFactory* mShapeFactory;
		StaticTextFactory* mStaticTextFactory;
		TextureFactory* mTextureFactory;

		virtual RenderStrategy* _createRenderStrategy(File* file) = 0;
		virtual MovieDebugger* _newDebugger(Movie* movie) = 0;

		void _initialize();
	};
}

#endif
