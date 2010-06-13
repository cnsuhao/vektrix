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

#include "vtxcurlWebRequest.h"

#define CURL_STATICLIB
#include "curl/curl.h"

namespace vtx
{
	namespace curl
	{
		//-----------------------------------------------------------------------
		WebRequest::WebRequest(const uint& timeout) 
			: mCurl(NULL), 
			mSize(0), 
			mBuffer(NULL)
		{
			mCurl = curl_easy_init();
			curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, this);
			curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, &memoryCallback);
			curl_easy_setopt(mCurl, CURLOPT_CONNECTTIMEOUT_MS, timeout);
		}
		//-----------------------------------------------------------------------
		WebRequest::~WebRequest()
		{
			if(mCurl)
			{
				curl_easy_cleanup(mCurl);
				mCurl = NULL;
			}
		}
		//-----------------------------------------------------------------------
		bool WebRequest::openURL(const String& url)
		{
			freeBuffer();

			curl_easy_setopt(mCurl, CURLOPT_NOBODY, false);

			curl_easy_setopt(mCurl, CURLOPT_URL, url.c_str());
			CURLcode result = curl_easy_perform(mCurl);

			if(result == CURLE_OK)
			{
				long statLong = 0;
				curl_easy_getinfo(mCurl, CURLINFO_HTTP_CODE, &statLong);

				if(statLong == 200 && mBuffer != NULL)
				{
					return true;
				}
				else
				{
					freeBuffer();
				}
			}

			return false;
		}
		//-----------------------------------------------------------------------
		bool WebRequest::doesFileExist(const String& url)
		{
			curl_easy_setopt(mCurl, CURLOPT_NOBODY, true);

			curl_easy_setopt(mCurl, CURLOPT_URL, url.c_str()); 
			curl_easy_perform(mCurl); 

			CURLcode result;
			if(curl_easy_getinfo(mCurl, CURLINFO_HTTP_CODE, &result) == CURLE_OK) 
			{
				return (result == 200);
			}

			return false;
		}
		//-----------------------------------------------------------------------
		uchar* WebRequest::getBuffer() const
		{
			return mBuffer;
		}
		//-----------------------------------------------------------------------
		const uint& WebRequest::getSize() const
		{
			return mSize;
		}
		//-----------------------------------------------------------------------
		void WebRequest::freeBuffer()
		{
			if(mBuffer)
			{
				free(mBuffer);
				mBuffer = NULL;
				mSize = 0;
			}
		}
		//-----------------------------------------------------------------------
		uint WebRequest::memoryCallback(void* ptr, uint size, uint nmemb, void* data)
		{
			uint realsize = size * nmemb;
			WebRequest* thisPtr = static_cast<WebRequest*>(data);

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
