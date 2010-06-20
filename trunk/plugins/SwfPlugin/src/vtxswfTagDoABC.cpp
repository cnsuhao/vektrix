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
#include "vtxswfTag.h"
#include "vtxswfTagDoABC.h"
#include "vtxScriptResource.h"
#include "vtxswfParser.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfTagDoABC::SwfTagDoABC(uint tag_length, uchar* tag_data)
			: SwfTag(TT_DoABC, tag_length, tag_data)
		{}
		//-----------------------------------------------------------------------
		SwfTagDoABC::~SwfTagDoABC()
		{}
		//-----------------------------------------------------------------------
		void SwfTagDoABC::ParseData(SwfParser* parser)
		{
			const uint& read_pos = parser->getReadPosition();
			uint start_pos = read_pos;

			UI32 flags = parser->readU32();
			String name = parser->readString();

			uint abc_len = mTagLength - (read_pos - start_pos);

			char* abc_buf = new char[abc_len];
			parser->readByteBlock(abc_buf, abc_len);

			parser->getCurrentFile()->addResource(new ScriptResource("Script", abc_buf, abc_len));
		}
		//-----------------------------------------------------------------------
	}
}
