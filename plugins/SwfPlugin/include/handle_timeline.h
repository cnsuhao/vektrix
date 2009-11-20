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

void handle_PlaceObject2(TAG* tag, FILE* file);
void handle_RemoveObject2(TAG* tag, FILE* file);
void handle_StartSound(TAG* tag, FILE* file);
//-----------------------------------------------------------------------
// main method
//-----------------------------------------------------------------------
void handle_timeline(TAG* tag, FILE* file)
{
	bool isSprite = false;
	fpos_t mFrameCountPos;
	fpos_t mEndPos;
	TAG* mRangeStart = tag;
	TAG* mRangeEnd = tag;
	unsigned int mFrameCount = 0;
	unsigned int mFrameIndex = 0;
	unsigned int mEventCount = 0;
	unsigned int mPreviousFrameIndex = 12345;

	// write TIMELINE tag
	unsigned int timeline_tag = ogreSwf::OBOE::ID_TIMELINE;
	fwrite(&timeline_tag, sizeof(unsigned int), 1, file);

	//store position of the frame count byte
	fgetpos(file, &mFrameCountPos);
	// write the framecount (currently ZERO!), we will overwrite this afterwards with the correct value
	fwrite(&mFrameCount, sizeof(unsigned int), 1, file);

	while(tag)
	{
		if(tag->id == ST_DEFINESPRITE)
		{
			isSprite = true;
		}
		else if(tag->id == ST_END)
		{
			if(!isSprite && mFrameIndex != mPreviousFrameIndex)
			{
				mEventCount = 0;

				// write the frame index and the number of events included
				printf("\n    Keyframe\n    {\n        Index: %d\n        Events: %d\n", mFrameIndex, mEventCount);
				fwrite(&mFrameIndex, sizeof(unsigned int), 1, file);
				fwrite(&mEventCount, sizeof(unsigned int), 1, file);

				// increase the frame count
				mFrameCount++;
				mRangeStart = tag;
			}
			isSprite = false;
		}
		else if(tag->id == ST_SHOWFRAME && !isSprite)
		{
			// advance the frame index and store it
			mFrameIndex++;
			mPreviousFrameIndex = mFrameIndex;

			// filter empty frames
			if(mEventCount != 0 || tag->next->id == ST_END)
			{
				// parse until here...
				mRangeEnd = tag;

				// write the frame index and the number of events included
				printf("\n    Keyframe\n    {\n        Index: %d\n        Events: %d\n", mFrameIndex, mEventCount);
				fwrite(&mFrameIndex, sizeof(unsigned int), 1, file);
				fwrite(&mEventCount, sizeof(unsigned int), 1, file);

				isSprite = false;

				// process the frame-events
				while(mRangeStart != mRangeEnd)
				{
					if(mRangeStart->id == ST_DEFINESPRITE)
					{
						isSprite = true;
					}
					else if(mRangeStart->id == ST_END)
					{
						isSprite = false;
					} 
					else if(mRangeStart->id == ST_PLACEOBJECT2 && !isSprite)
					{
						handle_PlaceObject2(mRangeStart, file);
					} 
					else if(mRangeStart->id == ST_REMOVEOBJECT2 && !isSprite)
					{
						handle_RemoveObject2(mRangeStart, file);
					}
					else if(mRangeStart->id == ST_STARTSOUND && !isSprite)
					{
						handle_StartSound(mRangeStart, file);
					}
					mRangeStart = mRangeStart->next;
				}

				// increase the frame count
				mFrameCount++;

				printf("    }\n");

				// set new start tag and reset the event count
				mRangeStart = tag;
				mEventCount = 0;
			}
		}
		// count the frame-events
		else if(!isSprite && (
			tag->id == ST_PLACEOBJECT2 || 
			tag->id == ST_REMOVEOBJECT2 || 
			tag->id == ST_STARTSOUND))
		{
			// increase the event count
			mEventCount++;
		}

		// go to the next tag
		tag = tag->next;
	}

	//store end position
	fgetpos(file, &mEndPos);
	//go to frame-count position
	fsetpos(file, &mFrameCountPos);
	//write the frame-count
	fwrite(&mFrameCount, sizeof(unsigned int), 1, file);
	//go to end position again
	fsetpos(file, &mEndPos);
}
//-----------------------------------------------------------------------
void handle_PlaceObject2(TAG* tag, FILE* file)
{
	unsigned int event_type = 0;

	if(tag->data[0]&1)
	{
		printf("\n        EID_MOVEOBJECT\n        {\n");
		event_type = ogreSwf::OBOE::EID_MOVEOBJECT;
	}
	else
	{
		printf("\n        EID_PLACEOBJECT\n        {\n");
		event_type = ogreSwf::OBOE::EID_PLACEOBJECT;
	}

	// write event-type tag
	fwrite(&event_type, sizeof(unsigned int), 1, file);

	// EID_PLACEOBJECT
	if(tag->data[0]&2)
	{
		unsigned int id = swf_GetPlaceID(tag);
		printf("            id: %d\n", id);

		// write flash id
		fwrite(&id, sizeof(unsigned int), 1, file);
	}

	unsigned int depth = swf_GetDepth(tag);
	printf("            depth: %d\n", depth);

	// write depth
	fwrite(&depth, sizeof(unsigned int), 1, file);

	U8 flags;
	MATRIX m;
	CXFORM cx;

	swf_SetTagPos(tag, 0);
	flags = swf_GetU8(tag);
	swf_GetU16(tag); //depth

	if(flags&2) swf_GetU16(tag); //id

	bool matrix_included = false;

	if(flags&4)
	{
		matrix_included = true;
		fwrite(&matrix_included, sizeof(bool), 1, file);

		swf_GetMatrix(tag,&m);

		printf("\n            Matrix:\n            {\n");
		printf("                %5.3f %5.3f %6.2f\n", m.sx/65536.0, m.r1/65536.0, m.tx/20.0);
		printf("                %5.3f %5.3f %6.2f\n            }\n", m.r0/65536.0, m.sy/65536.0, -m.ty/20.0);

		signed long matrix[6] = { 
			m.sx, -m.r1, m.tx, 
			-m.r0, m.sy, -m.ty };

			// write matrix
			fwrite(&matrix, sizeof(signed long[6]), 1, file);
	}
	else
	{
		matrix_included = false;
		fwrite(&matrix_included, sizeof(bool), 1, file);
	}

	bool cxform_included = false;

	if(flags&8)
	{
		cxform_included = true;
		fwrite(&cxform_included, sizeof(bool), 1, file);

		swf_GetCXForm(tag, &cx, 1);

		printf("\n            CXForm:\n            {\n                      r    g    b    a\n");
		printf("                mul %4.1f %4.1f %4.1f %4.1f\n", cx.r0/256.0, cx.g0/256.0, cx.b0/256.0, cx.a0/256.0);
		printf("                add %4d %4d %4d %4d\n            }\n        }\n", cx.r1, cx.g1, cx.b1, cx.a1);

		signed short cxform[8] = {
			cx.r0, cx.g0, cx.b0, cx.a0, 
			cx.r1, cx.g1, cx.b1, cx.a1 };

			// write cxform
			fwrite(&cxform, sizeof(signed short[8]), 1, file);
	}
	else
	{
		cxform_included = false;
		fwrite(&cxform_included, sizeof(bool), 1, file);
	}
}
//-----------------------------------------------------------------------
void handle_RemoveObject2(TAG* tag, FILE* file)
{
	unsigned int event_type = ogreSwf::OBOE::EID_REMOVEOBJECT;
	printf("\n        EID_REMOVEOBJECT\n        {\n");

	// write event-type tag
	fwrite(&event_type, sizeof(unsigned int), 1, file);

	unsigned int depth = swf_GetDepth(tag);
	printf("            depth: %d\n        }\n", depth);

	// write depth
	fwrite(&depth, sizeof(unsigned int), 1, file);
}
//-----------------------------------------------------------------------
void handle_StartSound(TAG* tag, FILE* file)
{
	unsigned int event_type = 0;

	unsigned int id = swf_GetU16(tag);
	U8 flags = swf_GetU8(tag);

	if(flags & 32)
	{
		printf("\n        EID_STOPSOUND\n        {\n");
		event_type = ogreSwf::OBOE::EID_STOPSOUND;
	}
	else
	{
		printf("\n        EID_STARTSOUND\n        {\n");
		event_type = ogreSwf::OBOE::EID_STARTSOUND;
	}

	// write event-type tag
	fwrite(&event_type, sizeof(unsigned int), 1, file);

	printf("            id: %d\n", id);

	// write flash id
	fwrite(&id, sizeof(unsigned int), 1, file);

	bool always_start = true;

	if(flags & 16)
	{
		always_start = false;
	}

	// only on START sound events
	if(!(flags & 32))
	{
		printf("            start if already playing: %s\n", always_start?"yes":"no");

		// write always_start flag
		fwrite(&always_start, sizeof(bool), 1, file);
	}

	if(flags & 1)
	{
		swf_GetU32(tag);
	}
	if(flags & 2)
	{
		swf_GetU32(tag);
	}
	if(flags & 4)
	{
		printf(" looping %d times", swf_GetU16(tag));
	}
	printf("        }\n");
}
//-----------------------------------------------------------------------
