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
	/** The base class for all factory templates */
	template<class T>
	class BaseFactory
	{
	public:
		/** Get the unique name of the factory */
		virtual const String& getName() const = 0;

		/** Destroy an object with this factory */
		virtual void destroyObject(T*) = 0;    
	};
	//-----------------------------------------------------------------------
	/** A factory template for creating objects with two constructor arguments */
	template<class T, class P1 = void, class P2 = void>
	class Factory : public BaseFactory<T>
	{
	public:
		virtual ~Factory() {};

		/** Create an object with this factory using two constructor arguments */
		virtual T* createObject(P1, P2) = 0;    
	};
	//-----------------------------------------------------------------------
	/** A factory template for creating objects with one constructor argument */
	template<class T, class P1>
	class Factory<T, P1> : public BaseFactory<T>
	{
	public:
		virtual ~Factory() {};

		/** Create an object with this factory using one constructor argument */
		virtual T* createObject(P1) = 0;    
	};
	//-----------------------------------------------------------------------
	/** A factory template for creating objects with no constructor arguments */
	template<class T>
	class Factory<T> : public BaseFactory<T>
	{
	public:
		virtual ~Factory() {};

		/** Create an object with this factory using no constructor arguments */
		virtual T* createObject() = 0;    
	};
	//-----------------------------------------------------------------------
#define FactoryDecl_P0(base) \
	class base##Factory : public Factory<base##>{}
	//-----------------------------------------------------------------------
#define FactoryDecl_P1(base, P1) \
	class base##Factory : public Factory<base, P1>{}
	//-----------------------------------------------------------------------
#define FactoryImpl_P0(type, base) \
	class type##Factory : public base##Factory \
	{ \
	public: \
		const String& getName() const \
		{ \
			static String name = #type; \
			return name; \
		} \
		base* createObject() \
		{ \
			return new type(); \
		} \
		void destroyObject(base* inst) \
		{ \
			delete inst; \
		} \
	}
	//-----------------------------------------------------------------------
#define FactoryImpl_P1(type, base, P1) \
	class type##Factory : public base##Factory \
	{ \
	public: \
		const String& getName() const \
		{ \
			static String name = #type; \
			return name; \
		} \
		base* createObject(P1 p1) \
		{ \
			return new type(p1); \
		} \
		void destroyObject(base* inst) \
		{ \
			delete inst; \
		} \
	}
	//-----------------------------------------------------------------------
#define FactoryImpl_P2(type, base, P1, P2) \
	class type##Factory : public base##Factory \
	{ \
	public: \
		const String& getName() const \
		{ \
			static String name = #type; \
			return name; \
		} \
		base* createObject(P1 p1, P2 p2) \
		{ \
			return new type(p1, p2); \
		} \
		void destroyObject(base* inst) \
		{ \
			delete inst; \
		} \
	}
	//-----------------------------------------------------------------------
}

#endif
