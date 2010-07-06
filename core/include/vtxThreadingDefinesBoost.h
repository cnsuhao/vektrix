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

#ifndef __vtxThreadingDefinesBoost_H__
#define __vtxThreadingDefinesBoost_H__

#if VTX_THREADING_LIB == VTX_THREADING_BOOST

// synchronization
#define VTX_MUTEX(name) mutable boost::recursive_mutex name
#define VTX_LOCK_MUTEX(mutex_name) boost::recursive_mutex::scoped_lock vtxMutexLock(mutex_name)
#define VTX_LOCK_MUTEX_NAMED(mutex_name, lock_name) boost::recursive_mutex::scoped_lock lock_name(mutex_name)

#define VTX_TRY_MUTEX_LOCK(mutex_name) mutex_name.try_lock()
#define VTX_MANUAL_MUTEX_LOCK(mutex_name) mutex_name.lock()
#define VTX_MANUAL_MUTEX_UNLOCK(mutex_name) mutex_name.unlock()

#define VTX_AUTO_MUTEX mutable boost::recursive_mutex VTX_MUTEX_ID
#define VTX_LOCK_AUTO_MUTEX boost::recursive_mutex::scoped_lock vtxMutexLock(VTX_MUTEX_ID)

#define VTX_CRITICAL_SECTION(mutex_name) {boost::recursive_mutex::scoped_lock critical_lock(mutex_name);
#define VTX_CRITICAL_SECTION_END }

#define VTX_THREAD_SYNCHRONIZER(sync) boost::condition sync
#define VTX_THREAD_WAIT(sync, mutex, lock) sync.wait(lock);
#define VTX_THREAD_NOTIFY_ONE(sync) sync.notify_one(); 
#define VTX_THREAD_NOTIFY_ALL(sync) sync.notify_all(); 

// thread creation & destruction
#define VTX_CREATE_THREAD(name, job) boost::thread* name = new boost::thread(job)
#define VTX_DESTROY_THREAD(name) delete name

// thread C++ type
#define VTX_THREAD_TYPE boost::thread

// threading utilities
#define VTX_SLEEP_THREAD(ms) boost::this_thread::sleep(boost::posix_time::millisec(ms))
#define VTX_NUM_THREAD_PROCESSORS boost::thread::hardware_concurrency()

#endif // VTX_THREADING_LIB == VTX_THREADING_BOOST

#endif
