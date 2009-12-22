#include "vtxswfParser2.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		void SwfParser2::handleSymbolClass()
		{
			UI16 num_symbols = readU16();

			for(UI16 i=0; i<num_symbols; ++i)
			{
				UI16 id = readU16();

				String name = readString();

				if(id == 0)
				{
					mHeader.script_root_class = name;
				}
			}
		}
		//-----------------------------------------------------------------------
	}
}
