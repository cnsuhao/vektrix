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

#include "vtxFile.h"

#include "vtxAtlasPacker.h"
#include "vtxLogManager.h"
#include "vtxMovieClipResource.h"
#include "vtxResource.h"
#include "vtxShapeResource.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	File::File(const String& filename) 
		: mFilename(filename), 
		mScriptEngineFactory(""), 
		mMainMovieClip(NULL)
	{

	}
	//-----------------------------------------------------------------------
	File::~File()
	{
		delete mMainMovieClip;

		ResourceMap::iterator it = mResources.begin();
		ResourceMap::iterator end = mResources.end();
		while(it != end)
		{
			delete it->second;
			++it;
		}
	}
	//-----------------------------------------------------------------------
	const String& File::getFilename()
	{
		return mFilename;
	}
	//-----------------------------------------------------------------------
	void File::setHeader(FileHeader header)
	{
		mHeader = header;
	}
	//-----------------------------------------------------------------------
	const File::FileHeader& File::getHeader()
	{
		return mHeader;
	}
	//-----------------------------------------------------------------------
	void File::setScriptEngine(const String& scriptEngineFactory)
	{
		mScriptEngineFactory = scriptEngineFactory;
	}
	//-----------------------------------------------------------------------
	const String& File::getScriptEngine()
	{
		return mScriptEngineFactory;
	}
	//-----------------------------------------------------------------------
	void File::setMainMovieClip(MovieClipResource* movieclip)
	{
		mMainMovieClip = movieclip;
	}
	//-----------------------------------------------------------------------
	MovieClipResource* File::getMainMovieClip()
	{
		return mMainMovieClip;
	}
	//-----------------------------------------------------------------------
	void File::addResource(Resource* res)
	{
		ResourceMap::iterator it = mResources.find(res->getID());

		if(it != mResources.end())
		{
			VTX_EXCEPT("\"%s\": Tried to add Resource with id \"%s\" twice!", mFilename.c_str(), res->getID().c_str());
		}

		mResources[res->getID()] = res;

		if(res->getType() == "Shape")
		{
			mShapes.push_back(dynamic_cast<ShapeResource*>(res));
		}
	}
	//-----------------------------------------------------------------------
	Resource* File::getResource(const String& id)
	{
		ResourceMap::iterator it = mResources.find(id);

		if(it != mResources.end())
		{
			return it->second;
		}

		VTX_WARN("\"%s\": Unable to find the requested resource with name \"%s\"!", mFilename.c_str(), id.c_str());

		return NULL;
	}
	//-----------------------------------------------------------------------
	const File::ShapeResourceList& File::getShapeResourceList() const
	{
		return mShapes;
	}
	//-----------------------------------------------------------------------
}
