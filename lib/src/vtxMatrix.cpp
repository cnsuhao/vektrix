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

#include "vtxMatrix.h"

#include "vtxVector2.h"

#include "vtxLogManager.h"
#include "vtxStringHelper.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/*
	*	[sx, cx, tx]
	*	[cy, sy, ty]
	*	[0,   0,  1]
	*/
	//-----------------------------------------------------------------------
	Matrix::Matrix(
		float sx, float cx, float tx, 
		float cy, float sy, float ty) 
	{
		// first row
		m[0][0] = sx;
		m[0][1] = cx;
		m[0][2] = tx;

		// second row
		m[1][0] = cy;
		m[1][1] = sy;
		m[1][2] = ty;
	}
	//-----------------------------------------------------------------------
	Vector2 Matrix::getTrans() const
	{
		return Vector2(m[0][2], m[1][2]);
	}
	//-----------------------------------------------------------------------
	Vector2 Matrix::getScale() const
	{
		return Vector2(m[0][0], m[1][1]);
	}
	//-----------------------------------------------------------------------
	Matrix Matrix::operator*(const Matrix& matrix) const
	{
		Matrix product;

		for (size_t iRow = 0; iRow < 2; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
			{
				product.m[iRow][iCol] =
					m[iRow][0]*matrix.m[0][iCol] +
					m[iRow][1]*matrix.m[1][iCol];
			}
		}

		product.m[0][2] += m[0][2];
		product.m[1][2] += m[1][2];

		return product;
	}
	//-----------------------------------------------------------------------
	Matrix Matrix::operator*(const float& scalar) const
	{
		Matrix product;

		// first row
		product.m[0][0] = m[0][0] * scalar;
		product.m[0][1] = m[0][1] * scalar;
		product.m[0][2] = m[0][2] * scalar;

		// second row
		product.m[1][0] = m[1][0] * scalar;
		product.m[1][1] = m[1][1] * scalar;
		product.m[1][2] = m[1][2] * scalar;

		return product;
	}
	//-----------------------------------------------------------------------
	Vector2 Matrix::transformAffine(const Vector2& v) const
	{
		return Vector2(
			m[0][0] * v.x + m[0][1] * v.y + m[0][2], 
			m[1][0] * v.x + m[1][1] * v.y + m[1][2]);
	}
	//-----------------------------------------------------------------------
}
