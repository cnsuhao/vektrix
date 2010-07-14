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

#ifndef __vtxThreadingDefinesNone_H__
#define __vtxThreadingDefinesNone_H__

#if VTX_THREADING_LIB == VTX_THREADING_NONE

// synchronization
#define VTX_MUTEX(name)
#define VTX_LOCK_MUTEX(name)
#define VTX_LOCK_MUTEX_NAMED(lock_name, mutex_name)

#define VTX_TRY_MUTEX_LOCK(mutex_name) true
#define VTX_MANUAL_MUTEX_LOCK(mutex_name)
#define VTX_MANUAL_MUTEX_UNLOCK(mutex_name)

#define VTX_AUTO_MUTEX
#define VTX_LOCK_AUTO_MUTEX

#define VTX_CRITICAL_SECTION(mutex_name)
#define VTX_CRITICAL_SECTION_END

#define VTX_THREAD_SYNCHRONIZER(sync)
#define VTX_THREAD_WAIT(sync, mutex, lock)
#define VTX_THREAD_NOTIFY_ONE(sync)
#define VTX_THREAD_NOTIFY_ALL(sync)

// thread creation & destruction
#define VTX_CREATE_THREAD(name, job)
#define VTX_DESTROY_THREAD(name)

// thread C++ type
#define VTX_THREAD_TYPE void

// threading utilities
#define VTX_SLEEP_THREAD(ms)
#define VTX_NUM_THREAD_PROCESSORS 0

#endif

#endif
