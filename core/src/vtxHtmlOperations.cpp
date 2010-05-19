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
#include "vtxHtmlFont.h"
#include "vtxHtmlImage.h"
#include "vtxHtmlParagraph.h"
#include "vtxHtmlText.h"
#include "vtxStringHelper.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	HtmlOperations::HtmlOperations() 
		: mHtmlTextNeedsUpdate(true)
	{

	}
	//-----------------------------------------------------------------------
	HtmlOperations::~HtmlOperations()
	{

	}
	//-----------------------------------------------------------------------
	HtmlSelection HtmlOperations::selectBackward(HtmlSelection sel)
	{
		if(sel.element)
		{
			switch(sel.element->getType())
			{
			case HtmlElement::Text:
				{
					HtmlText* text = static_cast<HtmlText*>(sel.element);

					if(sel.subSel > 0)
					{
						--sel.subSel;
					}
					else
					{
						HtmlElement* prev = sel.element->prevVisualNode;
						if(prev)
						{
							sel.element = prev;

							if(prev->getType() == HtmlElement::Text)
							{
								text = static_cast<HtmlText*>(prev);
								sel.subSel = text->text.length();
							}
							else
							{
								sel.subSel = -1;
							}
						}
					}
				}
				break;

			default:
				{
					HtmlElement* prev = sel.element->prevVisualNode;
					if(prev)
					{
						sel.element = prev;

						if(prev->getType() == HtmlElement::Text)
						{
							HtmlText* text = static_cast<HtmlText*>(prev);
							sel.subSel = text->text.length();
						}
						else
						{
							sel.subSel = -1;
						}
					}
				}
				break;
			}
		}

		return sel;
	}
	//-----------------------------------------------------------------------
	HtmlSelection HtmlOperations::selectForward(HtmlSelection sel)
	{
		if(sel.element)
		{
			switch(sel.element->getType())
			{
			case HtmlElement::Text:
				{
					HtmlText* text = static_cast<HtmlText*>(sel.element);

					if(sel.subSel < (int)text->text.length())
					{
						++sel.subSel;
					}
					else
					{
						HtmlElement* next = sel.element->nextVisualNode;
						if(next)
						{
							sel.element = next;

							if(next->getType() == HtmlElement::Text)
							{
								sel.subSel = 0;
							}
							else
							{
								sel.subSel = -1;
							}
						}
					}
				}
				break;

			default:
				{
					HtmlElement* next = sel.element->nextVisualNode;
					if(next)
					{
						sel.element = next;

						if(next->getType() == HtmlElement::Text)
						{
							sel.subSel = 0;
						}
						else
						{
							sel.subSel = -1;
						}
					}
				}
				break;
			}
		}

		return sel;
	}
	//-----------------------------------------------------------------------
	HtmlSelection HtmlOperations::eraseBackward(HtmlSelection sel)
	{
		mHtmlTextNeedsUpdate = true;

		if(sel.element)
		{
			switch(sel.element->getType())
			{
			case HtmlElement::Text:
				{
					HtmlText* text = static_cast<HtmlText*>(sel.element);

					// character index > 1
					if(sel.subSel > 0)
					{
						text->text = 
							text->text.substr(0, sel.subSel-1) + 
							text->text.substr(
							sel.subSel, 
							text->text.length()-sel.subSel);

						--sel.subSel;
					}
					else
					{
						sel = _selectPreviousElement(sel);

						//eraseBackward(sel);
						//selEnd = selBegin = sel;
					}

					if(text->text.length() == 0)
					{
						std::cout << "DELETED text node" << std::endl;
						HtmlElement* parent = sel.element->getParent();
						HtmlElement* elem = sel.element;

						if(sel.element->prevVisualNode)
						{
							sel = _selectPreviousElement(sel);
						}
						else
						{
							sel = _selectNextElement(sel);
						}

						delete elem;
						parent->removeChild(elem);
					}
				}
				break;

			case HtmlElement::Image:
				{
					HtmlElement* parent = sel.element->getParent();
					HtmlElement* elem = sel.element;

					if(sel.element->prevVisualNode)
					{
						sel = _selectPreviousElement(sel);
					}
					else
					{
						sel = _selectNextElement(sel);
					}

					delete elem;
					parent->removeChild(elem);
				}
				break;
			}
		}

		return sel;
	}
	//-----------------------------------------------------------------------
	HtmlSelection HtmlOperations::eraseForward(HtmlSelection sel)
	{
		mHtmlTextNeedsUpdate = true;

		if(sel.element)
		{
			switch(sel.element->getType())
			{
			case HtmlElement::Text:
				{
					HtmlText* text = static_cast<HtmlText*>(sel.element);

					// character index > 1
					if(sel.subSel < (int)text->text.length())
					{
						text->text = 
							text->text.substr(0, sel.subSel) + 
							text->text.substr(
							sel.subSel+1, 
							text->text.length()-sel.subSel-1);
					}
					else
					{
						// _selectNextElement(sel);
						//sel = _selectPreviousElement(sel);
						//sel.subSel++;
						//eraseBackward(sel);
						//selEnd = selBegin = sel;
					}

					if(text->text.length() == 0)
					{
						std::cout << "DELETED text node" << std::endl;
						HtmlElement* parent = sel.element->getParent();
						HtmlElement* elem = sel.element;

						sel = _selectPreviousElement(sel);

						delete elem;
						parent->removeChild(elem);
					}
				}
				break;

			case HtmlElement::Image:
				{
					HtmlElement* parent = sel.element->getParent();
					HtmlElement* elem = sel.element;

					sel = _selectPreviousElement(sel);

					delete elem;
					parent->removeChild(elem);
				}
				break;
			}
		}

		return sel;
	}
	//-----------------------------------------------------------------------
	HtmlSelection HtmlOperations::eraseSelection(HtmlElement* root, 
		const HtmlSelection& begin, const HtmlSelection& end)
	{
		mHtmlTextNeedsUpdate = true;
		mEraseState = ES_BEFORE_ERASE;

		mSelBegin = begin;
		mSelEnd = end;

		if(mSelBegin > mSelEnd)
		{
			std::swap(mSelBegin, mSelEnd);
		}

		if(mSelBegin.element == mSelEnd.element)
		{
			if(mSelBegin.element->getType() == HtmlElement::Text)
			{
				if(mSelBegin.subSel >= 0 && 
					mSelBegin.subSel < mSelEnd.subSel)
				{
					HtmlText* text = static_cast<HtmlText*>(mSelBegin.element);
					text->text = 
						text->text.substr(0, mSelBegin.subSel) + 
						text->text.substr(mSelEnd.subSel, text->text.length()-mSelEnd.subSel);
				}
			}
			else
			{

			}
		}
		else
		{
			_recursiveErase(root);

			if(mSelBegin.element->getType() == HtmlElement::Text)
			{
				HtmlText* text = static_cast<HtmlText*>(mSelBegin.element);

				if(text->text.length() > 1)
				{
					text->text = text->text.substr(0, mSelBegin.subSel);
				}
				else
				{
					text->getParent()->removeChild(text);
					delete text;
				}
			}

			if(mSelEnd.element->getType() == HtmlElement::Text)
			{
				HtmlText* text = static_cast<HtmlText*>(mSelEnd.element);

				if(text->text.length() > 1)
				{
					text->text = text->text.substr(mSelEnd.subSel, 
						text->text.length()-mSelEnd.subSel);
				}
				else
				{
					text->getParent()->removeChild(text);
					delete text;
				}
			}
		}

		return mSelBegin;
	}
	//-----------------------------------------------------------------------
	const WString& HtmlOperations::getHtmlText(HtmlElement* root)
	{
		if(mHtmlTextNeedsUpdate)
		{
			mHtmlText.clear();
			_recursiveGenerate(root);
			mHtmlTextNeedsUpdate = false;
		}

		return mHtmlText;
	}
	//-----------------------------------------------------------------------
	HtmlSelection HtmlOperations::_selectPreviousElement(HtmlSelection sel)
	{
		HtmlElement* prev = sel.element->prevVisualNode;
		if(prev)
		{
			std::cout << "DEBUG: selected prev element" << std::endl;

			switch(prev->getType())
			{
			case HtmlElement::Text:
				{
					HtmlText* text = static_cast<HtmlText*>(prev);
					if(text)
					{
						sel.element = text;
						sel.subSel = text->text.length();
					}
				}
				break;

			case HtmlElement::Image:
				{
					sel.element = prev;
					sel.subSel = -1;
				}
				break;
			}
		}

		return sel;
	}
	//-----------------------------------------------------------------------
	HtmlSelection HtmlOperations::_selectNextElement(HtmlSelection sel)
	{
		HtmlElement* next = sel.element->nextVisualNode;
		if(next)
		{
			std::cout << "DEBUG: selected next element" << std::endl;

			switch(next->getType())
			{
			case HtmlElement::Text:
				{
					HtmlText* text = static_cast<HtmlText*>(next);
					if(text)
					{
						sel.element = text;
						sel.subSel = 0;
					}
				}
				break;

			case HtmlElement::Image:
				{
					sel.element = next;
					sel.subSel = -1;
				}
				break;
			}
		}

		return sel;
	}
	//-----------------------------------------------------------------------
	void HtmlOperations::_recursiveErase(HtmlElement* current_element)
	{
		for(uint i=0; i<current_element->children.size(); )
		{
			HtmlElement* elem = current_element->children.at(i);
			_recursiveErase(elem);

			switch(mEraseState)
			{
			case ES_BEFORE_ERASE:
				{
					if(elem == mSelBegin.element)
					{
						mEraseState = ES_ERASING;
					}
				}
				break;

			case ES_ERASING:
				{
					if(elem == mSelEnd.element)
					{
						mEraseState = ES_AFTER_ERASE;
					}
					// only erase text and image elements
					else if(elem->getType() == HtmlElement::Text || elem->getType() == HtmlElement::Image)
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
	void HtmlOperations::_recursiveGenerate(HtmlElement* source_element)
	{
		HtmlElement::ChildList::const_iterator it = source_element->children.begin();
		HtmlElement::ChildList::const_iterator end = source_element->children.end();
		while(it != end)
		{
			switch((*it)->getType())
			{
			case HtmlElement::Font:
				{
					HtmlFont* font = static_cast<HtmlFont*>(*it);
					//if(!font) break;

					mHtmlText += L"<font";

					if(font->face.length())
					{
						mHtmlText += L" face=\"";
						mHtmlText.append(font->face.begin(), font->face.end());
						mHtmlText += L"\"";
					}

					if(font->size.length())
					{
						mHtmlText += L" size=\"";
						mHtmlText.append(font->size.begin(), font->size.end());
						mHtmlText += L"\"";
					}

					if(font->color.length())
					{
						mHtmlText += L" color=\"";
						mHtmlText.append(font->color.begin(), font->color.end());
						mHtmlText += L"\"";
					}

					mHtmlText += L">";

					// continue recursion
					_recursiveGenerate(*it);

					mHtmlText += L"</font>";
				}
				break;

			case HtmlElement::Image:
				{
					HtmlImage* img = static_cast<HtmlImage*>(*it);
					//if(!img) break;

					mHtmlText += L"<img";

					if(img->src.length())
					{
						mHtmlText += L" src=\"";
						mHtmlText.append(img->src.begin(), img->src.end());
						mHtmlText += L"\"";
					}

					if(img->width != 0.0f)
					{
						mHtmlText += L" width=\"";
						String width = StringHelper::toString(img->width);
						mHtmlText.append(width.begin(), width.end());
						mHtmlText += L"\"";
					}

					if(img->height != 0.0f)
					{
						mHtmlText += L" height=\"";
						String height = StringHelper::toString(img->height);
						mHtmlText.append(height.begin(), height.end());
						mHtmlText += L"\"";
					}

					mHtmlText += L"/>";
				}
				break;

			case HtmlElement::Paragraph:
				{
					HtmlParagraph* par = static_cast<HtmlParagraph*>(*it);
					//if(!par) break;

					// continue recursion
					_recursiveGenerate(*it);
				}
				break;

			case HtmlElement::Text:
				{
					HtmlText* text = static_cast<HtmlText*>(*it);
					//if(!text) break;

					mHtmlText.append(text->text.begin(), text->text.end());

					// continue recursion
					_recursiveGenerate(*it);
				}
				break;

			default:
				// continue recursion
				_recursiveGenerate(*it);
				break;
			}

			++it;
		}
	}
	//-----------------------------------------------------------------------
}
