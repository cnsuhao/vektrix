/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009 Fuse-Software (tm)

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/
#pragma once

#include "vtxPrerequesites.h"
#include "defines.h"

// predeclarations for EXPAT
#define XMLCALL
struct XML_ParserStruct;
typedef struct XML_ParserStruct *XML_Parser;

namespace vtx
{
	namespace xml
	{
		#define size_of(a) sizeof(a)/sizeof(a[0])

		class XMLParser
		{
		public:
			typedef std::map<std::string, size_t> XML_Tags;
			typedef std::map<DataHandler*, int> DataHandlers;
			typedef std::map<std::string, DataHandler*> DataHandlerMap;

			XMLParser(void* userdata);
			virtual ~XMLParser();

			void parse(FileStream* stream);

			void addDataHandler(std::string keys[], size_t numKeys, DataHandler* handler);
			void removeDataHandler(DataHandler* handler);

		protected:
			size_t mLine;
			std::string mKey;
			void* mUserData;
			FileStream* mCurrentFileStream;

			XML_Tags mTags;
			StringList mLevels;
			DataHandlers mHandlers;
			DataHandlerMap mDataHandlers;

			// expat
			XML_Parser mParser;

			static void XMLCALL _startElement(void *userData, const char *name, const char **atts);
			static void XMLCALL _endElement(void *userData, const char *name);
			static void XMLCALL _elementData(void *userData, const char* text, int len);

			void _startElement(std::string name, StringMap atts);
			void _endElement(std::string name);
			void _elementData(std::string text);
		};
	}
}
