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
#include "vtxswfScriptResource.h"

#include "vtxButtonResource.h"
#include "vtxButtonState.h"
#include "vtxCreateObjectEvent.h"
#include "vtxCXForm.h"
#include "vtxExecuteScriptEvent.h"
#include "vtxKeyframe.h"
#include "vtxMatrix.h"
#include "vtxMoveObjectEvent.h"
#include "vtxMovieClipResource.h"
#include "vtxRemoveObjectEvent.h"
#include "vtxScriptResource.h"
#include "vtxStringHelper.h"
#include "vtxTimeline.h"

#include "vtxLogManager.h"

namespace vtx { namespace swf {
	//-----------------------------------------------------------------------
	StructureParser::StructureParser(SwfParser* parser) 
		: mParser(parser), 
		// generic movieclips
		mMovieClipFrameIndex(0), 
		mCurrentMovieClip(NULL), 
		mMovieClipTimeline(NULL), 
		mMovieClipKeyframe(NULL), 
		// main movieclip
		mMainFrameIndex(0), 
		mMainMovieClip(NULL), 
		mMainTimeline(NULL), 
		mMainKeyframe(NULL)
	{
		mMainMovieClip = new MovieClipResource("0");
		mMainTimeline = new Timeline;
		mMainKeyframe = new Keyframe;

		mCurrKeyframe = mMainKeyframe;

		mMainMovieClip->setTimeline(mMainTimeline);
		mParser->getCurrentFile()->setMainMovieClip(mMainMovieClip);
	}
	//-----------------------------------------------------------------------
	StructureParser::~StructureParser()
	{
		// release empty frames
		if(mMainKeyframe)
		{
			delete mMainKeyframe;
			mMainKeyframe = NULL;
		}
	}
	//-----------------------------------------------------------------------
	void StructureParser::handleDefineButton2()
	{
		UI16 btn_id = mParser->readU16();
		UI8 menu = mParser->readU8();
		UI16 action_offset = mParser->readU16();

		ButtonResource* button = new ButtonResource(StringHelper::toString(btn_id));

		// parse button records
		UI8 state = mParser->readU8();
		while(state)
		{
			ButtonState* btn_state = new ButtonState;
			String id = StringHelper::toString(mParser->readU16());
			uint layer = mParser->readU16();

			MATRIX m = mParser->readMatrix();
			CXFORM cx = mParser->readCxForm(true);

			Matrix matrix(
				m.sx/65536.0f, m.cx/65536.0f, m.tx/20.0f, 
				m.cy/65536.0f, m.sy/65536.0f, m.ty/20.0f);

			CXForm cxform(
				cx.mul_red/256.0f, cx.mul_green/256.0f, cx.mul_blue/256.0f, cx.mul_alpha/256.0f, 
				cx.add_red/256.0f, cx.add_green/256.0f, cx.add_blue/256.0f, cx.add_alpha/256.0f);

			Resource* res = mParser->getCurrentFile()->getResource(id);
			btn_state->addEvent(new CreateObjectEvent(res, layer-1, matrix, cxform));

			if(state & 1) button->setState(btn_state, ButtonResource::SID_UP);
			if(state & 2) button->setState(btn_state, ButtonResource::SID_OVER);
			if(state & 4) button->setState(btn_state, ButtonResource::SID_DOWN);
			if(state & 8) button->setState(btn_state, ButtonResource::SID_HIT_AREA);

			state = mParser->readU8();
		}

		mParser->getCurrentFile()->addResource(button);
	}
	//-----------------------------------------------------------------------
	void StructureParser::handleDefineSprite()
	{
		VTX_WARN("MovieClip START");
		UI16 sprite_id = mParser->readU16();
		UI16 frame_count = mParser->readU16();
		mCurrentMovieClip = new MovieClipResource(StringHelper::toString(sprite_id));
		mMovieClipTimeline = new Timeline;
		mMovieClipKeyframe = new Keyframe;

		mCurrKeyframe = mMovieClipKeyframe;
	}
	//-----------------------------------------------------------------------
	void StructureParser::handlePlaceObject(const uint& tag_start, const UI32& length)
	{
		UI16 character = mParser->readU16();
		UI16 depth = mParser->readU16();

		MATRIX m = mParser->readMatrix();
		Matrix matrix = Matrix(
			m.sx/65536.0f, m.cx/65536.0f, m.tx/20.0f, 
			m.cy/65536.0f, m.sy/65536.0f, m.ty/20.0f);

		if(mParser->getReadPosition() - tag_start - length)
			mParser->readCxForm();
	}
	//-----------------------------------------------------------------------
	void StructureParser::handlePlaceObject2()
	{
		UI8 flags = mParser->readU8();
		UI16 depth = mParser->readU16();

		Matrix matrix;
		CXForm cxform;

		UI16 character = 0;
		if(flags & POF_HasCharacter)
		{
			character = mParser->readU16();
		}

		if(flags & POF_HasMatrix)
		{
			MATRIX m = mParser->readMatrix();
			matrix = Matrix(
				m.sx/65536.0f, m.cx/65536.0f, m.tx/20.0f, 
				m.cy/65536.0f, m.sy/65536.0f, m.ty/20.0f);
		}

		if(flags & POF_HasColorTransform)
		{
			CXFORM cx = mParser->readCxForm(true);
			cxform = CXForm(
				cx.mul_red/256.0f, cx.mul_green/256.0f, cx.mul_blue/256.0f, cx.mul_alpha/256.0f, 
				cx.add_red/256.0f, cx.add_green/256.0f, cx.add_blue/256.0f, cx.add_alpha/256.0f);
		}

		UI16 ratio = 0;
		if(flags & POF_HasRatio)
		{
			ratio = mParser->readU16();
		}

		String name = "";
		if(flags & POF_HasName)
		{
			name = mParser->readString();
		}

		UI16 clip_depth = 0;
		if(flags & POF_HasClipDepth)
		{
			clip_depth = mParser->readU16();
		}

		if(flags & POF_HasClipActions)
		{
			// reserved
			mParser->readU16();

			// AllEventFlags
			if(mParser->getSwfVersion() > 5)
			{
				mParser->readU32();
			}
			else
			{
				mParser->readU16();
			}

			UI32 clip_action_record_flags;
			if(mParser->getSwfVersion() > 5)
			{
				clip_action_record_flags = mParser->readU32();
			}
			else
			{
				clip_action_record_flags = mParser->readU16();
			}

			while(clip_action_record_flags)
			{
				UI32 action_record_size = mParser->readU32();

				mParser->skip(action_record_size);

				if(mParser->getSwfVersion() > 5)
				{
					clip_action_record_flags = mParser->readU32();
				}
				else
				{
					clip_action_record_flags = mParser->readU16();
				}
			}
		}

		if(flags & POF_Move)
		{
			// move
			mCurrKeyframe->addEvent(new MoveObjectEvent(depth, matrix, cxform));
			VTX_WARN("Move Object %d", depth);
		}
		else if(flags & POF_HasCharacter)
		{
			// place
			String id = StringHelper::toString(character);
			Resource* res = mParser->getCurrentFile()->getResource(id);
			mCurrKeyframe->addEvent(new CreateObjectEvent(res, depth, matrix, cxform, name));
			VTX_WARN("Create Object %s", id.c_str());
		}
	}
	//-----------------------------------------------------------------------
	void StructureParser::handleRemoveObject2()
	{
		UI16 depth = mParser->readU16();
		mCurrKeyframe->addEvent(new RemoveObjectEvent(depth));
	}
	//-----------------------------------------------------------------------
	void StructureParser::handleShowFrame()
	{
		// main timeline
		if(!mCurrentMovieClip)
		{
			VTX_WARN("Main Showframe %d events", mMainKeyframe->getEventCount());

			++mMainFrameIndex;

			//if(mCurrentKeyframe->getEventCount())
			{
				mMainKeyframe->setIndex(mMainFrameIndex);
				mMainTimeline->addKeyframe(mMainKeyframe);
				mMainKeyframe = NULL;
			}

			if(mMainFrameIndex < mParser->getHeader().frames)
			{
				mMainKeyframe = new Keyframe;
				mCurrKeyframe = mMainKeyframe;
			}
		}
		// movieclip timeline
		else
		{
			VTX_WARN("MovieClip Showframe %d events", mMovieClipKeyframe->getEventCount());

			++mMovieClipFrameIndex;

			//if(mCurrentKeyframe->getEventCount())
			{
				mMovieClipKeyframe->setIndex(mMovieClipFrameIndex);
				mMovieClipTimeline->addKeyframe(mMovieClipKeyframe);
				mMovieClipKeyframe = new Keyframe;
				mCurrKeyframe = mMainKeyframe;
			}
		}
	}
	//-----------------------------------------------------------------------
	void StructureParser::handleEnd()
	{
		// end of a movieclip definition
		if(mCurrentMovieClip)
		{
			VTX_WARN("MovieClip END");
			mCurrentMovieClip->setTimeline(mMovieClipTimeline);
			mParser->getCurrentFile()->addResource(mCurrentMovieClip);
			mMovieClipFrameIndex = 0;
			mCurrentMovieClip = NULL;
		}
		// end of the entire swf file
		else
		{
			VTX_WARN("Main END");
			int unread_bytes = mParser->getFileLength() - mParser->getReadPosition();
			if(unread_bytes)
				VTX_EXCEPT("%d unread bytes after TT_End tag", unread_bytes);
		}
	}
	//-----------------------------------------------------------------------
	void StructureParser::handleDefineScalingGrid()
	{
		UI16 id = mParser->readU16();
		RECT grid = mParser->readRect();

		Resource* res = mParser->getCurrentFile()->getResource(StringHelper::toString(id));
		DisplayResource* display_res = static_cast<DisplayResource*>(res);
		RectF scale9grid(
			grid.xmin/20.0f, grid.ymin/20.0f, 
			grid.xmax/20.0f, grid.ymax/20.0f);

		display_res->setScalingGrid(scale9grid);
	}
	//-----------------------------------------------------------------------
	void StructureParser::handleDoABC(const TagTypes& tag_type, const uint& tag_length, SwfParser* parser)
	{
		const uint& read_pos = parser->getReadPosition();
		uint start_pos = read_pos;

		UI32 flags = parser->readU32();
		String name = parser->readString();

		uint abc_len = tag_length - (read_pos - start_pos);

		char* abc_buf = new char[abc_len];
		parser->readByteBlock(abc_buf, abc_len);

		String script_name = "Frame" + StringHelper::toString(mMainFrameIndex) + "_Script";
		ScriptResource* script = new ScriptResource(script_name, abc_buf, abc_len);
		parser->getCurrentFile()->addResource(script);

		mCurrKeyframe->addEvent(new ExecuteScriptEvent(script));
	}
	//-----------------------------------------------------------------------
	void StructureParser::handleSymbolClass(const TagTypes& tag_type, const uint& tag_length, SwfParser* parser)
	{
		UI16 num_symbols = parser->readU16();

		Resource* res = parser->getCurrentFile()->getResource("Frame0_Script");
		ScriptResource* swf_as3_script = static_cast<ScriptResource*>(res);

		for(UI16 i=0; i<num_symbols; ++i)
		{
			UI16 id = parser->readU16();

			String name = parser->readString();

			if(id == 0)
			{
				parser->getHeader().script_root_class = name;
			}
			//else
			{
				if(swf_as3_script)
				{
					uint seperator = name.find_last_of('.');
					String class_name, package;

					if(seperator != String::npos)
					{
						class_name = name.substr(seperator+1, name.length()-seperator-1);
						package = name.substr(0, seperator);
					}
					else
					{
						class_name = name;
					}

					swf_as3_script->addSymbol(StringHelper::toString(id), class_name, package);
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	bool StructureParser::isParsingMovieClip() const
	{
		return (mCurrentMovieClip != NULL);
	}
	//-----------------------------------------------------------------------
}}
