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

#include "vtxHtmlRenderable.h"
#include "vtxHtmlFont.h"
#include "vtxHtmlImage.h"
#include "vtxHtmlParagraph.h"
#include "vtxHtmlText.h"
#include "vtxFile.h"
#include "vtxFontManager.h"
#include "vtxLogManager.h"
#include "vtxStringHelper.h"
#include "vtxTextLineElement.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	HtmlRenderable::HtmlRenderable() 
		: mPreviousVisualNode(NULL)
	{

	}
	//-----------------------------------------------------------------------
	HtmlRenderable::~HtmlRenderable()
	{

	}
	//-----------------------------------------------------------------------
	void HtmlRenderable::iterateDomTree(HtmlElement* root, File* file)
	{
		mFile = file;
		mPreviousVisualNode = NULL;

		mAlignStack = AlignmentStack();
		mStyleStack = StyleStack();

		// push default values on to the stacks
		mAlignStack.push(HtmlElement::AlignLeft);
		StyleElement default_style;
		default_style.font = FontManager::getSingletonPtr()->getFont("Times New Roman");
		default_style.color = Color::BLACK;
		default_style.size = 12;
		mStyleStack.push(default_style);

		_recursiveDomIteration(root);
	}
	//-----------------------------------------------------------------------
	void HtmlRenderable::_recursiveDomIteration(HtmlElement* source_element)
	{
		if(!source_element)
			return;

		for_each_const(it, HtmlElement::ChildList, source_element->children)
		{
			switch((*it)->getType())
			{
				//------------------
				// HTML FONT
				//------------------
			case HtmlElement::Font:
				{
					HtmlFont* font = static_cast<HtmlFont*>(*it);

					_addFont(font);

					StyleElement style;

					if(mStyleStack.size())
						style = mStyleStack.top();

					if(font->face.length())
					{
						FontResource* font_res = mFile->getFontByName(font->face);
						style.font = font_res ? font_res : style.font;
					}

					if(font->size.length())
						style.size = StringHelper::toFloat(font->size);

					if(font->color.length())
						style.color = StringHelper::colorFromHex(font->color);

					mStyleStack.push(style);

					_fontStyleChanged(mStyleStack.top());

					// continue recursion
					_recursiveDomIteration(*it);

					mStyleStack.pop();

					if(mStyleStack.size())
						_fontStyleChanged(mStyleStack.top());
				}
				break;

				//------------------
				// HTML IMAGE
				//------------------
			case HtmlElement::Image:
				{
					HtmlImage* img = static_cast<HtmlImage*>(*it);

					// connect this image node to the previous visual node
					if(mPreviousVisualNode)
						mPreviousVisualNode->nextVisualNode = img;

					// connect the  previous visual node to this image node
					img->prevVisualNode = mPreviousVisualNode;
					mPreviousVisualNode = img;

					// TODO: check what this is good for and if it could be replaced somehow
					// TODO2: if image is outside all font elements there is no style on the stack
					// add FONT_CHANGE element
					if(mStyleStack.size())
						_fontStyleChanged(mStyleStack.top());

					_addImage(img);

					if(mStyleStack.size())
						_fontStyleChanged(mStyleStack.top());
				}
				break;

				//------------------
				// HTML PARAGRAPH
				//------------------
			case HtmlElement::Paragraph:
				{
					HtmlParagraph* par = static_cast<HtmlParagraph*>(*it);

					HtmlElement::Alignment alignment = HtmlElement::AlignLeft;

					if(mAlignStack.size())
						alignment = mAlignStack.top();

					if(par->align != HtmlElement::AlignNull)
						alignment = par->align;

					mAlignStack.push(alignment);

					_startNewLine();
					_addParagraph(par);

					// continue recursion
					_recursiveDomIteration(*it);

					mAlignStack.pop();
				}
				break;

				//------------------
				// HTML TEXT
				//------------------
			case HtmlElement::Text:
				{
					HtmlText* text = static_cast<HtmlText*>(*it);

					if(!mStyleStack.size())
						break;

					// connect this text node to the previous visual node
					if(mPreviousVisualNode)
						mPreviousVisualNode->nextVisualNode = text;

					// connect the  previous visual node to this text node
					text->prevVisualNode = mPreviousVisualNode;
					mPreviousVisualNode = text;

					_addText(text);

					// continue recursion
					_recursiveDomIteration(*it);
				}
				break;

			case HtmlElement::Linebreak:
				_startNewLine();
				break;

			default:
				// continue recursion
				_recursiveDomIteration(*it);
				break;
			}
		}
	}
	//-----------------------------------------------------------------------
}
