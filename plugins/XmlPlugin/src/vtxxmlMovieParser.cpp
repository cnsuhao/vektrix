/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

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
#include "vtxxmlMovieParser.h"

#include "vtxFile.h"
#include "vtxFileStream.h"

#include "vtxxmlHeaderDataHandler.h"
#include "vtxxmlParser.h"
#include "vtxxmlResourcesDataHandler.h"
#include "vtxxmlTimelineDataHandler.h"


namespace vtx
{
	namespace xml
	{
		//-----------------------------------------------------------------------
		const std::string& MovieParser::getExtension() const
		{
			static std::string ext = ".xml";
			return ext;
		}
		//-----------------------------------------------------------------------
		File* MovieParser::parse(FileStream* stream)
		{
			File* file = new File(stream->getFilename());

			XMLParser movie_parser(file);

			std::string hdrDH[] = 
			{
				"vectrix|header|"
			};
			movie_parser.addDataHandler(hdrDH, size_of(hdrDH), new HeaderDataHandler);

			std::string rscsDH[] = 
			{
				"vectrix|resources|image|", 
				"vectrix|resources|material|", 
				"vectrix|resources|sound|", 
				"vectrix|resources|shape|", 
				"vectrix|resources|button|", 
				"vectrix|resources|button|state|", 
				"vectrix|resources|button|state|event|", 
				"vectrix|resources|movieclip|"
			};
			movie_parser.addDataHandler(rscsDH, size_of(rscsDH), new ResourcesDataHandler);

			std::string tmlnDH[] = 
			{
				"vectrix|timeline|", 
				"vectrix|timeline|keyframe|", 
				"vectrix|timeline|keyframe|event|"
			};
			movie_parser.addDataHandler(tmlnDH, size_of(tmlnDH), new TimelineDataHandler);

			movie_parser.parse(stream);

			return file;
		}
		//-----------------------------------------------------------------------
	}
}
