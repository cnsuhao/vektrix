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

#ifndef __vtxWin32_H__
#define __vtxWin32_H__

//-----------------------------------------------------------------------
// WIN32 settings
//-----------------------------------------------------------------------
#if VTX_OS == VTX_WIN32
#
#	pragma warning (disable : 4251) // disable "dll-interface" warning
#	pragma warning (disable : 4661) // disable singleton include warning
#	pragma warning (disable : 4996) // disable "vsprintf" warning
#
#	include <io.h>
#	include <sys/stat.h>
#
#	ifdef VTX_STATIC_LIB
#		define vtxExport
#	else
#		ifdef VEKTRIX_EXPORTS
#			define vtxExport __declspec(dllexport)
#		else
#			define vtxExport __declspec(dllimport)
#		endif
#	endif
#
#	if defined _DEBUG && !defined VTX_DISABLE_MEMORY_DEBUGGING
#		define _CRTDBG_MAP_ALLOC
#		include <stdlib.h>
#		include <crtdbg.h>
#
#		define VTX_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#		define malloc(x) _malloc_dbg(x, _NORMAL_BLOCK, __FILE__, __LINE__);
#
//#		define new VTX_NEW
#
#		define VTX_MEM_DEBUG_ENABLE() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#		define VTX_MEM_DEBUG_BREAK(a) _CrtSetBreakAlloc(a)
#	else
#		define VTX_MEM_DEBUG_ENABLE()
#		define VTX_MEM_DEBUG_BREAK(a)
#	endif
#
//#	if defined VTX_LOAD_PLUGIN && defined _DEBUG && !defined VTX_STATIC_LIB
//#		undef VTX_LOAD_PLUGIN
//#		define VTX_LOAD_PLUGIN(name) vtx::Root::getSingletonPtr()->loadLibrary(#name"_d")
//#	endif
#
#endif // WIN32 settings

#endif
