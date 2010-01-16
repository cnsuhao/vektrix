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

#ifndef __vtxswfParser_H__
#define __vtxswfParser_H__

#include "vtxFile.h"
#include "vtxFileParser.h"
#include "vtxSubshapeResource.h"

#include "vtxswfParserTypes.h"
#include "vtxswfContourElement.h"
#include "vtxswfSubShape.h"
#include "vtxswfSubLine.h"

namespace vtx
{
	namespace swf
	{
		class SwfParser : public FileParser
		{
		public:
			typedef std::stack<MovieClipResource*> MovieClipStack;

			SwfParser();
			virtual ~SwfParser();

			const std::string& getExtension() const;
			File* parse(FileStream* stream);

		protected:
			bool mCompressed;
			uint mReadPos;
			char* mBuffer;

			int mBitPos;
			int mBitBuf;

			UI32 mFileLength;
			File::FileHeader mHeader;

			File* mCurrentFile;
			FileStream* mCurrentStream;

			// shapes
			// -> FLASH
			FillstyleList2 mFillstyleArray; // the original flash fillstyles
			LinestyleList2 mLinestyleArray; // the original flash linestyles
			ShapeElementList mShapeElements; // the original flash shape elements
			// -> VEKTRIX
			FillstyleMap mFillstyles; // only the USED! fillstyles
			LinestyleMap mLinestyles; // only the USED! linestyles
			ContourChunkMap mChunkLists;
			SubShapeList mSubShapeList; // the sub-shapes
			SubLineList mSubLineList; // the sub-lines

			// movieclips
			MovieClipResource* mCurrentMovieClip;

			// main movieclip
			uint mMainFrameIndex;
			MovieClipResource* mMainMovieClip;
			Timeline* mTimeline;
			Keyframe* mCurrentKeyframe;

			void resetData();

			bool parseHeader();
			void readTag();

			void handleShowFrame();
			void handleDefineShape(const TagTypes& type);
			void handlePlaceObject2();
			void handleDefineButton2();
			void handleSymbolClass();

			void parseFillstyleArray(const TagTypes& type);
			void parseLinestyleArray(const TagTypes& type);

			// reading
			void getFlashStyles();
			void getFlashChunks();
			// processing
			void generateSubshapes();
			void generateSublines();
			// writing
			void writeFillstyles(const UI16& shape_id);
			void writeSubshapes(const UI16& shape_id, ShapeResource* shape_resource);

			void debug_contour_element(const ContourElement& element, FILE* file);
			void debug_shape_element(const SubshapeResource::ShapeElement& element, FILE* file);

			UI8 readU8();
			UI16 readU16();
			UI32 readU32();

			RECT readRect();
			COLOR readColor(const bool& alpha = false);
			MATRIX readMatrix();
			CXFORM readCxForm(const bool& alpha = false);
			String readString();

			void fillReadBits();
			void resetReadBits();
			UI32 readUBits(UI32 n);
			int readSBits(UI32 n);
			void readByteBlock(char* buf, UI32 n);
		};
	}
}

#endif
