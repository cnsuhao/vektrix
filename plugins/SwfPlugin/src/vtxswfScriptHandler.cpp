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

#include "vtxswfScriptHandler.h"

#include "vtxFile.h"
#include "vtxScriptResource.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		void ScriptHandler::handleScript(TAG* swfTag, File* file)
		{
			if(swfTag->id == ST_DOABC)
			{
				U32 flags = swf_GetU32(swfTag);
				swf_GetString(swfTag);

				uint len = swfTag->len - swfTag->pos;

				char* buf = (char*)malloc(len);
				swf_GetBlock(swfTag, (U8*)buf, len);

				std::cout << "LENGTH: " << len << std::endl;

				std::ofstream debug;
				debug.open("abc_dump.abc", std::ios::binary);
				debug.write(buf, len);
				debug.close();

				file->addResource(new ScriptResource("Script", buf, len));
			}
		}
		//-----------------------------------------------------------------------
	}
}
