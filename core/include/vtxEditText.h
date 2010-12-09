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

#include "vtxPrerequisites.h"
#include "vtxDisplayObjectContainer.h"
#include "vtxEventListener.h"
#include "vtxHtmlOperations.h"
#include "vtxHtmlRenderable.h"
#include "vtxTextLine.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** A visual dynamic/editable textfield that can be displayed inside a Movie */
	class vtxExport EditText : 
		public DisplayObjectContainer, 
		public HtmlOperations, 
		public HtmlRenderable
	{
	public:
		static const String TYPE;
		typedef std::vector<TextLine> LineList;
		typedef std::map<String, File*> LoadedFiles;

		EditText();
		virtual ~EditText();

		virtual void initFromResource(Resource* resource);

		const String& getType() const;

		/** @copybrief DisplayObject::_update */
		virtual void _update(const float& delta_time = 0.0f);

		/** Set the plain text for this textfield */
		void setText(const WString& text);
		/** Get the plain text of this textfield */
		const WString& getText();

		/** Set the HTML code for this textfield */
		void setHtmlText(const WString& text);
		/** Get the HTML code of this textfield */
		const WString& getHtmlText();

		const GlyphStrip::Glyph& getGlyphAtPoint(const Vector2& point);

		const TextLine& getLineAtPoint(const Vector2& point);

		/** Set the currently selected text */
		void setSelection(const uint& beginIndex, const uint& endIndex);

		/** Get the currently selected text's start index */
		const uint& getSelectionBeginIndex() const;

		/** Get the currently selected text's end index */
		const uint& getSelectionEndIndex() const;

		/** Implementation of DisplayObject::isPointInside */
		bool isPointInside(const Vector2& coord);

		// inherited from EventListener
		virtual void eventFired(const Event& evt);

	protected:
		// properties
		WString mText;
		WString mHtmlText;

		// selection management
		uint mSelectionBeginIndex;
		uint mSelectionEndIndex;
		HtmlSelection mSelectionBegin;
		HtmlSelection mSelectionEnd;

		// DOM management
		bool mNeedDomUpdate;
		HtmlElement* mHtmlDom;

		uint mGlyphCount;

		// visuals
		float mCurrentHeight;
		GlyphStrip mCurrentStrip;
		GlyphStripList mGlyphStrips;

		TextLine mCurrentLine;
		LineList mLines;

		LoadedFiles mLoadedFiles;

		void _buildGraphicsFromDOM();

		/** Inform textfield implementations that they need to update their graphics */
		virtual void _updateGraphics() = 0;

		void _addFont(HtmlFont* font);

		void _fontStyleChanged(const StyleElement& style);

		/** Add an image to the line that is currently being created */
		void _addImage(HtmlImage* image);

		void _addParagraph(HtmlParagraph* paragraph);

		/** Add a piece of text to the line that is currently being created */
		void _addText(HtmlText* text);

		/** Add a single line element to the line that is currently being created */
		void _addLineElement(TextLineElement& elem);

		/** Start a new line */
		void _startNewLine();

		// event handlers
		void keyboardEvent(const KeyboardEvent& evt);
		void mouseEvent(const MouseEvent& evt);

		bool mSelecting;
		typedef std::vector<Shape*> SelectionShapes;
		SelectionShapes mSelectionShapes;

		/** Create GlyphStrip objects and Shape instances from the generated line elements */
		void _createStripsAndShapes();

		void _addSelectionShape(const float& sx, const float& sy, const float& x, const float& y);

		/** Create Shape instances to display the current selection */
		void _createSelectionShapes();

		void _clearSelectionShapes();

		HtmlSelection _getSelectionAtPoint(const Vector2& point);

		void loadingCompleted(File* file);
		void loadingFailed(File* file);
	};
	//-----------------------------------------------------------------------
}

#endif
