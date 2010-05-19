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

#include "vtxDynLib.h"
#include "vtxLogManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	#if VTX_OS == VTX_WIN32
		#define WIN32_LEAN_AND_MEAN
		#include <windows.h>
	#endif

	#if VTX_OS == VTX_APPLE
		#include "macPlugins.h"
	#endif
	//-----------------------------------------------------------------------
	DynLib::DynLib(const String& name) 
		: mName(name), 
		mInstance(NULL)
	{

	}
	//-----------------------------------------------------------------------
	DynLib::~DynLib()
	{

	}
	//-----------------------------------------------------------------------
	void DynLib::load()
	{
		VTX_LOG("Loading dynamic library \"%s\"", mName.c_str());

		String name = mName;

		#if VTX_OS == VTX_LINUX
			// on linux add .so
			if (name.substr(name.length() - 3, 3) != ".so")
			{
				name += ".so";
			}
		#endif

		mInstance = (DYNLIB_HANDLE)DYNLIB_LOAD(name.c_str());

		if(!mInstance)
		{
			VTX_EXCEPT("Unable to load dynamic library \"%s\"\n(\"%s\")", mName.c_str(), getError().c_str());
		}
	}
	//-----------------------------------------------------------------------
	void DynLib::unload()
	{
		VTX_LOG("Unloading dynamic library \"%s\"", mName.c_str());

		if(DYNLIB_UNLOAD(mInstance))
		{
			VTX_EXCEPT("Unable to unload dynamic library \"%s\"\n(\"%s\")", mName.c_str(), getError().c_str());
		}
	}
	//-----------------------------------------------------------------------
	const String& DynLib::getName() const
	{
		return mName;
	}
	//-----------------------------------------------------------------------
	void* DynLib::getSymbol(const String& name) const throw()
	{
		return (void*)DYNLIB_GETSYM(mInstance, name.c_str() );
	}
	//-----------------------------------------------------------------------
	String DynLib::getError() 
	{
		#if VTX_OS == VTX_WIN32
			LPVOID lpMsgBuf; 
			FormatMessage( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				FORMAT_MESSAGE_FROM_SYSTEM | 
				FORMAT_MESSAGE_IGNORE_INSERTS, 
				NULL, 
				GetLastError(), 
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
				(LPTSTR) &lpMsgBuf, 
				0, 
				NULL 
				);

			String ret = (char*)lpMsgBuf;
			// remove line break
			ret = ret.substr(0, ret.length()-2);
			LocalFree(lpMsgBuf);
			return ret;

		#elif VTX_OS == VTX_LINUX
			return String(dlerror());

		#elif VTX_OS == VTX_APPLE
			return String(mac_errorBundle());

		#else
			return String("");
		#endif
	}
	//-----------------------------------------------------------------------
}
