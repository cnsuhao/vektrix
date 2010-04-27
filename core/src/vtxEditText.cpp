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
#include "vtxHtmlFont.h"
#include "vtxHtmlImage.h"
#include "vtxHtmlParser.h"
#include "vtxHtmlParagraph.h"
#include "vtxHtmlText.h"
#include "vtxKeyboardEvent.h"
#include "vtxLogManager.h"
#include "vtxMouseEvent.h"
#include "vtxMovie.h"
#include "vtxScriptObject.h"
#include "vtxShape.h"
#include "vtxShapeResource.h"
#include "vtxStringHelper.h"

#include "vtxHtmlOperations.h"

#include "vtxFocusEvent.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	EditText::EditText(Resource* resource) 
		: DisplayObjectContainer(resource), 
		mNeedDomUpdate(true), 
		mSelectionBeginIndex(0), 
		mSelectionEndIndex(0), 
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
			delete mHtmlDom;

			HtmlParser html_parser;
			html_parser.parse(StringHelper::utf8Encode(mHtmlText));

			mText = StringHelper::utf8Decode(html_parser.getPlainText());
			mHtmlDom = html_parser.getRoot();

			_buildGraphicsFromDOM();

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
	const GlyphStrip::Glyph& EditText::getGlyphAtPoint(const Vector2& point)
	{
		const Line& line = getLineAtPoint(point);

		// iterate line elements
		ElementList::const_iterator elem_it = line.elements.begin();
		ElementList::const_iterator elem_end = line.elements.end();
		while(elem_it != elem_end)
		{
			const LineElement& elem = *elem_it;

			if(elem.x <= point.x && elem.x + elem.width >= point.x)
			{
				GlyphStrip::GlyphList::const_iterator glyph_it = elem.glyphs.begin();
				GlyphStrip::GlyphList::const_iterator glyph_end = elem.glyphs.end();
				while(glyph_it != glyph_end)
				{
					const GlyphStrip::Glyph& glyph = *glyph_it;
					return glyph;
				}
			}

			++elem_it;
		}

		// no fitting glyph found
		static GlyphStrip::Glyph glyph;
		return glyph;
	}
	//-----------------------------------------------------------------------
	const EditText::Line& EditText::getLineAtPoint(const Vector2& point)
	{
		static const Line empty;

		if(
			point.x < 0.0f || 
			point.x > getBoundingBox().getWidth() || 
			point.y < 0.0f || 
			point.y > getBoundingBox().getHeight())
		{
			return empty;
		}

		// iterate lines
		LineList::iterator line_it = mLines.begin();
		LineList::iterator line_end = mLines.end();
		while(line_it != line_end)
		{
			const Line& line = *line_it;

			// line that contains the given point reached
			if(line.y - line.height <= point.y && line.y >= point.y)
			{
				return line;
			}

			++line_it;
		}

		// no fitting line found
		return empty;
	}
	//-----------------------------------------------------------------------
	void EditText::setSelection(const uint& beginIndex, const uint& endIndex)
	{
		mSelectionBeginIndex = beginIndex;
		mSelectionEndIndex = endIndex;
	}
	//-----------------------------------------------------------------------
	const uint& EditText::getSelectionBeginIndex() const
	{
		return mSelectionBeginIndex;
	}
	//-----------------------------------------------------------------------
	const uint& EditText::getSelectionEndIndex() const
	{
		return mSelectionEndIndex;
	}
	//-----------------------------------------------------------------------
	const BoundingBox& EditText::getBoundingBox() const
	{
		return mBoundingBox;
	}
	//-----------------------------------------------------------------------
	bool EditText::isPointInside(const Vector2& coord)
	{
		if(coord.x >= mTransform.getWorldBounding().getMinX() && 
			coord.x <= mTransform.getWorldBounding().getMaxX() && 
			coord.y >= mTransform.getWorldBounding().getMinY() && 
			coord.y <= mTransform.getWorldBounding().getMaxY())
		{
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	void EditText::eventFired(const Event& evt)
	{
		DisplayObjectContainer::eventFired(evt);

		if(evt.getCategory() == KeyboardEvent::CATEGORY)
		{
			const KeyboardEvent& keybd_evt = dynamic_cast<const KeyboardEvent&>(evt);

			if(evt.getType() == KeyboardEvent::KEY_DOWN)
			{
				switch(keybd_evt.keyCode)
				{
				case KC_BACK:
					{
						// DEBUG
						Shape* shape = dynamic_cast<Shape*>(mParentMovie->getInstance("BlackBox"));
						if(shape)
						{
							// TODO:
							addChildAt(shape, -1);
							shape->setMatrix(Matrix(100, 0, 0, 0, 100, 0));
						}
					}
					break;

				case KC_DELETE:
					{
						if(mSelectionBegin.element && mSelectionEnd.element)
						{
							HtmlOperations op(mHtmlDom);
							op.eraseSelection(mSelectionBegin, mSelectionEnd);
							_buildGraphicsFromDOM();
						}
					}
					break;

				case KC_RETURN:
					break;

					// usual character input
				default:
					if(mSelectionBegin == mSelectionEnd && keybd_evt.charCode != 0)
					{
						if(mSelectionBegin.element)
						{
							if(mSelectionBegin.element->type == HtmlElement::Text && mSelectionBegin.subSelection >= 0)
							{
								HtmlText* text = dynamic_cast<HtmlText*>(mSelectionBegin.element);
								text->text.insert(mSelectionBegin.subSelection, 1, keybd_evt.charCode);
								++mSelectionBegin.subSelection;
								++mSelectionEnd.subSelection;
								_buildGraphicsFromDOM();
							}
						}
					}
					break;
				}
			}

			//VTX_LOG("Key pressed: code: %d, char: %c", keybd_evt.keyCode, keybd_evt.charCode);
		}
		else if(evt.getCategory() == MouseEvent::CATEGORY)
		{
			const MouseEvent& mouse_evt = dynamic_cast<const MouseEvent&>(evt);

			if(isPointInside(Vector2(mouse_evt.stageX, mouse_evt.stageY)))
			{
				Vector2 coord = mTransform.getWorldMatrix().transformInverse(
					Vector2(mouse_evt.stageX, mouse_evt.stageY));

				if(mouse_evt.getType() == MouseEvent::MOUSE_DOWN)
				{
					mSelectionBegin = _getSelectionAtPoint(coord);
				}
				else if(mouse_evt.getType() == MouseEvent::MOUSE_UP)
				{
					mSelectionEnd = _getSelectionAtPoint(coord);
				}
			}
		}
		else if(evt.getCategory() == FocusEvent::CATEGORY)
		{
			//if(evt.getType() == FocusEvent::FOCUS_IN)
			//{
			//	VTX_LOG("FOCUS_IN");
			//}
			//else if(evt.getType() == FocusEvent::FOCUS_OUT)
			//{
			//	VTX_LOG("FOCUS_OUT");
			//}
		}

		// TODO: do this in InteractiveObject
		if(mScriptObject)
		{
			mScriptObject->eventFired(evt);
		}
	}
	//-----------------------------------------------------------------------
	void EditText::_buildGraphicsFromDOM()
	{
		mGlyphCount = 0;
		mCurrentHeight = 0.0f;
		mCurrentLine.reset();
		mCurrentStrip.reset();

		mPreviousTextNode = NULL;
		mPreviousImageNode = NULL;

		assert(!mStyleStack.size() && "Style stacks not cleared");

		mLines.clear();
		mGlyphStrips.clear();
		mComposedHTMLText.clear();

		clearLayers();

		_recursiveDomIteration(mHtmlDom);

		_createStripsAndShapes();

		_updateGraphics();
	}
	//-----------------------------------------------------------------------
	void EditText::_recursiveDomIteration(HtmlElement* source_element)
	{
		HtmlElement::ChildList::const_iterator it = source_element->children.begin();
		HtmlElement::ChildList::const_iterator end = source_element->children.end();
		while(it != end)
		{
			switch((*it)->type)
			{
			case HtmlElement::Font:
				{
					HtmlFont* font = dynamic_cast<HtmlFont*>(*it);
					if(!font) break;

					mComposedHTMLText += L"<font";

					StyleElement style;

					if(font->face.length())
					{
						mComposedHTMLText += L" face=";
						mComposedHTMLText.append(font->face.begin(), font->face.end());

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
					{
						mComposedHTMLText += L" size=";
						mComposedHTMLText.append(font->size.begin(), font->size.end());

						style.size = StringHelper::toFloat(font->size);
					}
					else if(mStyleStack.size())
						style.size = mStyleStack.top().size;

					if(font->color.length())
					{
						mComposedHTMLText += L" color=";
						mComposedHTMLText.append(font->color.begin(), font->color.end());

						style.color = StringHelper::colorFromHex(font->color);
					}
					else if(mStyleStack.size())
						style.color = mStyleStack.top().color;

					mComposedHTMLText += L">";

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

					mComposedHTMLText += L"</font>";

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

					// apply previous text node to this image
					img->prevTextNode = mPreviousTextNode;
					mPreviousImageNode = img;

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

					_addText(text);

					// apply this text node as "next-node" to the previous image
					if(mPreviousImageNode)
					{
						if(!mPreviousImageNode->nextTextNode)
						{
							mPreviousImageNode->nextTextNode = text;
						}
					}
					mPreviousTextNode = text;

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
		img.parentHTML = image;

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
		_addLineElement(img);

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
	void EditText::_addText(HtmlText* text)
	{
		LineElement word_element;
		word_element.type = LineElement::ET_Word;
		word_element.parentHTML = text;
		FontResource* font = mStyleStack.top().font;

		// iterate over characters
		uint charIndex = 0;
		WString::const_iterator str_it = text->text.begin();
		WString::const_iterator str_end = text->text.end();
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
			glyph.index_in_string = charIndex;
			glyph.x_advance = glyph_res->getAdvance() * mStyleStack.top().size/20.0f;
			word_element.width += glyph.x_advance;
			word_element.glyphs.push_back(glyph);

			// word delimiter reached
			if(*str_it == ' ')
			{
				_addLineElement(word_element);
				word_element.reset();
			}

			++mGlyphCount;
			++charIndex;
			++str_it;

		} // while(characters)

		// last word not added yet
		if(word_element.glyphs.size())
		{
			_addLineElement(word_element);
			word_element.reset();
		}
	}
	//-----------------------------------------------------------------------
	void EditText::_addLineElement(LineElement& elem)
	{
		// word doesn't fit into current line --> start a new one
		if(mCurrentLine.width + elem.width > getBoundingBox().getWidth())
		{
			_startNewLine();
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
		if(mCurrentHeight/* + mCurrentLine.height*/ > getBoundingBox().getHeight())
		{
			return;
		}

		elem.x = mCurrentLine.width;
		mCurrentLine.width += elem.width;
		mCurrentLine.elements.push_back(elem);
	}
	//-----------------------------------------------------------------------
	void EditText::_startNewLine()
	{
		mCurrentHeight += mCurrentLine.height;
		mCurrentLine.index = mLines.size();
		mCurrentLine.y = mCurrentHeight;
		mLines.push_back(mCurrentLine);
		mCurrentLine.reset();
	}
	//-----------------------------------------------------------------------
	void EditText::_createStripsAndShapes()
	{
		if(mCurrentLine.elements.size())
		{
			// the last line has not been added yet
			_startNewLine();
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
						// only store the current strip if there already were some glyphs processed
						if(mCurrentStrip.glyphs.size())
						{
							mGlyphStrips.push_back(mCurrentStrip);
						}

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

						addChild(shape);
						float sx = elem.width / shape->getBoundingBox().getWidth();
						float sy = elem.height / shape->getBoundingBox().getHeight();
						shape->setMatrix(Matrix(sx, 0, /*mCurrentStrip.x + */elem.x, 0, sy, mCurrentStrip.y - elem.height/* * 0.9f*/));
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
	HtmlSelection EditText::_getSelectionAtPoint(const Vector2& point)
	{
		const Line& line = getLineAtPoint(point);

		// valid line
		if(line.index >= 0)
		{
			// iterate line elements
			ElementList::const_iterator elem_it = line.elements.begin();
			ElementList::const_iterator elem_end = line.elements.end();
			while(elem_it != elem_end)
			{
				const LineElement& elem = *elem_it;

				if(elem.x <= point.x && elem.x + elem.width >= point.x)
				{
					HtmlSelection selection;
					selection.element = elem.parentHTML;

					if(selection.element)
					{
						if(selection.element->type == HtmlElement::Text)
						{
							float glyph_x = elem.x;
							GlyphStrip::GlyphList::const_iterator glyph_it = elem.glyphs.begin();
							GlyphStrip::GlyphList::const_iterator glyph_end = elem.glyphs.end();
							while(glyph_it != glyph_end)
							{
								const GlyphStrip::Glyph& glyph = *glyph_it;

								if(glyph_x + glyph.x_advance * 0.5f >= point.x)
								{
									selection.subSelection = glyph.index_in_string;
									return selection;
								}

								glyph_x += glyph.x_advance;

								++glyph_it;
							}
						}
						else if(selection.element->type == HtmlElement::Image)
						{
							// TODO: find next or previous "Text" node and set it as selection instead
							float center = elem.x + elem.width * 0.5f;

							HtmlImage* img = dynamic_cast<HtmlImage*>(elem.parentHTML);

							if(img)
							{
								// cursor to the left of the image
								if(point.x < center)
								{
									selection.element = img->prevTextNode;
									if(img->prevTextNode)
									{
										selection.subSelection = img->prevTextNode->text.length();
									}
								}
								// cursor to the right of the image
								else
								{
									selection.element = img->nextTextNode;
									if(img->nextTextNode)
									{
										selection.subSelection = 0;
									}
								}
							}

							return selection;
						}
					}

					return selection;

				} // point inside element

				++elem_it;

			} // while(line_elements)

		} // if(line.index >= 0)

		// no selection found
		return HtmlSelection();
	}
	//-----------------------------------------------------------------------
}
