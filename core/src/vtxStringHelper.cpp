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
#include "vtxLogManager.h"
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
	String StringHelper::formatByteUnit(uint bytes)
	{
		String result;

		if(bytes < 1024) // 1 kByte
		{
			result = toString(bytes) + " byte(s)";
		}
		else if(bytes < 1048576) // 1 MByte
		{
			result = toString((float)bytes/1024.0f) + " kByte(s)";
		}
		else if(bytes < 1073741824) // 1 GByte
		{
			result = toString((float)bytes/1048576.0f) + " MByte(s)";
		}
		else
		{
			result = "<unimplemented size>";
		}

		return result;
	}
	//-----------------------------------------------------------------------
	WString StringHelper::utf8Decode(const String& encoded_string)
	{
		WString result;

		String::const_iterator it = encoded_string.begin();
		String::const_iterator end = encoded_string.end();
		while(it != end)
		{
			// UTF-8 multi-byte char
			if(*it & 128)
			{
				uchar shifted = *it;
				shifted = shifted >> 4;
				switch(shifted)
				{
				case 0xF: // 1111
					{
						VTX_EXCEPT("unexpected 4 byte UTF-8 value");
					}
					break;

				case 0xE: // 1110
					{
						ushort byte[3] = { *it, *++it, *++it };
						ushort utf_char = 
							byte[0] << 12 | 
							(byte[1] << 6) & 4032 | 
							byte[2] & 63;
						result.append(1, utf_char);
					}
					break;

				case 0xC: // 1100
					{
						ushort byte[2] = { *it, *++it };
						ushort utf_char = 
							(byte[0] << 6) & 1984 | 
							byte[1] & 63;
						result.append(1, utf_char);
					}
					break;
				}

			}
			// single 7 bit ASCII char
			else
			{
				result.append(1, *it);
			}

			++it;
		}

		return result;
	}
	//-----------------------------------------------------------------------
	String StringHelper::utf8Encode(const WString& utf8_string)
	{
		String result;

		WString::const_iterator it = utf8_string.begin();
		WString::const_iterator end = utf8_string.end();
		while(it != end)
		{
			// UTF-8 multi-byte char
			if(*it > 128)
			{
				ushort utf_char = *it;

				// 3 byte form
				if(utf_char > 2047)
				{
					uchar byte[3];
					byte[0] = 224 | utf_char >> 12;
					byte[1] = 128 | ((utf_char >> 6) & 63);
					byte[2] = 128 | (utf_char & 63);

					result.append((char*)&byte, 3);
				}
				// 2 byte form
				else
				{
					uchar byte[2];
					byte[0] = 192 | ((utf_char >> 6) & 63);
					byte[1] = 128 | (utf_char & 63);

					result.append((char*)&byte, 2);
				}
			}
			// single 7 bit ASCII char
			else
			{
				result.append(1, (uchar)*it);
			}

			++it;
		}

		return result;
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
	String StringHelper::getFileExtension(const String& path)
	{
		uint dotPos = (uint)path.find_last_of('.');

		if(dotPos != String::npos)
		{
			return path.substr(dotPos, path.length()-dotPos);
		}

		return "";
	}
	//-----------------------------------------------------------------------
	int StringHelper::intFromHex(const String& hexStr)
	{
		int val;
		std::stringstream sstr;
		sstr << std::hex << hexStr;
		sstr >> val;
		return val;
	}
	//-----------------------------------------------------------------------
	Color StringHelper::colorFromHex(const String& hexStr)
	{
		Color result;

		if(hexStr.length() != 7)
		{
			return result;
		}

		if(hexStr.at(0) != '#')
		{
			return result;
		}

		result.r = (float)intFromHex(hexStr.substr(1, 2))/255.0f;
		result.g = (float)intFromHex(hexStr.substr(3, 2))/255.0f;
		result.b = (float)intFromHex(hexStr.substr(5, 2))/255.0f;

		return result;
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
			val.mul.r << " " << val.mul.g << " " << val.mul.b << " " << val.mul.a << "\n" << 
			val.add.r << " " << val.add.g << " " << val.add.b << " " << val.add.a;

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
