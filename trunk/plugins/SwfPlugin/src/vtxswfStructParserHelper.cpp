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
#include "vtxswfStructParserHelper.h"
#include "vtxLogManager.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		void ParserHelper::readRect(MemoryBlockReader& memoryBlock, RECT& result)
		{
			int nBits = (int)memoryBlock.readUnsignedBits(5);
			result.xmin = memoryBlock.readSignedBits(nBits);
			result.xmax = memoryBlock.readSignedBits(nBits);
			result.ymin = memoryBlock.readSignedBits(nBits);
			result.ymax = memoryBlock.readSignedBits(nBits);
			memoryBlock.align();
		}
		//-----------------------------------------------------------------------
		void ParserHelper::readColorRGB(MemoryBlockReader& memoryBlock, COLOR& result)
		{
			result.alpha	= 255;
			result.red		= memoryBlock.readUI8();
			result.green	= memoryBlock.readUI8();
			result.blue		= memoryBlock.readUI8();
		}
		//-----------------------------------------------------------------------
		void ParserHelper::readColorRGBA(MemoryBlockReader& memoryBlock, bool readARGB, COLOR& result)
		{
			result.alpha	= readARGB ? memoryBlock.readUI8() : 255;
			result.red		= memoryBlock.readUI8();
			result.green	= memoryBlock.readUI8();
			result.blue		= memoryBlock.readUI8();
			result.alpha	= !readARGB ? memoryBlock.readUI8() : 255;
		}
		//-----------------------------------------------------------------------
		void ParserHelper::readMatrix(MemoryBlockReader& memoryBlock, MATRIX& result)
		{
			result.hasScale = memoryBlock.readBooleanBit();
			if (result.hasScale)
			{
				int nScaleBits = (int)memoryBlock.readUnsignedBits(5);
				result.scale_x   = memoryBlock.readFPBits(nScaleBits);
				result.scale_y   = memoryBlock.readFPBits(nScaleBits);
			}
			result.hasRotate = memoryBlock.readBooleanBit();
			if (result.hasRotate)
			{
				int nRotateBits = (int)memoryBlock.readUnsignedBits(5);
				result.rotate_x   = memoryBlock.readFPBits(nRotateBits);
				result.rotate_y   = memoryBlock.readFPBits(nRotateBits);
			}
			int nTranslateBits = (int)memoryBlock.readUnsignedBits(5);
			result.trans_x   = memoryBlock.readFPBits(nTranslateBits);
			result.trans_y   = memoryBlock.readFPBits(nTranslateBits);
			memoryBlock.align();
		}
		//-----------------------------------------------------------------------
		void ParserHelper::readCXform(MemoryBlockReader& memoryBlock, bool readAlpha, CXFORM& result)
		{
			result.has_add = memoryBlock.readBooleanBit();
			result.has_mul = memoryBlock.readBooleanBit();
			int nBits = (int)memoryBlock.readUnsignedBits(4);
			if (result.has_mul)
			{
				result.mul_red		= (int)memoryBlock.readSignedBits(nBits);
				result.mul_green	= (int)memoryBlock.readSignedBits(nBits);
				result.mul_blue		= (int)memoryBlock.readSignedBits(nBits);
				result.mul_alpha	= readAlpha ? (int)memoryBlock.readSignedBits(nBits) : 255;
			}
			if (result.has_add)
			{
				result.add_red		= (int)memoryBlock.readSignedBits(nBits);
				result.add_green	= (int)memoryBlock.readSignedBits(nBits);
				result.add_blue		= (int)memoryBlock.readSignedBits(nBits);
				result.add_alpha	= readAlpha ? (int)memoryBlock.readSignedBits(nBits) : 255;
			}
			memoryBlock.align();
		}
		//-----------------------------------------------------------------------
		void ParserHelper::readGradient(MemoryBlockReader& memoryBlock, bool readAlpha, GRADIENT& result)
		{
			result.spreadMethod			= (SpreadMethod)memoryBlock.readUnsignedBits(2);
			result.interpolationMethod	= (InterpolationMethod)memoryBlock.readUnsignedBits(2);
			result.numRecords			= (int)memoryBlock.readUnsignedBits(4);
			for(int i = 0; i < result.numRecords; ++i)
			{
				result.gradientRecords[i].ratio = memoryBlock.readUI8();
				if(readAlpha)
					readColorRGBA(memoryBlock, false, result.gradientRecords[i].color);
				else
					readColorRGB(memoryBlock, result.gradientRecords[i].color);
			}
		}
		//-----------------------------------------------------------------------
		void ParserHelper::readFocalGradient(MemoryBlockReader& memoryBlock, GRADIENT& result)
		{
			ParserHelper::readGradient(memoryBlock, true, result);
			result.focalPointRatio = memoryBlock.readFP16();
		}
		//-----------------------------------------------------------------------
		void ParserHelper::readKerningRecord(MemoryBlockReader& memoryBlock, bool wideCodes, KERNINGRECORD& result)
		{
			if (wideCodes)
			{
				result.left_char_code    = memoryBlock.readUI16();
				result.right_char_code   = memoryBlock.readUI16();
			}
			else
			{
				result.left_char_code    = memoryBlock.readUI8();
				result.right_char_code   = memoryBlock.readUI8();
			}
			result.adjustment = memoryBlock.readSI16();
		}
		//-----------------------------------------------------------------------
		void ParserHelper::readGlyphEntry(MemoryBlockReader& memoryBlock, int glyphBits, int advanceBits, GLYPHENTRY& result)
		{
			result.index = memoryBlock.readUnsignedBits(glyphBits);
			result.x_advance = memoryBlock.readSignedBits(advanceBits);
		}
		//-----------------------------------------------------------------------
		void ParserHelper::readFillStyle(MemoryBlockReader& memoryBlock, bool hasAlpha, FILLSTYLE& result)
		{
			result.type = (FillStyleType)memoryBlock.readUI8();
			switch (result.type)
			{
			case FST_Solid:
				if(hasAlpha)
					readColorRGBA(memoryBlock, false, result.color);
				else
					readColorRGB(memoryBlock, result.color);
				break;
			case FST_LinearGradient:
			case FST_RadialGradient:
			case FST_FocalRadialGradient:
				readMatrix(memoryBlock, result.gradientMatrix);
				if(result.type == FST_FocalRadialGradient)
					readFocalGradient(memoryBlock, result.gradient);
				else
					readGradient(memoryBlock, hasAlpha, result.gradient);
				break;
			case FST_RepeatingBitmap:
			case FST_ClippedBitmap:
			case FST_NonSmoothedRepeatingBitmap:
			case FST_NonSmoothedClippedBitmap:
				result.bitmapId = memoryBlock.readUI16();
				readMatrix(memoryBlock, result.bitmapMatrix);
				break;
			default:
				VTX_DEBUG_FAIL("Unknown fill type");
			}
		}
		//-----------------------------------------------------------------------
		void ParserHelper::readFillStyleArray(MemoryBlockReader& memoryBlock, bool hasAlpha, FILLSTYLEARRAY& result)
		{
			result.numStyles = memoryBlock.readUI8();
			if(result.numStyles == 0xFF)
				result.numStyles = memoryBlock.readUI16();
			result.styles = new FILLSTYLE[result.numStyles];
			for(int i = 0; i < result.numStyles; ++i)
			{
				readFillStyle(memoryBlock, hasAlpha, result.styles[i]);
			}
		}
		//-----------------------------------------------------------------------
		void ParserHelper::readLineStyle(MemoryBlockReader& memoryBlock, bool hasAlpha, LINESTYLE& result)
		{
			result.width = memoryBlock.readUI16();
			if(hasAlpha)
				readColorRGBA(memoryBlock, false, result.color);
			else
				readColorRGB(memoryBlock, result.color);
		}
		//-----------------------------------------------------------------------
		void ParserHelper::readLineStyle2(MemoryBlockReader& memoryBlock, LINESTYLE& result)
		{
			result.width = memoryBlock.readUI16();
			result.startCapStyle = (CapStyle)memoryBlock.readUnsignedBits(2);
			result.endCapStyle = (CapStyle)memoryBlock.readUnsignedBits(2);

			bool hasFill = memoryBlock.readBooleanBit();
			bool noHScale = memoryBlock.readBooleanBit();
			bool noVScale = memoryBlock.readBooleanBit();

			result.scaleStroke = (ScaleStrokeMethod)((noHScale ? 0 : 2) | (noVScale ? 0 : 1));
			result.pixelHinting = memoryBlock.readBooleanBit();

			memoryBlock.readUnsignedBits(5);
			result.close = !memoryBlock.readBooleanBit();

			result.jointStyle = (JointStyle)memoryBlock.readUnsignedBits(2);
			if (result.jointStyle == JS_MITER)
				result.miterLimit = memoryBlock.readFP16();

			if (hasFill)
			{
				readFillStyle(memoryBlock, true, result.fillStyle);
			}
			else
			{
				readColorRGBA(memoryBlock, false, result.color);
			}
		}
		//-----------------------------------------------------------------------
		void ParserHelper::readLineStyleArray(MemoryBlockReader& memoryBlock, LINESTYLEARRAY& result)
		{
			result.numStyles = memoryBlock.readUI8();
			if(result.numStyles == 0xFF)
				result.numStyles = memoryBlock.readUI16();
			result.styles = new LINESTYLE[result.numStyles];
			for(int i = 0; i < result.numStyles; ++i)
			{
				readLineStyle2(memoryBlock, result.styles[i]);
			}
		}
		//-----------------------------------------------------------------------
		void ParserHelper::readLineStyleArray(MemoryBlockReader& memoryBlock, bool hasAlpha, LINESTYLEARRAY& result)
		{
			result.numStyles = memoryBlock.readUI8();
			if(result.numStyles == 0xFF)
				result.numStyles = memoryBlock.readUI16();
			result.styles = new LINESTYLE[result.numStyles];
			for(int i = 0; i < result.numStyles; ++i)
			{
				readLineStyle(memoryBlock, hasAlpha, result.styles[i]);
			}
		}
		//-----------------------------------------------------------------------
		void ParserHelper::readTagHeader(MemoryBlockReader& blockReader, TagTypes& tag_type, UI32& tag_len)
		{
			UI16 tnl = blockReader.readUI16();
			tag_type = (TagTypes)(tnl >> 6);
			tag_len = tnl & 63;
			if(tag_len == 63)
			{
				tag_len = blockReader.readUI32();
			}
		}
		//-----------------------------------------------------------------------
	}
}
