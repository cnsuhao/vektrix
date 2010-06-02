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

#include "vtxMaterialResource.h"

#include "vtxLogManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	MaterialResource::MaterialResource(const String& id, const MaterialType& type) 
		: Resource(id), 
		mType(type), 
		mRGBA(0,0,0,1), 
		mImageID("")
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
	void MaterialResource::setTransformMatrix(const Matrix& matrix)
	{
		mTransformMatrix = matrix;
	}
	//-----------------------------------------------------------------------
	const Matrix& MaterialResource::getTransformMatrix() const
	{
		return mTransformMatrix;
	}
	//-----------------------------------------------------------------------
	void MaterialResource::setGradientColor(const uchar& ratio, const Color& color)
	{
		if(mType != MT_LINEAR_GRADIENT && mType != MT_RADIAL_GRADIENT)
		{
			VTX_WARN("MaterialResource::setGradientColor was called on a wrong material type!");
		}

		mGradientMap[ratio] = color;
	}
	//-----------------------------------------------------------------------
	MaterialResource::GradientMap& MaterialResource::getGradientMap()
	{
		if(mType != MT_LINEAR_GRADIENT && mType != MT_RADIAL_GRADIENT)
		{
			VTX_WARN("MaterialResource::getGradientMap was called on a wrong material type!");
		}

		return mGradientMap;
	}
	//-----------------------------------------------------------------------
}
