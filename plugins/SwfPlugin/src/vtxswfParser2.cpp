/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009 Fuse-Software (tm)

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/gpl.txt.
-----------------------------------------------------------------------------
*/
#include "vtxswfParser2.h"

#include "vtxFile.h"
#include "vtxFileStream.h"
#include "vtxKeyframe.h"
#include "vtxLogManager.h"
#include "vtxMovieClipResource.h"
#include "vtxScriptResource.h"
#include "vtxStringHelper.h"
#include "vtxTimeline.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfParser2::SwfParser2() 
			: mCompressed(false), 
			mReadPos(0), 
			mBitPos(0), 
			mBitBuf(0), 
			mFileLength(0), 
			mCurrentFile(NULL), 
			mCurrentStream(NULL), 
			// movieclips
			mCurrentMovieClip(NULL), 
			// main movieclip
			mMainFrameIndex(0), 
			mMainMovieClip(NULL), 
			mTimeline(NULL), 
			mCurrentKeyframe(NULL)
		{

		}
		//-----------------------------------------------------------------------
		SwfParser2::~SwfParser2()
		{

		}
		//-----------------------------------------------------------------------
		const std::string& SwfParser2::getExtension() const
		{
			static std::string ext = ".swf";
			return ext;
		}
		//-----------------------------------------------------------------------
		File* SwfParser2::parse(FileStream* stream)
		{
			mCurrentStream = stream;

			if(!parseHeader())
			{
				return NULL;
			}

			mCurrentFile = new File(stream->getFilename());

			mMainMovieClip = new MovieClipResource("__RESERVED__");
			mTimeline = new Timeline;
			mCurrentKeyframe = new Keyframe;

			while(mReadPos < mFileLength)
			{
				readTag();
			}

			delete[] mBuffer;

			mCurrentFile->setHeader(mHeader);
			mCurrentFile->setScriptEngine("AS3ScriptEngine");

			mMainMovieClip->setTimeline(mTimeline);
			mCurrentFile->setMainMovieClip(mMainMovieClip);

			return mCurrentFile;
		}
		//-----------------------------------------------------------------------
		bool SwfParser2::parseHeader()
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
				// TODO: implement ZLIB decompression
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
		void SwfParser2::readTag()
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
				assert(!(mFileLength - mReadPos) && "Unread bytes after TT_End tag");
				break;

			case TT_ShowFrame:
				handleShowFrame();
				break;

			case TT_DefineShape:
				handleDefineShape();
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

			case TT_SymbolClass:
				handleSymbolClass();
				break;

			case TT_DoABC:
				{
					uint start_pos = mReadPos;

					UI32 flags = readU32();
					String name = readString();

					uint abc_len = length - (mReadPos-start_pos);

					char* abc_buf = new char[abc_len];
					readByteBlock(abc_buf, abc_len);

					mCurrentFile->addResource(new ScriptResource("Script", abc_buf, abc_len));
				}
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
		UI8 SwfParser2::readU8()
		{
			return mBuffer[mReadPos++];
		}
		//-----------------------------------------------------------------------
		UI16 SwfParser2::readU16()
		{
			return readU8() | readU8()<<8;
		}
		//-----------------------------------------------------------------------
		UI32 SwfParser2::readU32()
		{
			return readU8() | readU8()<<8 | readU8()<<16 | readU8()<<24;
		}
		//-----------------------------------------------------------------------
		RECT SwfParser2::readRect()
		{
			RECT result;
			UI32 n = readUBits(5);
			result.xmin = readSBits(n);
			result.xmax = readSBits(n);
			result.ymin = readSBits(n);
			result.ymax = readSBits(n);

			return result;
		}
		//-----------------------------------------------------------------------
		COLOR SwfParser2::readColor(const bool& alpha)
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
		MATRIX SwfParser2::readMatrix()
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
				result.cx = readSBits(num_bits);
				result.cy = readSBits(num_bits);
			}

			// TRANSLATION
			num_bits = readUBits(5);
			result.tx = readSBits(num_bits);
			result.ty = readSBits(num_bits);

			return result;
		}
		//-----------------------------------------------------------------------
		CXFORM SwfParser2::readCxForm(const bool& alpha)
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
		String SwfParser2::readString()
		{
			String result;
			UI8 cur_char = readU8();
			while(cur_char != 0)
			{
				result.append(1, cur_char);
				cur_char = readU8();
			}

			return result;
		}
		//-----------------------------------------------------------------------
		void SwfParser2::fillReadBits()
		{
			mBitBuf = readU8();
			mBitPos = 8;
		}
		//-----------------------------------------------------------------------
		void SwfParser2::resetReadBits()
		{
			mBitPos = mBitBuf = 0;
		}
		//-----------------------------------------------------------------------
		UI32 SwfParser2::readUBits(UI32 n)
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
		int SwfParser2::readSBits(UI32 n)
		{
			assert(n <= 32);
			int num = readUBits(n);
			int shift = 32 - n;
			return (num << shift) >> shift; // sign extend
		}
		//-----------------------------------------------------------------------
		void SwfParser2::readByteBlock(char* buf, UI32 n)
		{
			memcpy(buf, &mBuffer[mReadPos], n);
			mReadPos += n;
		}
		//-----------------------------------------------------------------------
	}
}
