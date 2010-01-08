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

			if(key == "vektrix|resources|button|")
				handleButton();

			else if(key == "vektrix|resources|button|state|")
				handleButtonState();

			else if(key == "vektrix|resources|button|state|event|")
				handleEvent();

			else if(key == "vektrix|resources|image|")
				handleImage();

			else if(key == "vektrix|resources|material|")
				handleMaterial();

			else if(key == "vektrix|resources|material|gradient_step|")
				handleMaterialGradientStep();

			else if(key == "vektrix|resources|shape|")
				handleShape();
		}
		//-----------------------------------------------------------------------
		void ResourcesDataHandler::end(const std::string& key)
		{
			if(key == "vektrix|resources|material|")
			{
				mCurrentFile->addResource(mMaterial);
				mMaterial = NULL;
			}

			else if(key =="vektrix|resources|button|")
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

			if(type == "up")
			{
				mButton->setState(static_cast<ButtonState*>(mContainer), ButtonResource::SID_UP);
			}
			else if(type == "over")
			{
				mButton->setState(static_cast<ButtonState*>(mContainer), ButtonResource::SID_OVER);
			}
			else if(type == "down")
			{
				mButton->setState(static_cast<ButtonState*>(mContainer), ButtonResource::SID_DOWN);
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
			else if(type == "linear_gradient")
			{
				mMaterial = new MaterialResource(id, MaterialResource::MT_LINEAR_GRADIENT);
				//mMaterial->setTransformMatrix(Matrix(
				//	1.0f/100.0f, 0.0f, 0.0f, 
				//	0.0f, 1.0f/100.0f, 0.0f));
			}
			else if(type == "radial_gradient")
			{
				mMaterial = new MaterialResource(id, MaterialResource::MT_RADIAL_GRADIENT);
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
		void ResourcesDataHandler::handleMaterialGradientStep()
		{
			std::string pos = (*mAttributes)["pos"];
			std::string rgba = (*mAttributes)["rgba"];

			if(!pos.length())
			{
				VTX_EXCEPT("\"%s\": Missing parameter \"pos\"", mCurrentFile->getFilename().c_str());
			}

			if(!rgba.length())
			{
				VTX_EXCEPT("\"%s\": Missing parameter \"rgba\"", mCurrentFile->getFilename().c_str());
			}

			uchar ratio = StringHelper::toUint(pos);
			Color color = StringHelper::toColor(rgba);

			mMaterial->setGradientColor(ratio, color);
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

			FileStream* stream = FileManager::getSingletonPtr()->getFileStream(file);

			if(!stream)
			{
				VTX_EXCEPT("Unable to open Shape Definition File: '%s'.", file.c_str());
			}

			ShapeResource* shape = new ShapeResource(id);

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
			delete stream;

			mCurrentFile->addResource(shape);
		}
		//-----------------------------------------------------------------------
	}
}
