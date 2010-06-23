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
#include "vtxswfImageParser.h"
#include "vtxswfShapeParser.h"
#include "vtxswfStructureParser.h"
#include "vtxFileStream.h"
#include "vtxLogManager.h"
#include "vtxStringHelper.h"
#include "vtxswfStructParserHelper.h"

#ifdef USE_ZLIB
#include "zlib/zlib.h"
#endif

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfParser::SwfParser() 
			: mCompressed(false),
			mBuffer(NULL),
			mFileLength(0), 
			mCurrentFile(NULL), 
			mCurrentStream(NULL)
		{}
		//-----------------------------------------------------------------------
		SwfParser::~SwfParser()
		{}
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

			if(!parseHeader())
			{
				return;
			}

			while(mMemoryBlockReader.available())
			{
				readTag();
			}
			mCurrentFile->setHeader(mHeader);

			delete[] mBuffer;
		}
		//-----------------------------------------------------------------------
		void SwfParser::resetData()
		{
			mCompressed = false;
			mBuffer = NULL;
			mFileLength = 0;
			mCurrentFile = NULL;
			mCurrentStream = NULL;
			mMemoryBlockReader.init(NULL, 0);
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
				uchar* readBuf = (uchar*)alloca(chunk_size);
				mBuffer = new uchar[mFileLength];

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

					mMemoryBlockReader.init(mBuffer, bufStart);

				} while(ret != Z_STREAM_END);

				// clean up
				(void)inflateEnd(&zlib_stream);
#else
				error("Unable to load compressed SWF file (SWF plugin was compiled without zlib support).");
				return false;
#endif
			}
			else
			{
				mBuffer = new uchar[mFileLength];
				mCurrentStream->read(mBuffer, mFileLength);
				mMemoryBlockReader.init(mBuffer, mFileLength);
			}

			RECT dimensions;
			ParserHelper::readRect(mMemoryBlockReader, dimensions);

			mHeader.width		= (uint)((dimensions.xmax - dimensions.xmin)/20.0f);
			mHeader.height		= (uint)((dimensions.ymax - dimensions.ymin)/20.0f);

			UI16 fps			= mMemoryBlockReader.readUI16();
			UI16 frame_count	= mMemoryBlockReader.readUI16();

			mHeader.version		= "test_version";
			mHeader.fps			= fps/256;
			mHeader.frames		= frame_count;

			return true;
		}
		//-----------------------------------------------------------------------
		void SwfParser::readTag()
		{
			TagTypes tag_type;
			size_t tag_len = 0;

			ParserHelper::readTagHeader(mMemoryBlockReader, tag_type, tag_len);
			MemoryBlockReader tagReader = MemoryBlockReader(mMemoryBlockReader.getBufferCurrentPtr(), tag_len);

			switch(tag_type)
			{
			//case TT_RemoveObject:
			//	pTag = new SwfTagRemoveObject(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_DefineButton:
			//	pTag = new SwfTagButton(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_DefineSound:
			//	pTag = new SwfTagDefineSound(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_StartSound:
			//	pTag = new SwfTagStartSound(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_DefineButtonSound:
			//	pTag = new SwfTagButtonSound(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_DefineButtonCXform:
			//	pTag = new SwfTagButtonCXform(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_FrameLabel:
			//	pTag = new SwfTagFrameLabel(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_DefineMorphShape:
			//	pTag = new SwfTagMorphShape(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_ExportAssets:
			//	pTag = new SwfTagExportAssets(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_ImportAssets:
			//	pTag = new SwfTagImportAssets(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_DoInitAction:
			//	pTag = new SwfTagDoInitAction(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_ImportAssets2:
			//	pTag = new SwfTagImportAssets2(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_DefineFontAlignment:
			//	pTag = new SwfTagFontAlignment(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_Scale9Grid:
			//	pTag = new SwfTagScale9Grid(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_DefineMorphShape2:
			//	pTag = new SwfTagMorphShape2(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_DefineFontName:
			//	pTag = new SwfTagFontName(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_StartSound2:
			//	pTag = new SwfTagStartSound2(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_DoAction:
			//	pTag = new SwfTagDoAction(length, (uchar*)&mBuffer[mReadPos]);
			//	break;

			//
			// STREAMING AUDIO TAGS
			//
			//case TT_SoundStreamHead:
			//	pTag = new SwfTagSoundStreamHead(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_SoundStreamHead2:
			//	pTag = new SwfTagSoundStreamHead2(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_SoundStreamBlock:
			//	pTag = new SwfTagSoundStreamBlock(length, (uchar*)&mBuffer[mReadPos]);
			//	break;

			//
			// STREAMING VIDEO TAGS
			//
			//case TT_DefineVideoStream:
			//	pTag = new SwfTagDefineVideoStream(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_VideoFrame:
			//	pTag = new SwfTagVideoFrame(length, (uchar*)&mBuffer[mReadPos]);
			//	break;

			//
			// DOCUMENT TAGS
			//
			//case TT_SetTabIndex:
			//	pTag = new SwfTagSetTabIndex(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_FileAttributes:
			//	pTag = new SwfTagFileAttributes(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_EnableDebugger:
			//	pTag = new SwfTagEnableDebugger(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_EnableDebugger2:
			//	pTag = new SwfTagEnableDebugger2(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_DebugId:
			//	pTag = new SwfTagDebugId(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_ProductInfo:
			//	pTag = new SwfTagProductInfo(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_Protect:
			//	pTag = new SwfTagProtect(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_SetBackgroundColor:
			//	pTag = new SwfTagSetBackgroundColor(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_MetaData:
			//	pTag = new SwfTagMetadata(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_DefineSceneAndFrameLabelData:
			//	pTag = new SwfTagDefineSceneFrameData(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_ScriptLimits:
			//	pTag = new SwfTagScriptLimits(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_FlashTypeSettings:
			//	pTag = new SwfTagFlashTypeSettings(length, (uchar*)&mBuffer[mReadPos]);
			//	break;

			//
			// ACTIONSCRIPT TAGS
			//
			//case TT_DefineBinaryData:
			//	pTag = new SwfTagUnknownTag(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			case TT_SymbolClass:
				mScriptParser.handleSymbolClass(tag_type, tagReader, this);
				break;
			case TT_DoABCDefine:
			case TT_DoABC:
				mScriptParser.handleDoABC(tag_type, tagReader, this);
				break;

			//
			// FONT TAGS
			//
			//case TT_DefineFontInfo:
			//	pTag = new SwfTagFontInfo(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_DefineFontInfo2:
			//	pTag = new SwfTagFontInfo2(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			//case TT_FreeCharacter:
			//	pTag = new SwfTagFreeCharacter(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			case TT_DefineFont:
			case TT_DefineFont2:
			case TT_DefineFont3:
			case TT_DefineFont4:
				mFontParser.handleDefineFont(tag_type, tagReader, this);
				break;

			//
			// TEXT TAGS
			//
			case TT_DefineText:
			case TT_DefineText2:
				mTextParser.handleDefineText(tag_type, tagReader, this);
				break;
			case TT_DefineEditText:
				mTextParser.handleDefineEditText(tag_type, tagReader, this);
				break;

			//
			// IMAGE TAGS
			//
			case TT_JPEGTables:
				mImageParser.handleJPEGTables(tag_type, tagReader, this);
				break;
			case TT_DefineBits:
			case TT_DefineBitsJPEG2:
			case TT_DefineBitsJPEG3:
			case TT_DefineBitsJPEG4:
				mImageParser.handleDefineBitsJPEG(tag_type, tagReader, this);
				break;
			case TT_DefineBitsLossless:
			case TT_DefineBitsLossless2:
				mImageParser.handleDefineBitsLossless(tag_type, tagReader, this);
				break;

			//
			// STRUCTURE TAGS
			//
			//case TT_RemoveObject2:
			//	pTag = new SwfTagRemoveObject2(length, (uchar*)&mBuffer[mReadPos]);
			//	break;
			case TT_End:
				mStructureParser.handleEnd(tag_type, tagReader, this);
				break;
			case TT_ShowFrame:
				mStructureParser.handleShowFrame(tag_type, tagReader, this);
				break;
			case TT_PlaceObject:
			case TT_PlaceObject2:
			case TT_PlaceObject3:
				mStructureParser.handlePlaceObject2(tag_type, tagReader, this);
				break;
			case TT_DefineSprite:
				mStructureParser.handleDefineSprite(tag_type, tagReader, this);
				break;
			case TT_DefineButton2:
				mStructureParser.handleDefineButton2(tag_type, tagReader, this);
				break;

			//
			// SHAPE TAGS
			//
			case TT_DefineShape:
			case TT_DefineShape2:
			case TT_DefineShape3:
			case TT_DefineShape4:
				mShapeParser.handleDefineShape(tag_type, tagReader, this);
				break;

			//
			// UNKNOWN TAGS
			//
			default:
				VTX_WARN("SWF tag type not implemented: %d", tag_type);
				break;
			}

			//
			// ERROR CHECKING
			//
			if(tagReader.available() != 0)
			{
				VTX_WARN("Not all bytes were read from the tag. type=%d, available=%d", tag_type, tagReader.available());
			}
			else
			{
				VTX_LOG("Parsed tag type=%d, len=%d", tag_type, tag_len);
			}

			mMemoryBlockReader.move(tag_len);
		}
		//-----------------------------------------------------------------------
	}
}
