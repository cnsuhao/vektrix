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

#include "vtxxmlDocumentParser.h"
#include "vtxxmlDataHandler.h"

#include "vtxFile.h"
#include "vtxFileStream.h"
#include "vtxLogManager.h"
#include "vtxStringHelper.h"

namespace vtx
{
	namespace xml
	{
		//-----------------------------------------------------------------------
		DocumentParser::DocumentParser(void* userdata)
			: mCurrentFileStream(NULL), 
			mUserData(userdata)
		{

		}
		//-----------------------------------------------------------------------
		DocumentParser::~DocumentParser()
		{
			DataHandlers::iterator it = mHandlers.begin();
			DataHandlers::iterator end = mHandlers.end();
			while(it != end)
			{
				delete it->first;
				++it;
			}
		}
		//-----------------------------------------------------------------------
		void DocumentParser::parse(FileStream* stream)
		{
			mLine = 1;
			mCurrentFileStream = stream;

			// go to the beginning of the file
			stream->seek(0);

			VTX_LOG("Started Parsing '%s'...", mCurrentFileStream->getFilename().c_str());

			// step through all lines of the file
			while(!stream->eof())
			{
				std::string line = stream->getLine();

				if(!XmlParser::parse(line))
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
		}
		//-----------------------------------------------------------------------
		void DocumentParser::addDataHandler(std::string keys[], size_t numKeys, DataHandler* handler)
		{
			for(size_t i=0; i<numKeys; ++i)
			{
				mDataHandlers.insert(DataHandlerMap::value_type(keys[i], handler));
			}

			mHandlers.insert(DataHandlers::value_type(handler, handler));
		}
		//-----------------------------------------------------------------------
		void DocumentParser::removeDataHandler(DataHandler* handler)
		{
			DataHandlers::iterator it = mHandlers.find(handler);

			if(it != mHandlers.end())
			{
				mHandlers.erase(it);
			}
		}
		//-----------------------------------------------------------------------
		void DocumentParser::startElement(String name, StringMap atts)
		{
			mLevels.push_back(name);
			mTags.insert(XML_Tags::value_type(name, mLine));

			mKey = "";
			StringList::iterator str_it = mLevels.begin();

			for( ; str_it != mLevels.end(); ++str_it)
			{
				mKey += *str_it + "|";
			}

			DataHandlerMap::iterator it = mDataHandlers.find(mKey);

			if(it != mDataHandlers.end())
			{
				it->second->handle(mKey, atts, mUserData);
			}
		}
		//-----------------------------------------------------------------------
		void DocumentParser::endElement(String name)
		{
			mKey = "";
			StringList::iterator str_it = mLevels.begin();

			for( ; str_it != mLevels.end(); ++str_it)
			{
				mKey += *str_it + "|";
			}

			DataHandlerMap::iterator it_dh = mDataHandlers.find(mKey);

			if(it_dh != mDataHandlers.end())
			{
				it_dh->second->end(mKey);
			}

			if(mLevels.back() == name)
			{
				mLevels.pop_back();
			}

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
		void DocumentParser::elementData(String text)
		{

		}
		//-----------------------------------------------------------------------
	}
}
