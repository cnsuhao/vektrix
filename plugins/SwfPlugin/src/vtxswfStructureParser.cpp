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

#include "vtxswfStructureParser.h"
#include "vtxswfParser.h"

#include "vtxButtonResource.h"
#include "vtxButtonState.h"
#include "vtxCreateObjectEvent.h"
#include "vtxCXForm.h"
#include "vtxKeyframe.h"
#include "vtxMatrix.h"
#include "vtxMoveObjectEvent.h"
#include "vtxMovieClipResource.h"
#include "vtxStringHelper.h"
#include "vtxTimeline.h"
#include "vtxswfStructParserHelper.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		StructureParser::StructureParser()
			: mMovieClipFrameIndex(0), 
			mCurrentMovieClip(NULL), 
			mMovieClipTimeline(NULL), 
			mMainFrameIndex(0), 
			mMainMovieClip(NULL), 
			mMainTimeline(NULL), 
			mCurrentKeyframe(NULL)
		{
			mMainMovieClip = new MovieClipResource("__MainMovieClip__");
			mMainTimeline = new Timeline;
			mCurrentKeyframe = new Keyframe;

			mMainMovieClip->setTimeline(mMainTimeline);
			//mParser->getCurrentFile()->setMainMovieClip(mMainMovieClip);
		}
		//-----------------------------------------------------------------------
		StructureParser::~StructureParser()
		{
			// release empty frame
			if(mCurrentKeyframe)
			{
				delete mCurrentKeyframe;
				mCurrentKeyframe = NULL;
			}
		}
		//-----------------------------------------------------------------------
		void StructureParser::handleDefineButton2(const TagTypes& tag_type, MemoryBlockReader& tag_reader, SwfParser* parser)
		{
			UI16 btn_id = tag_reader.readUI16();
			UI8 menu = tag_reader.readUI8();
			UI16 action_offset = tag_reader.readUI16();

			ButtonResource* button = new ButtonResource(StringHelper::toString(btn_id));

			UI8 state = tag_reader.readUI8();
			while(state)	// state  -> parse ButtonRecord
			{
				ButtonState* btn_state = new ButtonState;
				String id = StringHelper::toString(tag_reader.readUI16());
				uint layer = tag_reader.readUI16();

				MATRIX m;
				ParserHelper::readMatrix(tag_reader, m);

				CXFORM cx;
				ParserHelper::readCXform(tag_reader, true, cx);

				Matrix matrix;
				CXForm cxform;
				btn_state->addEvent(new CreateObjectEvent(NULL, id, layer, matrix, cxform));

				if(state & 1) button->setState(btn_state, ButtonResource::SID_UP);
				if(state & 2) button->setState(btn_state, ButtonResource::SID_OVER);
				if(state & 4) button->setState(btn_state, ButtonResource::SID_DOWN);
				if(state & 8) button->setState(btn_state, ButtonResource::SID_HIT_AREA);

				state = tag_reader.readUI8();
			}

			parser->getCurrentFile()->addResource(button);
		}
		//-----------------------------------------------------------------------
		void StructureParser::handleDefineSprite(const TagTypes& tag_type, MemoryBlockReader& tag_reader, SwfParser* parser)
		{
			UI16 sprite_id = tag_reader.readUI16();
			UI16 frame_count = tag_reader.readUI16();
			mCurrentMovieClip = new MovieClipResource(StringHelper::toString(sprite_id));
			mMovieClipTimeline = new Timeline;
		}
		//-----------------------------------------------------------------------
		void StructureParser::handlePlaceObject2(const TagTypes& tag_type, MemoryBlockReader& tag_reader, SwfParser* parser)
		{
			UI8 has_clip_actions =	(UI8)tag_reader.readUnsignedBits(1);
			UI8 has_clip_depth =	(UI8)tag_reader.readUnsignedBits(1);
			UI8 has_name =			(UI8)tag_reader.readUnsignedBits(1);
			UI8 has_ratio =			(UI8)tag_reader.readUnsignedBits(1);
			UI8 has_color =			(UI8)tag_reader.readUnsignedBits(1);
			UI8 has_matrix =		(UI8)tag_reader.readUnsignedBits(1);
			UI8 has_character =		(UI8)tag_reader.readUnsignedBits(1);
			UI8 has_move =			(UI8)tag_reader.readUnsignedBits(1);

			UI16 depth = tag_reader.readUI16();

			Matrix matrix;
			CXForm cxform;

			UI16 character = 0;
			if(has_character)
			{
				character = tag_reader.readUI16();
			}

			if(has_matrix)
			{
				MATRIX m;
				ParserHelper::readMatrix(tag_reader, m);
			}

			if(has_color)
			{
				CXFORM cx;
				ParserHelper::readCXform(tag_reader, true, cx);
			}

			UI16 ratio = 0;
			if(has_ratio)
				ratio = tag_reader.readUI16();

			String name = "";
			if(has_name)
				name = tag_reader.readString(true);

			UI16 clip_depth = 0;
			if(has_clip_depth)
				clip_depth = tag_reader.readUI16();

			if(has_clip_actions)
			{
				VTX_DEBUG_FAIL("Currently not supporting clip actions");
			}

			if(has_move)
				mCurrentKeyframe->addEvent(new MoveObjectEvent(NULL, depth, matrix, cxform));
			else if(has_character)
			{
				String id = StringHelper::toString(character);
				mCurrentKeyframe->addEvent(new CreateObjectEvent(NULL, id, depth, matrix, cxform, name));
			}
		}
		//-----------------------------------------------------------------------
		void StructureParser::handleShowFrame(const TagTypes& tag_type, MemoryBlockReader& tag_reader, SwfParser* parser)
		{
			// main timeline
			if(!mCurrentMovieClip)
			{
				++mMainFrameIndex;

				//if(mCurrentKeyframe->getEventCount())
				{
					mCurrentKeyframe->setIndex(mMainFrameIndex);
					mMainTimeline->addKeyframe(mCurrentKeyframe);
					mCurrentKeyframe = NULL;
				}

				if(mMainFrameIndex < parser->getHeader().frames)
				{
					mCurrentKeyframe = new Keyframe;
				}
			}
			// movieclip timeline
			else
			{
				++mMovieClipFrameIndex;

				if(mCurrentKeyframe->getEventCount())
				{
					mCurrentKeyframe->setIndex(mMovieClipFrameIndex);
					mMovieClipTimeline->addKeyframe(mCurrentKeyframe);
					mCurrentKeyframe = new Keyframe;
				}
			}
		}
		//-----------------------------------------------------------------------
		void StructureParser::handleEnd(const TagTypes& tag_type, MemoryBlockReader& tag_reader, SwfParser* parser)
		{
			// denotes the end of a movieclip definition
			if(mCurrentMovieClip)
			{
				mCurrentMovieClip->setTimeline(mMovieClipTimeline);
				parser->getCurrentFile()->addResource(mCurrentMovieClip);
				mMovieClipFrameIndex = 0;
				mCurrentMovieClip = NULL;
			}
			// denotes the end of the entire swf file
			else
			{
				VTX_DEBUG_ASSERT(parser->getMemoryBlock().available()==0, "Unread bytes after TT_End tag, this is a bad thing.");
			}
		}
		//-----------------------------------------------------------------------
	}
}
