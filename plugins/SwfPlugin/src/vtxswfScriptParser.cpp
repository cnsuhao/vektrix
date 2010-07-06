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

#include "vtxLogManager.h"
#include "vtxScriptResource.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		void ScriptParser::handleDoABC(const TagTypes& tag_type, const uint& tag_length, SwfParser* parser)
		{
			const uint& read_pos = parser->getReadPosition();
			uint start_pos = read_pos;

			UI32 flags = parser->readU32();
			String name = parser->readString();

			uint abc_len = tag_length - (read_pos - start_pos);

			char* abc_buf = new char[abc_len];
			parser->readByteBlock(abc_buf, abc_len);

			parser->getCurrentFile()->addResource(new ScriptResource("Script", abc_buf, abc_len));
		}
		//-----------------------------------------------------------------------
		void ScriptParser::handleSymbolClass(const TagTypes& tag_type, const uint& tag_length, SwfParser* parser)
		{
			UI16 num_symbols = parser->readU16();

			for(UI16 i=0; i<num_symbols; ++i)
			{
				UI16 id = parser->readU16();

				String name = parser->readString();

				if(id == 0)
				{
					parser->getHeader().script_root_class = name;
				}
				else
				{
					VTX_LOG("ST_SymbolClass: %s", name.c_str());
				}
			}
		}
		//-----------------------------------------------------------------------
	}
}
