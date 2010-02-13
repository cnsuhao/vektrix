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
#include "vtxHtmlParser.h"
#include "vtxHtmlText.h"
#include "vtxLogManager.h"
#include "vtxScriptEditText.h"
#include "vtxStringHelper.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	EditText::EditText(Resource* resource) 
		: MovableObject(resource), 
		mNeedDomUpdate(true), 
		mHtmlDom(NULL), 
		mGlyphCount(0), 
		mMaxSize(0.0f), 
		mPosition(0.0f)
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
	const String& EditText::getType() const
	{
		static String type = "EditText";
		return type;
	}
	//-----------------------------------------------------------------------
	void EditText::_update(const float& delta_time)
	{
		MovableObject::_update(delta_time);

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
			mMaxSize = 0.0f;
			mPosition = 0.0f;
			mGlyphStrips.clear();

			_recursiveDomIteration(mHtmlDom);

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

					FontResource* new_font = mResource->getFile()->getFontByName(font->face);
					if(new_font)
					{
						mFontStack.push(new_font);
					}
					// font name given, but font unavailable
					else if(font->face.length())
					{
						VTX_WARN("Unable to find font %s", font->face.c_str());
					}

					if(font->size.length()) mSizeStack.push(StringHelper::toFloat(font->size));
					if(font->color.length()) mColorStack.push(StringHelper::colorFromHex(font->color));

					// continue recursion
					_recursiveDomIteration(*it);

					if(new_font) mFontStack.pop();
					if(font->size.length()) mSizeStack.pop();
					if(font->color.length()) mColorStack.pop();
				}
				break;

			case HtmlElement::Text:
				{
					HtmlText* text = dynamic_cast<HtmlText*>(*it);
					if(!text || !mFontStack.size()) break;

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
	void EditText::_addText(const WString& text)
	{
		mCurrentStrip.glyphs.clear();
		mCurrentStrip.color = mColorStack.top();
		mCurrentStrip.size = mSizeStack.top();
		mCurrentStrip.fontid = mFontStack.top()->getID();

		float word_length = 0.0f;
		StaticTextResource::GlyphList word;

		WString::const_iterator str_it = text.begin();
		WString::const_iterator str_end = text.end();
		while(str_it != str_end)
		{
			// get glyph from font
			GlyphResource* glyph_res = mFontStack.top()->getGlyphByCode(*str_it);
			if(!glyph_res)
			{
				VTX_WARN("Unable to find glyph for character %d", (int)*str_it);
				++str_it;
				continue;
			}

			float max_size = mSizeStack.top()*0.05f*glyph_res->getBoundingBox().getHeight();
			if(max_size > mMaxSize)
			{
				mMaxSize = max_size;
			}

			StaticTextResource::Glyph glyph;
			glyph.index = glyph_res->getIndex();
			glyph.x = glyph_res->getAdvance() * mSizeStack.top()/20.0f;
			word_length += glyph.x;
			word.push_back(glyph);

			if(*str_it == ' ')
			{
				_addWord(word, word_length);
				word.clear();
				word_length = 0.0f;
			}

			++mGlyphCount;
			++str_it;

		} // while(characters)

		// add imaginary word which is nearly as long as a whole line
		// this is just done to add the very last glyph strip to the text
		_addWord(StaticTextResource::GlyphList(), getBoundingBox().getWidth()*0.99f);
	}
	//-----------------------------------------------------------------------
	void EditText::_addWord(const StaticTextResource::GlyphList& glyphs, const float& word_length)
	{
		StaticTextResource::GlyphList::const_iterator it = glyphs.begin();
		StaticTextResource::GlyphList::const_iterator end = glyphs.end();

		const float& textfield_width = getBoundingBox().getWidth();

		// word doesn't fit into this line as a whole
		if(mPosition + word_length > textfield_width)
		{
			// special case, the word is longer than the textfield width
			if(word_length > textfield_width)
			{
				while(it != end)
				{
					const StaticTextResource::Glyph& glyph = *it;

					// glyph doesn't fit into current line, start a new one
					if(mPosition + glyph.x > textfield_width)
					{
						mCurrentStrip.newline = true;
						_addStrip();
					}
					//// glyph does fit into current line
					//else
					//{
					//	mCurrentStrip.newline = true;
					//}

					mPosition += glyph.x;
					mCurrentStrip.glyphs.push_back(glyph);
					++it;

				} // while(glyphs)
			}
			// add word into a new line
			else
			{
				// finish previous line and start a new one
				mCurrentStrip.newline = true;
				_addStrip();

				while(it != end)
				{
					const StaticTextResource::Glyph& glyph = *it;
					mCurrentStrip.glyphs.push_back(glyph);
					++it;
				}

				mPosition += word_length;
			}
		}
		// word fits into current line
		else
		{
			while(it != end)
			{
				const StaticTextResource::Glyph& glyph = *it;
				mCurrentStrip.glyphs.push_back(glyph);
				++it;
			}

			mPosition += word_length;
		}
	}
	//-----------------------------------------------------------------------
	void EditText::_addStrip()
	{
		// DEBUG
		//mCurrentStrip.color = Color(rand()%255/255.0f, rand()%255/255.0f, rand()%255/255.0f);

		mGlyphStrips.push_back(mCurrentStrip);

		if(mCurrentStrip.newline)
		{
			mCurrentStrip.y += mMaxSize * 1.2f; // TODO: line spacing
			mPosition = 0.0f;
		}

		mCurrentStrip.glyphs.clear();
		mCurrentStrip.newline = false;
	}
	//-----------------------------------------------------------------------
}
