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
#include "vtxswfParser.h"

// TagParsers
#include "vtxswfFontParser.h"
#include "vtxswfImageParser.h"
#include "vtxswfScriptParser.h"
#include "vtxswfShapeParser.h"
#include "vtxswfStructureParser.h"
#include "vtxswfTextParser.h"

#include "vtxFileStream.h"
#include "vtxLogManager.h"
#include "vtxStringHelper.h"

#ifdef USE_ZLIB
#include "zlib.h"
#endif

namespace vtx { namespace swf {
	//-----------------------------------------------------------------------
	SwfParser::SwfParser() 
		: mCompressed(false), 
		mReadPos(0), 
		mBuffer(NULL), 
		mBitPos(0), 
		mBitBuf(0), 
		mFileLength(0), 
		mCurrentFile(NULL), 
		mCurrentStream(NULL)
	{

	}
	//-----------------------------------------------------------------------
	SwfParser::~SwfParser()
	{

	}
	//-----------------------------------------------------------------------
	const StringList& SwfParser::getExtensions() const
	{
		static StringList extensions;
		extensions.push_back(".swf");
		return extensions;
	}
	//-----------------------------------------------------------------------
	void SwfParser::parse(FileStream* stream, File* file)
	{
		resetData();

		mCurrentStream = stream;
		mCurrentFile = file;
		mCurrentFile->setScriptEngine("AS3ScriptEngine");

		mFontParser = new FontParser();
		mImageParser = new ImageParser();
		mScriptParser = new ScriptParser;
		mShapeParser = new ShapeParser();
		mStructureParser = new StructureParser(this);
		mTextParser = new TextParser;

		if(!parseHeader())
		{
			return;
		}

		while(mReadPos < mFileLength)
		{
			readTag();
		}

		mCurrentFile->setHeader(mHeader);

		delete[] mBuffer;

		delete mFontParser;
		delete mImageParser;
		delete mScriptParser;
		delete mShapeParser;
		delete mStructureParser;
		delete mTextParser;
	}
	//-----------------------------------------------------------------------
	void SwfParser::resetData()
	{
		mCompressed = false;
		mReadPos = 0; 
		mBuffer = NULL; 
		mBitPos = 0; 
		mBitBuf = 0; 
		mFileLength = 0;
		mSWFVersion = 0;
		mCurrentFile = NULL; 
		mCurrentStream = NULL;
	}
	//-----------------------------------------------------------------------
	bool SwfParser::parseHeader()
	{
		UI8 sig[3];
		mCurrentStream->read(&sig, sizeof(UI8)*3);

		if((sig[0] != 'C' && sig[0] != 'F') || 
			sig[1] != 'W' || sig[2] != 'S')
		{
			error("File is not a valid SWF file.");
			return false;
		}

		mCompressed = (sig[0] == 'C');

		//UI8 version;
		mCurrentStream->read(&mSWFVersion, sizeof(UI8));
		mHeader.version = StringHelper::toString(mSWFVersion);

		mCurrentStream->read(&mFileLength, sizeof(UI32));

		// subtract header size (8 bytes)
		mFileLength -= 8;

		if(mCompressed)
		{
#ifdef USE_ZLIB
			uint chunk_size = 0x40000; // 256 kBytes

			z_stream zlib_stream;
			zlib_stream.zalloc = Z_NULL;
			zlib_stream.zfree = Z_NULL;
			zlib_stream.opaque = Z_NULL;

			zlib_stream.avail_in = 0;
			zlib_stream.next_in = Z_NULL;

			int ret = inflateInit(&zlib_stream);
			if(ret != Z_OK)
			{
				error("ZLIB error: unknown startup error");
				return false;
			}

			uint bufStart = 0;
			char* readBuf = new char[chunk_size];
			mBuffer = new char[mFileLength];

			do 
			{
				// read a chunk of data from the SWF file
				zlib_stream.avail_in = mCurrentStream->read(readBuf, chunk_size);

				// no data available
				if(zlib_stream.avail_in == 0)
				{
					break;
				}

				// give the read chunk to ZLIB
				zlib_stream.next_in = (Bytef*)readBuf;

				do
				{
					// copy the extracted content to the final buffer
					zlib_stream.avail_out = chunk_size;
					zlib_stream.next_out = (Bytef*)&mBuffer[bufStart];

					ret = inflate(&zlib_stream, Z_NO_FLUSH);
					VTX_DEBUG_ASSERT(ret != Z_STREAM_ERROR, "");
					switch(ret)
					{
					case Z_NEED_DICT:
					case Z_DATA_ERROR:
					case Z_MEM_ERROR:
						(void)inflateEnd(&zlib_stream);
						error("ZLIB error: extraction failed");
						return false;
					}

					// calculate the written bytes
					uint written = chunk_size - zlib_stream.avail_out;
					bufStart += written;

				} while(zlib_stream.avail_out == 0);

			} while(ret != Z_STREAM_END);

			// clean up
			(void)inflateEnd(&zlib_stream);
			delete[] readBuf;

#else
			error("Unable to load compressed SWF file (SWF plugin was compiled without zlib support).");
			return false;
#endif
		}
		else
		{
			mBuffer = new char[mFileLength];
			mCurrentStream->read(mBuffer, mFileLength);
		}

		RECT dimensions = readRect();

		mHeader.width  = (uint)((dimensions.xmax - dimensions.xmin)/20.0f);
		mHeader.height = (uint)((dimensions.ymax - dimensions.ymin)/20.0f);

		UI16 fps = readU16();
		UI16 frame_count = readU16();

		mHeader.version = "test_version";
		mHeader.fps = fps/256;
		mHeader.frames = frame_count;

		return true;
	}
	//-----------------------------------------------------------------------
	void SwfParser::readTag()
	{
		// type and length
		UI16 tnl = readU16();

		TagTypes type = (TagTypes)(tnl >> 6);
		UI32 length = tnl & 63;

		if(length == 63)
		{
			length = readU32();
		}

		switch(type)
		{
			// fonts
		case TT_DefineFont3:
			{
				mFontParser->handleDefineFont(type, length, this);
			}
			break;

			// images
		case TT_JPEGTables:
			{
				mImageParser->handleJPEGTables(type, length, this);
			}
			break;

		//case TT_DefineBits:
		//case TT_DefineBitsJPEG2:
		//case TT_DefineBitsJPEG3:
		//case TT_DefineBitsJPEG4:
		//	{
		//		mImageParser->handleDefineBitsJPEG(type, length, this);
		//	}
		//	break;

		//case TT_DefineBitsLossless:
		//case TT_DefineBitsLossless2:
		//	{
		//		mImageParser->handleDefineBitsLossless(type, length, this);
		//	}
		//	break;

			// shapes
		case TT_DefineShape:
		case TT_DefineShape2:
		case TT_DefineShape3:
		case TT_DefineShape4:
			{
				mShapeParser->handleDefineShape(type, this);
			}
			break;

			// structure
		//case TT_DefineButton:
		//	mStructureParser->handleDefineButton2()
		//	break;

		case TT_DefineButton2:
			mStructureParser->handleDefineButton2();
			break;

		case TT_DefineSprite:
			mStructureParser->handleDefineSprite();
			break;

		case TT_PlaceObject2:
			mStructureParser->handlePlaceObject2();
			break;

		case TT_RemoveObject2:
			mStructureParser->handleRemoveObject2();
			break;

		case TT_ShowFrame:
			mStructureParser->handleShowFrame();
			break;

		case TT_End:
			mStructureParser->handleEnd();
			break;

		case TT_DefineScalingGrid:
			mStructureParser->handleDefineScalingGrid();
			break;

		case TT_SetBackgroundColor:
			{
				COLOR color = readColor();
				mHeader.bgcolor = Color(
					(float)color.red/255.0f, 
					(float)color.green/255.0f, 
					(float)color.blue/255.0f, 
					(float)color.alpha/255.0f);
			}
			break;


			// dynamic text
		case TT_DefineEditText:
			mTextParser->handleDefineEditText(type, length, this);
			break;

			// static text
		case TT_DefineText:
		case TT_DefineText2:
			{
				mTextParser->handleDefineText(type, length, this);
			}
			break;

			// ActionScript
		case TT_SymbolClass:
			mStructureParser->handleSymbolClass(type, length, this);
			break;

		case TT_DoABC:
			mStructureParser->handleDoABC(type, length, this);
			break;

			// skip tags that don't need to be parsed (yet?)
		case TT_FileAttributes:
		case TT_MetaData:
		case TT_DefineSceneAndFrameLabelData:
			mReadPos += length;
			break;

		default:
			VTX_WARN("SWF tag type not implemented: %d", type);
			mReadPos += length;
			break;
		}
	}
	//-----------------------------------------------------------------------
	void SwfParser::skip(const uint& len)
	{
		mReadPos += len;
	}
	//-----------------------------------------------------------------------
	UI8 SwfParser::readU8()
	{
		return mBuffer[mReadPos++];
	}
	//-----------------------------------------------------------------------
	UI16 SwfParser::readU16()
	{
		return readU8() | readU8()<<8;
	}
	//-----------------------------------------------------------------------
	UI32 SwfParser::readU32()
	{
		return readU8() | readU8()<<8 | readU8()<<16 | readU8()<<24;
	}
	//-----------------------------------------------------------------------
	UI32 SwfParser::readUBits(UI32 n)
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
	SI16 SwfParser::readS16()
	{
		//return readU16()>>8;
		return readU16();
	}
	//-----------------------------------------------------------------------
	int SwfParser::readSBits(UI32 n)
	{
		VTX_DEBUG_ASSERT(n <= 32, "");
		int num = readUBits(n);
		int shift = 32 - n;
		return (num << shift) >> shift; // sign extend
	}
	//-----------------------------------------------------------------------
	void SwfParser::readByteBlock(char* buf, UI32 n)
	{
		memcpy(buf, &mBuffer[mReadPos], n);
		mReadPos += n;
	}
	//-----------------------------------------------------------------------
	void SwfParser::resetReadBits()
	{
		mBitPos = mBitBuf = 0;
	}
	//-----------------------------------------------------------------------
	RECT SwfParser::readRect()
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
	COLOR SwfParser::readColor(const bool& alpha)
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
	MATRIX SwfParser::readMatrix()
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
	CXFORM SwfParser::readCxForm(const bool& alpha)
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
	String SwfParser::readString(const bool& zero_terminated)
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
	KERNINGRECORD SwfParser::readKerningRecord(const UI8& wide_codes)
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
	void SwfParser::readShape(const TagTypes& type, SHAPE& result)
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
	void SwfParser::readShapeWithStyle(const TagTypes& type, SHAPE& result)
	{
		readFillstyleArray(type, result.fillstyles);
		readLinestyleArray(type, result.linestyles);

		readShape(type, result);
	}
	//-----------------------------------------------------------------------
	void SwfParser::readFillstyleArray(const TagTypes& type, FillstyleList& result)
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

			default:
				VTX_DEBUG_FAIL("SWF shape fillstyle type not implemented");
				break;
			}
		}
	}
	//-----------------------------------------------------------------------
	void SwfParser::readLinestyleArray(const TagTypes& type, LinestyleList& result)
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
	void SwfParser::fillReadBits()
	{
		mBitBuf = readU8();
		mBitPos = 8;
	}
	//-----------------------------------------------------------------------
}}
