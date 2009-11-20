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
#include "vtxRect.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	Rect::Rect() 
		: left(0), 
		top(0), 
		right(0), 
		bottom(0)
	{

	}
	//-----------------------------------------------------------------------
	Rect::Rect(uint l, uint t, uint r, uint b) 
		: left(l), 
		top(t), 
		right(r), 
		bottom(b)
	{

	}
	//-----------------------------------------------------------------------
	const RectF Rect::relativeTo(const Rect& rect) const
	{
		return RectF((float)left/rect.w(), (float)top/rect.h(), (float)right/rect.w(), (float)bottom/rect.h());
	}
	//-----------------------------------------------------------------------
	uint Rect::w() const
	{
		return right - left;
	}
	//-----------------------------------------------------------------------
	uint Rect::h() const
	{
		return bottom - top;
	}
	//-----------------------------------------------------------------------
	uint Rect::w2() const
	{
		return right - left + 1;
	}
	//-----------------------------------------------------------------------
	uint Rect::h2() const
	{
		return bottom - top + 1;
	}
	//-----------------------------------------------------------------------
	RectF::RectF() 
		: left(0), 
		top(0), 
		right(0), 
		bottom(0)
	{

	}
	//-----------------------------------------------------------------------
	RectF::RectF(float l, float t, float r, float b) 
		: left(l), 
		top(t), 
		right(r), 
		bottom(b)
	{

	}
	//-----------------------------------------------------------------------
	float RectF::w() const
	{
		return right - left;
	}
	//-----------------------------------------------------------------------
	float RectF::h() const
	{
		return bottom - top;
	}
	//-----------------------------------------------------------------------
}
