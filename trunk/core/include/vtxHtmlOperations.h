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

#ifndef __vtxHtmlOperations_H__
#define __vtxHtmlOperations_H__

#include "vtxPrerequisites.h"
#include "vtxHtmlElement.h"

namespace vtx
{
	class vtxExport HtmlOperations
	{
	public:
		HtmlOperations();
		virtual ~HtmlOperations();

		enum EraseState
		{
			ES_BEFORE_ERASE = 0, 
			ES_ERASING, 
			ES_AFTER_ERASE
		};

		HtmlSelection selectBackward(HtmlSelection sel);
		HtmlSelection selectForward(HtmlSelection sel);

		HtmlSelection eraseBackward(HtmlSelection sel);
		HtmlSelection eraseForward(HtmlSelection sel);

		HtmlSelection eraseSelection(HtmlElement* root, 
			const HtmlSelection& begin, const HtmlSelection& end);

		const WString& getHtmlText(HtmlElement* root);

	protected:
		HtmlSelection mSelBegin;
		HtmlSelection mSelEnd;

	private:
		EraseState mEraseState;

		// generate HTML from DOM
		bool mHtmlTextNeedsUpdate;
		WString mHtmlText;

		HtmlSelection _selectPreviousElement(HtmlSelection sel);
		HtmlSelection _selectNextElement(HtmlSelection sel);

		// recursive utility functions
		void _recursiveErase(HtmlElement* current_element);
		void _recursiveGenerate(HtmlElement* current_element);
	};
}

#endif
