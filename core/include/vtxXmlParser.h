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

#ifndef __vtxXmlParser_H__
#define __vtxXmlParser_H__

#include "vtxPrerequisites.h"

// predeclarations for EXPAT
#define XMLCALL
struct XML_ParserStruct;
typedef struct XML_ParserStruct* XML_Parser;

namespace vtx
{
	//-----------------------------------------------------------------------
	/** An event-based XML parser */
	class vtxExport XmlParser
	{
	public:
		XmlParser();
		virtual ~XmlParser();

		/** Parse the given XML input string */
		bool parse(const String& input);

	private:
		// expat
		XML_Parser mXmlParser;

		/** Static callback function for expat */
		static void XMLCALL expat_startElement(void *userData, const char *name, const char **atts);
		/** Static callback function for expat */
		static void XMLCALL expat_endElement(void *userData, const char *name);
		/** Static callback function for expat */
		static void XMLCALL expat_elementData(void *userData, const char* text, int len);

	protected:
		/** A XML tag has been parsed */
		virtual void startElement(String name, StringMap atts) = 0;
		/** A XML tag has been closed */
		virtual void endElement(String name) = 0;
		/** Text data has been parsed */
		virtual void elementData(String text) = 0;
	};
	//-----------------------------------------------------------------------
}

#endif
