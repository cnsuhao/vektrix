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
				"vektrix|header|"
			};
			movie_parser.addDataHandler(hdrDH, size_of(hdrDH), new HeaderDataHandler);

			std::string rscsDH[] = 
			{
				"vektrix|resources|image|", 
				"vektrix|resources|material|", 
				"vektrix|resources|material|gradient_step|", 
				"vektrix|resources|sound|", 
				"vektrix|resources|shape|", 
				"vektrix|resources|button|", 
				"vektrix|resources|button|state|", 
				"vektrix|resources|button|state|event|", 
				"vektrix|resources|movieclip|"
			};
			movie_parser.addDataHandler(rscsDH, size_of(rscsDH), new ResourcesDataHandler);

			std::string tmlnDH[] = 
			{
				"vektrix|timeline|", 
				"vektrix|timeline|keyframe|", 
				"vektrix|timeline|keyframe|event|"
			};
			movie_parser.addDataHandler(tmlnDH, size_of(tmlnDH), new TimelineDataHandler);

			movie_parser.parse(stream);

			return file;
		}
		//-----------------------------------------------------------------------
	}
}
