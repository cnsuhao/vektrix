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
		// unsigned types
		typedef unsigned char	UI8;
		typedef unsigned short	UI16;
		typedef unsigned int	UI32;
		typedef unsigned		UBits;

		// signed types
		typedef signed short	SI16;
		typedef signed			SBits;
		//-----------------------------------------------------------------------
		enum TagTypes
		{
			TT_MalformedTag = -1,
			TT_End = 0, 
			TT_ShowFrame = 1, 
			TT_DefineShape = 2, 
			TT_FreeCharacter = 3,
			TT_PlaceObject = 4,
			TT_RemoveObject = 5,
			TT_DefineBits = 6,
			TT_DefineButton = 7,
			TT_JPEGTables = 8,
			TT_SetBackgroundColor = 9, 
			TT_DefineFont = 10, 
			TT_DefineText = 11, 
			TT_DoAction = 12,
			TT_DefineFontInfo = 13,
			TT_DefineSound = 14,
			TT_StartSound = 15,
			TT_DefineButtonSound = 17,
			TT_SoundStreamHead = 18,
			TT_SoundStreamBlock = 19,
			TT_DefineBitsLossless = 20, 
			TT_DefineBitsJPEG2 = 21,
			TT_DefineShape2 = 22,
			TT_DefineButtonCXform = 23,
			TT_Protect = 24,
			TT_PlaceObject2 = 26, 
			TT_RemoveObject2 = 28,
			TT_DefineShape3 = 32, 
			TT_DefineText2 = 33, 
			TT_DefineButton2 = 34, 
			TT_DefineBitsJPEG3 = 35,
			TT_DefineBitsLossless2 = 36, 
			TT_DefineEditText = 37, 
			TT_DefineSprite = 39, 
			TT_ProductInfo = 41,
			TT_FrameLabel = 43,
			TT_SoundStreamHead2 = 45,
			TT_DefineMorphShape = 46,
			TT_DefineFont2 = 48,
			TT_ExportAssets = 56,
			TT_ImportAssets = 57,
			TT_EnableDebugger = 58,
			TT_DoInitAction = 59,
			TT_DefineVideoStream = 60,
			TT_VideoFrame = 61,
			TT_DefineFontInfo2 = 62,
			TT_DebugId = 63,
			TT_EnableDebugger2 = 64,
			TT_ScriptLimits = 65,
			TT_SetTabIndex = 66,
			TT_FileAttributes = 69, 
			TT_PlaceObject3 = 70,
			TT_ImportAssets2 = 71,
			TT_DoABCDefine = 72,
			TT_DefineFontAlignment = 73,
			TT_FlashTypeSettings = 74,
			TT_DefineFont3 = 75, 
			TT_SymbolClass = 76, 
			TT_MetaData = 77, 
			TT_Scale9Grid = 78,
			TT_DoABC = 82, 
			TT_DefineShape4 = 83, 
			TT_DefineMorphShape2 = 84,
			TT_DefineSceneAndFrameLabelData = 86,
			TT_DefineBinaryData = 87,
			TT_DefineFontName = 88,
			TT_StartSound2 = 89,
			TT_DefineBitsJPEG4 = 90,
			TT_DefineFont4 = 91,
			TT_UnknownTag,
		};
		//-----------------------------------------------------------------------
		enum BitmapFormat
		{
			BF_8BIT_COLOR_MAPPED = 3, 
			BF_15BIT_RGB = 4, 
			BF_24BIT_RGB = 5, 
			BF_32BIT_ARGB = 5
		};
		//-----------------------------------------------------------------------
		enum LanguageCode
		{
			LC_Latin = 1, 
			LC_Japanese = 2, 
			LC_Korean = 3, 
			LC_Simplified_Chinese = 4, 
			LC_Traditional_Chinese = 5
		};
		//-----------------------------------------------------------------------
		enum ShapeElementType
		{
			SET_MOVE = 0, 
			SET_LINE, 
			SET_BEZIER
		};
		//-----------------------------------------------------------------------
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
		//-----------------------------------------------------------------------
		enum InterpolationMethod
		{
			IM_RGB = 0,
			IM_LINEAR_RGB = 1,
			IM_RESERVED1 = 2,
			IM_RESERVED2 = 3,
		};
		//-----------------------------------------------------------------------
		enum SpreadMethod
		{
			SM_PAD = 0,
			SM_REFLECT = 1,
			SM_REPEAT = 2,
			SM_RESERVED = 3,
		};
		//-----------------------------------------------------------------------
		enum BlendMode
		{
			BM_NORMAL = 1,
			BM_LAYER = 2,
			BM_MULTIPLY = 3,
			BM_SCREEN = 4,
			BM_LIGHTEN = 5,
			BM_DARKEN = 6,
			BM_DIFFERENCE = 7,
			BM_ADD = 8,
			BM_SUBTRACT = 9,
			BM_INVERT = 10,
			BM_ALPHA = 11,
			BM_ERASE = 12,
			BM_OVERLAY = 13,
			BM_HARD_LIGHT = 14,
		};
		//-----------------------------------------------------------------------
		enum FilterType
		{
			FT_DROP_SHADOW = 0,
			FT_BLUR = 1,
			FT_GLOW = 2,
			FT_BEVEL = 3,
			FT_GRADIENT_GLOW = 4,
			FT_CONVOLUTION = 5,
			FT_COLOR_MATRIX = 6,
			FT_GRADIENT_BEVEL = 7,
		};
		//-----------------------------------------------------------------------
		enum LangCode
		{
			LC_UNDEFINED = 0,
			LC_LATIN = 1,
			LC_JAPANESE = 2,
			LC_KOREAN = 3,
			LC_SIMPLIFIED_CHINESE = 4,
			LC_TRADITIONAL_CHINESE = 5,
		};
		//-----------------------------------------------------------------------
		enum ScaleStrokeMethod
		{
			SSM_NONE = 0,
			SSM_VERTICAL = 1,
			SSM_HORIZONTAL = 2,
			SSM_BOTH = 3,
		};
		//-----------------------------------------------------------------------
		enum CapStyle
		{
			CS_ROUND = 0,
			CS_NONE = 1,
			CS_SQUARE = 2,
		};
		//-----------------------------------------------------------------------
		enum JointStyle
		{
			JS_ROUND = 0,
			JS_BEVEL = 1,
			JS_MITER = 2,
		};
		//-----------------------------------------------------------------------
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
		//-----------------------------------------------------------------------
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

			COLOR(UI8 R, UI8 G, UI8 B, UI8 A) 
				: red(255), 
				green(255), 
				blue(255), 
				alpha(255){}
		};
		static const COLOR COLOR_BLACK = COLOR(0, 0, 0, 255);
		static const COLOR COLOR_WHITE = COLOR(255, 255, 255, 255);
		static const COLOR COLOR_ALLZERO = COLOR(0, 0, 0, 0);
		//-----------------------------------------------------------------------
		class MATRIX
		{
		public:
			float scale_x, scale_y;
			float rotate_x, rotate_y;
			float trans_x, trans_y;
			bool hasScale, hasRotate;

			MATRIX()
				: scale_x(0.f)
				, scale_y(0.f)
				, rotate_x(0.f)
				, rotate_y(0.f)
				, trans_x(0.f)
				, trans_y(0.f)
				, hasScale(false)
				, hasRotate(false)
			{}
		};
		//-----------------------------------------------------------------------
		class CXFORM
		{
		public:
			SBits add_red, add_green, add_blue, add_alpha, 
				  mul_red, mul_green, mul_blue, mul_alpha;
			bool has_add, has_mul;

			CXFORM() 
				: add_red(255), add_green(255), add_blue(255), add_alpha(255), 
				mul_red(255), mul_green(255), mul_blue(255), mul_alpha(255),
				has_add(true), has_mul(true){}
		};
		//-----------------------------------------------------------------------
		class GRADRECORD
		{
		public:
			int ratio;
			COLOR color;
		};
		//-----------------------------------------------------------------------
		class GRADIENT
		{
		public:
			static const int kMaxGradientRecords = 16;
			GRADRECORD gradientRecords[kMaxGradientRecords];
			int numRecords;

			SpreadMethod spreadMethod;
			InterpolationMethod interpolationMethod;

			// focal gradient
			float focalPointRatio;
		};
		//-----------------------------------------------------------------------
		// FONT TYPES
		//-----------------------------------------------------------------------
		class KERNINGRECORD
		{
		public:
			UI16 left_char_code;
			UI16 right_char_code;
			SI16 adjustment;
		};
		//-----------------------------------------------------------------------
		class TEXTRECORD
		{
		public:
			UI16 font_id;
			COLOR color;
			SI16 x, y;
			UI16 size;
		};
		typedef std::vector<TEXTRECORD> TextRecordList;
		//-----------------------------------------------------------------------
		class GLYPHENTRY
		{
		public:
			UBits index;
			SBits x_advance;
		};
		typedef std::vector<GLYPHENTRY> GlyphEntryList;
		//-----------------------------------------------------------------------
		// SHAPE TYPES
		//-----------------------------------------------------------------------
		class FILLSTYLE
		{
		public:
			FillStyleType type;
			COLOR color;
			MATRIX gradientMatrix;
			GRADIENT gradient;
			int bitmapId;
			MATRIX bitmapMatrix;
		};
		typedef std::vector<FILLSTYLE> FillstyleList;
		typedef std::map<uint, FILLSTYLE> FillstyleMap;
		//-----------------------------------------------------------------------
		class FILLSTYLEARRAY
		{
		public:
			FILLSTYLE* styles;
			int numStyles;

			FILLSTYLEARRAY()
				: styles(NULL)
				, numStyles(0)
			{}

			~FILLSTYLEARRAY()
			{
				if(styles)
				{
					delete[] styles;
				}
			}
		};
		//-----------------------------------------------------------------------
		class LINESTYLE
		{
		public:
			// linestyle
			COLOR color;
			UI16 width;

			// enhanced stroke style
			CapStyle startCapStyle;
			CapStyle endCapStyle;
			JointStyle jointStyle;
			ScaleStrokeMethod scaleStroke;
			bool close;
			float miterLimit;
			bool pixelHinting;

			// linestyle2
			FILLSTYLE fillStyle;
		};
		typedef std::vector<LINESTYLE> LinestyleList;
		typedef std::map<uint, LINESTYLE> LinestyleMap;
		//-----------------------------------------------------------------------
		class LINESTYLEARRAY
		{
		public:
			LINESTYLE* styles;
			int numStyles;

			LINESTYLEARRAY()
				: styles(NULL)
				, numStyles(0)
			{}

			~LINESTYLEARRAY()
			{
				if(styles)
				{
					delete[] styles;
				}
			}
		};
		//-----------------------------------------------------------------------
		class SHAPEELEMENT
		{
		public:
			SBits x, y, cx, cy;
			int fill0, fill1, line;
			ShapeElementType type;

			// SET_LINE
			int deltaX;
			int deltaY;

			// SET_BEZIER
			int controlDeltaX;
			int controlDeltaY;
			int anchorDeltaX;
			int anchorDeltaY;

			SHAPEELEMENT() 
				: x(0), y(0), 
				cx(0), cy(0), 
				type(SET_MOVE){}
		};
		typedef std::vector<SHAPEELEMENT> ShapeElementList;
		//-----------------------------------------------------------------------
		class SHAPE
		{
		public:
			// shape
			FillstyleList fillstyles;
			LinestyleList linestyles;
			ShapeElementList elements;

			void clear()
			{
				elements.clear();
				fillstyles.clear();
				linestyles.clear();
			}
		};
		//-----------------------------------------------------------------------
	}
}

#endif
