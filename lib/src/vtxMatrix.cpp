/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009 Fuse-Software (tm)

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/
#include "vtxMatrix.h"

#include "vtxVector2.h"

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
	Vector2 Matrix::getScale() const
	{
		return Vector2(m[0][0], m[1][1]);
	}
	//-----------------------------------------------------------------------
	Matrix Matrix::operator*(const Matrix& matrix) const
	{
		Matrix product;

		// first row
		product.m[0][0] = m[0][0] * matrix.m[0][0] + m[0][1] * matrix.m[1][0];
		product.m[0][1] = m[0][0] * matrix.m[0][1] + m[0][1] * matrix.m[1][1];
		product.m[0][2] = m[0][0] * matrix.m[0][2] + m[0][1] * matrix.m[1][2] + m[0][2];

		// second row
		product.m[1][0] = m[1][0] * matrix.m[1][0] + m[1][1] * matrix.m[1][0];
		product.m[1][1] = m[1][0] * matrix.m[1][1] + m[1][1] * matrix.m[1][1];
		product.m[1][2] = m[1][0] * matrix.m[1][2] + m[1][1] * matrix.m[1][2] + m[1][2];

		return product;
	}
	//-----------------------------------------------------------------------
}
