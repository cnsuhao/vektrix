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

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		ImageParser::ImageParser() 
			: mJPEGTables(NULL)
		{

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
		}
		//-----------------------------------------------------------------------
		void ImageParser::handleDefineBitsLossless(const TagTypes& tag_type, const uint& tag_length, SwfParser* parser)
		{
			UI16 id = parser->readU16();

			UI8 bitmap_format = parser->readU8();

			UI16 width = parser->readU16();
			UI16 height = parser->readU16();

			UI32 img_data_size = width * height;

			if(bitmap_format == BF_8BIT_COLOR_MAPPED)
			{
				UI8 color_table_size = parser->readU8(); // color table size

				// COLORMAPDATA
				for(UI8 i=0; i<color_table_size; ++i)
				{
					// COLORS
					parser->readColor();
				}

				for(UI32 i=0; i<img_data_size; ++i)
				{
					// INDICES
					parser->readU8();
				}
			}
			else if(bitmap_format == BF_15BIT_RGB || bitmap_format == BF_24BIT_RGB)
			{
				// BITMAPDATA
			}
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
			UI16 characterId = parser->readU16();
			//readByteBlock(pJpegData, tag_length-2);
		}
		//-----------------------------------------------------------------------
	}
}
