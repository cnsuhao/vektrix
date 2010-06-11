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

#include "vtxcurlWebFileContainer.h"
#include "vtxLogManager.h"
#include "vtxMemoryFileStream.h"

#define CURL_STATICLIB
#include "curl.h"

namespace vtx
{
	namespace curl
	{
		//-----------------------------------------------------------------------
		WebFileContainer::WebFileContainer(const String& base_uri) 
			: mBaseURL(base_uri), 
			mCurl(NULL), 
			mSize(0), 
			mBuffer(NULL)
		{
			mCurl = curl_easy_init();
			curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, &memoryCallback);
			curl_easy_setopt(mCurl, CURLOPT_CONNECTTIMEOUT_MS, 1000);
		}
		//-----------------------------------------------------------------------
		WebFileContainer::~WebFileContainer()
		{
			if(mCurl)
			{
				curl_easy_cleanup(mCurl);
				mCurl = NULL;
			}

			freeBuffer();
		}
		//-----------------------------------------------------------------------
		FileStream* WebFileContainer::openFile(const String& filename)
		{
			freeBuffer();

			String full_url = mBaseURL + filename;

			long statLong = fetchURL(full_url);

			if(statLong != 200 || mBuffer == NULL)
			{
				VTX_EXCEPT("Unable to open file '%s'!", full_url.c_str());
			}

			return (FileStream*)new MemoryFileStream(filename, mBuffer, mSize);
		}
		//-----------------------------------------------------------------------
		bool WebFileContainer::hasFile(const String& filename)
		{
			if(!filename.length())
			{
				return false;
			}

			freeBuffer();

			String full_url = mBaseURL + filename;

			if(full_url.length() < 7)
			{
				return false;
			}

			if(
				full_url.substr(0, 7) != "http://" && 
				full_url.substr(0, 7) != "ftp://")
			{
				return false;
			}

			long statLong = fetchURL(full_url);

			if(statLong != 200)
			{
				freeBuffer();
			}

			return (statLong == 200);
		}
		//-----------------------------------------------------------------------
		long WebFileContainer::fetchURL(const String& url)
		{
			curl_easy_setopt(mCurl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, this);
			CURLcode res = curl_easy_perform(mCurl);

			long statLong = 0;
			if(res == CURLE_OK)
			{
				curl_easy_getinfo(mCurl, CURLINFO_HTTP_CODE, &statLong);
			}

			return statLong;
		}
		//-----------------------------------------------------------------------
		void WebFileContainer::freeBuffer()
		{
			if(mBuffer)
			{
				free(mBuffer);
				mBuffer = NULL;
				mSize = 0;
			}
		}
		//-----------------------------------------------------------------------
		uint WebFileContainer::memoryCallback(void* ptr, uint size, uint nmemb, void* data)
		{
			uint realsize = size * nmemb;
			WebFileContainer* thisPtr = (WebFileContainer*)data;

			thisPtr->mBuffer = (uchar*)realloc(thisPtr->mBuffer, thisPtr->mSize + realsize);

			if(thisPtr->mBuffer)
			{
				memcpy(&thisPtr->mBuffer[thisPtr->mSize], ptr, realsize);
				thisPtr->mSize += realsize;
			}

			return realsize;
		}
		//-----------------------------------------------------------------------
	}
}
