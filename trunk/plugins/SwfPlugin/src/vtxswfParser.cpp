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

#include "vtxFile.h"
#include "vtxFileStream.h"
#include "vtxKeyframe.h"
#include "vtxLogManager.h"
#include "vtxMovieClipResource.h"
#include "vtxStringHelper.h"
#include "vtxTimeline.h"

#ifdef USE_ZLIB
#include "zlib.h"
#endif

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfParser::SwfParser() 
			: mCompressed(false), 
			mReadPos(0), 
			mBuffer(NULL), 
			mBitPos(0), 
			mBitBuf(0), 
			mFileLength(0), 
			mCurrentFile(NULL), 
			mCurrentStream(NULL), 
			// movieclips
			mMovieClipFrameIndex(0), 
			mCurrentMovieClip(NULL), 
			mMovieClipTimeline(NULL), 
			// main movieclip
			mMainFrameIndex(0), 
			mMainMovieClip(NULL), 
			mMainTimeline(NULL), 
			mCurrentKeyframe(NULL)
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

			if(!parseHeader())
			{
				return/* NULL*/;
			}

			//mCurrentFile = new File(stream->getFilename());
			mCurrentFile = file;

			mMainMovieClip = new MovieClipResource("__MainMovieClip__");
			mMainTimeline = new Timeline;
			mCurrentKeyframe = new Keyframe;

			while(mReadPos < mFileLength)
			{
				readTag();
			}

			delete[] mBuffer;

			// release empty frame
			if(mCurrentKeyframe)
			{
				delete mCurrentKeyframe;
				mCurrentKeyframe = NULL;
			}

			mCurrentFile->setHeader(mHeader);
			mCurrentFile->setScriptEngine("AS3ScriptEngine");

			mMainMovieClip->setTimeline(mMainTimeline);
			mCurrentFile->setMainMovieClip(mMainMovieClip);

			//return mCurrentFile;
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
			mCurrentFile = NULL; 
			mCurrentStream = NULL; 

			// movieclips
			mMovieClipFrameIndex = 0;
			mCurrentMovieClip = NULL;
			mMovieClipTimeline = NULL;

			// main movieclip
			mMainFrameIndex = 0; 
			mMainMovieClip = NULL; 
			mMainTimeline = NULL; 
			mCurrentKeyframe = NULL;
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

			UI8 version;
			mCurrentStream->read(&version, sizeof(UI8));
			mHeader.version = StringHelper::toString(version);

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
						vtxDebugAssert(ret != Z_STREAM_ERROR, "");
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

			UI16 type = tnl >> 6;
			UI32 length = tnl & 63;

			if(length == 63)
			{
				length = readU32();
			}

			switch(type)
			{
			case TT_End:
				handleEnd();
				break;

			case TT_ShowFrame:
				handleShowFrame();
				break;

			case TT_DefineShape:
			case TT_DefineShape2:
			case TT_DefineShape3:
			case TT_DefineShape4:
				handleDefineShape((TagTypes)type);
				break;

			case TT_DefineText:
			case TT_DefineText2:
				handleDefineText((TagTypes)type);
				break;

			case TT_DefineBitsLossless:
			case TT_DefineBitsLossless2:
				handleDefineBitsLossless((TagTypes)type);
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

			case TT_PlaceObject2:
				handlePlaceObject2();
				break;

			case TT_DefineButton2:
				handleDefineButton2();
				break;

			case TT_DefineEditText:
				handleDefineEditText((TagTypes)type);
				break;

			case TT_DefineSprite:
				handleDefineSprite();
				break;

			case TT_DefineFont3:
				handleDefineFont3();
				break;

			case TT_SymbolClass:
				handleSymbolClass();
				break;

			case TT_DoABC:
				handleDoABC(length);
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
		SI16 SwfParser::readS16()
		{
			//return readU16()>>8;
			return readU16();
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
		void SwfParser::fillReadBits()
		{
			mBitBuf = readU8();
			mBitPos = 8;
		}
		//-----------------------------------------------------------------------
		void SwfParser::resetReadBits()
		{
			mBitPos = mBitBuf = 0;
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
		int SwfParser::readSBits(UI32 n)
		{
			vtxDebugAssert(n <= 32, "");
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
	}
}
