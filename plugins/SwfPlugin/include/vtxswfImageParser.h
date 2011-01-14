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

#ifndef __vtxswfImageParser_H__
#define __vtxswfImageParser_H__

#include "vtxswf.h"
#include "vtxswfParserTypes.h"

namespace vtx { namespace swf {
	//-----------------------------------------------------------------------
	class ImageParser
	{
	public:
		ImageParser();
		virtual ~ImageParser();

		void handleDefineBitsLossless(const TagTypes& tag_type, const uint& tag_length, SwfParser* parser);
		void handleJPEGTables(const TagTypes& tag_type, const uint& tag_length, SwfParser* parser);
		void handleDefineBitsJPEG(const TagTypes& tag_type, const uint& tag_length, SwfParser* parser);

	protected:
		struct BitmapData
		{
			BitmapData()
				: 
				width(0), 
				height(0), 
				bpp(0),
				bitmap_data_size(0),
				color_table_size(0),
				color_table(NULL),
				bitmap_data(NULL),
				has_alpha_data(false)
			{		
			}

			uint width;
			uint height;
			uint bpp;
			uint bitmap_data_size;
			uint color_table_size;
			RGBA* color_table;
			uchar* bitmap_data;
			bool has_alpha_data;
		};

		ImageResource* createImageFromJPEG(ushort id, void* fileBuf, uint size);
		ImageResource* createImageFromBitmapData(ushort id, void* fileBuf, uint size, BitmapData& data);

		uint calculatePitch(uint width, uint bpp);
		uint calculateBitmapDataSize(const TagTypes& tag_type, uchar bitmap_format, uint width, uint height, UI8 color_table_size);

		void readAlphaData(SwfParser* parser, uint zlib_alpha_size, uint alpha_size, ImageResource* image_res);
		void setAlphaData(ImageResource* image_res, uint alpha_size, const UI8* alpha_data);
		void checkZlibError(int ret_value);
		
		// jpeg tables
		char* mJPEGTables;
	};
	//-----------------------------------------------------------------------
}}

#endif
