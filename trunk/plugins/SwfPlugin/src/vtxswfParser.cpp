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

		while(getReadPosition() < mFileLength)
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
		DataReader::reset();

		mCompressed = false;
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

		// initialize DataReader
		init(mBuffer);

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
			length = readU32();

		const uint& tag_start = getReadPosition();

		switch(type)
		{
			// fonts
		case TT_DefineFont3:
				mFontParser->handleDefineFont(type, length, this);
			break;

			// images
		case TT_JPEGTables:
				mImageParser->handleJPEGTables(type, length, this);
			break;

		case TT_DefineBits:
		case TT_DefineBitsJPEG2:
		case TT_DefineBitsJPEG3:
		case TT_DefineBitsJPEG4:
				mImageParser->handleDefineBitsJPEG(type, length, this);
			break;

		case TT_DefineBitsLossless:
		case TT_DefineBitsLossless2:
				mImageParser->handleDefineBitsLossless(type, length, this);
			break;

			// shapes
		case TT_DefineShape:
		case TT_DefineShape2:
		case TT_DefineShape3:
		case TT_DefineShape4:
				mShapeParser->handleDefineShape(type, this);
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
				RGBA color = readRGBA();
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
				mTextParser->handleDefineText(type, length, this);
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
			skip(length);
			break;

		default:
			VTX_WARN("SWF tag type not implemented: %d", type);
			skip(length);
			break;
		}

		uint tag_end = tag_start + length;
		if(getReadPosition() != tag_end)
		{
			// something has gone wrong
			VTX_WARN("%d unread bytes after tag type: %d bytes: ", tag_end - getReadPosition(), type);			
			setReadPosition(tag_end);
		}
	}
	//-----------------------------------------------------------------------
}}
