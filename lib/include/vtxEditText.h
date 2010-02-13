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
#include "vtxMovableObject.h"

#include "vtxStaticTextResource.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	class vtxExport EditText : public MovableObject
	{
	public:
		EditText(Resource* resource);
		virtual ~EditText();

		const String& getType() const;

		virtual void _update(const float& delta_time = 0.0f);

		void setText(const WString& text);
		const WString& getText();

		void setHtmlText(const WString& text);
		const WString& getHtmlText();

		const BoundingBox& getBoundingBox() const;
		bool isPointInside(const Vector2& coord);

		void setScriptObject(ScriptObject* obj);
		ScriptObject* getScriptObject() const;

	protected:
		bool mNeedDomUpdate;
		WString mText;
		WString mHtmlText;
		HtmlElement* mHtmlDom;
		BoundingBox mBoundingBox;
		EditTextResource* mEditTextResource;

		uint mGlyphCount;
		float mMaxSize;
		float mPosition;
		std::stack<float> mSizeStack;
		std::stack<Color> mColorStack;
		std::stack<FontResource*> mFontStack;
		StaticTextResource::GlyphStripList mGlyphStrips;

		StaticTextResource::GlyphStrip mCurrentStrip;

		virtual void _updateGraphics() = 0;

		void _recursiveDomIteration(HtmlElement* source_element);

		void _addText(const WString& text);
		void _addWord(const StaticTextResource::GlyphList& glyphs, const float& word_length);
		void _addStrip();
	};
	//-----------------------------------------------------------------------
	class vtxExport EditTextFactory : public InstanceFactory<EditText> {};
	//-----------------------------------------------------------------------
}

#endif
