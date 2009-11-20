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
#include "vtxCXForm.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	CXForm::CXForm(
		float _mul_red, float _mul_green, float _mul_blue, float _mul_alpha, 
		float _add_red, float _add_green, float _add_blue, float _add_alpha)
		: mul_red(_mul_red), mul_green(_mul_green), mul_blue(_mul_blue), mul_alpha(_mul_alpha), 
		add_red(_add_red), add_green(_add_green), add_blue(_add_blue), add_alpha(_add_alpha)
	{

	}
	//-----------------------------------------------------------------------
}
