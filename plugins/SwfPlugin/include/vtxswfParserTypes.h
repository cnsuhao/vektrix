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

#ifndef __vtxswfParserTypes_H__
#define __vtxswfParserTypes_H__

namespace vtx
{
	namespace swf
	{
		typedef signed SBits;
		typedef unsigned char UI8;
		typedef unsigned short UI16;
		typedef unsigned int UI32;

		enum TagTypes
		{
			TT_End = 0, 
			TT_ShowFrame = 1, 
			TT_DefineShape = 2, 
			TT_SetBackgroundColor = 9, 
			TT_DefineShape2 = 22, 
			TT_PlaceObject2 = 26, 
			TT_DefineShape3 = 32, 
			TT_DefineButton2 = 34, 
			TT_FileAttributes = 69, 
			TT_SymbolClass = 76, 
			TT_MetaData = 77, 
			TT_DoABC = 82, 
			TT_DefineShape4 = 83, 
			TT_DefineSceneAndFrameLabelData = 86
		};

		enum ShapeElementType
		{
			SET_MOVE = 0, 
			SET_LINE, 
			SET_BEZIER
		};

		enum FillStyleType
		{
			FST_Solid = 0, 
			FST_LinearGradient = 16, 
			FST_RadialGradient = 18, 
			FST_FocalRadialGradient = 19, 
			FST_RepeatingBitmap = 64, 
			FST_ClippedBitmap = 65, 
			FST_NonSmoothedRepeatingBitmap = 66, 
			FST_NonSmoothedClippedBitmap = 67
		};

		class RECT
		{
		public:
			SBits xmin;
			SBits ymin;
			SBits xmax;
			SBits ymax;

			RECT() 
				: xmin(0), 
				xmax(0), 
				ymin(0), 
				ymax(0){}
		};

		class COLOR
		{
		public:
			UI8 red, 
				green, 
				blue, 
				alpha;

			COLOR() 
				: red(255), 
				green(255), 
				blue(255), 
				alpha(255){}
		};

		class MATRIX
		{
		public:
			SBits sx, cx, tx, 
				  cy, sy, ty;

			MATRIX() 
				: sx(65536), cx(0), tx(0), 
				  cy(0), sy(65536), ty(0){}
		};

		class CXFORM
		{
		public:
			SBits add_red, add_green, add_blue, add_alpha, 
				  mul_red, mul_green, mul_blue, mul_alpha;

			CXFORM() 
				: add_red(255), add_green(255), add_blue(255), add_alpha(255), 
				mul_red(255), mul_green(255), mul_blue(255), mul_alpha(255){}
		};

		class FILLSTYLE
		{
		public:
			typedef std::map<UI8, COLOR> GradientMap;

			FillStyleType type;
			COLOR color;
			GradientMap gradient;
			MATRIX matrix;
		};

		class LINESTYLE
		{
		public:
			COLOR color;
			UI16 width;
		};

		class SHAPEELEMENT
		{
		public:
			SBits x, y, cx, cy;
			int fill0, fill1, line;
			ShapeElementType type;

			SHAPEELEMENT() 
				: x(0), y(0), 
				cx(0), cy(0), 
				type(SET_MOVE){}
		};

		typedef std::vector<FILLSTYLE> FillstyleList2;
		typedef std::vector<LINESTYLE> LinestyleList2;
		typedef std::map<uint, FILLSTYLE> FillstyleMap;
		typedef std::map<uint, LINESTYLE> LinestyleMap;
		typedef std::vector<SHAPEELEMENT> ShapeElementList;
	}
}

#endif
