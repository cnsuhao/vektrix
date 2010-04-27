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

#include "vtxHtmlOperations.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	HtmlOperations::HtmlOperations(HtmlElement* root) 
		: mEraseState(ES_BEFORE_ERASE), 
		mRoot(root)
	{

	}
	//-----------------------------------------------------------------------
	HtmlOperations::~HtmlOperations()
	{

	}
	//-----------------------------------------------------------------------
	void HtmlOperations::eraseSelection(const HtmlSelection& selectionBegin, const HtmlSelection& selectionEnd)
	{
		if(selectionBegin.element == selectionEnd.element)
		{

		}
		else
		{
			mSelectionBegin = selectionBegin;
			mSelectionEnd = selectionEnd;
			_erase(mRoot);
		}
	}
	//-----------------------------------------------------------------------
	void HtmlOperations::_erase(HtmlElement* current_element)
	{
		for(uint i=0; i<current_element->children.size(); )
		{
			HtmlElement* elem = current_element->children.at(i);
			_erase(elem);

			switch(mEraseState)
			{
			case ES_BEFORE_ERASE:
				{
					if(elem == mSelectionBegin.element)
					{
						mEraseState = ES_ERASING;
					}
				}
				break;

			case ES_ERASING:
				{
					if(elem == mSelectionEnd.element)
					{
						mEraseState = ES_AFTER_ERASE;
					}
					else
					{
						current_element->children.erase(current_element->children.begin()+i);
						delete elem;
						continue;
					}
				}
				break;

			case ES_AFTER_ERASE:
				{
					return;
				}
				break;
			}

			++i;
		}
	}
	//-----------------------------------------------------------------------
}
