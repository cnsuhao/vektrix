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

#include "vtxswfButtonHandler.h"

#include "vtxFile.h"
#include "vtxCXForm.h"
#include "vtxMatrix.h"
#include "vtxButtonResource.h"
#include "vtxButtonState.h"
#include "vtxStringHelper.h"
#include "vtxCreateObjectEvent.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		void ButtonHandler::handleButton(TAG* swfTag, File* file)
		{
			if(swfTag->id == ST_DEFINEBUTTON)
			{

			}
			else if(swfTag->id == ST_DEFINEBUTTON2)
			{
				U32 oldTagPos;
				U32 offsetpos;
				//U32 condition;

				oldTagPos = swf_GetTagPos(swfTag);

				// scan DefineButton2 Record
				uint btn_id = swf_GetU16(swfTag);	// Character ID
				swf_GetU8(swfTag);	// Flags;

				ButtonResource* button = new ButtonResource(StringHelper::toString(btn_id));

				offsetpos = swf_GetTagPos(swfTag);  // first offset
				swf_GetU16(swfTag);

				U8 state = swf_GetU8(swfTag);
				while(state)	// state  -> parse ButtonRecord
				{
					ButtonState* btn_state = new ButtonState;
					String id = StringHelper::toString(swf_GetU16(swfTag));
					// debug
					uint layer = swf_GetU16(swfTag);

					MATRIX m;
					CXFORM cx;
					swf_GetMatrix(swfTag, &m);
					swf_GetCXForm(swfTag, &cx, 1);

					Matrix matrix(
						m.sx/65536.0f, -m.r1/65536.0f, m.tx/20.0f, 
						-m.r0/65536.0f, m.sy/65536.0f, m.ty/20.0f);

					CXForm cxform(
						cx.r0/256.0f, cx.g0/256.0f, cx.b0/256.0f, cx.a0/256.0f, 
						cx.r1/256.0f, cx.g1/256.0f, cx.b1/256.0f, cx.a1/256.0f);

					btn_state->addEvent(new CreateObjectEvent(NULL, id, layer, matrix, cxform));

					if(state & 1)
					{
						button->setState(btn_state, ButtonResource::SID_UP);
					}
					if(state & 2)
					{
						button->setState(btn_state, ButtonResource::SID_OVER);
					}
					if(state & 4)
					{
						button->setState(btn_state, ButtonResource::SID_DOWN);
					}
					if(state & 8)
					{
						button->setState(btn_state, ButtonResource::SID_HIT_AREA);
					}

					state = swf_GetU8(swfTag);
				}

				swf_SetTagPos(swfTag, oldTagPos);

				file->addResource(button);
			}

			//std::cout << "BUTTON" << std::endl;
			//swf_SetTagPos(swfTag, 0);
			//swf_GetU16(swfTag); // id
			//while(true)
			//{
			//	U8 flags = swf_GetU8(swfTag);
			//	if(!flags)
			//	{
			//		std::cout << "break" << std::endl;
			//		break;
			//	}
			//	U16 id = swf_GetU16(swfTag);
			//	U16 depth = swf_GetU16(swfTag);
			//	char event[80];
			//	sprintf(event, "%s%s%s%s", 
			//		(flags&BS_HIT)?"[hit]":"",
			//		(flags&BS_DOWN)?"[down]":"",
			//		(flags&BS_OVER)?"[over]":"",
			//		(flags&BS_UP)?"[up]":"");
			//	if(flags&0xf0) {
			//		printf("Show %d at depth %d for %s flags=%02x\n", id, depth, event, flags);
			//	} else {
			//		printf("Show %d at depth %d for %s\n", id, depth, event);
			//	}
			//	swf_GetMatrix(swfTag, NULL);  // matrix
			//}
		}
		//-----------------------------------------------------------------------
	}
}
