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

#include "vtxHtmlParser.h"

#include "vtxEditTextResource.h"
#include "vtxFile.h"
#include "vtxFontResource.h"
#include "vtxGlyphResource.h"
#include "vtxHtmlElement.h"
#include "vtxHtmlFont.h"
#include "vtxHtmlImage.h"
#include "vtxHtmlParagraph.h"
#include "vtxHtmlText.h"
#include "vtxLogManager.h"
#include "vtxStringHelper.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	HtmlParser::HtmlParser() 
		: mPrevElementWasText(false)
	{

	}
	//-----------------------------------------------------------------------
	HtmlParser::~HtmlParser()
	{

	}
	//-----------------------------------------------------------------------
	bool HtmlParser::parse(const String& input)
	{
		mPlainText.clear();
		while(mElementStack.size()) mElementStack.pop(); // clear

		mRoot = new HtmlElement(HtmlElement::Root);
		mElementStack.push(mRoot);

		// ensure that expat doesn't throw the XML_ERROR_JUNK_AFTER_DOC_ELEMENT error
		String html_input = "<html>" + input + "</html>";

		if(!XmlParser::parse(html_input))
		{
			delete mRoot;
			mRoot = NULL;
			return false;
		}

		return true;
	}
	//-----------------------------------------------------------------------
	HtmlElement* HtmlParser::getRoot() const
	{
		return mRoot;
	}
	//-----------------------------------------------------------------------
	const String& HtmlParser::getPlainText() const
	{
		return mPlainText;
	}
	//-----------------------------------------------------------------------
	void HtmlParser::startElement(String name, StringMap atts)
	{
		if(/*!mPrevElementWasText && */mConcatenatedText.length())
		{
			HtmlText* text = new HtmlText;
			text->text = StringHelper::utf8Decode(mConcatenatedText);
			mElementStack.top()->children.push_back(text);

			// store plain text
			mPlainText += mConcatenatedText;

			mConcatenatedText.clear();
		}

		if(name == "img") image(atts);
		else if(name == "font") font(atts);
		else if(name == "p") paragraph(atts);

		mPrevElementWasText = false;
	}
	//-----------------------------------------------------------------------
	void HtmlParser::endElement(String name)
	{
		if(mConcatenatedText.length())
		{
			HtmlText* text = new HtmlText;
			text->text = StringHelper::utf8Decode(mConcatenatedText);
			mElementStack.top()->children.push_back(text);

			// store plain text
			mPlainText += mConcatenatedText;

			mConcatenatedText.clear();
		}

		mPrevElementWasText = false;

		if(mElementStack.size())
		{
			mElementStack.pop();
		}
	}
	//-----------------------------------------------------------------------
	void HtmlParser::elementData(String text)
	{
		mConcatenatedText += text;
		mPrevElementWasText = true;
	}
	//-----------------------------------------------------------------------
	void HtmlParser::font(StringMap& atts)
	{
		HtmlFont* font = new HtmlFont;

		// "color" property
		font->color = atts["color"];

		// "face" property
		font->face = atts["face"];

		// "size" property
		font->size = atts["size"];

		mElementStack.top()->children.push_back(font);
		mElementStack.push(font);
	}
	//-----------------------------------------------------------------------
	void HtmlParser::image(StringMap& atts)
	{
		HtmlImage* img = new HtmlImage;

		// "align" property
		const String& align = atts["align"];
		if(align == "left") img->align = HtmlElement::AlignLeft;
		else if(align == "right") img->align = HtmlElement::AlignRight;
		else if(align == "center") img->align = HtmlElement::AlignCenter;
		else if(align == "justify") img->align = HtmlElement::AlignJustify;

		// "width" property
		img->width = StringHelper::toFloat(atts["width"]);

		// "height" property
		img->height = StringHelper::toFloat(atts["height"]);

		// "hspace" property
		img->hspace = StringHelper::toFloat(atts["hspace"]);

		// "vspace" property
		img->vspace = StringHelper::toFloat(atts["vspace"]);

		// "class" property
		img->css_class = atts["class"];

		// "id" property
		img->id = atts["id"];

		// "src" property
		img->src = atts["src"];

		mElementStack.top()->children.push_back(img);
		mElementStack.push(img);
	}
	//-----------------------------------------------------------------------
	void HtmlParser::paragraph(StringMap& atts)
	{
		HtmlParagraph* paragraph = new HtmlParagraph;

		// "align" property
		const String& align = atts["align"];
		if(align == "left") paragraph->align = HtmlElement::AlignLeft;
		else if(align == "right") paragraph->align = HtmlElement::AlignRight;
		else if(align == "center") paragraph->align = HtmlElement::AlignCenter;
		else if(align == "justify") paragraph->align = HtmlElement::AlignJustify;

		// "class" property
		paragraph->css_class = atts["class"];

		mElementStack.top()->children.push_back(paragraph);
		mElementStack.push(paragraph);
	}
	//-----------------------------------------------------------------------
}
