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

#ifndef __vtxStringHelper_H__
#define __vtxStringHelper_H__

#include "vtxPrerequisites.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** A helper class for string operations */
	class vtxExport StringHelper
	{
	public:
		static String versionString(const uint& version);

		static String formatByteUnit(uint bytes);

		static WString utf8Decode(const String& encoded_string);
		static String utf8Encode(const WString& utf8_string);

		static StringList splitString(const String& str, const char& delimiter = ' ');
		static String getFileExtension(const String& str);

		static int intFromHex(const String& hexStr);
		static Color colorFromHex(const String& hexStr);

		static String toString(float val);
		static float toFloat(const String& str);

		static String toString(int val);
		static int toInt(const String& str);

		static String toString(uint val);
		static uint toUint(const String& str);

		static String toString(Color val);
		static Color toColor(const String& str);

		static String toString(Matrix val);
		static Matrix toMatrix(const String& str);

		static String toString(CXForm val);
		static CXForm toCXForm(const String& str);

		static String toString(Vector2 val);
		static Vector2 toVector2(const String& str);

		static String toString(Rect val);
		static Rect toRect(const String& str);

		static String toString(BoundingBox val);
		static BoundingBox toBoundingBox(const String& str);
	};
	//-----------------------------------------------------------------------
}

#endif
