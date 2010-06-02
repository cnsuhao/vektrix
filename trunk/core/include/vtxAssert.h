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

#ifndef __vtxAssert_H__
#define __vtxAssert_H__

#include <stdio.h>

namespace vtx
{
#if defined (_DEBUG)

#	define vtxDebugBreak()														\
	if ( true ) 																\
	{ 																			\
		__debugbreak(); 														\
	} 																			\
	else 																		\
		(void)0
#	define vtxDebugAssert( condition, message ) 								\
	if ( !( condition ) ) 														\
	{ 																			\
		printf( "vtxDebugAssert(%s:%d): %s\n", __FILE__, __LINE__, message ); 	\
		vtxDebugBreak(); 														\
	} 																			\
	else 																		\
		(void)0
#	define vtxDebugWarning( condition, message ) 								\
	if ( !( condition ) ) 														\
	{ 																			\
		printf( "vtxDebugWarning(%s:%d): %s\n", __FILE__, __LINE__, message ); 	\
	} 																			\
	else 																		\
		(void)0
#	define vtxDebugFail( message ) 												\
	if ( true ) 																\
	{ 																			\
		printf( "vtxDebugFail(%s:%d): %s\n", __FILE__, __LINE__, message ); 	\
		vtxDebugBreak(); 														\
	} 																			\
	else 																		\
		(void)0
#	define vtxDebugPrint( message ) printf( message )
#	define vtxDebugPrintVA( arguments ) printf arguments

#else

#	define vtxDebugBreak() (void(0))
#	define vtxDebugAssert( condition, message ) (void(0))
#	define vtxDebugWarning( condition, message ) (void(0))
#	define vtxDebugFail( message ) (void(0))
#	define vtxDebugPrint( message ) (void(0))
#	define vtxDebugPrintVA( arguments ) (void(0))

#endif 
}

#endif //__vtxAssert_H__
