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
		SPT_String, 
		SPT_WString, 
		SPT_Object, 
		SPT_Null
	};
	//-----------------------------------------------------------------------
#define ScriptParamInternalType(container, kind) \
	ScriptParam(const kind& val) { type_ = SPT_##kind; container##.##kind##_ = val; } \
	ScriptParam& operator= (const kind& val) { type_ = SPT_##kind; container##.##kind##_ = val; return *this; } \
	inline const kind& kind##Value() const \
	{ if(type_ != SPT_##kind) VTX_WARN("Requested type '%s' but ScriptParam type is '%d'", #kind, type_); return container##.##kind##_; }
	//-----------------------------------------------------------------------
#define ScriptParamInternalTypeAlias(container, kind, alias) \
	ScriptParam(alias val) { type_ = SPT_##kind; container##.##kind##_ = val; } \
	ScriptParam& operator= (alias val) { type_ = SPT_##kind; container##.##kind##_ = val; return *this; }
	//-----------------------------------------------------------------------
	class vtxExport ScriptParam
	{
	public:
		ScriptParam() { const_cast<ScriptParam&>(Null).type_ = SPT_Null; }

		static const ScriptParam Null;

		inline const uchar& type() const { return type_; }

		ScriptParamInternalType(_b, bool);
		ScriptParamInternalType(_b, int);
		ScriptParamInternalType(_b, double);
		ScriptParamInternalType(_s, String);
		ScriptParamInternalType(_s, WString);

		ScriptParamInternalTypeAlias(_s, String, const char*);
		ScriptParamInternalTypeAlias(_s, WString, const wchar_t*);

	private:
		uchar type_;

		union _base_types
		{
			bool bool_;
			int int_;
			double double_;
		} _b;

		struct _string_types
		{
			String String_;
			WString WString_;
		} _s;
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
