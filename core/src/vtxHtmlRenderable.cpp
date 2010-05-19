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
#include "vtxLogManager.h"
#include "vtxStringHelper.h"
#include "vtxTextLineElement.h"

// TODO: remove resource
#include "vtxFile.h"
#include "vtxResource.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	HtmlRenderable::HtmlRenderable(Resource* resource) 
		: mResource2(resource), 
		mPreviousVisualNode(NULL)
	{

	}
	//-----------------------------------------------------------------------
	HtmlRenderable::~HtmlRenderable()
	{

	}
	//-----------------------------------------------------------------------
	void HtmlRenderable::interateDomTree(HtmlElement* root)
	{
		assert(!mStyleStack.size() && "Style stacks not cleared");

		mPreviousVisualNode = NULL;
		_recursiveDomIteration(root);
	}
	//-----------------------------------------------------------------------
	void HtmlRenderable::_recursiveDomIteration(HtmlElement* source_element)
	{
		HtmlElement::ChildList::const_iterator it = source_element->children.begin();
		HtmlElement::ChildList::const_iterator end = source_element->children.end();
		while(it != end)
		{
			switch((*it)->getType())
			{
				//------------------
				// HTML FONT
				//------------------
			case HtmlElement::Font:
				{
					HtmlFont* font = static_cast<HtmlFont*>(*it);
					//if(!font) break;
					_addFont(font);

					////mComposedHTMLText += L"<font";

					StyleElement style;

					if(font->face.length())
					{
						//mComposedHTMLText += L" face=";
						//mComposedHTMLText.append(font->face.begin(), font->face.end());

						FontResource* new_font = mResource2->getFile()->getFontByName(font->face);
						if(new_font)
						{
							style.font = new_font;
						}
						// font name given, but font unavailable
						else if(mStyleStack.size())
						{
							VTX_WARN("Unable to find font %s", font->face.c_str());
							style.font = mStyleStack.top().font;
						}
					}
					else if(mStyleStack.size())
					{
						style.font = mStyleStack.top().font;
					}

					if(font->size.length())
					{
						//mComposedHTMLText += L" size=";
						//mComposedHTMLText.append(font->size.begin(), font->size.end());

						style.size = StringHelper::toFloat(font->size);
					}
					else if(mStyleStack.size())
						style.size = mStyleStack.top().size;

					if(font->color.length())
					{
						//mComposedHTMLText += L" color=";
						//mComposedHTMLText.append(font->color.begin(), font->color.end());

						style.color = StringHelper::colorFromHex(font->color);
					}
					else if(mStyleStack.size())
						style.color = mStyleStack.top().color;

					//mComposedHTMLText += L">";

					mStyleStack.push(style);

					_fontStyleChanged(mStyleStack.top());

					//// add FONT_CHANGE element
					//TextLineElement font_element;
					//font_element.type = TextLineElement::ET_FontChange;
					//font_element.color = mStyleStack.top().color;
					//font_element.font = mStyleStack.top().font;
					//font_element.height = mStyleStack.top().size;
					//font_element.x = mCurrentLine.width;
					//mCurrentLine.elements.push_back(font_element);

					//// continue recursion
					_recursiveDomIteration(*it);

					////mComposedHTMLText += L"</font>";

					mStyleStack.pop();

					if(mStyleStack.size())
					{
						_fontStyleChanged(mStyleStack.top());
					}

					//if(mStyleStack.size())
					//{
					//	// add FONT_CHANGE element
					//	font_element.reset();
					//	font_element.type = TextLineElement::ET_FontChange;
					//	font_element.color = mStyleStack.top().color;
					//	font_element.font = mStyleStack.top().font;
					//	font_element.height = mStyleStack.top().size;
					//	font_element.x = mCurrentLine.width;
					//	mCurrentLine.elements.push_back(font_element);
					//}
				}
				break;

				//------------------
				// HTML IMAGE
				//------------------
			case HtmlElement::Image:
				{
					HtmlImage* img = static_cast<HtmlImage*>(*it);
					//if(!img) break;

					// connect this image node to the previous visual node
					if(mPreviousVisualNode)
					{
						mPreviousVisualNode->nextVisualNode = img;
					}

					// connect the  previous visual node to this image node
					img->prevVisualNode = mPreviousVisualNode;
					mPreviousVisualNode = img;

					// TODO: check what this is good for and if it could be replaced somehow
					// add FONT_CHANGE element
					_fontStyleChanged(mStyleStack.top());

					_addImage(img);

					if(mStyleStack.size())
					{
						_fontStyleChanged(mStyleStack.top());
					}
				}
				break;

				//------------------
				// HTML PARAGRAPH
				//------------------
			case HtmlElement::Paragraph:
				{
					HtmlParagraph* par = static_cast<HtmlParagraph*>(*it);
					//if(!par) break;

					mAlignStack.push(par->align);

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
					//if(!text || !mStyleStack.size()) break;
					if(!mStyleStack.size()) break;

					//mComposedHTMLText.append(text->text.begin(), text->text.end());

					// connect this text node to the previous visual node
					if(mPreviousVisualNode)
					{
						mPreviousVisualNode->nextVisualNode = text;
					}

					// connect the  previous visual node to this text node
					text->prevVisualNode = mPreviousVisualNode;
					mPreviousVisualNode = text;

					_addText(text);

					// continue recursion
					_recursiveDomIteration(*it);
				}
				break;

			default:
				// continue recursion
				_recursiveDomIteration(*it);
				break;
			}

			++it;
		}
	}
	//-----------------------------------------------------------------------
}
