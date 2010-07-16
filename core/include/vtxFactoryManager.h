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
	/** A template for managing Factory instances */
	template<typename T>
	class FactoryManager
	{
	public:
		//-----------------------------------------------------------------------
		typedef std::map<String, T*> FactoryMap;
		//-----------------------------------------------------------------------
		FactoryManager(const String& base_type) : mBaseType(base_type) {}
		//-----------------------------------------------------------------------
		virtual ~FactoryManager()
		{
			typename FactoryMap::const_iterator it = mFactories.begin();
			typename FactoryMap::const_iterator end = mFactories.end();
			while(it != end)
			{
				delete it->second;
				++it;
			}
		}
		//-----------------------------------------------------------------------
		virtual bool addFactory(T* factory)
		{
			typename FactoryMap::iterator it = mFactories.find(factory->getName());

			if(it == mFactories.end())
			{
				mFactories.insert(typename FactoryMap::value_type(factory->getName(), factory));

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
			typename FactoryMap::iterator it = mFactories.find(factory->getName());

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
			typename FactoryMap::iterator it = mFactories.find(name);

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
#define FactoryManagerImpl(name, type) \
	class name : public FactoryManager<type##Factory> \
	{ \
	public: \
		name() : FactoryManager<type##Factory>(#type){} \
	};
	//-----------------------------------------------------------------------
}

#endif
