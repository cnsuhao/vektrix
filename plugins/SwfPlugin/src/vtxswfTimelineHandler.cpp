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
#include "vtxswfTimelineHandler.h"

#include "vtxCXForm.h"
#include "vtxFile.h"
#include "vtxLogManager.h"
#include "vtxMatrix.h"
#include "vtxMovieClipResource.h"
#include "vtxMoveObjectEvent.h"
#include "vtxCreateObjectEvent.h"
#include "vtxStringHelper.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		TimelineHandler::TimelineHandler() 
		{

		}
		//-----------------------------------------------------------------------
		TimelineHandler::~TimelineHandler()
		{

		}
		//-----------------------------------------------------------------------
		void TimelineHandler::handleTimeline(TAG* swfTag, File* file)
		{
			bool isMovieClip = false;
			size_t frameIndex = 0;

			//timeline->clear();
			//keyframe->clear();

			Keyframe* keyframe = new Keyframe;
			Timeline* timeline = new Timeline;

			MovieClipResource* main_movieclip = new MovieClipResource("__RESERVED__");

			while(swfTag)
			{
				// following tags belong to a movieclip
				if(swfTag->id == ST_DEFINESPRITE)
				{
					isMovieClip = true;
				}
				// movieclip tags finished
				else if(swfTag->id == ST_END)
				{
					isMovieClip = false;
				}
				else if(!isMovieClip)
				{
					if(swfTag->id == ST_SHOWFRAME)
					{
						++frameIndex;

						if(keyframe->getEventCount())
						{
							keyframe->setIndex(frameIndex);
							timeline->addKeyframe(keyframe);

							keyframe = new Keyframe;
						}
					}
					else if(swfTag->id == ST_PLACEOBJECT2 || swfTag->id == ST_PLACEOBJECT3)
					{
						// get layer
						uint layer = swf_GetDepth(swfTag);

						// reset tag reading position
						swf_SetTagPos(swfTag, 0);

						// get flags
						U8 flags = swf_GetU8(swfTag);
						swf_GetU16(swfTag); //depth
						if(flags&2) swf_GetU16(swfTag); //id

						Matrix matrix;
						CXForm cxform;

						// matrix included
						if(flags&4)
						{
							MATRIX m;
							swf_GetMatrix(swfTag, &m);
							matrix = Matrix(
								m.sx/65536.0f, -m.r1/65536.0f, m.tx/20.0f, 
								-m.r0/65536.0f, m.sy/65536.0f, m.ty/20.0f);
						}

						// cxform included
						if(flags&8)
						{
							CXFORM cx;
							swf_GetCXForm(swfTag, &cx, 1);
							cxform = CXForm(
								cx.r0/256.0f, cx.g0/256.0f, cx.b0/256.0f, cx.a0/256.0f, 
								cx.r1/256.0f, cx.g1/256.0f, cx.b1/256.0f, cx.a1/256.0f);
						}

						if(swfTag->data[0]&1)
						{
							// move
							keyframe->addEvent(new MoveObjectEvent(layer, matrix, cxform));
						}
						else if(swfTag->data[0]&2)
						{
							// place
							std::string id = StringHelper::toString(swf_GetPlaceID(swfTag));

							keyframe->addEvent(new CreateObjectEvent(id, layer, matrix, cxform));
						}
					}
				}

				swfTag = swfTag->next;
			}// while(swfTag)

			//file->setTimeline(timeline);

			main_movieclip->setTimeline(timeline);
			file->setMainMovieClip(main_movieclip);
		}
		//-----------------------------------------------------------------------
	}
}
