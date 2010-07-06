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

#include "vtxxmlEventHandlerBase.h"

#include "vtxCreateObjectEvent.h"
#include "vtxMoveObjectEvent.h"
#include "vtxRemoveObjectEvent.h"
#include "vtxFile.h"
#include "vtxKeyframe.h"
#include "vtxLogManager.h"
#include "vtxMatrix.h"
#include "vtxStringHelper.h"

namespace vtx
{
	namespace xml
	{
		//-----------------------------------------------------------------------
		EventHandlerBase::EventHandlerBase() 
			: mContainer(NULL)
		{

		}
		//-----------------------------------------------------------------------
		void EventHandlerBase::handleEvent()
		{
			std::string type = (*mAttributes)["type"];

			if(!type.length())
			{
				VTX_EXCEPT("\"%s\": Missing parameter \"type\" in <event .../>!", mCurrentFile->getFilename().c_str());
			}

			if(type == "create")
			{
				std::string id = (*mAttributes)["id"];
				size_t layer = StringHelper::toUint((*mAttributes)["layer"]);
				Matrix matrix = StringHelper::toMatrix((*mAttributes)["matrix"]);
				CXForm cxform = StringHelper::toCXForm((*mAttributes)["cxform"]);
				String name = (*mAttributes)["name"];

				mContainer->addEvent(new CreateObjectEvent(NULL, mCurrentFile, id, layer, matrix, cxform, name));
			}
			else if(type == "move")
			{
				size_t layer = StringHelper::toUint((*mAttributes)["layer"]);
				Matrix matrix = StringHelper::toMatrix((*mAttributes)["matrix"]);
				CXForm cxform = StringHelper::toCXForm((*mAttributes)["cxform"]);

				mContainer->addEvent(new MoveObjectEvent(NULL, layer, matrix, cxform));
			}
			else if(type == "remove")
			{
				size_t layer = StringHelper::toUint((*mAttributes)["layer"]);

				mContainer->addEvent(new RemoveObjectEvent(NULL, layer));
			}
		}
		//-----------------------------------------------------------------------
	}
}
