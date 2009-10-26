/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/vektrix

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
#include "vtxswfParser.h"

#include "vtxFile.h"
#include "vtxFileStream.h"
#include "vtxLogManager.h"

#include "rfxswf.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		const std::string& SwfParser::getExtension() const
		{
			static std::string ext = ".swf";
			return ext;
		}
		//-----------------------------------------------------------------------
		File* SwfParser::parse(FileStream* stream)
		{
			File* file = new File(stream->getFilename());

			char* file_data = new char[stream->size()];
			stream->read(file_data, stream->size());

			// the flash definition
			SWF swfDefinition;

			// the memory reader struct
			reader_t swfReader;
			reader_init_memreader(&swfReader, file_data, stream->size());

			if(swf_ReadSWF2(&swfReader, &swfDefinition) < 0)
			{
				VTX_EXCEPT("%s is not a valid SWF file or contains errors.\n", stream->getFilename().c_str());
				return NULL;
			}

			// the swf reading tag
			TAG* swfTag = swfDefinition.firstTag;

			// the file header
			File::FileHeader header;

			header.fps    = swfDefinition.frameRate/256.0;
			header.frames = swfDefinition.frameCount;
			header.width  =	(swfDefinition.movieSize.xmax - swfDefinition.movieSize.xmin)/20.0f;
			header.height = (swfDefinition.movieSize.ymax - swfDefinition.movieSize.ymin)/20.0f;
			header.version = "test_version";

			// background color
			while(swfTag)
			{
				if(swfTag->id == ST_SETBACKGROUNDCOLOR)
				{
					header.bgcolor = Color(
						(float)swf_GetU8(swfTag)/255.0f,	// red
						(float)swf_GetU8(swfTag)/255.0f,	// green
						(float)swf_GetU8(swfTag)/255.0f,	// blue
						1.0f);								// alpha (fully opaque)
					break;
				}
				swfTag = swfTag->next;
			}

			// apply the parsed header
			file->setHeader(header);

			// reset the tag
			swfTag = swfDefinition.firstTag;

			//-------------------//
			// parse vector-data //
			//-------------------//
			while(swfTag)
			{
				//tag contains vector-data
				if(swfTag->id == ST_DEFINESHAPE || 
					swfTag->id == ST_DEFINESHAPE2 || 
					swfTag->id == ST_DEFINESHAPE3 || 
					swfTag->id == ST_DEFINESHAPE4)
				{
					VTX_LOG("BEFORE SHAPE PARSE");
					mShapeHandler.handleShape(swfTag, file);
					VTX_LOG("AFTER SHAPE PARSE");
					//handleShape(swfTag, mOutputFile);
				}

				swfTag = swfTag->next;
			}

			// reset the tag
			swfTag = swfDefinition.firstTag;

			//----------------//
			// parse timeline //
			//----------------//
			mTimelineHandler.handleTimeline(swfTag, file);

			// DEBUG
			VTX_LOG("SWF_DEBUG: Flash Version %u", swfDefinition.fileVersion);
			VTX_LOG("SWF_DEBUG: Frame Rate %u", (size_t)(swfDefinition.frameRate/256.0));
			VTX_LOG("SWF_DEBUG: Frame Count %u", swfDefinition.frameCount);
			VTX_LOG("SWF_DEBUG: width %u", (size_t)((swfDefinition.movieSize.xmax - swfDefinition.movieSize.xmin)/20.0));
			VTX_LOG("SWF_DEBUG: height %u", (size_t)((swfDefinition.movieSize.ymax - swfDefinition.movieSize.ymin)/20.0));

			delete[] file_data;

			return file;
		}
		//-----------------------------------------------------------------------
	}
}
