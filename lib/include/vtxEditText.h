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

#ifndef __vtxEditText_H__
#define __vtxEditText_H__

#include "vtxPrerequesites.h"
#include "vtxDisplayObjectContainer.h"
#include "vtxGlyphStrip.h"
#include "vtxHtmlElement.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** A visual dynamic/editable textfield that can be displayed inside a Movie */
	class vtxExport EditText : public DisplayObjectContainer
	{
	public:
		/** Represents a single line element, such as a word or an image */
		class LineElement
		{
		public:
			enum ElementType
			{
				ET_Word = 0, 
				ET_Image, 
				ET_FontChange, 
				ET_ParagraphChange
			};

			LineElement()
			{
				reset();
			}

			/** Reset all attributes of this element */
			void reset()
			{
				// IMAGE
				image_shape.clear();

				// WORD
				color = Color();
				width = x = 0.0f;
				glyphs.clear();

				// ALIGN_CHANGE
				align = HtmlElement::AlignLeft;

				// FONT_CHANGE
				height = 0.0f;
				font = NULL;
			}

			ElementType type;

			// IMAGE
			String image_shape;

			// WORD
			Color color;
			float width, x;
			GlyphStrip::GlyphList glyphs;

			// ALIGN_CHANGE
			HtmlElement::Alignment align;

			// FONT_CHANGE
			float height;
			FontResource* font;
		};
		typedef std::vector<LineElement> ElementList;

		/** Represents a single line of an EditText textfield */
		class Line
		{
		public:
			Line()
			{
				align = HtmlElement::AlignLeft;
				reset();
			}

			/** Reset all attributes and contents of this line */
			void reset()
			{
				width = height = 0.0f;
				elements.clear();
			}

			float width, height;
			HtmlElement::Alignment align;
			ElementList elements;
		};
		typedef std::vector<Line> LineList;

		/** Represents a style element which contains information about font, color and size */
		class StyleElement
		{
		public:
			StyleElement() : size(0.0f) {}
			float size;
			Color color;
			FontResource* font;
		};
		typedef std::stack<StyleElement> StyleStack;
		typedef std::stack<HtmlElement::Alignment> AlignmentStack;

		EditText(Resource* resource);
		virtual ~EditText();

		/** @copybrief MovableObject::_update */
		virtual void _update(const float& delta_time = 0.0f);

		/** Set the plain text for this textfield */
		void setText(const WString& text);
		/** Get the plain text of this textfield */
		const WString& getText();

		/** Set the HTML code for this textfield */
		void setHtmlText(const WString& text);
		/** Get the HTML code of this textfield */
		const WString& getHtmlText();

		/** @copybrief MovableObject::getBoundingBox */
		const BoundingBox& getBoundingBox() const;
		/** Implementation for MovableObject::isPointInside */
		bool isPointInside(const Vector2& coord);

		/** @copybrief Instance::setScriptObject */
		void setScriptObject(ScriptObject* obj);
		/** @copybrief Instance::getScriptObject */
		ScriptObject* getScriptObject() const;

	protected:
		bool mNeedDomUpdate;
		WString mText;
		WString mHtmlText;
		HtmlElement* mHtmlDom;
		BoundingBox mBoundingBox;
		EditTextResource* mEditTextResource;

		uint mGlyphCount;

		StyleStack mStyleStack;
		AlignmentStack mAlignStack;

		GlyphStripList mGlyphStrips;

		Line mCurrentLine;
		LineList mLines;

		float mCurrentHeight;
		GlyphStrip mCurrentStrip;

		/** Inform textfield implementations that they need to update their graphics */
		virtual void _updateGraphics() = 0;

		/** Recursive method to iterate over the HTML DOM tree */
		void _recursiveDomIteration(HtmlElement* source_element);

		/** Add an image to the textfield */
		void _addImage(HtmlImage* image);
		/** Add a piece of text to the textfield */
		void _addText(const WString& text);
		/** Add a single line element to the textfield */
		void _addElement(const LineElement& elem);
		/** Start a new line */
		void _newLine();

		/** Create GlyphStrip objects and Shape instances from the parsed DOM tree */
		void _createStripsAndShapes();
	};
	//-----------------------------------------------------------------------
	/** The InstanceFactory for creating EditText objects */
	class vtxExport EditTextFactory : public InstanceFactory<EditText> {};
	//-----------------------------------------------------------------------
}

#endif
