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

#include "vtxThreadJobQueue.h"
#include "vtxLogManager.h"
#include "vtxThreadJob.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	ThreadJobQueue::ThreadJobQueue() 
		: mRunning(true), 
		mSemaphore(VTX_NUM_THREAD_PROCESSORS)
	{
		setNumberOfThreads(VTX_NUM_THREAD_PROCESSORS);
	}
	//-----------------------------------------------------------------------
	ThreadJobQueue::~ThreadJobQueue()
	{
		mRunning.setValue(false);
		mSemaphore.release(VTX_NUM_THREAD_PROCESSORS);
		destroyThreads();
	}
	//-----------------------------------------------------------------------
	void ThreadJobQueue::setNumberOfThreads(const uint& num_threads)
	{
		VTX_LOCK_MUTEX(mMutex);
		if(num_threads < mThreadPool.size())
		{
			destroyThreads();

			for(uint i=0; i<num_threads; ++i)
			{
				VTX_CREATE_THREAD(thread, boost::bind(&ThreadJobQueue::threadFunc, this));
				mThreadPool.push_back(thread);
			}
		}
		else
		{
			const uint& existing_threads = mThreadPool.size();
			for(uint i=0; i<num_threads - existing_threads; ++i)
			{
				VTX_CREATE_THREAD(thread, boost::bind(&ThreadJobQueue::threadFunc, this));
				mThreadPool.push_back(thread);
			}
		}
	}
	//-----------------------------------------------------------------------
	void ThreadJobQueue::queueJob(ThreadJob* job)
	{
		VTX_LOCK_MUTEX(mMutex);
		mQueue.push(job);
		mSemaphore.release();
	}
	//-----------------------------------------------------------------------
	void ThreadJobQueue::threadFunc(/*void* args*/)
	{
		while(mRunning.getValue())
		{
			mSemaphore.acquire();
			//VTX_LOG("Job acquired");

			ThreadJob* job = NULL;

			VTX_CRITICAL_SECTION(mMutex);
			if(mQueue.size())
			{
				job = mQueue.back();
				mQueue.pop();
			}
			VTX_CRITICAL_SECTION_END;

			if(job)
			{
				job->start();
				delete job;
			}
			//VTX_LOG("Job finished");
		}
	}
	//-----------------------------------------------------------------------
	void ThreadJobQueue::destroyThreads()
	{
		VTX_LOG("Waiting for %d threads to finish...", mThreadPool.size());

		ThreadPool::iterator it = mThreadPool.begin();
		ThreadPool::iterator end = mThreadPool.end();
		while(it != end)
		{
			(*it)->join();
			delete *it;
			++it;
		}
	}
	//-----------------------------------------------------------------------
}
