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

#include "vtxEditText.h"
#include "vtxEditTextResource.h"
#include "vtxFile.h"
#include "vtxFontResource.h"
#include "vtxGlyphResource.h"
#include "vtxHtmlElement.h"
#include "vtxHtmlFont.h"
#include "vtxHtmlImage.h"
#include "vtxHtmlParser.h"
#include "vtxHtmlParagraph.h"
#include "vtxHtmlText.h"
#include "vtxLogManager.h"
#include "vtxMovie.h"
#include "vtxScriptEditText.h"
#include "vtxShape.h"
#include "vtxShapeResource.h"
#include "vtxStringHelper.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	EditText::EditText(Resource* resource) 
		: DisplayObjectContainer(resource), 
		mNeedDomUpdate(true), 
		mHtmlDom(NULL), 
		mGlyphCount(0)
	{
		mEditTextResource = dynamic_cast<EditTextResource*>(resource);

		if(mEditTextResource)
		{
			mBoundingBox = mEditTextResource->getBoundingBox();
		}
	}
	//-----------------------------------------------------------------------
	EditText::~EditText()
	{
		delete mHtmlDom;
	}
	//-----------------------------------------------------------------------
	void EditText::_update(const float& delta_time)
	{
		DisplayObjectContainer::_update(delta_time);

		if(mNeedDomUpdate)
		{
			// update DOM
			if(mHtmlDom)
			{
				delete mHtmlDom;
			}

			HtmlParser html_parser;
			html_parser.parse(StringHelper::utf8Encode(mHtmlText));

			mText = StringHelper::utf8Decode(html_parser.getPlainText());
			mHtmlDom = html_parser.getRoot();

			mGlyphCount = 0;
			mCurrentHeight = 0.0f;
			mCurrentLine.reset();
			mCurrentStrip.reset();

			assert(!mStyleStack.size() && "Style stacks not cleared");

			mLines.clear();
			mGlyphStrips.clear();

			_recursiveDomIteration(mHtmlDom);

			_createStripsAndShapes();

			_updateGraphics();

			mNeedDomUpdate = false;
		}
	}
	//-----------------------------------------------------------------------
	void EditText::setText(const WString& text)
	{
		mText = text;
	}
	//-----------------------------------------------------------------------
	const WString& EditText::getText()
	{
		return mText;
	}
	//-----------------------------------------------------------------------
	void EditText::setHtmlText(const WString& text)
	{
		mHtmlText = text;
		mNeedDomUpdate = true;
	}
	//-----------------------------------------------------------------------
	const WString& EditText::getHtmlText()
	{
		return mHtmlText;
	}
	//-----------------------------------------------------------------------
	const BoundingBox& EditText::getBoundingBox() const
	{
		return mBoundingBox;
	}
	//-----------------------------------------------------------------------
	bool EditText::isPointInside(const Vector2& coord)
	{
		return false;
	}
	//-----------------------------------------------------------------------
	void EditText::setScriptObject(ScriptObject* obj)
	{

	}
	//-----------------------------------------------------------------------
	ScriptObject* EditText::getScriptObject() const
	{
		return NULL;
	}
	//-----------------------------------------------------------------------
	void EditText::_recursiveDomIteration(HtmlElement* source_element)
	{
		HtmlElement::ChildList::iterator it = source_element->children.begin();
		HtmlElement::ChildList::iterator end = source_element->children.end();
		while(it != end)
		{
			switch((*it)->type)
			{
			case HtmlElement::Font:
				{
					HtmlFont* font = dynamic_cast<HtmlFont*>(*it);
					if(!font) break;

					StyleElement style;

					if(font->face.length())
					{
						FontResource* new_font = mResource->getFile()->getFontByName(font->face);
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
						style.size = StringHelper::toFloat(font->size);
					else if(mStyleStack.size())
						style.size = mStyleStack.top().size;

					if(font->color.length())
						style.color = StringHelper::colorFromHex(font->color);
					else if(mStyleStack.size())
						style.color = mStyleStack.top().color;

					mStyleStack.push(style);

					// add FONT_CHANGE element
					LineElement font_element;
					font_element.type = LineElement::ET_FontChange;
					font_element.color = mStyleStack.top().color;
					font_element.font = mStyleStack.top().font;
					font_element.height = mStyleStack.top().size;
					font_element.x = mCurrentLine.width;
					mCurrentLine.elements.push_back(font_element);

					// continue recursion
					_recursiveDomIteration(*it);

					mStyleStack.pop();

					if(mStyleStack.size())
					{
						// add FONT_CHANGE element
						font_element.reset();
						font_element.type = LineElement::ET_FontChange;
						font_element.color = mStyleStack.top().color;
						font_element.font = mStyleStack.top().font;
						font_element.height = mStyleStack.top().size;
						font_element.x = mCurrentLine.width;
						mCurrentLine.elements.push_back(font_element);
					}
				}
				break;

			case HtmlElement::Image:
				{
					HtmlImage* img = dynamic_cast<HtmlImage*>(*it);
					if(!img) break;
					_addImage(img);
				}
				break;

			case HtmlElement::Paragraph:
				{
					HtmlParagraph* par = dynamic_cast<HtmlParagraph*>(*it);
					if(!par) break;

					mAlignStack.push(par->align);

					// continue recursion
					_recursiveDomIteration(*it);

					mAlignStack.pop();
				}
				break;

			case HtmlElement::Text:
				{
					HtmlText* text = dynamic_cast<HtmlText*>(*it);
					if(!text || !mStyleStack.size()) break;

					_addText(text->text);

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
	void EditText::_addImage(HtmlImage* image)
	{
		ShapeResource* shape_res = dynamic_cast<ShapeResource*>(mParentMovie->getFile()->getResource(image->src));
		if(!shape_res) return;

		// add FONT_CHANGE element
		LineElement font_element;
		font_element.type = LineElement::ET_FontChange;
		font_element.color = mStyleStack.top().color;
		font_element.font = mStyleStack.top().font;
		font_element.height = mStyleStack.top().size;
		font_element.x = mCurrentLine.width;
		mCurrentLine.elements.push_back(font_element);

		LineElement img;
		img.type = LineElement::ET_Image;
		img.align = image->align;
		img.image_shape = image->src;

		// dimensions explicitely given through HTML
		if(image->width != 0.0f || image->height != 0.0f)
		{
			// only height given
			if(image->width == 0.0f)
			{
				img.width = 
					(image->height / shape_res->getBoundingBox().getHeight()) * 
					shape_res->getBoundingBox().getWidth();
				img.height = image->height;
			}
			// only width given
			else if(image->height == 0.0f)
			{
				img.width = image->width;
				img.height = 
					(image->width / shape_res->getBoundingBox().getWidth()) * 
					shape_res->getBoundingBox().getHeight();
			}
			// both, width and height given
			else
			{
				img.width = image->width;
				img.height = image->height;
			}
		}
		// use default dimensions
		else
		{
			img.width = shape_res->getBoundingBox().getWidth();
			img.height = shape_res->getBoundingBox().getHeight();
		}

		// add the image element
		_addElement(img);

		if(mStyleStack.size())
		{
			// add FONT_CHANGE element
			font_element.reset();
			font_element.type = LineElement::ET_FontChange;
			font_element.color = mStyleStack.top().color;
			font_element.font = mStyleStack.top().font;
			font_element.height = mStyleStack.top().size;
			font_element.x = mCurrentLine.width;
			mCurrentLine.elements.push_back(font_element);
		}
	}
	//-----------------------------------------------------------------------
	void EditText::_addText(const WString& text)
	{
		LineElement word_element;
		word_element.type = LineElement::ET_Word;
		FontResource* font = mStyleStack.top().font;

		// iterate over characters
		WString::const_iterator str_it = text.begin();
		WString::const_iterator str_end = text.end();
		while(str_it != str_end)
		{
			// get glyph from font
			GlyphResource* glyph_res = font->getGlyphByCode(*str_it);
			if(!glyph_res)
			{
				VTX_WARN("Unable to find glyph for character %d", (int)*str_it);
				++str_it;
				continue;
			}

			GlyphStrip::Glyph glyph;
			glyph.index = glyph_res->getIndex();
			glyph.x = glyph_res->getAdvance() * mStyleStack.top().size/20.0f;
			word_element.width += glyph.x;
			word_element.glyphs.push_back(glyph);

			// word delimiter reached
			if(*str_it == ' ')
			{
				_addElement(word_element);
				word_element.reset();
			}

			++mGlyphCount;
			++str_it;

		} // while(characters)

		// last word not added yet
		if(word_element.glyphs.size())
		{
			_addElement(word_element);
			word_element.reset();
		}
	}
	//-----------------------------------------------------------------------
	void EditText::_addElement(const LineElement& elem)
	{
		// word doesn't fit into current line --> start a new one
		if(mCurrentLine.width + elem.width > getBoundingBox().getWidth())
		{
			_newLine();
		}

		switch(elem.type)
		{
		case LineElement::ET_Word:
			if(mStyleStack.top().size > mCurrentLine.height)
			{
				mCurrentLine.height = mStyleStack.top().size;
			}
			break;

		case LineElement::ET_Image:
			if(elem.height > mCurrentLine.height)
			{
				mCurrentLine.height = elem.height;
			}
			break;
		}

		// check if we are already at the bottom boundary of this textfield
		if(mCurrentHeight + mCurrentLine.height > getBoundingBox().getHeight())
		{
			return;
		}

		mCurrentLine.width += elem.width;
		mCurrentLine.elements.push_back(elem);
	}
	//-----------------------------------------------------------------------
	void EditText::_newLine()
	{
		mCurrentHeight += mCurrentLine.height;
		mLines.push_back(mCurrentLine);
		mCurrentLine.reset();
	}
	//-----------------------------------------------------------------------
	void EditText::_createStripsAndShapes()
	{
		if(mCurrentLine.elements.size())
		{
			// the last line has not been added yet
			_newLine();
		}

		// iterate lines
		LineList::iterator line_it = mLines.begin();
		LineList::iterator line_end = mLines.end();
		while(line_it != line_end)
		{
			const Line& line = *line_it;

			mCurrentStrip.y += line.height;

			// iterate line elements
			ElementList::const_iterator elem_it = line.elements.begin();
			ElementList::const_iterator elem_end = line.elements.end();
			while(elem_it != elem_end)
			{
				const LineElement& elem = *elem_it;

				switch(elem.type)
				{
				case LineElement::ET_FontChange:
					{
						mGlyphStrips.push_back(mCurrentStrip);
						mCurrentStrip.glyphs.clear();
						mCurrentStrip.x = elem.x;

						mCurrentStrip.color = elem.color;
						mCurrentStrip.fontid = elem.font->getID();
						mCurrentStrip.size = elem.height;
					}
					break;

				case LineElement::ET_Word:
					{
						mCurrentStrip.glyphs.insert(
							mCurrentStrip.glyphs.end(), 
							elem.glyphs.begin(), 
							elem.glyphs.end());
					}
					break;

				case LineElement::ET_Image:
					{
						Shape* shape = dynamic_cast<Shape*>(mParentMovie->getInstance(elem.image_shape));
						if(!shape) break;

						shape->setParentContainer(this);
						addChild(shape);
						float sx = elem.width / shape->getBoundingBox().getWidth();
						float sy = elem.height / shape->getBoundingBox().getHeight();
						shape->setMatrix(Matrix(sx, 0, mCurrentStrip.x + elem.x, 0, sy, mCurrentStrip.y - elem.height/* * 0.9f*/));
						mCurrentStrip.x += elem.width;
					}
					break;
				}

				++elem_it;

			} // while(line_elements)

			mCurrentStrip.newline = true;
			mGlyphStrips.push_back(mCurrentStrip);
			mCurrentStrip.glyphs.clear();
			mCurrentStrip.x = 0.0f;

			++line_it;

		} // while(lines)
	}
	//-----------------------------------------------------------------------
}
