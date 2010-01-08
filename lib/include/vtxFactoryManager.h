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

#ifndef __vtxFactoryManager_H__
#define __vtxFactoryManager_H__

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
		FactoryManagerBase(const String& base_type) : mBaseType(base_type) {}
		//-----------------------------------------------------------------------
		virtual bool addFactory(T* factory)
		{
			FactoryMap::iterator it = mFactories.find(factory->getName());

			if(it == mFactories.end())
			{
				mFactories.insert(FactoryMap::value_type(factory->getName(), factory));

				// LOG: Factory added successfully
				VTX_LOG("Added %sFactory '%s'.", mBaseType.c_str(), factory->getName().c_str());

				return true;
			}

			// WARN: Factory already added
			VTX_WARN("Tried to add %sFactory '%s' twice!", mBaseType.c_str(), factory->getName().c_str());

			return false;
		}
		//-----------------------------------------------------------------------
		virtual bool removeFactory(T* factory)
		{
			FactoryMap::iterator it = mFactories.find(factory->getName());

			if(it != mFactories.end())
			{
				mFactories.erase(it);

				// LOG: Factory removed successfully
				VTX_LOG("Removed %sFactory '%s'.", mBaseType.c_str(), factory->getName().c_str());

				return true;
			}

			// WARN: unknown Factory
			VTX_WARN("Requested removal of unknown %sFactory '%s'!", mBaseType.c_str(), factory->getName().c_str());

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
		String mBaseType;
		FactoryMap mFactories;
	};
	//-----------------------------------------------------------------------
	template<typename T>
	class FactoryManagerNULL : public FactoryManagerBase<T>
	{
	public:
		FactoryManagerNULL(const String& base_type) 
			: FactoryManagerBase(base_type){}
	};
	//-----------------------------------------------------------------------
	template<typename T, class P1>
	class FactoryManager : public FactoryManagerBase<T>
	{
	public:
		//-----------------------------------------------------------------------
		FactoryManager(const String& base_type) 
			: FactoryManagerBase(base_type)
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
				VTX_WARN("A %sFactory with name \"%s\" is not available, using DefaultFactory", mBaseType.c_str(), name.c_str());
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

#endif
