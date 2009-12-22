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
#include "vtxMaterialResource.h"

#include "vtxLogManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	MaterialResource::MaterialResource(const String& id, const MaterialType& type) 
		: Resource(id), 
		mType(type), 
		mImageID(""), 
		mRGBA(0,0,0,1)
	{

	}
	//-----------------------------------------------------------------------
	MaterialResource::~MaterialResource()
	{

	}
	//-----------------------------------------------------------------------
	const String& MaterialResource::getType() const
	{
		static String type = "Material";
		return type;
	}
	//-----------------------------------------------------------------------
	const MaterialResource::MaterialType& MaterialResource::getMaterialType()
	{
		return mType;
	}
	//-----------------------------------------------------------------------
	void MaterialResource::setColor(const Color& rgba)
	{
		if(mType != MT_COLOR)
		{
			VTX_WARN("MaterialResource::setColor was called on a wrong material type!");
		}

		mRGBA = rgba;
	}
	//-----------------------------------------------------------------------
	const Color& MaterialResource::getColor() const
	{
		if(mType != MT_COLOR)
		{
			VTX_WARN("MaterialResource::getColor was called on a wrong material type!");
		}

		return mRGBA;
	}
	//-----------------------------------------------------------------------
	void MaterialResource::setImageID(const String& image_id)
	{
		if(mType != MT_IMAGE)
		{
			VTX_WARN("MaterialResource::setImageID was called on a wrong material type!");
		}

		mImageID = image_id;
	}
	//-----------------------------------------------------------------------
	const String& MaterialResource::getImageID() const
	{
		if(mType != MT_IMAGE)
		{
			VTX_WARN("MaterialResource::getImageID was called on a wrong material type!");
		}

		return mImageID;
	}
	//-----------------------------------------------------------------------
}
