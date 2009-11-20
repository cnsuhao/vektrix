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
#pragma once

#include "vtxLogManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	template<typename T>
	class FactoryManagerBase
	{
	public:
		//-----------------------------------------------------------------------
		typedef std::map<String, T*> FactoryMap;
		//-----------------------------------------------------------------------
		virtual bool addFactory(T* factory)
		{
			FactoryMap::iterator it = mFactories.find(factory->getName());

			if(it == mFactories.end())
			{
				mFactories.insert(FactoryMap::value_type(factory->getName(), factory));

				// LOG: Factory added successfully
				VTX_LOG("Added %sFactory '%s'.", factory->getType().c_str(), factory->getName().c_str());

				return true;
			}

			// WARN: Factory already added
			VTX_WARN("Tried to add %sFactory '%s' twice!", factory->getType().c_str(), factory->getName().c_str());

			return false;
		}
		//-----------------------------------------------------------------------
		virtual bool removeFactory(T* factory)
		{
			FactoryMap::iterator it = mFactories.find(factory->getName());

			if(it != mFactories.end())
			{
				mFactories.erase(it);
				return true;
			}

			// WARN: unknown Factory
			VTX_WARN("Requested removal of unknown %sFactory '%s'!", factory->getType().c_str(), factory->getName().c_str());

			return false;
		}
		//-----------------------------------------------------------------------
		virtual T* getFactory(const String& name)
		{
			FactoryMap::iterator it = mFactories.find(name);

			if(it != mFactories.end())
			{
				return it->second;
			}

			return NULL;
		}
		//-----------------------------------------------------------------------
	protected:
		FactoryMap mFactories;
	};
	//-----------------------------------------------------------------------
	template<typename T>
	class FactoryManagerNULL : public FactoryManagerBase<T>{};
	//-----------------------------------------------------------------------
	template<typename T, class P1>
	class FactoryManager : public FactoryManagerBase<T>
	{
	public:
		//-----------------------------------------------------------------------
		FactoryManager()
		{
			mDefaultFactory = new P1;
			addFactory(mDefaultFactory);
		}
		//-----------------------------------------------------------------------
		virtual ~FactoryManager()
		{
			delete mDefaultFactory;
		}
		//-----------------------------------------------------------------------
		virtual T* getFactory(const String& name)
		{
			T* factory = FactoryManagerBase::getFactory(name);

			if(!factory)
			{
				VTX_WARN("A %sFactory with name \"%s\" is not available, using DefaultFactory", mDefaultFactory->getType().c_str(), name.c_str());
				return mDefaultFactory;
			}

			return factory;
		}
		//-----------------------------------------------------------------------
	protected:
		P1* mDefaultFactory;
	};
	//-----------------------------------------------------------------------
}
