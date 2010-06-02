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

			static_cast<File*>(userdata)->setHeader(header);
		}
		//-----------------------------------------------------------------------
		void HeaderDataHandler::end(const std::string& key)
		{

		}
		//-----------------------------------------------------------------------
	}
}
