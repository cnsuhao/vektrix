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

#include "vtxswfScriptResource.h"

#include "vtxLogManager.h"

namespace vtx { namespace swf {
	//-----------------------------------------------------------------------
	const String ScriptResource::SCRIPT_TYPE = "adobe/swf/actionscript3";
	//-----------------------------------------------------------------------
	ScriptResource::ScriptResource(char* buffer, const uint& buffer_size) 
		: vtx::ScriptResource(SCRIPT_TYPE), 
		mBuffer(buffer), 
		mBufferSize(buffer_size)
	{

	}
	//-----------------------------------------------------------------------
	ScriptResource::~ScriptResource()
	{

	}
	//-----------------------------------------------------------------------
	const char* ScriptResource::getBuffer() const
	{
		return mBuffer;
	}
	//-----------------------------------------------------------------------
	const uint& ScriptResource::getBufferSize() const
	{
		return mBufferSize;
	}
	//-----------------------------------------------------------------------
	bool ScriptResource::addSymbol(const String& id, const String& class_name, const String& package)
	{
		SymbolMap::iterator it = mSymbols.find(id);
		if(it == mSymbols.end())
		{
			VTX_LOG("SymbolClass: [%s] %s -> %s", id.c_str(), package.c_str(), class_name.c_str());
			mSymbols.insert(std::make_pair(id, StringPair(package, class_name)));
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool ScriptResource::hasSymbol(const String& id)
	{
		return (mSymbols.find(id) != mSymbols.end());
	}
	//-----------------------------------------------------------------------
	const StringPair& ScriptResource::getSymbol(const String& id)
	{
		SymbolMap::iterator it = mSymbols.find(id);
		if(it != mSymbols.end())
		{
			return it->second;
		}

		static StringPair empty;
		return empty;
	}
	//-----------------------------------------------------------------------
}}
