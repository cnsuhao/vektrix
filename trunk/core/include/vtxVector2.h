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

#ifndef __vtxVector2_H__
#define __vtxVector2_H__

#include "vtxPrerequisites.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** Represents a two-dimensional vector */
	class vtxExport Vector2
	{
	public:
		Vector2();
		Vector2(float x, float y);

		/** Get the length of the vector */
		float length();

		/** Normalize the vector */
		void normalize();

		/** Calculate the dot product of two vectors */
		float dotProduct(const Vector2& vec);

		inline bool operator != (const Vector2& vec) const
		{
			return (x != vec.x || y != vec.y);
		}

		inline Vector2 operator + (const Vector2& vec) const
		{
			return Vector2(x + vec.x, y + vec.y);
		}

		inline Vector2 operator - (const Vector2& vec) const
		{
			return Vector2(x - vec.x, y - vec.y);
		}

		inline Vector2 operator * (const Vector2& vec) const
		{
			return Vector2(x * vec.x, y * vec.y);
		}

		inline Vector2 operator * (const float& scalar) const
		{
			return Vector2(x * scalar, y * scalar);
		}

		inline Vector2 operator / (const Vector2& vec) const
		{
			return Vector2(x / vec.x, y / vec.y);
		}

		float x, y;

		static const Vector2 ZERO;
	};
	//-----------------------------------------------------------------------
}

#endif
