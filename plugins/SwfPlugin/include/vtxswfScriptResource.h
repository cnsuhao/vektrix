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

#ifndef __vtxswfScriptResource_H__
#define __vtxswfScriptResource_H__

#include "vtxswf.h"
#include "vtxScriptResource.h"

namespace vtx { namespace swf {
	//-----------------------------------------------------------------------
	/** A Flash specific ScriptResource for linking Resource IDs to ActionScript 3 classes */
	class vtxswfExport ScriptResource : public vtx::ScriptResource
	{
	public:
		static const String SCRIPT_TYPE;

		typedef std::map<String, StringPair> SymbolMap;

		ScriptResource(char* buffer, const uint& buffer_size);
		virtual ~ScriptResource();

		const char* getBuffer() const;
		const uint& getBufferSize() const;

		/** Add a link from a Resource ID to the given script class */
		bool addSymbol(const String& id, const String& class_name, const String& package);
		/** Check if a script class has been registered for this Resource ID */
		bool hasSymbol(const String& id);
		/** Get the script class for the given Resource ID */
		const StringPair& getSymbol(const String& id);

	protected:
		char* mBuffer;
		uint mBufferSize;
		SymbolMap mSymbols;
	};
	//-----------------------------------------------------------------------
}}

#endif
