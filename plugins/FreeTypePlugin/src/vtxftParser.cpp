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

#include "vtxftParser.h"

#include "vtxFileStream.h"
#include "vtxFontResource.h"
#include "vtxGlyphResource.h"
#include "vtxLogManager.h"

#include "vtxStringHelper.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_ERRORS_H

namespace vtx { namespace ft {
	FT_Library lib;
	//-----------------------------------------------------------------------
	FreeTypeParser::FreeTypeParser() 
		: mCurrentGlyph(NULL)
	{
		//mFreeType = malloc(sizeof(FT_Library));
		FT_Error error = FT_Init_FreeType(&lib);
	}
	//-----------------------------------------------------------------------
	FreeTypeParser::~FreeTypeParser()
	{
		//delete mFreeType;
	}
	//-----------------------------------------------------------------------
	const StringList& FreeTypeParser::getExtensions() const
	{
		static StringList extensions;
		extensions.push_back(".ttf");
		return extensions;
	}
	//-----------------------------------------------------------------------
	int moveTo(const FT_Vector* to, void* user)
	{
		const FreeTypeParser* thiz = static_cast<FreeTypeParser*>(user);
		const float& em_size = thiz->getEmSize();
		GlyphResource* glyph = thiz->getCurrentGlyph();

		ShapeElement shape_element;
		shape_element.type = ShapeElement::SID_MOVE_TO;
		shape_element.pos = Vector2(to->x / em_size, -to->y / em_size);

		glyph->addShapeElement(shape_element);

		//std::cout << "move: " << to->x << ", " << to->y << std::endl;
		return 0;
	}
	//-----------------------------------------------------------------------
	int lineTo(const FT_Vector* to, void* user)
	{
		const FreeTypeParser* thiz = static_cast<FreeTypeParser*>(user);
		const float& em_size = thiz->getEmSize();
		GlyphResource* glyph = thiz->getCurrentGlyph();

		ShapeElement shape_element;
		shape_element.type = ShapeElement::SID_LINE_TO;
		shape_element.pos = Vector2(to->x / em_size, -to->y / em_size);

		glyph->addShapeElement(shape_element);
	
		//std::cout << "line: " << to->x << ", " << to->y << std::endl;
		return 0;
	}
	//-----------------------------------------------------------------------
	int conicTo(const FT_Vector* ctrl, const FT_Vector* to, void* user)
	{
		const FreeTypeParser* thiz = static_cast<FreeTypeParser*>(user);
		const float& em_size = thiz->getEmSize();
		GlyphResource* glyph = thiz->getCurrentGlyph();

		ShapeElement shape_element;
		shape_element.type = ShapeElement::SID_CURVE_TO;
		shape_element.ctrl = Vector2(ctrl->x / em_size, -ctrl->y / em_size);
		shape_element.pos = Vector2(to->x / em_size, -to->y / em_size);;

		glyph->addShapeElement(shape_element);
		return 0;
	}
	//-----------------------------------------------------------------------
	int cubicTo(const FT_Vector* ctrl1, const FT_Vector* ctrl2, const FT_Vector* to, void* user)
	{
		const FreeTypeParser* thiz = static_cast<FreeTypeParser*>(user);
		GlyphResource* glyph = thiz->getCurrentGlyph();

		return 0;
	}
	//-----------------------------------------------------------------------
	FontResource* FreeTypeParser::parse(FileStream* stream)
	{
		FT_Face face;

		const uint len = stream->size();
		uchar* buf = new uchar[len];
		stream->read(buf, len);

		FT_Error error = FT_New_Memory_Face(lib, buf, stream->size(), 0, &face);

		if(face->num_glyphs == 0)
		{
			VTX_WARN("Couldn't load font file \"%s\" using FreeType, no scalable fonts available");
			return NULL;
		}

		FT_Outline_Funcs outline_funcs = { moveTo, lineTo, conicTo, cubicTo, 0, 0 };

		// what should I be doing to get the correct scaling here ? Should I use one of the other FT_Request/Size methods instead ?
		float px_size = face->units_per_EM;
		px_size /= 3.2f;
		FT_Set_Pixel_Sizes(face, px_size, px_size);

		//FT_Size_RequestRec req = 
		//{
		//	FT_SIZE_REQUEST_TYPE_BBOX,
		//	2048,
		//	2048,
		//	2048,
		//	2048
		//};

		//FT_Request_Size(face, &req);

		mEmSize = face->units_per_EM;

		FontResource* font = new FontResource(face->family_name);
		font->setName(face->family_name);
		font->setAscender(face->ascender / mEmSize);
		font->setDescender(face->descender / mEmSize);
		font->setLeading((face->ascender - face->descender - face->units_per_EM) / mEmSize);

		uint glyph_idx = 0;
		for(uint i=65; i<91; ++i)
		{
			mCurrentGlyph = new GlyphResource(font);

			uint glyph_index = FT_Get_Char_Index(face, i);
			error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
			error = FT_Outline_Decompose(&face->glyph->outline, &outline_funcs, this);

			//face->glyph->metrics->width

			mCurrentGlyph->setIndex(glyph_idx);
			mCurrentGlyph->setAdvance(face->glyph->advance.x / mEmSize);
			mCurrentGlyph->setCode(i);

			font->addGlyph(mCurrentGlyph);
			++glyph_idx;
		}

		free(buf);
		return font;
	}
	//-----------------------------------------------------------------------
	const float FreeTypeParser::getEmSize() const
	{
		return mEmSize;
	}
	//-----------------------------------------------------------------------
	GlyphResource* FreeTypeParser::getCurrentGlyph() const
	{
		return mCurrentGlyph;
	}
	//-----------------------------------------------------------------------
}}
