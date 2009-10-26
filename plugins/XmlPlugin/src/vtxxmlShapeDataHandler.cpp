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

			//else if(key == "vectrix|resources|shape|")
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
				VTX_EXCEPT("Subshape->Move: Missing parameter \"pos\"!!!");
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

			std::string uv = (*mAttributes)["uv"];

			if(!uv.length())
			{
				VTX_EXCEPT("Subshape->Line: Missing parameter \"uv\"!!!");
			}

			SubshapeResource::ShapeElement element;

			element.type = SubshapeResource::ShapeElement::SID_LINE_TO;
			element.pos = StringHelper::toVector2(xy);
			element.texcoord = StringHelper::toVector2(uv);

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
