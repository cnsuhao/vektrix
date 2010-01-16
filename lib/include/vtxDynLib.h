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

#ifndef __vtxDynLib_H__
#define __vtxDynLib_H__

#include "vtxPrerequesites.h"

namespace vtx
{
	#if VTX_OS == VTX_WIN32
		#define DYNLIB_HANDLE hInstance
		#define DYNLIB_LOAD(a) LoadLibrary(a)
		#define DYNLIB_GETSYM(a, b) GetProcAddress(a, b)
		#define DYNLIB_UNLOAD(a) !FreeLibrary(a)
		struct HINSTANCE__;
		typedef struct HINSTANCE__* hInstance;

	#elif VTX_OS == VTX_LINUX
		#define DYNLIB_HANDLE void*
		#define DYNLIB_LOAD(a) dlopen(a, RTLD_LAZY | RTLD_GLOBAL)
		#define DYNLIB_GETSYM(a, b) dlsym(a, b)
		#define DYNLIB_UNLOAD(a) dlclose(a)

	#elif VTX_OS == VTX_APPLE
		#define DYNLIB_HANDLE CFBundleRef
		#define DYNLIB_LOAD(a) mac_loadExeBundle(a)
		#define DYNLIB_GETSYM(a, b) mac_getBundleSym(a, b)
		#define DYNLIB_UNLOAD(a) mac_unloadExeBundle(a)
	#endif

	/** For loading a external program library
	*/
	class DynLib
	{
	public:
		DynLib(const String& name);
		~DynLib();

		void load();
		void unload();

		const String& getName() const { return mName; }
		void* getSymbol(const String& name) const throw();
		String getError();

	protected:
		String mName;
		DYNLIB_HANDLE mInstance;
	};
}

#endif
