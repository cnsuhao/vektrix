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

#include "vtxxmlShapeDataHandler.h"

#include "vtxFile.h"
#include "vtxLogManager.h"
#include "vtxMaterialResource.h"
#include "vtxShapeResource.h"
#include "vtxStringHelper.h"
#include "vtxSubshapeResource.h"

namespace vtx
{
	namespace xml
	{
		//-----------------------------------------------------------------------
		ShapeDataHandler::ShapeDataHandler() 
			: mAttributes(NULL), 
			mCurrentFile(NULL), 
			mShapeResource(NULL), 
			mSubShapeResource(NULL)
		{

		}
		//-----------------------------------------------------------------------
		void ShapeDataHandler::handle(const std::string& key, StringMap& atts, void* userdata)
		{
			FileShapePair* input_pair = static_cast<FileShapePair*>(userdata);
			mShapeResource = input_pair->shape;
			mCurrentFile = input_pair->file;
			mAttributes = &atts;

			if(key == "shape|bounding|")
				handleBounding();

			else if(key == "shape|subshape|")
				handleSubshape();

			else if(key == "shape|subshape|move|")
				handleSubshape_Move();

			else if(key == "shape|subshape|line|")
				handleSubshape_Line();

			else if(key == "shape|subshape|curve|")
				handleSubshape_Curve();

			//else if(key == "vektrix|resources|shape|")
			//	handleShape();
		}
		//-----------------------------------------------------------------------
		void ShapeDataHandler::end(const std::string& key)
		{

		}
		//-----------------------------------------------------------------------
		void ShapeDataHandler::handleBounding()
		{
			std::string maxx = (*mAttributes)["maxx"];
			std::string maxy = (*mAttributes)["maxy"];
			std::string minx = (*mAttributes)["minx"];
			std::string miny = (*mAttributes)["miny"];

			if(!maxx.length() || !maxy.length() || !minx.length() || !miny.length())
			{
				VTX_EXCEPT("Shape \"%s\": Missing parameter in bounding box argument!!!", mShapeResource->getID().c_str());
			}

			BoundingBox box(
				Vector2(
				StringHelper::toFloat(maxx), 
				StringHelper::toFloat(maxy)), 
				Vector2(
				StringHelper::toFloat(minx), 
				StringHelper::toFloat(miny))
				);

			mShapeResource->setBoundingBox(box);
		}
		//-----------------------------------------------------------------------
		void ShapeDataHandler::handleSubshape()
		{
			std::string material = (*mAttributes)["material"];

			if(!material.length())
			{
				VTX_EXCEPT("Subshape: Missing parameter \"material\"!!!");
			}

			MaterialResource* mat = dynamic_cast<MaterialResource*>(mCurrentFile->getResource(material));

			if(!mat)
			{
				VTX_EXCEPT("The requested Resource with the ID: %s is no MaterialResource.", material.c_str());
			}

			mSubShapeResource = new SubshapeResource();
			mSubShapeResource->setMaterial(mat);
			mShapeResource->addSubshapeResource(mSubShapeResource);
		}
		//-----------------------------------------------------------------------
		void ShapeDataHandler::handleSubshape_Move()
		{
			std::string xy = (*mAttributes)["xy"];

			if(!xy.length())
			{
				VTX_EXCEPT("Subshape->Move: Missing parameter \"xy\"!!!");
			}

			SubshapeResource::ShapeElement element;

			element.type = SubshapeResource::ShapeElement::SID_MOVE_TO;
			element.pos = StringHelper::toVector2(xy);

			mSubShapeResource->addShapeElement(element);
		}
		//-----------------------------------------------------------------------
		void ShapeDataHandler::handleSubshape_Line()
		{
			std::string xy = (*mAttributes)["xy"];

			if(!xy.length())
			{
				VTX_EXCEPT("Subshape->Line: Missing parameter \"xy\"!!!");
			}

			SubshapeResource::ShapeElement element;

			element.type = SubshapeResource::ShapeElement::SID_LINE_TO;
			element.pos = StringHelper::toVector2(xy);

			mSubShapeResource->addShapeElement(element);
		}
		//-----------------------------------------------------------------------
		void ShapeDataHandler::handleSubshape_Curve()
		{
			std::string xy = (*mAttributes)["xy"];

			if(!xy.length())
			{
				VTX_EXCEPT("Subshape->Curve: Missing parameter \"xy\"!!!");
			}

			std::string cp = (*mAttributes)["cp"];

			if(!cp.length())
			{
				VTX_EXCEPT("Subshape->Curve: Missing parameter \"cp\"!!!");
			}

			//std::string uv = (*mAttributes)["uv"];

			//if(!uv.length())
			//{
			//	VTX_EXCEPT("Subshape->Curve: Missing parameter \"uv\"!!!");
			//}


			SubshapeResource::ShapeElement element;

			element.type = SubshapeResource::ShapeElement::SID_CURVE_TO;
			element.pos = StringHelper::toVector2(xy);
			element.ctrl = StringHelper::toVector2(cp);

			mSubShapeResource->addShapeElement(element);
		}
		//-----------------------------------------------------------------------
	}
}
