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

#ifndef __vtxScriptParameters_H__
#define __vtxScriptParameters_H__

#include "vtxPrerequisites.h"
#include "vtxLogManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	class ScriptParamObject;
	//-----------------------------------------------------------------------
	enum ScriptParamType
	{
		SPT_bool, 
		SPT_int, 
		SPT_float, 
		SPT_double, 
		SPT_string, 
		SPT_wstring, 
		SPT_Object, 
		SPT_Null
	};
	//-----------------------------------------------------------------------
#define ScriptParamInternalType(kind) \
	ScriptParam(const kind& val) \
	{ \
		_type = SPT_##kind; \
		_data.##kind##_ = val; \
	} \
	ScriptParam& operator= (const kind& val) \
	{ \
		_type = SPT_##kind; \
		_data.##kind##_ = val; \
		return *this; \
	} \
	inline const kind& kind##Value() const \
	{ \
		if(_type != SPT_##kind) \
			VTX_WARN("Requested type '%s' but ScriptParam type is '%d'", #kind, _type); return _data.##kind##_; \
	}
	//-----------------------------------------------------------------------
#define ScriptParamCopyString(dest, src, chr, fns) \
	dest = new chr[(fns##len(src) + 1) * sizeof(chr)]; \
	fns##cpy(dest, src)
	//-----------------------------------------------------------------------
#define ScriptParamInternalStringType(kind, chr, fns) \
	ScriptParam(const chr* val) \
	{ \
		_type = SPT_##kind; \
		ScriptParamCopyString(_data.##kind##_, val, chr, fns); \
	} \
	ScriptParam& operator= (const chr* val) \
	{ \
		_type = SPT_##kind; \
		ScriptParamCopyString(_data.##kind##_, val, chr, fns); \
		return *this; \
	} \
	inline chr* kind##Value() const \
	{ \
		if(_type != SPT_##kind) \
			VTX_WARN("Requested type '%s' but ScriptParam type is '%d'", #kind, _type); \
		return _data.##kind##_; \
	}
	//-----------------------------------------------------------------------
	class vtxExport ScriptParam
	{
	public:
		//-----------------------------------------------------------------------
		static const ScriptParam Null;
		//-----------------------------------------------------------------------
		ScriptParam()
		{
			const_cast<ScriptParam&>(Null)._type = SPT_Null;
		}
		//-----------------------------------------------------------------------
		ScriptParam(const ScriptParam& src)
		{
			_type = src._type;

			if(_type == SPT_string)
			{ 
				ScriptParamCopyString(_data.string_, src._data.string_, char, str);
			}
			else if(_type == SPT_wstring)
			{
				ScriptParamCopyString(_data.wstring_, src._data.wstring_, wchar_t, wcs);
			}
			else
				_data = src._data;
		}
		//-----------------------------------------------------------------------
		virtual ~ScriptParam()
		{
			if(_type == SPT_string)
				delete[] (_data.string_);

			else if(_type == SPT_wstring)
				delete[] (_data.wstring_);
		}
		//-----------------------------------------------------------------------
		ScriptParam(const String& val)
		{
			_type = SPT_string;
			ScriptParamCopyString(_data.string_, val.c_str(), char, str);
		}
		//-----------------------------------------------------------------------
		ScriptParam& operator= (const String& val)
		{
			_type = SPT_string;
			ScriptParamCopyString(_data.string_, val.c_str(), char, str);
			return *this;
		}
		//-----------------------------------------------------------------------
		ScriptParam(const WString& val)
		{
			_type = SPT_wstring;
			ScriptParamCopyString(_data.wstring_, val.c_str(), wchar_t, wcs);
		}
		//-----------------------------------------------------------------------
		ScriptParam& operator= (const WString& val)
		{
			_type = SPT_wstring;
			ScriptParamCopyString(_data.wstring_, val.c_str(), wchar_t, wcs);
			return *this;
		}
		//-----------------------------------------------------------------------
		inline const uchar& type() const { return _type; }
		//-----------------------------------------------------------------------
		ScriptParamInternalType(bool);
		ScriptParamInternalType(int);
		ScriptParamInternalType(double);

		ScriptParamInternalStringType(string, char, str);
		ScriptParamInternalStringType(wstring, wchar_t, wcs);

	private:
		uchar _type;

		union _data_types
		{
			bool bool_;
			int int_;
			double double_;
			char* string_;
			wchar_t* wstring_;
		} _data;
	};
	//-----------------------------------------------------------------------
	class ScriptParamObject
	{
	public:
		typedef std::map<String, ScriptParam> MemberList;
		MemberList members;
	};
	//-----------------------------------------------------------------------
	typedef std::vector<ScriptParam> ScriptParamList;
	//-----------------------------------------------------------------------
}

#endif
