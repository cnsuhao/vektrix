/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

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
			//mAtlasPacker->addShape(dynamic_cast<ShapeResource*>(res));
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
