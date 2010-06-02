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
	const String EditText::TYPE = "EditText";
	//-----------------------------------------------------------------------
	EditText::EditText() 
		: mNeedDomUpdate(true), 
		mSelectionBeginIndex(0), 
		mSelectionEndIndex(0), 
		mHtmlDom(NULL), 
		mGlyphCount(0), 
		mSelecting(false)
	{
		mBoundingBox = BoundingBox(0, 0, 100, 100);
	}
	//-----------------------------------------------------------------------
	EditText::~EditText()
	{
		delete mHtmlDom;
	}
	//-----------------------------------------------------------------------
	void EditText::initFromResource(Resource* resource)
	{
		EditTextResource* text_res = dynamic_cast<EditTextResource*>(resource);

		if(text_res)
		{
			mBoundingBox = text_res->getBoundingBox();
		}
	}
	//-----------------------------------------------------------------------
	const String& EditText::getType() const
	{
		return TYPE;
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
		return HtmlOperations::getHtmlText(mHtmlDom);
	}
	//-----------------------------------------------------------------------
	const GlyphStrip::Glyph& EditText::getGlyphAtPoint(const Vector2& point)
	{
		const TextLine& line = getLineAtPoint(point);

		// iterate line elements
		TextLine::ElementList::const_iterator elem_it = line.elements.begin();
		TextLine::ElementList::const_iterator elem_end = line.elements.end();
		while(elem_it != elem_end)
		{
			const TextLineElement& elem = *elem_it;

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
	const TextLine& EditText::getLineAtPoint(const Vector2& point)
	{
		static const TextLine empty;

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
			const TextLine& line = *line_it;

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
			const KeyboardEvent& keybd_evt = static_cast<const KeyboardEvent&>(evt);

			keyboardEvent(keybd_evt);
		}
		else if(evt.getCategory() == MouseEvent::CATEGORY)
		{
			const MouseEvent& mouse_evt = static_cast<const MouseEvent&>(evt);

			mouseEvent(mouse_evt);
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

		mLines.clear();
		mGlyphStrips.clear();

		_clearSelectionShapes();

		clearLayers();

		interateDomTree(mHtmlDom, mParentMovie->getFile());

		_createStripsAndShapes();

		_createSelectionShapes();

		_updateGraphics();
	}
	//-----------------------------------------------------------------------
	void EditText::_addFont(HtmlFont* font)
	{

	}
	//-----------------------------------------------------------------------
	void EditText::_fontStyleChanged(const StyleElement& style)
	{
		// add FONT_CHANGE element
		TextLineElement font_element;
		font_element.type = TextLineElement::ET_FontChange;
		font_element.color = style.color;
		font_element.font = style.font;
		font_element.height = style.size;
		font_element.x = mCurrentLine.width;
		mCurrentLine.elements.push_back(font_element);
	}
	//-----------------------------------------------------------------------
	void EditText::_addImage(HtmlImage* image)
	{
		ShapeResource* shape_res = dynamic_cast<ShapeResource*>(mParentMovie->getFile()->getResource(image->src));
		if(!shape_res) return;

		TextLineElement img;
		img.type = TextLineElement::ET_Image;
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
	}
	//-----------------------------------------------------------------------
	void EditText::_addParagraph(HtmlParagraph* paragraph)
	{

	}
	//-----------------------------------------------------------------------
	void EditText::_addText(HtmlText* text)
	{
		const StyleElement& style = getCurrentStyle();

		TextLineElement word_element;
		word_element.type = TextLineElement::ET_Word;
		word_element.parentHTML = text;
		FontResource* font = style.font;

		if(!font)
		{
			VTX_WARN("Invalid font");
			return;
		}

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
			glyph.x_advance = glyph_res->getAdvance() * style.size/20.0f;
			word_element.width += glyph.x_advance;
			glyph.x_in_word = word_element.width;
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
	void EditText::_addLineElement(TextLineElement& elem)
	{
		const StyleElement& style = getCurrentStyle();

		// word doesn't fit into current line --> start a new one
		if(mCurrentLine.width + elem.width > getBoundingBox().getWidth())
		{
			_startNewLine();
		}

		switch(elem.type)
		{
		case TextLineElement::ET_Word:
			if(style.size > mCurrentLine.height)
			{
				mCurrentLine.height = style.size;
			}
			break;

		case TextLineElement::ET_Image:
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
	void EditText::keyboardEvent(const KeyboardEvent& evt)
	{
		if(evt.getType() == KeyboardEvent::KEY_DOWN)
		{
			switch(evt.keyCode)
			{
			case KC_LEFT:
				{
					mSelectionBegin = mSelectionEnd = 
						selectBackward(mSelectionBegin);

					// TODO: add "_buildSelectionShapes()" since no DOM update should be necessary here
					// add special method at EditText for calculating and updating graphical selection properties
					_buildGraphicsFromDOM();
				}
				break;

			case KC_RIGHT:
				{
					mSelectionBegin = mSelectionEnd = 
						selectForward(mSelectionEnd);

					_buildGraphicsFromDOM();
				}
				break;

			case KC_BACK:
				{
					if(mSelectionBegin.element && mSelectionEnd.element)
					{
						if(mSelectionBegin != mSelectionEnd)
						{
							mSelectionBegin = mSelectionEnd = 
								eraseSelection(mHtmlDom, mSelectionBegin, mSelectionEnd);
						}
						else
						{
							mSelectionBegin = mSelectionEnd = 
								eraseBackward(mSelectionBegin);
						}

						_buildGraphicsFromDOM();
					}
				}
				break;

			case KC_DELETE:
				{
					if(mSelectionBegin.element && mSelectionEnd.element)
					{
						if(mSelectionBegin != mSelectionEnd)
						{
							mSelectionBegin = mSelectionEnd = 
								eraseSelection(mHtmlDom, mSelectionBegin, mSelectionEnd);
						}
						else
						{
							mSelectionBegin = mSelectionEnd = 
								eraseForward(mSelectionBegin);
						}

						_buildGraphicsFromDOM();
					}
				}
				break;

			case KC_RETURN:
				break;

				// usual character input
			default:
				if(mSelectionBegin == mSelectionEnd && evt.charCode != 0)
				{
					if(mSelectionBegin.element)
					{
						if(mSelectionBegin.element->getType() == HtmlElement::Text && mSelectionBegin.subSel >= 0)
						{
							HtmlText* text = static_cast<HtmlText*>(mSelectionBegin.element);
							text->text.insert(mSelectionBegin.subSel, 1, evt.charCode);
							++mSelectionBegin.subSel;
							++mSelectionEnd.subSel;
							_buildGraphicsFromDOM();
						}
					}
				}
				break;
			}
		}
	}
	//-----------------------------------------------------------------------
	void EditText::mouseEvent(const MouseEvent& evt)
	{
		if(isPointInside(Vector2(evt.stageX, evt.stageY)))
		{
			Vector2 coord = mTransform.getWorldMatrix().transformInverse(
				Vector2(evt.stageX, evt.stageY));

			if(evt.getType() == MouseEvent::MOUSE_DOWN)
			{
				mSelectionBegin = _getSelectionAtPoint(coord);
				mSelecting = true;
			}
			else if(evt.getType() == MouseEvent::MOUSE_MOVE)
			{
				if(mSelecting)
				{
					mSelectionEnd = _getSelectionAtPoint(coord);
					_createSelectionShapes();
				}
			}
		}

		// TODO: no more _getSelectionAtPoint here, just use the already present result
		// (note: but looks like its needed, without it failure)
		if(evt.getType() == MouseEvent::MOUSE_UP)
		{
			Vector2 coord = mTransform.getWorldMatrix().transformInverse(
				Vector2(evt.stageX, evt.stageY));

			mSelectionEnd = _getSelectionAtPoint(coord);
			_createSelectionShapes();
			mSelecting = false;
		}
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
		//LineList::iterator line_it = mLines.begin();
		//LineList::iterator line_end = mLines.end();
		//while(line_it != line_end)
		for(uint line_it=0; line_it<mLines.size(); ++line_it)
		{
			//const TextLine& line = *line_it;
			const TextLine& line = mLines.at(line_it);

			mCurrentStrip.y += line.height;

			// iterate line elements
			TextLine::ElementList::const_iterator elem_it = line.elements.begin();
			TextLine::ElementList::const_iterator elem_end = line.elements.end();
			while(elem_it != elem_end)
			{
				const TextLineElement& elem = *elem_it;

				switch(elem.type)
				{
				case TextLineElement::ET_FontChange:
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

				case TextLineElement::ET_Word:
					{
						// DEBUG
						if(
							elem.parentHTML == mSelectionBegin.element && 
							mSelectionBegin == mSelectionEnd)
						{
							if(elem.glyphs.size())
							{
								const int& startIdx = elem.glyphs.front().index_in_string;
								const int& endIdx = elem.glyphs.back().index_in_string;

								if(mSelectionBegin.subSel >= startIdx && 
									mSelectionBegin.subSel <= endIdx+1)
								{
									std::cout << "successful x calc" << std::endl;
									mSelectionBegin.lineIndex = mSelectionEnd.lineIndex = line_it;
									mSelectionBegin.x = elem.x;

									int idx = mSelectionBegin.subSel-startIdx-1;
									if(idx >= 0)
									{
										mSelectionBegin.x += elem.glyphs.at(idx).x_in_word;
									}

									//GlyphStrip::GlyphList::const_iterator glyph_it = elem.glyphs.begin();
									//GlyphStrip::GlyphList::const_iterator glyph_end = elem.glyphs.end();
									//while(glyph_it != glyph_end && (*glyph_it).index_in_string < mSelectionBegin.subSel)
									//{
									//	mSelectionBegin.x += (*glyph_it).x_advance;
									//	++glyph_it;
									//}

									mSelectionEnd.x = mSelectionBegin.x;
								}
							}
						}

						mCurrentStrip.glyphs.insert(
							mCurrentStrip.glyphs.end(), 
							elem.glyphs.begin(), 
							elem.glyphs.end());
					}
					break;

				case TextLineElement::ET_Image:
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

		} // for(lines)
	}
	//-----------------------------------------------------------------------
	void EditText::_addSelectionShape(const float& sx, const float& sy, 
		const float& x, const float& y)
	{
		Shape* shape = dynamic_cast<Shape*>(mParentMovie->getInstance("BlackBox"));
		if(shape)
		{
			addChild(shape);
			mSelectionShapes.push_back(shape);

			shape->setMatrix(Matrix(
				sx, 0, x, 
				0, sy, y));
		}
	}
	//-----------------------------------------------------------------------
	void EditText::_createSelectionShapes()
	{
		// TODO: fix bug when selectionBegin is an empty space
		if(mSelectionBegin.lineIndex < 0 || mSelectionEnd.lineIndex < 0)
		{
			return;
		}

		_clearSelectionShapes();

		// simple cursor position
		if(mSelectionBegin == mSelectionEnd)
		{
			const TextLine& line = mLines.at(mSelectionBegin.lineIndex);
			_addSelectionShape(
				1.0f, line.height, 
				mSelectionBegin.x-0.5f, line.y-line.height);
		}
		// selecting backwards
		else if(mSelectionBegin > mSelectionEnd)
		{
			// selecting a single line
			if(mSelectionBegin.lineIndex == mSelectionEnd.lineIndex)
			{
				const TextLine& line = mLines.at(mSelectionBegin.lineIndex);

				_addSelectionShape(
					mSelectionBegin.x-mSelectionEnd.x, line.height, 
					mSelectionEnd.x, line.y-line.height);
			}
			// selecting multiple lines
			else
			{
				for(int i=mSelectionBegin.lineIndex; i>=mSelectionEnd.lineIndex; --i)
				{
					const TextLine& line = mLines.at(i);

					// last line
					if(i == mSelectionBegin.lineIndex)
					{
						_addSelectionShape(
							mSelectionBegin.x, line.height, 
							0.0f, line.y-line.height);
					}
					// first line
					else if(i == mSelectionEnd.lineIndex)
					{
						_addSelectionShape(
							getBoundingBox().getWidth()-mSelectionEnd.x, line.height, 
							mSelectionEnd.x, line.y-line.height);
					}
					// lines in between
					else
					{
						_addSelectionShape(
							getBoundingBox().getWidth(), line.height, 
							0.0f, line.y-line.height);
					}

				} // for(lines)
			}
		}
		// selecting forward
		else
		{
			// selecting a single line
			if(mSelectionBegin.lineIndex == mSelectionEnd.lineIndex)
			{
				const TextLine& line = mLines.at(mSelectionBegin.lineIndex);

				_addSelectionShape(
					mSelectionEnd.x-mSelectionBegin.x, line.height, 
					mSelectionBegin.x, line.y-line.height);
			}
			// selecting multiple lines
			else
			{
				for(int i=mSelectionBegin.lineIndex; i<=mSelectionEnd.lineIndex; ++i)
				{
					const TextLine& line = mLines.at(i);

					// first line
					if(i == mSelectionBegin.lineIndex)
					{
						_addSelectionShape(
							getBoundingBox().getWidth()-mSelectionBegin.x, line.height, 
							mSelectionBegin.x, line.y-line.height);
					}
					// last line
					else if(i == mSelectionEnd.lineIndex)
					{
						_addSelectionShape(
							mSelectionEnd.x, line.height, 
							0.0f, line.y-line.height);
					}
					// lines in between
					else
					{
						_addSelectionShape(
							getBoundingBox().getWidth(), line.height, 
							0.0f, line.y-line.height);
					}

				} // for(lines)
			}
		}
	}
	//-----------------------------------------------------------------------
	void EditText::_clearSelectionShapes()
	{
		SelectionShapes::iterator it = mSelectionShapes.begin();
		SelectionShapes::iterator end = mSelectionShapes.end();
		while(it != end)
		{
			removeChildAt((*it)->getLayer());
			++it;
		}

		mSelectionShapes.clear();
	}
	//-----------------------------------------------------------------------
	HtmlSelection EditText::_getSelectionAtPoint(const Vector2& point)
	{
		const TextLine& line = getLineAtPoint(point);

		// valid line
		if(line.index >= 0)
		{
			// iterate line elements
			TextLine::ElementList::const_iterator elem_it = line.elements.begin();
			TextLine::ElementList::const_iterator elem_end = line.elements.end();
			while(elem_it != elem_end)
			{
				const TextLineElement& elem = *elem_it;

				if(elem.x <= point.x && elem.x + elem.width >= point.x)
				{
					HtmlSelection sel;
					sel.x = elem.x + elem.width;
					sel.lineIndex = line.index;
					sel.element = elem.parentHTML;
					//sel.subSelection = -1; // TODO: check for correctness / debug

					if(sel.element)
					{
						if(sel.element->getType() == HtmlElement::Text)
						{
							float glyph_x = elem.x;
							GlyphStrip::GlyphList::const_iterator glyph_it = elem.glyphs.begin();
							GlyphStrip::GlyphList::const_iterator glyph_end = elem.glyphs.end();
							while(glyph_it != glyph_end)
							{
								const GlyphStrip::Glyph& glyph = *glyph_it;

								if(glyph_x + glyph.x_advance * 0.5f >= point.x)
								{
									sel.x = glyph_x;
									sel.subSel = glyph.index_in_string;
									return sel;
								}

								glyph_x += glyph.x_advance;

								++glyph_it;
							}
						}
						else if(sel.element->getType() == HtmlElement::Image)
						{
							// TODO: find next or previous "Text" node and set it as selection instead
							float center = elem.x + elem.width * 0.5f;

							HtmlImage* img = static_cast<HtmlImage*>(sel.element);

							//sel.x = elem.x + elem.width;

							// cursor to the left of the image
							if(point.x < center)
							{
								sel.element = img->prevVisualNode;

								HtmlText* prevText = dynamic_cast<HtmlText*>(img->prevVisualNode);
								if(prevText)
								{
									sel.subSel = prevText->text.length();
								}
							}
							// cursor to the right of the image
							else
							{
								sel.element = img->nextVisualNode;

								HtmlText* nextText = dynamic_cast<HtmlText*>(img->nextVisualNode);
								if(nextText)
								{
									sel.subSel = 0;
								}
							}

							return sel;

						} // switch(element.type)

					} // if(sel.element)

					return sel;

				} // point inside element

				++elem_it;

			} // while(line_elements)

		} // if(line.index >= 0)

		// no selection found
		return HtmlSelection();
	}
	//-----------------------------------------------------------------------
}
