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
		/** Convert a version number from integer to String format */
		static String versionString(const uint& version);

		/** Automatically format a byte number [byte,kByte,MByte] */
		static String formatByteUnit(uint bytes);

		/** Decode an UTF String that was previously encoded to a usual String */
		static WString utf8Decode(const String& encoded_string);
		/** Encode a usual String to an UTF String */
		static String utf8Encode(const WString& utf8_string);

		/** Split a String by the given delimiter */
		static StringList splitString(const String& str, const char& delimiter = ' ');

		/** Get the file extension from the given path */
		static String getFileExtension(const String& path);

		/** Parse a hexadecimal number and convert it to an integer number */
		static int intFromHex(const String& hexStr);

		/** Parse a Color out of a hexadecimally formatted String color */
		static Color colorFromHex(const String& hexStr);

		/** Convert the given floating-point value to a String */
		static String toString(float val);
		/** Convert the given String to a floating-point value */
		static float toFloat(const String& str);

		/** Convert the given integer value to a String */
		static String toString(int val);
		/** Convert the given String to an integer value */
		static int toInt(const String& str);

		/** Convert the given unsigned integer value to a String */
		static String toString(uint val);
		/** Convert the given String to an unsigned integer value */
		static uint toUint(const String& str);

		/** Convert the given Color to a String */
		static String toString(Color val);
		/** Convert the given String to a Color */
		static Color toColor(const String& str);

		/** Convert the given Matrix to a String */
		static String toString(Matrix val);
		/** Convert the given String to a Matrix */
		static Matrix toMatrix(const String& str);

		/** Convert the given color transformation to a String */
		static String toString(CXForm val);
		/** Convert the given String to a color transformation */
		static CXForm toCXForm(const String& str);

		/** Convert the given Vector2 to a String */
		static String toString(Vector2 val);
		/** Convert the given String to a Vector2 */
		static Vector2 toVector2(const String& str);

		/** Convert the given rectangle to a String */
		static String toString(Rect val);
		/** Convert the given String to a rectangle */
		static Rect toRect(const String& str);

		/** Convert the given BoundingBox to a String */
		static String toString(BoundingBox val);
		/** Convert the given String to a BoundingBox */
		static BoundingBox toBoundingBox(const String& str);
	};
	//-----------------------------------------------------------------------
}

#endif
