/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/vektrix

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
#include "vtxResource.h"
#include "vtxShapeResource.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	File::File(const String& filename) 
		: mFilename(filename)
	{

	}
	//-----------------------------------------------------------------------
	File::~File()
	{

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
	void File::setTimeline(Timeline timeline)
	{
		mTimeline = timeline;
	}
	//-----------------------------------------------------------------------
	Timeline& File::getTimeline()
	{
		return mTimeline;
	}
	//-----------------------------------------------------------------------
	// TODO: remove
	//void File::setAtlasSize(uint size)
	//{
	//	if(mAtlasPacker->getSize() < size)
	//	{
	//		mAtlasPacker->setSize(size);
	//	}
	//}
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

		VTX_EXCEPT("\"%s\": Unable to find the requested resource with name \"%s\"!", mFilename.c_str(), id.c_str());

		return NULL;
	}
	//-----------------------------------------------------------------------
	const File::ShapeResourceList& File::getShapeResourceList() const
	{
		return mShapes;
	}
	//-----------------------------------------------------------------------
	void File::startedLoading()
	{

	}
	//-----------------------------------------------------------------------
	void File::finishedLoading()
	{
		//mAtlasPacker->packAtlas();
		//mAtlasPacker->renderAtlas();
	}
	//-----------------------------------------------------------------------
}
