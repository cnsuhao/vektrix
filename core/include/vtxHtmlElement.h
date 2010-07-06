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

#ifndef __vtxHtmlElement_H__
#define __vtxHtmlElement_H__

#include "vtxPrerequisites.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	class HtmlSelection
	{
	public:
		HtmlSelection() 
			: x(-50.0f), 
			lineIndex(-1), 
			subSel(-1), 
			element(NULL) {}

		inline bool operator == (const HtmlSelection& sel) const
		{
			return (subSel == sel.subSel && 
				element == sel.element && element);
		}

		inline bool operator != (const HtmlSelection& sel) const
		{
			return (subSel != sel.subSel || 
				element != sel.element);
		}

		inline bool operator > (const HtmlSelection& sel) const
		{
			return (lineIndex > sel.lineIndex) || (lineIndex == sel.lineIndex && x > sel.x);
		}

		inline bool operator < (const HtmlSelection& sel) const
		{
			return (lineIndex < sel.lineIndex) || (lineIndex == sel.lineIndex && x < sel.x);
		}

		float x;
		int lineIndex;
		int subSel;
		HtmlElement* element;
	};

	class vtxExport HtmlElement
	{
	public:
		typedef std::vector<HtmlElement*> ChildList;

		enum Type
		{
			Unknown = 0, 
			Root, 
			Image, 
			Paragraph, 
			Font, 
			Text
		};

		enum Alignment
		{
			AlignLeft = 0, 
			AlignRight, 
			AlignCenter, 
			AlignJustify
		};

		HtmlElement(const Type& type, HtmlElement* parent);
		virtual ~HtmlElement();

		void addChild(HtmlElement* child);
		void removeChild(const uint& index);
		void removeChild(HtmlElement* element);

		inline const Type& getType() const
		{
			return type;
		}

		inline HtmlElement* getParent() const
		{
			return parent;
		}

		ChildList children;

		/// the nearest visual node that is located <b>BEFORE</b> this element inside the DOM tree
		HtmlElement* prevVisualNode;

		/// the nearest visual node that is located <b>AFTER</b> this element inside the DOM tree
		HtmlElement* nextVisualNode;

	protected:
		Type type;
		HtmlElement* parent;
	};
	//-----------------------------------------------------------------------
}

#endif
