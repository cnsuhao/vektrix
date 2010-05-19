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

#include "vtxOpSysHelper.h"

#if VTX_OS == VTX_WIN32

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	bool OpSysHelper::copyToClipboard(WString str)
	{
		// open the clipboard
		if(!OpenClipboard(NULL))
		{
			return false;
		}

		// empty the clipboard
		if(!EmptyClipboard())
		{
			CloseClipboard();
			return false;
		}

		// allocate global memory
		uint str_len = (str.length() + 1) * sizeof(wchar_t);
		HGLOBAL mem = GlobalAlloc(GMEM_MOVEABLE, str_len);
		if(mem == NULL)
		{
			CloseClipboard();
			return false;
		}

		// lock memory, and copy text to it
		wchar_t* dest = (wchar_t*)GlobalLock(mem);
		if(dest == NULL)
		{
			GlobalUnlock(mem);
			CloseClipboard();
			return false;
		}

		memcpy(dest, str.c_str(), str_len);

		// unlock memory block
		GlobalUnlock(mem);

		// copy memory to clipboard
		if(SetClipboardData(CF_UNICODETEXT, mem) == NULL)
		{
			CloseClipboard();
			return false;
		}

		// release the clipboard
		CloseClipboard();

		return true;
	}
	//-----------------------------------------------------------------------
	WString OpSysHelper::getWStringFromClipboard()
	{
		WString result;

		// open the clipboard
		if(!OpenClipboard(NULL))
		{
			return L"";
		}

		HGLOBAL mem = GetClipboardData(CF_UNICODETEXT);

		if(mem == NULL)
		{
			CloseClipboard();
			return L"";
		}

		uint len = GlobalSize(mem) / sizeof(wchar_t);

		wchar_t* begin = (wchar_t*)GlobalLock(mem);
		if(begin == NULL)
		{
			GlobalUnlock(mem);
			CloseClipboard();
			return L"";
		}

		wchar_t* end = std::find(begin, begin + len, L'\0');
		result.assign(begin, end);

		// unlock memory block
		GlobalUnlock(mem);

		// release the clipboard
		CloseClipboard();

		return result;
	}
	//-----------------------------------------------------------------------
}

#endif
