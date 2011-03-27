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

#include "vtxGlyphResource.h"
#include "vtxFontResource.h"
#include "vtxLogManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	GlyphResource::GlyphResource(FontResource* parent) 
		: mIndex(0), 
		mCode(0), 
		mAdvance(0.0f), 
		mParent(parent)
	{

	}
	//-----------------------------------------------------------------------
	GlyphResource::~GlyphResource()
	{

	}
	//-----------------------------------------------------------------------
	void GlyphResource::setIndex(const uint& index)
	{
		mIndex = index;
	}
	//-----------------------------------------------------------------------
	const uint& GlyphResource::getIndex() const
	{
		return mIndex;
	}
	//-----------------------------------------------------------------------
	void GlyphResource::setCode(const ushort& code)
	{
		if(code == 65)
		VTX_LOG("CHAR: %c %4.2f %4.2f", (char)code, mBoundingBox.getWidth(), mBoundingBox.getHeight());

		//for_each(it, ShapeElementList, mShapeElements)
		//{
		//	ShapeElement& element = *it;
		//	switch(element.type)
		//	{
		//	case ShapeElement::SID_MOVE_TO:
		//		std::cout << "move: " << element.pos.x << " " << element.pos.y << std::endl;
		//		break;

		//	case ShapeElement::SID_CURVE_TO:
		//		std::cout << "curve: " << element.ctrl.x << " " << element.ctrl.y << std::endl;
		//		std::cout << "to: " << element.pos.x << " " << element.pos.y << std::endl;
		//		break;

		//	case ShapeElement::SID_LINE_TO:
		//		std::cout << "line: " << element.pos.x << " " << element.pos.y << std::endl;
		//		break;
		//	}
		//}

		mCode = code;
		mParent->_notifyGlyphCode(mCode, this);
	}
	//-----------------------------------------------------------------------
	const ushort& GlyphResource::getCode() const
	{
		return mCode;
	}
	//-----------------------------------------------------------------------
	const float& GlyphResource::getAdvance() const
	{
		return mAdvance;
	}
	//-----------------------------------------------------------------------
	void GlyphResource::setAdvance(const float& advance)
	{
		mAdvance = advance;
	}
	//-----------------------------------------------------------------------
	void GlyphResource::addShapeElement(ShapeElement element, const bool& auto_extend_bb)
	{
		if(auto_extend_bb)
		{
			mBoundingBox.extend(element.pos);

			if(element.type == ShapeElement::SID_CURVE_TO)
				mBoundingBox.extend(element.ctrl);
		}

		mShapeElements.push_back(element);
	}
	//-----------------------------------------------------------------------
	const ShapeElementList& GlyphResource::getElementList() const
	{
		return mShapeElements;
	}
	//-----------------------------------------------------------------------
	void GlyphResource::setBoundingBox(const BoundingBox& bb)
	{
		mBoundingBox = bb;
	}
	//-----------------------------------------------------------------------
	const BoundingBox& GlyphResource::getBoundingBox() const
	{
		return mBoundingBox;
	}
	//-----------------------------------------------------------------------
	FontResource* GlyphResource::getParentFont() const
	{
		return mParent;
	}
	//-----------------------------------------------------------------------
}
