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

#include "vtxswfImageParser.h"
#include "vtxswfParser.h"
#include "vtxImageResource.h"
#include "vtxLogManager.h"
#include "vtxFile.h"
#include "vtxImageResource.h"
#include "vtxMaterialResource.h"
#include "vtxShapeResource.h"
#include "vtxSubshapeResource.h"

#define FREEIMAGE_LIB
#include "freeimage/FreeImage.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		void FreeImageLoadErrorHandler(FREE_IMAGE_FORMAT fif, const char *message) 
		{
			// Callback method as required by FreeImage to report problems
			const char* typeName = FreeImage_GetFormatFromFIF(fif);
			if (typeName)
			{
				VTX_WARN("FreeImage error: '%s' while loading format %s", message, typeName);
			}
			else
			{
				VTX_WARN("FreeImage error: '%s'", message);
			}
		}
		//-----------------------------------------------------------------------
		ImageParser::ImageParser() 
			: mJPEGTables(NULL)
			, mJPEGTableLen(0)
		{
			FreeImage_Initialise(false);
			FreeImage_SetOutputMessage(FreeImageLoadErrorHandler);
		}
		//-----------------------------------------------------------------------
		ImageParser::~ImageParser()
		{
			if(mJPEGTables)
			{
				delete[] mJPEGTables;
				mJPEGTables = NULL;
			}
			FreeImage_DeInitialise();
		}
		//-----------------------------------------------------------------------
		void ImageParser::handleDefineBitsLossless(const TagTypes& tag_type, MemoryBlockReader& tag_reader, SwfParser* parser)
		{
			// read tag data
			int character_id = tag_reader.readUI16();
			BitmapFormat format = (BitmapFormat)tag_reader.readUI8();
			int width = tag_reader.readUI16();
			int height = tag_reader.readUI16();

			// read color table data
			short colorTableSize = 0;
			if (format == BF_8BIT_COLOR_MAPPED)
			{
				colorTableSize = (short) (tag_reader.readUI8() + 1);
			}

			// calculate length of compressed data
			int zLength = (int) tag_reader.available();

			// copy the compressed bytes into a new buffer
			unsigned char* zBuf = (uchar*)alloca(zLength);
			tag_reader.readBytes(zLength, zBuf);

			// create a memory block reader and decompress data
			MemoryBlockReader zBlock;
			zBlock.init(zBuf, zLength);
			zBlock.enableCompression();

			uchar* pixel_data = NULL;
			switch(tag_type)
			{
			case TT_DefineBitsLossless:
				{
					switch (format)
					{
					case BF_8BIT_COLOR_MAPPED:
						pixel_data = readColorMapData(zBlock, colorTableSize, width, height);
						break;
					case BF_15BIT_RGB:
					case BF_24BIT_RGB:
						pixel_data = readBitmapData(zBlock, format, width, height);
						break;
					default:
						VTX_DEBUG_FAIL("Unknown bitmap format");
					}
				}
				break;
			case TT_DefineBitsLossless2:
				{
					switch (format)
					{
					case BF_8BIT_COLOR_MAPPED:
						pixel_data = readAlphaColorMapData(zBlock, colorTableSize, width, height);
						break;
					case BF_32BIT_ARGB:
						pixel_data = readAlphaBitmapData(zBlock, width, height);
						break;
					default:
						VTX_DEBUG_FAIL("Unknown bitmap format");
					}
				}
				break;
			default:
				VTX_DEBUG_FAIL("Unknown tag type");
			}

			if(pixel_data)
				finish(parser->getCurrentFile(), pixel_data, width, height, character_id);
		}
		//-----------------------------------------------------------------------
		void ImageParser::handleJPEGTables(const TagTypes& tag_type, MemoryBlockReader& tag_reader, SwfParser* parser)
		{
			mJPEGTableLen = tag_reader.available();
			mJPEGTables = new uchar[mJPEGTableLen];
			tag_reader.readBytes(mJPEGTableLen, mJPEGTables);
		}
		//-----------------------------------------------------------------------
		void ImageParser::handleDefineBitsJPEG(const TagTypes& tag_type, MemoryBlockReader& tag_reader, SwfParser* parser)
		{
			int width, height;
			int character_id = tag_reader.readUI16();
			uchar* pixel_data = NULL;
			switch(tag_type)
			{
			case TT_DefineBits:
				pixel_data = readDefineBitsJPEG(tag_reader, width, height);
				break;
			case TT_DefineBitsJPEG2:
				pixel_data = readDefineBitsJPEG2(tag_reader, width, height);
				break;
			case TT_DefineBitsJPEG3:
				pixel_data = readDefineBitsJPEG3(tag_reader, width, height);
				break;
			case TT_DefineBitsJPEG4:
				pixel_data = readDefineBitsJPEG4(tag_reader, width, height);
				break;
			default:
				VTX_DEBUG_FAIL("Unknown tag type encountered");
			}

			if(pixel_data)
				finish(parser->getCurrentFile(), pixel_data, width, height, character_id);
		}
		//-----------------------------------------------------------------------
		uchar* ImageParser::readDefineBitsJPEG(MemoryBlockReader& tag_reader, int& width, int& height)
		{
			size_t tag_length = tag_reader.available();

			uchar* jpeg_data = readJpegData(tag_reader, tag_length);
			uchar* pixel_data = decodeJPEGData(jpeg_data, tag_length, width, height, mJPEGTables, mJPEGTableLen);

			delete[] jpeg_data;
			return pixel_data;
		}
		//-----------------------------------------------------------------------
		uchar* ImageParser::readDefineBitsJPEG2(MemoryBlockReader& tag_reader, int& width, int& height)
		{
			size_t tag_length = tag_reader.available();

			uchar* jpeg_data = readJpegData(tag_reader, tag_length);
			uchar* pixel_data = decodeJPEGData(jpeg_data, tag_length, width, height);

			delete[] jpeg_data;
			return pixel_data;
		}
		//-----------------------------------------------------------------------
		uchar* ImageParser::readDefineBitsJPEG3(MemoryBlockReader& tag_reader, int& width, int& height)
		{
			int alphaDataOffset = (int)tag_reader.readUI32();

			uchar* jpeg_data = readJpegData(tag_reader, alphaDataOffset);
			uchar* pixel_data = decodeJPEGData(jpeg_data, alphaDataOffset, width, height);

			int alphaDataSize = tag_reader.available();
			uchar* alpha_data = readBitmapAlphaData(tag_reader, alphaDataSize);

			for(int y = 0; y < height; ++y)
			{
				for(int x = 0; x < width; ++x)
				{
					pixel_data[(y*width)+(x*4)] = alpha_data[(y*width)+x];
				}
			}

			delete[] jpeg_data;
			delete[] alpha_data;
			return pixel_data;
		}
		//-----------------------------------------------------------------------
		uchar* ImageParser::readDefineBitsJPEG4(MemoryBlockReader& tag_reader, int& width, int& height)
		{
			int alphaDataOffset = (int)tag_reader.readUI32();
			int deblockParam = (int)tag_reader.readUI16();

			uchar* jpeg_data = readJpegData(tag_reader, alphaDataOffset);
			uchar* pixel_data = decodeJPEGData(jpeg_data, alphaDataOffset, width, height);

			int alphaDataSize = tag_reader.available();
			uchar* alpha_data = readBitmapAlphaData(tag_reader, alphaDataSize);

			for(int y = 0; y < height; ++y)
			{
				for(int x = 0; x < width; ++x)
				{
					pixel_data[(y*width)+(x*4)] = alpha_data[(y*width)+x];
				}
			}

			delete[] jpeg_data;
			delete[] alpha_data;
			return pixel_data;
		}
		//-----------------------------------------------------------------------
		uchar* ImageParser::readJpegData(MemoryBlockReader& tag_reader, size_t len)
		{
			uchar* jpeg_data = new uchar[len];
			tag_reader.readBytes(len, jpeg_data);
			return jpeg_data;
		}
		//-----------------------------------------------------------------------
		uchar* ImageParser::readBitmapAlphaData(MemoryBlockReader& tag_reader, size_t len)
		{
			uchar* alpha_data = new uchar[len];
			tag_reader.readBytes(len, alpha_data);
			return alpha_data;
		}
		//-----------------------------------------------------------------------
		uchar* ImageParser::decodeJPEGData(uchar* jpeg_data, size_t data_len, int& width, int& height, uchar* table_data /*= NULL*/, size_t table_len /*= 0*/)
		{
			uchar* jpegData = jpeg_data;
			size_t dataLen = data_len;
			if(table_data)
			{
				dataLen = table_len+data_len;
				jpegData = (uchar*)alloca(dataLen);
				memcpy(jpegData, table_data, table_len);
				memcpy(jpegData+table_len, jpeg_data, data_len);
			}

			FIMEMORY* fiMem = FreeImage_OpenMemory(jpegData, static_cast<DWORD>(dataLen));
			FIBITMAP* fiBitmap = FreeImage_LoadFromMemory(FreeImage_GetFileTypeFromMemory(fiMem, dataLen), fiMem);
			if (!fiBitmap)
			{
				VTX_DEBUG_FAIL("Error loading image with freetype");
			}

			FIBITMAP* fiRGBA = FreeImage_ConvertTo32Bits(fiBitmap);
			width = FreeImage_GetWidth(fiRGBA);
			height = FreeImage_GetHeight(fiRGBA);

			uchar* srcData = FreeImage_GetBits(fiRGBA);
			uchar* dstData = new uchar[width * height * 4];
			uchar* pixel_data = dstData;

			uint srcPitch = FreeImage_GetPitch(fiRGBA);
			for(int y = 0; y < height; ++y)
			{
				uchar* pSrc = srcData + (height - y - 1) * srcPitch;
				memcpy(dstData, pSrc, 4 * width);
				dstData += 4 * width;
			}

			FreeImage_Unload(fiBitmap);
			FreeImage_Unload(fiRGBA);
			FreeImage_CloseMemory(fiMem);

			return pixel_data;
		}
		//-----------------------------------------------------------------------
		uchar* ImageParser::readAlphaColorMapData(MemoryBlockReader& tag_reader, size_t colorTableSize, int width, int height)
		{
			uchar* mColorTableRGBA = (uchar*)alloca(colorTableSize*4);
			tag_reader.readBytes(colorTableSize*4, mColorTableRGBA);

			int imageDataSize = (width + getScanlinePadLength(width)) * height;

			uchar* mColorMapPixelData = (uchar*)alloca(imageDataSize);
			tag_reader.readBytes(imageDataSize, mColorMapPixelData);

			uchar* pixel_data = new uchar[width*height*4];
			for(int y = 0; y < height; ++y)
			{
				for(int x = 0; x < width; ++x)
				{
					pixel_data[(y*width)+(x*4)+0] = mColorTableRGBA[(mColorMapPixelData[(y*width)+x]*4)+0];
					pixel_data[(y*width)+(x*4)+1] = mColorTableRGBA[(mColorMapPixelData[(y*width)+x]*4)+1];
					pixel_data[(y*width)+(x*4)+2] = mColorTableRGBA[(mColorMapPixelData[(y*width)+x]*4)+2];
					pixel_data[(y*width)+(x*4)+3] = mColorTableRGBA[(mColorMapPixelData[(y*width)+x]*4)+3];
				}
			}
			return pixel_data;
		}
		//-----------------------------------------------------------------------
		uchar* ImageParser::readColorMapData(MemoryBlockReader& tag_reader, size_t colorTableSize, int width, int height)
		{
			uchar* mColorTableRGB = (uchar*)alloca(colorTableSize*3);
			tag_reader.readBytes(colorTableSize*3, mColorTableRGB);

			int imageDataSize = (width + getScanlinePadLength(width)) * height;

			uchar* mColorMapPixelData = (uchar*)alloca(imageDataSize);
			tag_reader.readBytes(imageDataSize, mColorMapPixelData);

			uchar* pixel_data = new uchar[width*height*4];
			for(int y = 0; y < height; ++y)
			{
				for(int x = 0; x < width; ++x)
				{
					pixel_data[(y*width)+(x*4)+0] = 255;
					pixel_data[(y*width)+(x*4)+1] = mColorTableRGB[(mColorMapPixelData[(y*width)+x]*3)+0];
					pixel_data[(y*width)+(x*4)+2] = mColorTableRGB[(mColorMapPixelData[(y*width)+x]*3)+1];
					pixel_data[(y*width)+(x*4)+3] = mColorTableRGB[(mColorMapPixelData[(y*width)+x]*3)+2];
				}
			}
			return pixel_data;
		}
		//-----------------------------------------------------------------------
		uchar* ImageParser::readAlphaBitmapData(MemoryBlockReader& tag_reader, int width, int height)
		{
			int imageDataSize = width * height;
			uchar* pixel_data = new uchar[imageDataSize*4];
			tag_reader.readBytes(imageDataSize*4, pixel_data);

			// swizzle RGBA format to ARGB
			for(int y = 0; y < height; ++y)
			{
				for(int x = 0; x < width; ++x)
				{
					uchar temp = pixel_data[(y*width)+(x*4)+0];
					pixel_data[(y*width)+(x*4)+0] = pixel_data[(y*width)+(x*4)+3];
					pixel_data[(y*width)+(x*4)+3] = temp;
				}
			}
			return pixel_data;
		}
		//-----------------------------------------------------------------------
		uchar* ImageParser::readBitmapData(MemoryBlockReader& tag_reader, BitmapFormat format, int width, int height)
		{
			int imageDataSize = 0;
			uchar* pixel_data = NULL;
			switch (format)
			{
			case BF_15BIT_RGB:
				imageDataSize = (width + getScanlinePadLength2(width)) * height;
				pixel_data = readPix15BitmapData(tag_reader, imageDataSize, width, height);
				break;
			case BF_24BIT_RGB:
				imageDataSize = width * height;
				pixel_data = readPix24BitmapData(tag_reader, imageDataSize, width, height);
				break;
			}
			return pixel_data;
		}
		//-----------------------------------------------------------------------
		uchar* ImageParser::readPix15BitmapData(MemoryBlockReader& tag_reader, int data_size, int width, int height)
		{
			uchar* pixel_data = new uchar[data_size*4];
			for(int i = 0; i < data_size; ++i)
			{
				pixel_data[i*4+0] = 255;
				pixel_data[i*4+1] = (uchar)tag_reader.readUnsignedBits(5);
				pixel_data[i*4+2] = (uchar)tag_reader.readUnsignedBits(5);
				pixel_data[i*4+3] = (uchar)tag_reader.readUnsignedBits(5);
			}
			return pixel_data;
		}
		//-----------------------------------------------------------------------
		uchar* ImageParser::readPix24BitmapData(MemoryBlockReader& tag_reader, int data_size, int width, int height)
		{
			uchar* mBitmapPixelData = (uchar*)alloca(data_size*3);
			tag_reader.readBytes(data_size*3, mBitmapPixelData);

			uchar* pixel_data = new uchar[width*height*4];
			for(int y = 0; y < height; ++y)
			{
				for(int x = 0; x < width; ++x)
				{
					pixel_data[(y*width)+(x*4)+0] = 255;
					pixel_data[(y*width)+(x*4)+1] = mBitmapPixelData[((y*width)+x*3)+0];
					pixel_data[(y*width)+(x*4)+2] = mBitmapPixelData[((y*width)+x*3)+1];
					pixel_data[(y*width)+(x*4)+3] = mBitmapPixelData[((y*width)+x*3)+2];
				}
			}
			return pixel_data;
		}
		//-----------------------------------------------------------------------
		int ImageParser::getScanlinePadLength(int width)
		{
			int pad = 0;
			if ((width & 3) != 0)
				pad = 4 - (width & 3);
			return pad;
		}
		//-----------------------------------------------------------------------
		int ImageParser::getScanlinePadLength2(int width)
		{
			return (width & 1);
		}
		//-----------------------------------------------------------------------
		void ImageParser::finish(File* file, uchar* bitmap_data, int width, int height, int character_id)
		{
			char strResourceId[16];
			sprintf((char*)&strResourceId, "%d", character_id);
			String resourceId = String((char*)&strResourceId);

			// IMAGE
			ImageResource* image_res = new ImageResource(resourceId + "_Image");
			image_res->setImageData(width, height, (char*)bitmap_data);

			// MATERIAL
			MaterialResource* material_res = new MaterialResource(resourceId + "_Material", MaterialResource::MT_IMAGE);
			material_res->setImageID(image_res->getID());

			// SHAPE
			ShapeResource* shape_res = new ShapeResource(resourceId + "_Shape");

			BoundingBox box(Vector2::ZERO, Vector2((float)width, (float)height));
			shape_res->setBoundingBox(box);

			SubshapeResource* subshape = new SubshapeResource();
			subshape->setMaterial(material_res);

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
		}
		//-----------------------------------------------------------------------
	}
}
