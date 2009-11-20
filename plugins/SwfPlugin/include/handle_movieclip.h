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
#include "handle_timeline.h"

void handle_movieclip_timeline(TAG* tag, FILE* file);

// main method
void handle_movieclip(TAG* tag, FILE* file)
{
	// write DEFINEMOVIECLIP tag
	unsigned int type_tag = ogreSwf::OBOE::ID_DEFINEMOVIECLIP;
	fwrite(&type_tag, sizeof(unsigned int), 1, file);

	// flash ID of the current shape
	int flash_id = 0;

	if(swf_isDefiningTag(tag))
	{
		flash_id = swf_GetDefineID(tag);
	}
	else
	{
		printf("Error in parsing Movieclip (exiting)...\n");
		exit(1);
	}

	// write Flash ID of the movieclip
	fwrite(&flash_id, sizeof(unsigned int), 1, file);

	//printf("\n--------------------------\n");
	printf("MOVIECLIP\n{\n    ID: %d\n", flash_id);

	handle_movieclip_timeline(tag, file);
}

void handle_movieclip_timeline(TAG* tag, FILE* file)
{
	fpos_t mFrameCountPos;
	fpos_t mEndPos;
	TAG* mRangeStart = tag;
	TAG* mRangeEnd = tag;
	unsigned int mFrameCount = 0;
	unsigned int mFrameIndex = 0;
	unsigned int mEventCount = 0;

	//store position of the frame count byte
	fgetpos(file, &mFrameCountPos);
	// write the framecount (currently ZERO!), we will overwrite this afterwards with the correct value
	fwrite(&mFrameCount, sizeof(unsigned int), 1, file);

	while(tag)
	{
		if(tag->id == ST_END)
		{
			//store end position
			fgetpos(file, &mEndPos);
			//go to frame-count position
			fsetpos(file, &mFrameCountPos);
			//write the frame-count
			fwrite(&mFrameCount, sizeof(unsigned int), 1, file);
			//go to end position again
			fsetpos(file, &mEndPos);

			printf("}\n\n");

			break;
		}
		else if(tag->id == ST_SHOWFRAME)
		{
			mRangeEnd = tag;
			mFrameIndex++;

			// filter empty frames
			if(mEventCount != 0 || tag->next->id == ST_END)
			{
				// write the frame index and the number of events included
				printf("\n    Keyframe\n    {\n        Index: %d\n        Events: %d\n", mFrameIndex, mEventCount);
				fwrite(&mFrameIndex, sizeof(unsigned int), 1, file);
				fwrite(&mEventCount, sizeof(unsigned int), 1, file);

				// process the frame-events
				while(mRangeStart != mRangeEnd)
				{
					if(mRangeStart->id == ST_PLACEOBJECT2)
					{
						handle_PlaceObject2(mRangeStart, file);
					} 
					else if(mRangeStart->id == ST_REMOVEOBJECT2)
					{
						handle_RemoveObject2(mRangeStart, file);
					}
					mRangeStart = mRangeStart->next;
				}

				// increase the frame count
				mFrameCount++;

				printf("    }\n");

				mRangeStart = mRangeEnd;
				mEventCount = 0;
			}
		}
		// count the frame-events
		else if(tag->id == ST_PLACEOBJECT2 || 
			tag->id == ST_REMOVEOBJECT2)
		{
			// increase the event count
			mEventCount++;
		}

		// go to the next tag
		tag = tag->next;
	}
}
