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
#include "vtxxmlParser.h"

#include "vtxFile.h"
#include "vtxXMLDataHandler.h"
#include "vtxFileStream.h"
#include "vtxLogManager.h"
#include "vtxStringHelper.h"

#include "expat.h"

namespace vtx
{
	namespace xml
	{
		//-----------------------------------------------------------------------
		XMLParser::XMLParser(void* userdata)
			: mCurrentFileStream(NULL), 
			mUserData(userdata)
		{
			// create EXPAT parser
			mParser = XML_ParserCreate(NULL);

			// store "this" pointer for static functions
			XML_SetUserData (mParser, (void*)this);

			// set element / data handlers (static)
			XML_SetElementHandler(mParser, _startElement, _endElement);
			XML_SetCharacterDataHandler(mParser, _elementData);
		}
		//-----------------------------------------------------------------------
		XMLParser::~XMLParser()
		{
			// free the EXPAT parser
			if(mParser)
			{
				XML_ParserFree(mParser);
				mParser = NULL;
			}
		}
		//-----------------------------------------------------------------------
		void XMLParser::parse(FileStream* stream)
		{
			mLine = 1;
			//mCurrentFile = new File(stream->getFilename());
			mCurrentFileStream = stream;

			// go to the beginning of the file
			stream->seek(0);

			VTX_LOG("Started Parsing '%s'...", mCurrentFileStream->getFilename().c_str());

			// step through all lines of the file
			while(!stream->eof())
			{
				std::string line = stream->getLine();

				if(XML_Parse(mParser, line.c_str(), (int)line.size(), NULL) == XML_STATUS_ERROR)
				{
					if(!mTags.size())
					{
						VTX_EXCEPT("'%s': Error at line %d!", mCurrentFileStream->getFilename().c_str(), mLine);
					}
				}

				mLine++;
			}

			if(mTags.size())
			{
				VTX_EXCEPT("'%s': Missing closing tag </%s> at line %d!", mCurrentFileStream->getFilename().c_str(), (--mTags.end())->first.c_str(), (--mTags.end())->second);
			}

			// everything went fine

			//return mCurrentFile;
		}
		//-----------------------------------------------------------------------
		void XMLParser::addDataHandler(std::string keys[], size_t numKeys, DataHandler* handler)
		{
			for(size_t i=0; i<numKeys; ++i)
			{
				mDataHandlers.insert(DataHandlerMap::value_type(keys[i], handler));
			}

			//mHandlers.insert(DataHandlers::value_type(handler, NULL));
		}
		//-----------------------------------------------------------------------
		void XMLParser::removeDataHandler(DataHandler* handler)
		{
			DataHandlers::iterator it = mHandlers.find(handler);

			if(it != mHandlers.end())
			{
				mHandlers.erase(it);
			}
		}
		//-----------------------------------------------------------------------
		void XMLCALL XMLParser::_startElement(void *userData, const char *name, const char **atts)
		{
			// get the "this" pointer
			XMLParser* thisPointer = static_cast<XMLParser*>(userData);

			StringMap map;

			while(*atts)
			{
				map[*atts++] = *atts++;
			}

			// call non-static method
			thisPointer->_startElement(name, map);
		}
		//-----------------------------------------------------------------------
		void XMLCALL XMLParser::_endElement(void *userData, const char *name)
		{
			// get the "this" pointer
			XMLParser* thisPointer = static_cast<XMLParser*>(userData);

			// call non-static method
			thisPointer->_endElement(name);
		}
		//-----------------------------------------------------------------------
		void XMLCALL XMLParser::_elementData(void *userData, const char* text, int len)
		{

		}
		//-----------------------------------------------------------------------
		void XMLParser::_startElement(std::string name, StringMap atts)
		{
			mLevels.push_back(name);
			mTags.insert(XML_Tags::value_type(name, mLine));

			mKey = "";
			StringList::iterator str_it = mLevels.begin();

			for( ; str_it != mLevels.end(); ++str_it)
			{
				mKey += *str_it + "|";
			}

			// OLD
			//DataHandlers::iterator it = mHandlers.begin();

			//for( ; it != mHandlers.end(); ++it)
			//{
			//	//_handleElement(it->first, mKey, atts);
			//	it->first->handle(mKey, atts, mUserData);
			//}

			DataHandlerMap::iterator it = mDataHandlers.find(mKey);

			if(it != mDataHandlers.end())
			{
				it->second->handle(mKey, atts, mUserData);
			}
		}
		//-----------------------------------------------------------------------
		void XMLParser::_endElement(std::string name)
		{
			mKey = "";
			StringList::iterator str_it = mLevels.begin();

			for( ; str_it != mLevels.end(); ++str_it)
			{
				mKey += *str_it + "|";
			}

			// OLD
			//DataHandlers::iterator it_dh = mHandlers.begin();

			//for( ; it_dh != mHandlers.end(); ++it_dh)
			//{
			//	it_dh->first->end(mKey);
			//}

			DataHandlerMap::iterator it_dh = mDataHandlers.find(mKey);

			if(it_dh != mDataHandlers.end())
			{
				it_dh->second->end(mKey);
			}

			if(mLevels.back() == name)
			{
				mLevels.pop_back();
			}
			//else
			//{
			//	mSyntaxError = true;
			//}

			XML_Tags::iterator it = mTags.find(name);
			if(it != mTags.end())
			{
				mTags.erase(it);
			}
			else
			{
				VTX_EXCEPT("'%s': Error at line %d, missing opening tag: <%s>", mCurrentFileStream->getFilename().c_str(), mLine, name.c_str());
			}
		}
		//-----------------------------------------------------------------------
		void XMLParser::_elementData(std::string text)
		{

		}
		//-----------------------------------------------------------------------
	}
}
