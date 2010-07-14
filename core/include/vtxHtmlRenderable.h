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

#ifndef __vtxHtmlRenderable_H__
#define __vtxHtmlRenderable_H__

#include "vtxPrerequisites.h"
#include "vtxColor.h"
#include "vtxHtmlElement.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** An interface for classes that need to render a HTML DOM tree */
	class vtxExport HtmlRenderable
	{
	public:
		/** Represents a style element which contains information about font, color and size */
		class StyleElement
		{
		public:
			StyleElement() : size(0.0f), font(NULL) {}
			float size;
			Color color;
			FontResource* font;
		};
		typedef std::stack<StyleElement> StyleStack;
		typedef std::stack<HtmlElement::Alignment> AlignmentStack;

		HtmlRenderable();
		virtual ~HtmlRenderable();

	protected:
		void interateDomTree(HtmlElement* root, File* file);

		// inline for best performance
		inline const StyleElement& getCurrentStyle() const
		{
			if(mStyleStack.size())
			{
				return mStyleStack.top();
			}

			static StyleElement empty;
			return empty;
		}

		//inline bool hasStyle() const
		//{
		//	return mStyleStack.size() != 0;
		//}

	private:
		File* mFile;
		StyleStack mStyleStack;
		AlignmentStack mAlignStack;

		/// remember the previous visual node during the DOM iteration
		HtmlElement* mPreviousVisualNode;

		virtual void _addFont(HtmlFont* font) = 0;
		virtual void _fontStyleChanged(const StyleElement& style) {}
		virtual void _addImage(HtmlImage* image) = 0;
		virtual void _addParagraph(HtmlParagraph* paragraph) = 0;
		virtual void _addText(HtmlText* text) = 0;

		/** Recursive method to iterate over the HTML DOM tree */
		void _recursiveDomIteration(HtmlElement* source_element);
	};
	//-----------------------------------------------------------------------
}

#endif
