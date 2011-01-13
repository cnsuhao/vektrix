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

#include "vtxswfDataReader.h"

#include "vtxLogManager.h"

namespace vtx { namespace swf {
	//-----------------------------------------------------------------------
	DataReader::DataReader() 
		: mBuffer(NULL), 
		mReadPos(0), 
		mBitPos(0), 
		mBitBuf(0)
	{

	}
	//-----------------------------------------------------------------------
	void DataReader::reset()
	{
		mReadPos = 0; 
		mBuffer = NULL; 
		mBitPos = 0; 
		mBitBuf = 0; 
	}
	//-----------------------------------------------------------------------
	void DataReader::init(char* buffer)
	{
		reset();
		mBuffer = buffer;
	}
	//-----------------------------------------------------------------------
	void DataReader::setReadPosition(const uint& offset)
	{
		mReadPos = offset;
	}
	//-----------------------------------------------------------------------
	const uint& DataReader::getReadPosition() const
	{
		return mReadPos;
	}
	//-----------------------------------------------------------------------
	void DataReader::skip(const uint& len)
	{
		mReadPos += len;
	}
	//-----------------------------------------------------------------------
	UI8 DataReader::readU8()
	{
		return mBuffer[mReadPos++];
	}
	//-----------------------------------------------------------------------
	UI16 DataReader::readU16()
	{
		return readU8() | readU8()<<8;
	}
	//-----------------------------------------------------------------------
	UI32 DataReader::readU32()
	{
		return readU8() | readU8()<<8 | readU8()<<16 | readU8()<<24;
	}
	//-----------------------------------------------------------------------
	UI32 DataReader::readUBits(UI32 n)
	{
		if(n == 0)
		{
			return 0;
		}

		int bitsLeft = n;
		int result = 0;
		if (!mBitPos)
		{
			fillReadBits();
		}

		int shift;
		for(shift = bitsLeft - mBitPos; shift > 0; shift = bitsLeft - mBitPos)
		{
			result |= mBitBuf << shift;
			bitsLeft -= mBitPos;
			fillReadBits();
		}

		// consume part of buffer
		result |= mBitBuf >> -shift;
		mBitPos -= bitsLeft;
		mBitBuf &= 0xff >> (8 - mBitPos); // mask consumed bits
		return result;
	}
	//-----------------------------------------------------------------------
	SI16 DataReader::readS16()
	{
		//return readU16()>>8;
		return readU16();
	}
	//-----------------------------------------------------------------------
	int DataReader::readSBits(UI32 n)
	{
		VTX_DEBUG_ASSERT(n <= 32, "");
		int num = readUBits(n);
		int shift = 32 - n;
		return (num << shift) >> shift; // sign extend
	}
	//-----------------------------------------------------------------------
	void DataReader::readByteBlock(char* buf, UI32 n)
	{
		memcpy(buf, &mBuffer[mReadPos], n);
		mReadPos += n;
	}
	//-----------------------------------------------------------------------
	void DataReader::resetReadBits()
	{
		mBitPos = mBitBuf = 0;
	}
	//-----------------------------------------------------------------------
	RECT DataReader::readRect()
	{
		resetReadBits();

		RECT result;
		UI32 n = readUBits(5);
		result.xmin = readSBits(n);
		result.xmax = readSBits(n);
		result.ymin = readSBits(n);
		result.ymax = readSBits(n);

		return result;
	}
	//-----------------------------------------------------------------------
	COLOR DataReader::readColor(const bool& alpha)
	{
		COLOR result;
		resetReadBits();

		result.red = readU8();
		result.green = readU8();
		result.blue = readU8();

		if(alpha)
		{
			result.alpha = readU8();
		}

		return result;
	}
	//-----------------------------------------------------------------------
	MATRIX DataReader::readMatrix()
	{
		MATRIX result;
		resetReadBits();

		UI32 num_bits = 0;
		resetReadBits();

		// SCALE
		if(readUBits(1))
		{
			num_bits = readUBits(5);
			result.sx = readSBits(num_bits);
			result.sy = readSBits(num_bits);
		}

		// SKEW
		if(readUBits(1))
		{
			num_bits = readUBits(5);
			result.cy = readSBits(num_bits);
			result.cx = readSBits(num_bits);
		}

		// TRANSLATION
		num_bits = readUBits(5);
		result.tx = readSBits(num_bits);
		result.ty = readSBits(num_bits);

		return result;
	}
	//-----------------------------------------------------------------------
	CXFORM DataReader::readCxForm(const bool& alpha)
	{
		CXFORM result;
		resetReadBits();

		UI8 has_add = readUBits(1);
		UI8 has_mul = readUBits(1);
		UI8 num_bits = readUBits(4);

		if(has_mul)
		{
			result.mul_red = readSBits(num_bits);
			result.mul_green = readSBits(num_bits);
			result.mul_blue = readSBits(num_bits);

			if(alpha)
			{
				result.mul_alpha = readSBits(num_bits);
			}
		}

		if(has_add)
		{
			result.add_red = readSBits(num_bits);
			result.add_green = readSBits(num_bits);
			result.add_blue = readSBits(num_bits);

			if(alpha)
			{
				result.add_alpha = readSBits(num_bits);
			}
		}

		return result;
	}
	//-----------------------------------------------------------------------
	String DataReader::readString(const bool& zero_terminated)
	{
		String result;

		// zero terminated string
		if(zero_terminated)
		{
			UI8 cur_char = readU8();
			while(cur_char != 0)
			{
				result.append(1, cur_char);
				cur_char = readU8();
			}
		}
		// read string with a given length (non zero terminated)
		else
		{
			UI8 name_length = readU8();
			for(UI8 i=0; i<name_length; ++i)
			{
				UI8 cur_char = readU8();
				if(cur_char)
				{
					result.append(1, cur_char);
				}
			}
		}

		return result;
	}
	//-----------------------------------------------------------------------
	KERNINGRECORD DataReader::readKerningRecord(const UI8& wide_codes)
	{
		KERNINGRECORD record;

		if(wide_codes)
		{
			record.left_char_code = readU16();
			record.right_char_code = readU16();
		}
		else
		{
			record.left_char_code = readU8();
			record.right_char_code = readU8();
		}

		record.adjustment = readS16();

		return record;
	}
	//-----------------------------------------------------------------------
	void DataReader::readShape(const TagTypes& type, SHAPE& result)
	{
		resetReadBits();
		UI8 num_fill_bits = readUBits(4);
		UI8 num_line_bits = readUBits(4);

		int x = 0;
		int y = 0;
		int fillstyle0 = 0;
		int fillstyle1 = 0;
		int linestyle = 0;

		while(true)
		{
			UI8 flags = readUBits(1);
			// edge record
			if(flags)
			{
				flags = readUBits(1);
				// straight edge
				if(flags)
				{
					UI8 num_bits = readUBits(4) + 2;

					// general line
					flags = readUBits(1);
					if(flags)
					{
						// line flag
						x += readSBits(num_bits); // delta x
						y += readSBits(num_bits); // delta y
					}
					// vertical/horizontal line
					else
					{
						UI8 vertical = readUBits(1);
						if(vertical)
						{
							y += readSBits(num_bits);;
						}
						else
						{
							x += readSBits(num_bits);;
						}
					}

					SHAPEELEMENT se;
					se.type = SET_LINE;
					se.x = x;
					se.y = y;
					se.cx = se.cy = 0;
					se.fill0 = fillstyle0;
					se.fill1 = fillstyle1;
					se.line = linestyle;

					//std::cout << "[" << fillstyle0 << "|" << fillstyle1 << "]{" << linestyle << "} X: " << x/20.0 << ", Y: " << y/20.0 << std::endl;
					result.elements.push_back(se);
				}
				// curved edge
				else
				{
					UI8 num_bits = readUBits(4) + 2;

					x += readSBits(num_bits); // delta x
					y += readSBits(num_bits); // delta y

					int cx = x;
					int cy = y;

					x += readSBits(num_bits); // delta x
					y += readSBits(num_bits); // delta y

					SHAPEELEMENT se;
					se.type = SET_BEZIER;
					se.x = x;
					se.y = y;
					se.cx = cx;
					se.cy = cy;
					se.fill0 = fillstyle0;
					se.fill1 = fillstyle1;
					se.line = linestyle;

					//std::cout << "[" << fillstyle0 << "|" << fillstyle1 << "]{" << linestyle << "} X: " << x/20.0 << ", Y: " << y/20.0 << std::endl;
					result.elements.push_back(se);
				}
			}
			// non-edge record
			else
			{
				flags = readUBits(5);

				// end-shape record
				if(!flags)
				{
					break;
				}
				// move
				if(flags & 1)
				{
					UI8 num_move_bits = readUBits(5);
					x = readSBits(num_move_bits);
					y = readSBits(num_move_bits);

					SHAPEELEMENT se;
					se.type = SET_MOVE;
					se.x = x;
					se.y = y;
					se.cx = se.cy = 0;
					se.fill0 = fillstyle0;
					se.fill1 = fillstyle1;
					se.line = linestyle;

					//std::cout << "[" << fillstyle0 << "|" << fillstyle1 << "]{" << linestyle << "} X: " << x/20.0 << ", Y: " << y/20.0 << std::endl;
					result.elements.push_back(se);
				}
				// fillstyle 0
				if(flags & 2)
				{
					fillstyle0 = readUBits(num_fill_bits);
				}
				// fillstyle 1
				if(flags & 4)
				{
					fillstyle1 = readUBits(num_fill_bits);
				}
				// linestyle
				if(flags & 8)
				{
					linestyle = readUBits(num_line_bits);
				}
				// new styles
				if(flags & 16 && 
					(type == TT_DefineShape2 || 
					type == TT_DefineShape3))
				{
					//vtxDebugFail("new styles not tested yet");
					readFillstyleArray(type, result.fillstyles);
					readLinestyleArray(type, result.linestyles);
					num_fill_bits = readUBits(4);
					num_line_bits = readUBits(4);
				}
			}
		} // while(true)
	}
	//-----------------------------------------------------------------------
	void DataReader::readShapeWithStyle(const TagTypes& type, SHAPE& result)
	{
		readFillstyleArray(type, result.fillstyles);
		readLinestyleArray(type, result.linestyles);

		readShape(type, result);
	}
	//-----------------------------------------------------------------------
	void DataReader::readFillstyleArray(const TagTypes& type, FillstyleList& result)
	{
		resetReadBits();
		UI16 fillstyle_count = readU8();

		if(fillstyle_count == 255 && 
			(type == TT_DefineShape2 || 
			type == TT_DefineShape3))
		{
			fillstyle_count = readU16();
		}

		// FILLSTYLE ARRAY
		for(UI16 i=0; i<fillstyle_count; ++i)
		{
			UI8 fill_type = readU8();

			switch(fill_type)
			{
			case FST_Solid:
				{
					FILLSTYLE fs;
					fs.type = FST_Solid;
					fs.color = readColor(type == TT_DefineShape3 || type == TT_DefineShape4);
					result.push_back(fs);
				}
				break;

			case FST_LinearGradient:
			case FST_RadialGradient:
				{
					FILLSTYLE fs;
					fs.type = (FillStyleType)fill_type;
					fs.matrix = readMatrix();
					resetReadBits();

					UI8 spread_mode = readUBits(2);
					UI8 interp_mode = readUBits(2);
					UI8 num_gradients = readUBits(4);

					for(UI8 j=0; j<num_gradients; ++j)
					{
						UI8 ratio = readU8();
						COLOR color = readColor(type == TT_DefineShape3 || type == TT_DefineShape4);
						fs.gradient[ratio] = color;
					}

					result.push_back(fs);
				}
				break;

			case FST_RepeatingBitmap:
			case FST_ClippedBitmap:
			case FST_NonSmoothedRepeatingBitmap:
			case FST_NonSmoothedClippedBitmap:
				{
					UI16 bitmapId = readU16();
					MATRIX bitmapMatrix = readMatrix();

					FILLSTYLE fs;
					fs.type = (FillStyleType)fill_type;
					fs.bitmapId = bitmapId;					
					result.push_back(fs);
				}
				break;

			default:
				VTX_DEBUG_FAIL("SWF shape fillstyle type not implemented");
				break;
			}
		}
	}
	//-----------------------------------------------------------------------
	void DataReader::readLinestyleArray(const TagTypes& type, LinestyleList& result)
	{
		resetReadBits();
		UI16 linestyle_count = readU8();

		if(linestyle_count == 255)
		{
			linestyle_count = readU16();
		}

		// LINESTYLE ARRAY
		for(UI16 i=0; i<linestyle_count; ++i)
		{
			UI16 line_width = readU16();

			bool filled_line = false;
			if(type == TT_DefineShape4)
			{
				UI16 flags = readU16();

				if(((flags >> 12) & 3) == 2)
				{
					readU16(); // miter limit
				}

				if(flags & 8)
				{
					filled_line = true;
					VTX_WARN("Filled lines not yet supported");
				}
			}

			if(filled_line)
			{

			}
			else
			{
				LINESTYLE ls;
				ls.width = line_width;
				ls.color = readColor(type == TT_DefineShape3 || type == TT_DefineShape4);
				result.push_back(ls);
			}
		}
	}
	//-----------------------------------------------------------------------
	void DataReader::fillReadBits()
	{
		mBitBuf = readU8();
		mBitPos = 8;
	}
	//-----------------------------------------------------------------------
}}
