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
#include "vtxxmlResourcesDataHandler.h"

#include "vtxButtonResource.h"
#include "vtxButtonState.h"
#include "vtxFile.h"
#include "vtxFileManager.h"
#include "vtxFileStream.h"
#include "vtxImageResource.h"
#include "vtxLogManager.h"
#include "vtxMaterialResource.h"
#include "vtxShapeResource.h"
#include "vtxStringHelper.h"

#include "vtxxmlParser.h"
#include "vtxxmlShapeDataHandler.h"

namespace vtx
{
	namespace xml
	{
		//-----------------------------------------------------------------------
		void ResourcesDataHandler::handle(const std::string& key, StringMap& atts, void* userdata)
		{
			mCurrentFile = static_cast<File*>(userdata);
			mAttributes = &atts;

			if(key == "vectrix|resources|button|")
				handleButton();

			else if(key == "vectrix|resources|button|state|")
				handleButtonState();

			else if(key == "vectrix|resources|button|state|event|")
				handleEvent();

			else if(key == "vectrix|resources|image|")
				handleImage();

			else if(key == "vectrix|resources|material|")
				handleMaterial();

			else if(key == "vectrix|resources|shape|")
				handleShape();
		}
		//-----------------------------------------------------------------------
		void ResourcesDataHandler::end(const std::string& key)
		{
			if(key == "vectrix|resources|material|")
			{
				mCurrentFile->addResource(mMaterial);
				mMaterial = NULL;
			}

			else if(key =="vectrix|resources|button|")
			{
				mCurrentFile->addResource(mButton);
				mButton = NULL;
				mContainer = NULL;
			}
		}
		//-----------------------------------------------------------------------
		void ResourcesDataHandler::handleButton()
		{
			std::string id = (*mAttributes)["id"];

			if(!id.length())
			{
				VTX_EXCEPT("\"%s\": Missing parameter \"id\" in button tag!", mCurrentFile->getFilename().c_str());
			}

			mButton = new ButtonResource(id);
		}
		//-----------------------------------------------------------------------
		void ResourcesDataHandler::handleButtonState()
		{
			std::string type = (*mAttributes)["type"];

			if(!type.length())
			{
				VTX_EXCEPT("\"%s\": Missing parameter \"type\" in button state tag!", mCurrentFile->getFilename().c_str());
			}

			mContainer = new ButtonState;

			if(type == "default")
			{
				mButton->setState(static_cast<ButtonState*>(mContainer), ButtonResource::SID_DEFAULT);
			}
			else if(type == "over")
			{
				mButton->setState(static_cast<ButtonState*>(mContainer), ButtonResource::SID_OVER);
			}
			else if(type == "pressed")
			{
				mButton->setState(static_cast<ButtonState*>(mContainer), ButtonResource::SID_PRESSED);
			}
		}
		//-----------------------------------------------------------------------
		void ResourcesDataHandler::handleImage()
		{
			std::string type = (*mAttributes)["type"];
			std::string id = (*mAttributes)["id"];
			std::string file = (*mAttributes)["file"];

			if(!type.length())
			{
				VTX_EXCEPT("\"%s\": Missing parameter \"type\" in <image id=\"%s\" file=\"%s\"/>!", mCurrentFile->getFilename().c_str(), id.c_str(), file.c_str());
			}

			if(!id.length())
			{
				VTX_EXCEPT("\"%s\": Missing parameter \"id\" in <image type=\"%s\" file=\"%s\"/>!", mCurrentFile->getFilename().c_str(), type.c_str(), file.c_str());
			}

			if(!file.length())
			{
				VTX_EXCEPT("\"%s\": Missing parameter \"file\" in <image type=\"%s\" id=\"%s\"/>!", mCurrentFile->getFilename().c_str(), type.c_str(), id.c_str());
			}

			mCurrentFile->addResource(new ImageResource(id, type, file));
		}
		//-----------------------------------------------------------------------
		void ResourcesDataHandler::handleMaterial()
		{
			std::string type = (*mAttributes)["type"];
			std::string id = (*mAttributes)["id"];

			if(!type.length())
			{
				VTX_EXCEPT("\"%s\": Missing parameter \"type\" in <material id=\"%s\"/>!", mCurrentFile->getFilename().c_str(), id.c_str());
			}

			if(!id.length())
			{
				VTX_EXCEPT("\"%s\": Missing parameter \"id\" in <material type=\"%s\"/>!", mCurrentFile->getFilename().c_str(), type.c_str());
			}

			if(type == "color")
			{
				std::string rgba = (*mAttributes)["rgba"];

				if(!rgba.length())
				{
					VTX_EXCEPT("\"%s\": Missing parameter \"rgba\" in <material id=\"%s\"/>!", mCurrentFile->getFilename().c_str(), id.c_str());
				}

				Color color = StringHelper::toColor(rgba);

				mMaterial = new MaterialResource(id, MaterialResource::MT_COLOR);
				mMaterial->setColor(color);
			}
			else if(type == "gradient")
			{
				mMaterial = new MaterialResource(id, MaterialResource::MT_GRADIENT);
			}
			else if(type == "image")
			{
				std::string image_id = (*mAttributes)["image_id"];

				if(!image_id.length())
				{
					VTX_EXCEPT("\"%s\": Missing parameter \"image_id\" in <material id=\"%s\"/>!", mCurrentFile->getFilename().c_str(), id.c_str());
				}

				mMaterial = new MaterialResource(id, MaterialResource::MT_IMAGE);
				mMaterial->setImageID(image_id);
			}
			else
			{
				VTX_EXCEPT("\"%s\":Unknown material type: \"%s\" found!", mCurrentFile->getFilename().c_str(), type.c_str());
			}
		}
		//-----------------------------------------------------------------------
		void ResourcesDataHandler::handleShape()
		{
			std::string id = (*mAttributes)["id"];
			std::string file = (*mAttributes)["file"];

			if(!id.length())
			{
				VTX_EXCEPT("\"%s\": Missing parameter \"id\" in <shape file=\"%s\"/>!", mCurrentFile->getFilename().c_str(), file.c_str());
			}

			if(!file.length())
			{
				VTX_EXCEPT("\"%s\": Missing parameter \"file\" in <shape id=\"%s\"/>!", mCurrentFile->getFilename().c_str(), id.c_str());
			}

			// TODO: integrate this into the XML plugin
			FileStream* stream = FileManager::getSingletonPtr()->getFileStream(file);

			if(!stream)
			{
				VTX_EXCEPT("Unable to open Shape Definition File: '%s'.", file.c_str());
			}

			ShapeResource* shape = new ShapeResource(id, file);

			ShapeDataHandler::FileShapePair parser_input;
			parser_input.file = mCurrentFile;
			parser_input.shape = shape;

			XMLParser shape_parser(&parser_input);

			std::string shpDH[] = 
			{
				"shape|bounding|", 
				"shape|subshape|", 
				"shape|subshape|move|", 
				"shape|subshape|line|", 
				"shape|subshape|curve|", 
				"shape|subline|line|", 
				"shape|subline|curve|"
			};
			shape_parser.addDataHandler(shpDH, size_of(shpDH), new ShapeDataHandler);

			shape_parser.parse(stream);

			stream->close();

			mCurrentFile->addResource(shape);
		}
		//-----------------------------------------------------------------------
	}
}
