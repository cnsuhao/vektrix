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

#ifndef __vtxMatrix_H__
#define __vtxMatrix_H__

#include "vtxPrerequisites.h"

namespace vtx
{
	/** Represents a row-major 3x2 matrix */
	class vtxExport Matrix
	{
	public:
		float m[2][3];

		Matrix(
			float _sx = 1.0f, float _cx = 0.0f, float _tx = 0.0f, 
			float _cy = 0.0f, float _sy = 1.0f, float _ty = 0.0f);

		/** Get the translation component of the matrix */
		Vector2 getTransformation() const;

		/** Get the translation component of the matrix */
		Matrix getTransformationMatrix() const;

		/** Get the scale component of the matrix */
		Vector2 getScale() const;

		/** Get the scale component of the matrix */
		Matrix getScaleMatrix() const;

		/** Get the rotation component of the matrix */
		float getRotation() const;

		/** Get the rotation component of the matrix */
		Matrix getRotationMatrix() const;

		/** Standard matrix multiplication */
		Matrix operator*(const Matrix& matrix) const;

		/** Multiply the matrix with a given scalar */
		Matrix operator*(const float& scalar) const;

		/** Transform the matrix using another affine matrix */
		Vector2 transformAffine(const Vector2& v) const;

		/**  */
		Matrix transpose() const;

		/**  */
		Matrix inverseTransformation() const;

		/**  */
		Vector2 transformInverse(const Vector2& v) const;
	};
}

#endif
