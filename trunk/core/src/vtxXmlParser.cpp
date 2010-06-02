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

#include "vtxXmlParser.h"
#include "vtxLogManager.h"

#define XML_STATIC
#include "expat.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	XmlParser::XmlParser() 
	{
		// create EXPAT parser
		mXmlParser = XML_ParserCreate("UTF-8");

		// store "this" pointer for static functions
		XML_SetUserData(mXmlParser, (void*)this);

		// set element / data handlers (static)
		XML_SetElementHandler(mXmlParser, expat_startElement, expat_endElement);
		XML_SetCharacterDataHandler(mXmlParser, expat_elementData);
	}
	//-----------------------------------------------------------------------
	XmlParser::~XmlParser()
	{
		// free the EXPAT parser
		if(mXmlParser)
		{
			XML_ParserFree(mXmlParser);
			mXmlParser = NULL;
		}
	}
	//-----------------------------------------------------------------------
	bool XmlParser::parse(const String& input)
	{
		if(XML_Parse(mXmlParser, input.c_str(), input.length(), NULL) == XML_STATUS_ERROR)
		{
			uint column = XML_GetCurrentColumnNumber(mXmlParser);
			XML_Error error_code = XML_GetErrorCode(mXmlParser);

			VTX_WARN("Error while parsing XML: %s (%d) at column %d", 
				XML_ErrorString(error_code), 
				error_code, 
				column);
			VTX_LOG(input.c_str());

			return false;
		}

		return true;
	}
	//-----------------------------------------------------------------------
	void XMLCALL XmlParser::expat_startElement(void *userData, const char *name, const char **atts)
	{
		// get the "this" pointer
		XmlParser* thisPointer = static_cast<XmlParser*>(userData);

		StringMap map;

		while(*atts)
		{
			// read and increment the "key" char* pointer first and seperately!!!
			// (on linux this really matters, otherwise the key-value pairs are swapped)
			const char* key = *atts++;
			map[key] = *atts++;
		}

		// call non-static method
		thisPointer->startElement(name, map);
	}
	//-----------------------------------------------------------------------
	void XMLCALL XmlParser::expat_endElement(void *userData, const char *name)
	{
		// get the "this" pointer
		XmlParser* thisPointer = static_cast<XmlParser*>(userData);

		// call non-static method
		thisPointer->endElement(name);
	}
	//-----------------------------------------------------------------------
	void XMLCALL XmlParser::expat_elementData(void *userData, const char* text, int len)
	{
		// get the "this" pointer
		XmlParser* thisPointer = static_cast<XmlParser*>(userData);

		String elem_text;
		elem_text.append(text, len);

		// call non-static method
		thisPointer->elementData(elem_text);
	}
	//-----------------------------------------------------------------------
}
