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

#ifndef __vtxcurlWebFileContainer_H__
#define __vtxcurlWebFileContainer_H__

#include "vtxcurl.h"
#include "vtxFileContainer.h"

namespace vtx
{
	namespace curl
	{
		//-----------------------------------------------------------------------
		class WebFileContainer : public FileContainer
		{
		public:
			WebFileContainer(const String& base_uri);
			virtual ~WebFileContainer();

			/** @copybrief FileContainer::openFile */
			FileStream* openFile(const String& filename);
			/** @copybrief FileContainer::hasFile */
			bool hasFile(const String& filename);

		protected:
			String mBaseURL;
			void* mCurl;
			uint mSize;
			uchar* mBuffer;

			long fetchURL(const String& url);
			void freeBuffer();
			static uint memoryCallback(void* ptr, uint size, uint nmemb, void* data);
		};
		//-----------------------------------------------------------------------
		/** The FileContainerFactory for creating WebFileContainer objects */
		FactoryImpl_P1(WebFileContainer, FileContainer, const String&);
		//-----------------------------------------------------------------------
	}
}

#endif
