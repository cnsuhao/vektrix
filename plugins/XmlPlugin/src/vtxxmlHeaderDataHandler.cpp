/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/vektrix

Copyright (c) 2009 Fuse-Software (tm)

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/
#include "vtxxmlHeaderDataHandler.h"

#include "vtxFile.h"
#include "vtxLogManager.h"
#include "vtxStringHelper.h"

namespace vtx
{
	namespace xml
	{
		//-----------------------------------------------------------------------
		HeaderDataHandler::HeaderDataHandler()
		{

		}
		//-----------------------------------------------------------------------
		void HeaderDataHandler::handle(const std::string& key, StringMap& atts, void* userdata)
		{
			File::FileHeader header;

			header.version = atts["version"];
			header.fps = StringHelper::toUint(atts["fps"]);
			header.frames = StringHelper::toUint(atts["frames"]);
			header.width = StringHelper::toUint(atts["width"]);
			header.height = StringHelper::toUint(atts["height"]);
			header.bgcolor = StringHelper::toColor(atts["bgcolor"]);

			//if(num_atts != 6)
			//{
			//	VTX_EXCEPT("'%s': Not all header tags have been set correctly!", file->getFilename().c_str());
			//}


			// TODO: IMPORTANT implement this
			static_cast<File*>(userdata)->setHeader(header);
			//file->setHeader(header);
		}
		//-----------------------------------------------------------------------
		void HeaderDataHandler::end(const std::string& key)
		{

		}
		//-----------------------------------------------------------------------
	}
}
