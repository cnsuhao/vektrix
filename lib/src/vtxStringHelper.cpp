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

#include "vtxStringHelper.h"

#include "vtxBoundingBox.h"
#include "vtxColor.h"
#include "vtxCXForm.h"
#include "vtxMatrix.h"
#include "vtxRect.h"
#include "vtxVector2.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	String StringHelper::versionString(const uint& version)
	{
		return 
			StringHelper::toString((version>>16)) + "." + 
			StringHelper::toString((version>>8)&255) + "." + 
			StringHelper::toString((version>>0)&255);
	}
	//-----------------------------------------------------------------------
	StringList StringHelper::splitString(const String& str, const char& delimiter)
	{
		StringList list;
		uint start, pos;

		start = 0;
		do 
		{
			pos = (uint)str.find_first_of(delimiter, start);

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
			start = (uint)str.find_first_not_of(delimiter, start);

		}while(pos != String::npos);

		return list;
	}
	//-----------------------------------------------------------------------
	String StringHelper::getFileExtension(const String& str)
	{
		uint dotPos = (uint)str.find_last_of('.');

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
			val.m[0][0] << " " << val.m[0][1] << " " << val.m[0][2] << "\n" << 
			val.m[1][0] << " " << val.m[1][1] << " " << val.m[1][2];

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
	String StringHelper::toString(BoundingBox val)
	{
		std::ostringstream stream;
		stream << "Min: " << toString(val.getMin()) << 
			" Max: " << toString(val.getMax());

		return stream.str();
	}
	//-----------------------------------------------------------------------
	BoundingBox StringHelper::toBoundingBox(const String& str)
	{
		StringList list = splitString(str);

		if(list.size() == 6)
		{
			return BoundingBox(
				toVector2(list[1] + " " + list[2]), 
				toVector2(list[4] + " " + list[5])
				);
		}
		else
		{
			return BoundingBox();
		}
	}
	//-----------------------------------------------------------------------
}
