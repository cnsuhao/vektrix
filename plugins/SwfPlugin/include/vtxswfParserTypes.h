#pragma once

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
			TT_DefineButton2 = 34, 
			TT_FileAttributes = 69, 
			TT_SymbolClass = 76, 
			TT_MetaData = 77, 
			TT_DoABC = 82, 
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
			COLOR color;
			FillStyleType type;
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
		};

		typedef std::vector<FILLSTYLE> FillstyleList2;
		typedef std::vector<LINESTYLE> LinestyleList2;
		typedef std::map<uint, FILLSTYLE> FillstyleMap;
		typedef std::map<uint, LINESTYLE> LinestyleMap;
		typedef std::vector<SHAPEELEMENT> ShapeElementList;
	}
}
