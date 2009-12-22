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
#pragma once

#include "vtxFile.h"
#include "vtxFileParser.h"

#include "vtxswfParserTypes.h"

#include "vtxswfContourElement.h"
#include "vtxswfSubShape.h"
#include "vtxswfSubLine.h"
#include "vtxSubshapeResource.h"

namespace vtx
{
	namespace swf
	{
		class SwfParser2 : public FileParser
		{
		public:
			typedef std::stack<MovieClipResource*> MovieClipStack;

			SwfParser2();
			virtual ~SwfParser2();

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

			bool parseHeader();
			void readTag();

			void handleShowFrame();
			void handleDefineShape();
			void handlePlaceObject2();
			void handleDefineButton2();
			void handleSymbolClass();

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