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
#include "vtxswfMemoryBlockReader.h"

namespace vtx
{
	namespace swf
	{
		class ImageParser
		{
		public:
			ImageParser();
			virtual ~ImageParser();

			void handleDefineBitsLossless(const TagTypes& tag_type, MemoryBlockReader& tag_reader, SwfParser* parser);
			void handleJPEGTables(const TagTypes& tag_type, MemoryBlockReader& tag_reader, SwfParser* parser);
			void handleDefineBitsJPEG(const TagTypes& tag_type, MemoryBlockReader& tag_reader, SwfParser* parser);

		protected:
			// jpeg parsing functions
			uchar* readDefineBitsJPEG(MemoryBlockReader& tag_reader, int& width, int& height);
			uchar* readDefineBitsJPEG2(MemoryBlockReader& tag_reader, int& width, int& height);
			uchar* readDefineBitsJPEG3(MemoryBlockReader& tag_reader, int& width, int& height);
			uchar* readDefineBitsJPEG4(MemoryBlockReader& tag_reader, int& width, int& height);

			uchar* readJpegData(MemoryBlockReader& tag_reader, size_t len);
			uchar* readBitmapAlphaData(MemoryBlockReader& tag_reader, size_t len);
			uchar* decodeJPEGData(uchar* jpeg_data, size_t data_len, int& width, int& height, uchar* table_data = NULL, size_t table_len = 0);

			// lossless bitmap parsing functions
			uchar* readAlphaColorMapData(MemoryBlockReader& tag_reader, size_t colorTableSize, int width, int height);
			uchar* readColorMapData(MemoryBlockReader& tag_reader, size_t colorTableSize, int width, int height);
			uchar* readAlphaBitmapData(MemoryBlockReader& tag_reader, int width, int height);
			uchar* readBitmapData(MemoryBlockReader& tag_reader, BitmapFormat format, int width, int height);
			uchar* readPix15BitmapData(MemoryBlockReader& tag_reader, int data_size, int width, int height);
			uchar* readPix24BitmapData(MemoryBlockReader& tag_reader, int data_size, int width, int height);

			int getScanlinePadLength(int width);
			int getScanlinePadLength2(int width);

			// shared
			void finish(File* file, uchar* bitmap_data, int width, int height, int character_id);

		protected:
			// jpeg parsing data
			uchar* mJPEGTables;
			size_t mJPEGTableLen;
		};
	}
}

#endif // __vtxswfImageParser_H__
