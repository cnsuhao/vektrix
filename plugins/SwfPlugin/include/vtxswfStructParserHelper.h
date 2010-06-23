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

#ifndef __vtxswfStructParserHelper_H__
#define __vtxswfStructParserHelper_H__

#include "vtxswf.h"
#include "vtxswfParserTypes.h"
#include "vtxswfMemoryBlockReader.h"

namespace vtx
{
	namespace swf
	{
		class ParserHelper
		{
		public:
			static void readRect(MemoryBlockReader& memoryBlock, RECT& result);
			static void readColorRGB(MemoryBlockReader& memoryBlock, COLOR& result);
			static void readColorRGBA(MemoryBlockReader& memoryBlock, bool readARGB, COLOR& result);
			static void readMatrix(MemoryBlockReader& memoryBlock, MATRIX& result);
			static void readCXform(MemoryBlockReader& memoryBlock, bool readAlpha, CXFORM& result);
			static void readGradient(MemoryBlockReader& memoryBlock, bool readAlpha, GRADIENT& result);
			static void readFocalGradient(MemoryBlockReader& memoryBlock, GRADIENT& result);
			static void readKerningRecord(MemoryBlockReader& memoryBlock, bool wideCodes, KERNINGRECORD& result);
			static void readGlyphEntry(MemoryBlockReader& memoryBlock, int glyphBits, int advanceBits, GLYPHENTRY& result);
			static void readFillStyle(MemoryBlockReader& memoryBlock, bool hasAlpha, FILLSTYLE& result);
			static void readFillStyleArray(MemoryBlockReader& memoryBlock, bool hasAlpha, FILLSTYLEARRAY& result);
			static void readLineStyle(MemoryBlockReader& memoryBlock, bool hasAlpha, LINESTYLE& result);
			static void readLineStyle2(MemoryBlockReader& memoryBlock, LINESTYLE& result);
			static void readLineStyleArray(MemoryBlockReader& memoryBlock, bool hasAlpha, LINESTYLEARRAY& result);
			static void readLineStyleArray(MemoryBlockReader& memoryBlock, LINESTYLEARRAY& result);
			static void readTagHeader(MemoryBlockReader& memoryBlock, TagTypes& tag_type, UI32& tag_len);
		};
	}
}

#endif // __vtxswfStructParserHelper_H__
