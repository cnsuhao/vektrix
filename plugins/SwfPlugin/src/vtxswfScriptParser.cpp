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

#include "vtxswfScriptParser.h"
#include "vtxswfParser.h"

#include "vtxScriptResource.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		void ScriptParser::handleDoABC(const TagTypes& tag_type, MemoryBlockReader& tag_reader, SwfParser* parser)
		{
			const uint& read_pos = tag_reader.getOffset();
			uint start_pos = read_pos;

			UI32 flags = tag_reader.readUI32();
			String name = tag_reader.readString(true);

			uint abc_len = tag_reader.available();
			uchar* abc_buf = new uchar[abc_len];
			tag_reader.readBytes(abc_len, abc_buf);

			parser->getCurrentFile()->addResource(new ScriptResource("Script", (char*)abc_buf, abc_len));
		}
		//-----------------------------------------------------------------------
		void ScriptParser::handleSymbolClass(const TagTypes& tag_type, MemoryBlockReader& tag_reader, SwfParser* parser)
		{
			UI16 num_symbols = tag_reader.readUI16();
			for(UI16 i=0; i<num_symbols; ++i)
			{
				UI16 id = tag_reader.readUI16();
				String name = tag_reader.readString(true);
				if(id == 0)
				{
					parser->getHeader().script_root_class = name;
				}
			}
		}
		//-----------------------------------------------------------------------
	}
}
