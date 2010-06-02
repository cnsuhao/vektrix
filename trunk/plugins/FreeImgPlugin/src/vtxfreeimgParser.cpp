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

#include "vtxfreeimgParser.h"

#include "vtxCreateObjectEvent.h"
#include "vtxFile.h"
#include "vtxFileStream.h"
#include "vtxImageResource.h"
#include "vtxKeyframe.h"
#include "vtxLogManager.h"
#include "vtxMaterialResource.h"
#include "vtxMovieClipResource.h"
#include "vtxShapeResource.h"
#include "vtxSubshapeResource.h"
#include "vtxTimeline.h"

#define FREEIMAGE_LIB
#include "FreeImage.h"

namespace vtx
{
	namespace freeimg
	{
		//-----------------------------------------------------------------------
		void FreeImageLoadErrorHandler(FREE_IMAGE_FORMAT fif, const char *message) 
		{
			// Callback method as required by FreeImage to report problems
			const char* typeName = FreeImage_GetFormatFromFIF(fif);
			if (typeName)
			{
				VTX_LOG("FreeImage error: '%s' while loading format %s", message, typeName);
			}
			else
			{
				VTX_LOG("FreeImage error: '%s'", message);
			}
		}
		//-----------------------------------------------------------------------
		ImageParser::ImageParser() 
		{
			FreeImage_Initialise(false);

			FreeImage_SetOutputMessage(FreeImageLoadErrorHandler);
		}
		//-----------------------------------------------------------------------
		ImageParser::~ImageParser()
		{
			FreeImage_DeInitialise();
		}
		//-----------------------------------------------------------------------
		const StringList& ImageParser::getExtensions() const
		{
			static StringList extensions;
			extensions.push_back(".gif");
			extensions.push_back(".jpg");
			extensions.push_back(".png");
			return extensions;
		}
		//-----------------------------------------------------------------------
		void ImageParser::parse(FileStream* stream, File* file)
		{
			mCurrentStream = stream;
			const String& filename = stream->getFilename();

			//File* file = new File(filename);

			const uint& stream_size = stream->size();

			BYTE* fileBuf = new BYTE[stream_size];
			stream->read(fileBuf, stream_size);
			
			FIMEMORY* fiMem = FreeImage_OpenMemory(fileBuf, static_cast<DWORD>(stream_size));
			
			FIBITMAP* fiBitmap = FreeImage_LoadFromMemory(FreeImage_GetFileTypeFromMemory(fiMem), fiMem);
			if (!fiBitmap)
			{
				VTX_EXCEPT("Error loading image with freetype");
			}

			FIBITMAP* fiRGBA = FreeImage_ConvertTo32Bits(fiBitmap);

			uint width = FreeImage_GetWidth(fiRGBA);
			uint height = FreeImage_GetHeight(fiRGBA);

			char* srcData = (char*)FreeImage_GetBits(fiRGBA);
			char* dstData = new char[width * height * 4];
			char* pixelBuf = dstData;

			uint srcPitch = FreeImage_GetPitch(fiRGBA);

			for(uint y = 0; y < height; ++y)
			{
				char* pSrc = srcData + (height - y - 1) * srcPitch;
				memcpy(dstData, pSrc, 4 * width);
				dstData += 4 * width;
			}
			
			// IMAGE
			ImageResource* image_res = new ImageResource(filename + "_Image");
			image_res->setImageData(width, height, pixelBuf);

			FreeImage_Unload(fiBitmap);
			FreeImage_Unload(fiRGBA);
			FreeImage_CloseMemory(fiMem);
			delete [] fileBuf;

			// MATERIAL
			MaterialResource* material_res = new MaterialResource(filename + "_Material", MaterialResource::MT_IMAGE);
			material_res->setImageID(image_res->getID());

			// SHAPE
			ShapeResource* shape_res = new ShapeResource(filename);

			BoundingBox box(Vector2::ZERO, Vector2((float)width, (float)height));
			shape_res->setBoundingBox(box);

			SubshapeResource* subshape = new SubshapeResource();
			subshape->setMaterial(material_res);

			// counter-clockwise default rect

			// TOP-LEFT
			subshape->addShapeElement(
				ShapeElement(ShapeElement::SID_MOVE_TO, 0.0f, 0.0f));

			// BOTTOM-LEFT
			subshape->addShapeElement(
				ShapeElement(ShapeElement::SID_LINE_TO, 0.0f, (float)height));

			// BOTTOM-RIGHT
			subshape->addShapeElement(
				ShapeElement(ShapeElement::SID_LINE_TO, (float)width, (float)height));

			// TOP-RIGHT
			subshape->addShapeElement(
				ShapeElement(ShapeElement::SID_LINE_TO, (float)width, 0.0f));

			// TOP-LEFT
			subshape->addShapeElement(
				ShapeElement(ShapeElement::SID_LINE_TO, 0.0f, 0.0f));

			shape_res->addSubshapeResource(subshape);

			// add resources
			file->addResource(image_res);
			file->addResource(material_res);
			file->addResource(shape_res);

			MovieClipResource* main_mc = new MovieClipResource("MainMovieClip");
			Timeline* timeline = new Timeline();
			Keyframe* keyframe = new Keyframe();

			keyframe->setIndex(0);
			keyframe->addEvent(new CreateObjectEvent(NULL, filename, 1, Matrix(), CXForm()));
			timeline->addKeyframe(keyframe);

			main_mc->setTimeline(timeline);
			file->setMainMovieClip(main_mc);

			File::FileHeader header;
			header.frames = 1;
			header.width = (uint)width;
			header.height = (uint)height;
			file->setHeader(header);

			mCurrentStream = NULL;
			//return file;
		}
		//-----------------------------------------------------------------------
	}
}
