/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/vektrix

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
#pragma once

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

		const String& getName(void) const { return mName; }
		void* getSymbol(const String& name) const throw();

	protected:
		String mName;
		String getError(void);
		DYNLIB_HANDLE mInstance;
	};
}
