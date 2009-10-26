/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/vektrix

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

namespace vtx
{
	//-----------------------------------------------------------------------
	template<class T>
	class BaseFactory
	{
	public:
		// get the type of the instance that this factory creates
		virtual const String& getType() const = 0;

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
