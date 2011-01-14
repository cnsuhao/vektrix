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
#include "vtxStringHelper.h"

#ifdef USE_ZLIB
#include "zlib.h"
#endif

#define FREEIMAGE_LIB
#include "FreeImage.h"

namespace vtx { namespace swf {
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
		: mJPEGTables(NULL)
	{
		FreeImage_Initialise(false);

		FreeImage_SetOutputMessage(FreeImageLoadErrorHandler);
	}
	//-----------------------------------------------------------------------
	ImageParser::~ImageParser()
	{
		// jpeg tables
		if(mJPEGTables)
		{
			delete[] mJPEGTables;
			mJPEGTables = NULL;
		}

		FreeImage_DeInitialise();
	}
	//-----------------------------------------------------------------------
	void ImageParser::handleDefineBitsLossless(const TagTypes& tag_type, const uint& tag_length, SwfParser* parser)
	{
		uint start_read_pos = parser->getReadPosition();
		UI16 characterId = parser->readU16();
		UI8 bitmap_format = parser->readU8();
		UI16 width = parser->readU16();
		UI16 height = parser->readU16();

		UI8 color_table_size = 0;
		if(bitmap_format == BF_8BIT_COLOR_MAPPED)
			color_table_size = parser->readU8(); 

		uint end_read_pos = parser->getReadPosition();

		UI32 zlib_data_size = tag_length - (end_read_pos - start_read_pos);
		UI8* zlib_bitmap_data = (UI8*)parser->getReadData();
		parser->skip(zlib_data_size);

		uint bitmap_data_size = calculateBitmapDataSize(tag_type, bitmap_format, width, height, color_table_size);
		UI8* bitmap_data = new UI8[bitmap_data_size];

		int ret_value = uncompress((uchar*)bitmap_data, (ulong*)&bitmap_data_size, (uchar*)zlib_bitmap_data, zlib_data_size);
		checkZlibError(ret_value);

		DataReader bitmap_data_reader;
		bitmap_data_reader.init((char*)bitmap_data);

		ImageResource* image_res = NULL;

		if(bitmap_format == BF_8BIT_COLOR_MAPPED)
		{
			RGBA* color_table_data = new RGBA[(color_table_size+1)];	

			if(tag_type == TT_DefineBitsLossless2)
				bitmap_data_reader.readByteBlock((char*)color_table_data, (color_table_size + 1) * sizeof(RGBA));
			else
				for(UI8 i=0; i<color_table_size; ++i)
					color_table_data[i] = bitmap_data_reader.readRGBA();

			BitmapData data;
			data.width = width;
			data.height = height;
			data.bpp = 8;
			data.bitmap_data_size = bitmap_data_size;
			data.color_table_size = color_table_size;
			data.color_table = color_table_data;
			data.bitmap_data = (uchar*)bitmap_data_reader.getReadData();
			image_res = createImageFromBitmapData(characterId, bitmap_data, bitmap_data_size, data);

			delete[] color_table_data;
			
		}
		else if(bitmap_format == BF_15BIT_RGB) 
		{
			VTX_WARN("15bpp bitmap not fully implemented.");
			uint image_size = width * height;
			char* pixel_data = new char[image_size * 4];
			
			for(uint i=0; i<image_size; ++i)
			{
				UI16 color = bitmap_data_reader.readU16();
			}

			image_res = new ImageResource(StringHelper::toString(characterId));
			image_res->setImageData(width, height, pixel_data);
		}
		else if(bitmap_format == BF_24BIT_RGB)
		{
			BitmapData data;
			data.width = width;
			data.height = height;
			data.bpp = 24;

			if(tag_type == TT_DefineBitsLossless2)
				data.has_alpha_data = true;

			data.bitmap_data_size = bitmap_data_size;
			data.color_table_size = 0;
			data.color_table = 0;

			data.bitmap_data = (uchar*)bitmap_data_reader.getReadData();

			image_res = createImageFromBitmapData(characterId, bitmap_data, bitmap_data_size, data);
		}
		else if(bitmap_format == BF_32BIT_ARGB)
		{
			BitmapData data;
			data.width = width;
			data.height = height;
			data.bpp = 32;
			data.bitmap_data_size = bitmap_data_size;
			data.color_table_size = 0;
			data.color_table = 0;
			data.bitmap_data = (uchar*)bitmap_data_reader.getReadData();

			image_res = createImageFromBitmapData(characterId, bitmap_data, bitmap_data_size, data);
		}

		if(image_res)
			parser->getCurrentFile()->addResource(image_res);

		delete[] bitmap_data;
	}
	//-----------------------------------------------------------------------
	void ImageParser::handleJPEGTables(const TagTypes& tag_type, const uint& tag_length, SwfParser* parser)
	{
		char* pBuf = new char[tag_length];
		parser->readByteBlock(pBuf, tag_length);
		mJPEGTables = pBuf;
	}
	//-----------------------------------------------------------------------
	void ImageParser::handleDefineBitsJPEG(const TagTypes& tag_type, const uint& tag_length, SwfParser* parser)
	{
		uint start_read_pos = parser->getReadPosition();
		UI16 character_id = parser->readU16();

		ImageResource* image_res = NULL;

		switch(tag_type)
		{
		case TT_DefineBits:
			{
				uint img_data_size = tag_length - sizeof(UI16);
				image_res = createImageFromJPEG(character_id, parser->getReadData(), img_data_size);
				parser->skip(img_data_size);
			}
			break;

		case TT_DefineBitsJPEG2:
			{
				uint img_data_size = tag_length - sizeof(UI16);
				image_res = createImageFromJPEG(character_id, parser->getReadData(), img_data_size);
				parser->skip(img_data_size);
			}
			break;

		case TT_DefineBitsJPEG3:
			{
				UI32 alpha_offset = parser->readU32();
				image_res = createImageFromJPEG(character_id, parser->getReadData(), alpha_offset);
				parser->skip(alpha_offset);

				uint alpha_size = image_res->getWidth() * image_res->getHeight();
				uint zlib_alpha_size = tag_length - alpha_offset - sizeof(UI16) - sizeof(UI32);
				readAlphaData(parser, zlib_alpha_size, alpha_size, image_res);
			}
			break;

		case TT_DefineBitsJPEG4:
			{
				UI32 alpha_offset = parser->readU32();
				UI16 deblock_param = parser->readU16();
				image_res = createImageFromJPEG(character_id, parser->getReadData(), alpha_offset);
				parser->skip(alpha_offset);

				uint alpha_size = image_res->getWidth()*image_res->getHeight();
				uint zlib_alpha_size = tag_length - alpha_offset - (sizeof(UI16)*2) - sizeof(UI32);
				readAlphaData(parser, zlib_alpha_size, alpha_size, image_res);
			}
			break;
		default:
			{
				VTX_WARN("Image type not implemented: %d", tag_type);
				parser->skip(tag_length - sizeof(UI16));
			}
		};

		if(image_res)
		{
			parser->getCurrentFile()->addResource(image_res);
		}
	}
	//-----------------------------------------------------------------------
	ImageResource* ImageParser::createImageFromJPEG(ushort id, void* fileBuf, uint size)
	{
		FIMEMORY* fiMem = FreeImage_OpenMemory((uchar*)fileBuf, size);

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
		ImageResource* image_res = new ImageResource(StringHelper::toString(id));
		image_res->setImageData(width, height, pixelBuf);

		FreeImage_Unload(fiBitmap);
		FreeImage_Unload(fiRGBA);
		FreeImage_CloseMemory(fiMem);

		return image_res;
	}
	//-----------------------------------------------------------------------
	ImageResource* ImageParser::createImageFromBitmapData(ushort id, void* fileBuf, uint size, BitmapData& data)
	{
		FIMEMORY* fiMem = FreeImage_OpenMemory((BYTE*)fileBuf, size);

		uint bpp = data.bpp;
		if(data.bpp == 24 && data.has_alpha_data)
		{
			bpp = 32;
		}

		FIBITMAP* fiBitmap = FreeImage_Allocate(data.width, data.height, bpp);
		if (!fiBitmap)
		{
			VTX_EXCEPT("Error loading image with freetype");
		}

		unsigned width = FreeImage_GetWidth(fiBitmap);
		unsigned height = FreeImage_GetHeight(fiBitmap);
		unsigned pitch = FreeImage_GetPitch(fiBitmap);		

		if(data.bpp == 8)
		{		
			RGBQUAD* palette = FreeImage_GetPalette(fiBitmap);
			BYTE transparency[256];

			for (uint i = 0; i < data.color_table_size; i++) 
			{
				palette[i].rgbRed = data.color_table[i].red;
				palette[i].rgbGreen = data.color_table[i].green;
				palette[i].rgbBlue = data.color_table[i].blue;
				transparency[i] = data.color_table[i].alpha;
			}

			// set the transparency table
			FreeImage_SetTransparencyTable(fiBitmap, transparency, data.color_table_size);

			for(unsigned y = 0; y < height; ++y) 
			{					
				for(unsigned x = 0; x < width; ++x) 
				{
					BYTE index = data.bitmap_data[(y*pitch)+x];
					if(!FreeImage_SetPixelIndex(fiBitmap, x, (height - y - 1), &index))
					{
						VTX_EXCEPT("Error loading image");
					}
				}
			}
		}
		else if(data.bpp == 24 && data.has_alpha_data)
		{
			FreeImage_SetTransparent(fiBitmap, true);
			ARGB* rgb_data = (ARGB*)data.bitmap_data;

			for(unsigned y = 0; y < height; ++y) 
			{					
				for(unsigned x = 0; x < width; ++x) 
				{
					uint index = (y*width)+x;
					ARGB* rgb_ptr = &rgb_data[index];
					
					RGBQUAD color;
					color.rgbRed = rgb_ptr->red;
					color.rgbGreen = rgb_ptr->green;
					color.rgbBlue = rgb_ptr->blue;
					color.rgbReserved = rgb_ptr->alpha;

					if(!FreeImage_SetPixelColor(fiBitmap, x, (height - y - 1), &color))
					{
						VTX_EXCEPT("Error loading image");
					}
				}
			}
		}
		else if(data.bpp == 24)
		{
			ARGB* rgb_data = (ARGB*)data.bitmap_data;

			for(unsigned y = 0; y < height; ++y) 
			{					
				for(unsigned x = 0; x < width; ++x) 
				{
					uint index = (y*width)+x;
					ARGB* rgb_ptr = &rgb_data[index];

					RGBQUAD color;
					color.rgbRed = rgb_ptr->red;
					color.rgbGreen = rgb_ptr->green;
					color.rgbBlue = rgb_ptr->blue;
					color.rgbReserved = 255;

					if(!FreeImage_SetPixelColor(fiBitmap, x, (height - y - 1), &color))
					{
						VTX_EXCEPT("Error loading image");
					}
				}
			}
		}
		else if(data.bpp == 32)
		{
			FreeImage_SetTransparent(fiBitmap, true);
			ARGB* rgb_data = (ARGB*)data.bitmap_data;

			for(unsigned y = 0; y < height; ++y) 
			{					
				for(unsigned x = 0; x < width; ++x) 
				{
					uint index = (y*width)+x;
					ARGB* rgb_ptr = &rgb_data[index];

					RGBQUAD color;
					color.rgbRed = rgb_ptr->red;
					color.rgbGreen = rgb_ptr->green;
					color.rgbBlue = rgb_ptr->blue;
					color.rgbReserved = rgb_ptr->alpha;

					if(!FreeImage_SetPixelColor(fiBitmap, x, (height - y - 1), &color))
					{
						VTX_EXCEPT("Error loading image");
					}
				}
			}
		}
		else
		{
			VTX_WARN("BMP: Unhandled case.");
		}

		FIBITMAP* fiRGBA = FreeImage_ConvertTo32Bits(fiBitmap);

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
		ImageResource* image_res = new ImageResource(StringHelper::toString(id));
		image_res->setImageData(width, height, pixelBuf);

		FreeImage_Unload(fiBitmap);
		FreeImage_Unload(fiRGBA);
		FreeImage_CloseMemory(fiMem);

		return image_res;
	}
	//-----------------------------------------------------------------------
	uint ImageParser::calculatePitch(uint width, uint bpp)
	{
		return ((width * bpp + 7) / 8) + 3 & ~3;
	}
	//-----------------------------------------------------------------------
	uint ImageParser::calculateBitmapDataSize(const TagTypes& tag_type, uchar bitmap_format,
		uint width, uint height, UI8 color_table_size)
	{
		uint bitmap_data_size = 0;

		//calculate pitch
		uint pitch = width; 
		
		if(bitmap_format == BF_8BIT_COLOR_MAPPED)
			pitch = calculatePitch(width, 8);

		else if(bitmap_format == BF_15BIT_RGB) 
			pitch = calculatePitch(width, 15);

		else if(bitmap_format == BF_24BIT_RGB) 
			pitch = calculatePitch(width, 32);

		else if(bitmap_format == BF_32BIT_ARGB) 
			pitch = calculatePitch(width, 32);

		bitmap_data_size = pitch * height;

		if(bitmap_format == BF_8BIT_COLOR_MAPPED) 
			bitmap_data_size += (color_table_size + 1) * 4;	
		
		return bitmap_data_size;
	}
	//-----------------------------------------------------------------------
	void ImageParser::checkZlibError(int ret_value)
	{
		if(ret_value != Z_OK)
		{
			if(ret_value == Z_MEM_ERROR)
				VTX_WARN("zlib mem error");

			else if(ret_value == Z_BUF_ERROR)
				VTX_WARN("zlib buf error");

			else if(ret_value == Z_DATA_ERROR)
				VTX_WARN("zlib data error");
		}
	}
	//-----------------------------------------------------------------------
	void ImageParser::setAlphaData(ImageResource* image_res, uint alpha_size, const UI8* alpha_data)
	{
		uchar* pix_data = (uchar*)image_res->getPixelData();

		for(uint i=0; i<alpha_size; ++i)
			pix_data[(i*4)+3] = alpha_data[i];
	}
	//-----------------------------------------------------------------------
	void ImageParser::readAlphaData(SwfParser* parser, uint zlib_alpha_size, uint alpha_size, ImageResource* image_res)
	{
		UI8* zlib_alpha_data = (UI8*)parser->getReadData();
		parser->skip(zlib_alpha_size);		

		UI8* alpha_data = new UI8[alpha_size];
		int ret_value = uncompress((uchar*)alpha_data, (uLongf*)&alpha_size, (uchar*)zlib_alpha_data, zlib_alpha_size);
		checkZlibError(ret_value);

		setAlphaData(image_res, alpha_size, alpha_data);

		delete[] alpha_data;
	}
	//-----------------------------------------------------------------------
}}
