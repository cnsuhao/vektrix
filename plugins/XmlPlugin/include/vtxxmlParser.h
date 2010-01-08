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

#ifndef __vtxxmlParser_H__
#define __vtxxmlParser_H__

#include "vtxxml.h"

namespace vtx
{
	namespace xml
	{
		#define size_of(a) sizeof(a)/sizeof(a[0])

		class XMLParser
		{
		public:
			typedef std::map<std::string, size_t> XML_Tags;
			typedef std::map<DataHandler*, DataHandler*> DataHandlers;
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

#endif
