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
	void* DynLib::getSymbol(const String& name) const throw()
	{
		return (void*)DYNLIB_GETSYM(mInstance, name.c_str() );
	}
	//-----------------------------------------------------------------------
	String DynLib::getError(void) 
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
