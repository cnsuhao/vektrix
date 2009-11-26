/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

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

		VTX_LOG("InstancePool: destroyed %d instances", numDeletes);
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
