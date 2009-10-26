/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/vektrix

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
#include "vtxStringHelper.h"

#include "vtxColor.h"
#include "vtxCXForm.h"
#include "vtxMatrix.h"
#include "vtxRect.h"
#include "vtxVector2.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	StringList StringHelper::splitString(const String& str)
	{
		StringList list;
		uint start, pos;

		start = 0;
		do 
		{
			pos = str.find_first_of(' ', start);

			if(pos == start)
			{
				start = pos + 1;
			}
			else if(pos == String::npos)
			{
				list.push_back(str.substr(start));
				break;
			}
			else
			{
				list.push_back(str.substr(start, pos - start));
				start = pos + 1;
			}
			start = str.find_first_not_of(' ', start);

		}while(pos != String::npos);

		return list;
	}
	//-----------------------------------------------------------------------
	String StringHelper::getFileExtension(const String& str)
	{
		uint dotPos = str.find_last_of('.');

		if(dotPos != String::npos)
		{
			return str.substr(dotPos, str.length()-dotPos);
		}

		return "";
	}
	//-----------------------------------------------------------------------
	String StringHelper::toString(float val)
	{
		std::ostringstream stream;
		stream.precision(5);
		stream.width(0);
		stream.fill(' ');
		stream << val;

		return stream.str();
	}
	//-----------------------------------------------------------------------
	float StringHelper::toFloat(const String& str)
	{
		std::istringstream stream(str);
		float val = 0.0f;
		stream >> val;

		return val;
	}
	//-----------------------------------------------------------------------
	String StringHelper::toString(int val)
	{
		std::ostringstream stream;
		stream.width(0);
		stream.fill(' ');
		stream << val;

		return stream.str();
	}
	//-----------------------------------------------------------------------
	int StringHelper::toInt(const String& str)
	{
		std::istringstream stream(str);
		int val = 0;
		stream >> val;

		return val;
	}
	//-----------------------------------------------------------------------
	String StringHelper::toString(uint val)
	{
		std::ostringstream stream;
		stream.width(0);
		stream.fill(' ');
		stream << val;

		return stream.str();
	}
	//-----------------------------------------------------------------------
	uint StringHelper::toUint(const String& str)
	{
		std::istringstream stream(str);
		uint val = 0;
		stream >> val;

		return val;
	}
	//-----------------------------------------------------------------------
	String StringHelper::toString(Color val)
	{
		std::ostringstream stream;
		stream << val.r << " " << val.g << " " << val.b << " " << val.a;

		return stream.str();
	}
	//-----------------------------------------------------------------------
	Color StringHelper::toColor(const String& str)
	{
		StringList list = splitString(str);

		if(list.size() == 3)
		{
			return Color(
				toFloat(list[0]), 
				toFloat(list[1]), 
				toFloat(list[2]), 
				1.0f);
		}
		else if(list.size() == 4)
		{
			return Color(
				toFloat(list[0]), 
				toFloat(list[1]), 
				toFloat(list[2]), 
				toFloat(list[3]));
		}
		else
		{
			return Color();
		}
	}
	//-----------------------------------------------------------------------
	String StringHelper::toString(Matrix val)
	{
		std::ostringstream stream;
		stream << 
			val.sx << " " << val.cx << " " << val.tx << "\n" << 
			val.cy << " " << val.sy << " " << val.ty;

		return stream.str();
	}
	//-----------------------------------------------------------------------
	Matrix StringHelper::toMatrix(const String& str)
	{
		StringList list = splitString(str);

		if(list.size() == 6)
		{
			return Matrix(
				toFloat(list[0]), toFloat(list[1]), toFloat(list[2]), 
				toFloat(list[3]), toFloat(list[4]), toFloat(list[5]));
		}
		else
		{
			return Matrix();
		}
	}
	//-----------------------------------------------------------------------
	String StringHelper::toString(CXForm val)
	{
		std::ostringstream stream;
		stream << 
			val.mul_red << " " << val.mul_green << " " << val.mul_blue << " " << val.mul_alpha << "\n" << 
			val.add_red << " " << val.add_green << " " << val.add_blue << " " << val.add_alpha;

		return stream.str();
	}
	//-----------------------------------------------------------------------
	CXForm StringHelper::toCXForm(const String& str)
	{
		StringList list = splitString(str);

		if(list.size() == 8)
		{
			return CXForm(
				toFloat(list[0]), toFloat(list[1]), toFloat(list[2]), toFloat(list[3]), 
				toFloat(list[4]), toFloat(list[5]), toFloat(list[6]), toFloat(list[7]));
		}
		else
		{
			return CXForm();
		}
	}
	//-----------------------------------------------------------------------
	String StringHelper::toString(Vector2 val)
	{
		std::ostringstream stream;
		stream << val.x << " " << val.y;

		return stream.str();
	}
	//-----------------------------------------------------------------------
	Vector2 StringHelper::toVector2(const String& str)
	{
		StringList list = splitString(str);

		if(list.size() == 2)
		{
			return Vector2(toFloat(list[0]), toFloat(list[1]));
		}
		else
		{
			return Vector2();
		}
	}
	//-----------------------------------------------------------------------
	String StringHelper::toString(Rect val)
	{
		std::ostringstream stream;
		stream << val.left << " " << val.top << " " << val.right << " " << val.bottom;

		return stream.str();
	}
	//-----------------------------------------------------------------------
	Rect StringHelper::toRect(const String& str)
	{
		StringList list = splitString(str);

		if(list.size() == 4)
		{
			return Rect(toUint(list[0]), toUint(list[1]), toUint(list[2]), toUint(list[3]));
		}
		else
		{
			return Rect();
		}
	}
	//-----------------------------------------------------------------------
}
