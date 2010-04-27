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

#include "vtxInstancePool.h"
#include "vtxInstance.h"

#include "vtxLogManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	InstancePool::InstancePool()
	{

	}
	//-----------------------------------------------------------------------
	InstancePool::~InstancePool()
	{
		uint numDeletes = 0;

		PoolMap::iterator it = mPoolMap.begin();
		PoolMap::iterator end = mPoolMap.end();
		while(it != end)
		{
			while(it->second->size())
			{
				++numDeletes;
				delete it->second->top();
				it->second->pop();
			}

			delete it->second;
			++it;
		}

		VTX_LOG("InstancePool: destroyed %d instance%s", numDeletes, (numDeletes==1)?"":"s");
	}
	//-----------------------------------------------------------------------
	void InstancePool::push(Instance* inst)
	{
		_getPool(inst->getID())->push(inst);
	}
	//-----------------------------------------------------------------------
	Instance* InstancePool::pop(const String& id)
	{
		Pool* pool = _getPool(id);

		if(pool->size())
		{
			Instance* inst = pool->top();
			pool->pop();
			return inst;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	InstancePool::Pool* InstancePool::_getPool(const String& id)
	{
		Pool* pool = NULL;

		PoolMap::iterator it = mPoolMap.find(id);
		if(it != mPoolMap.end())
		{
			pool = it->second;
		}
		else
		{
			pool = new Pool;
			mPoolMap.insert(std::make_pair(id, pool));
		}

		return pool;
	}
	//-----------------------------------------------------------------------
}
