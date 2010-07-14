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

#include "vtxSymbolClassResource.h"

#include "vtxLogManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	SymbolClassResource::SymbolClassResource() 
		: Resource("__SymbolClassResource__")
	{

	}
	//-----------------------------------------------------------------------
	SymbolClassResource::~SymbolClassResource()
	{

	}
	//-----------------------------------------------------------------------
	const String& SymbolClassResource::getType() const
	{
		static String type = "__SymbolClassResource__";
		return type;
	}
	//-----------------------------------------------------------------------
	bool SymbolClassResource::addSymbol(const String& id, const String& class_name, const String& package)
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
	bool SymbolClassResource::hasSymbol(const String& id)
	{
		return (mSymbols.find(id) != mSymbols.end());
	}
	//-----------------------------------------------------------------------
	const StringPair& SymbolClassResource::getSymbol(const String& id)
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
}
