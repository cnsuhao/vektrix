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

#ifndef __vtxFactory_H__
#define __vtxFactory_H__

namespace vtx
{
	//-----------------------------------------------------------------------
	template<class T>
	class BaseFactory
	{
	public:
		// get the unique name of the factory
		virtual const String& getName() const = 0;

		// destruction method is the same for all factories
		virtual void destroyObject(T*) = 0;    
	};
	//-----------------------------------------------------------------------
	template<class T, class P1 = void, class P2 = void>
	class Factory : public BaseFactory<T>
	{
	public:
		virtual ~Factory() {};

		virtual T* createObject(P1, P2) = 0;    
	};
	//-----------------------------------------------------------------------
	template<class T, class P1>
	class Factory<T, P1> : public BaseFactory<T>
	{
	public:
		virtual ~Factory() {};
	
		virtual T* createObject(P1) = 0;    
	};
#define FactoryDecl_P1(base, P1) \
	class base##Factory : public Factory<base##, P1##>{}

#define FactoryImpl_P1(type, base, P1) \
	class type##Factory : public base##Factory \
	{ \
	public: \
		const String& getName() const \
		{ \
			static String name = #type; \
			return name; \
		} \
		base##* createObject(P1## p1) \
		{ \
			return new type##(p1); \
		} \
		void destroyObject(base##* inst) \
		{ \
			delete inst; \
		} \
	}
	//-----------------------------------------------------------------------
	template<class T>
	class Factory<T> : public BaseFactory<T>
	{
	public:
		virtual ~Factory() {};

		virtual T* createObject() = 0;    
	};
	//-----------------------------------------------------------------------
}

#endif
