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
#include "vtxopMovableMovieFactory.h"

#include "vtxopMovableMovie.h"
#include "vtxopRenderStrategy.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		const std::string& MovableMovieFactory::getName() const
		{
			static std::string name = "OgreMovableMovie";
			return name;
		}
		//-----------------------------------------------------------------------
		vtx::Movie* MovableMovieFactory::createObject(std::string name, vtx::File* file)
		{
			return new MovableMovie(name, file, this);
		}
		//-----------------------------------------------------------------------
		void MovableMovieFactory::destroyObject(vtx::Movie* instance)
		{
			delete instance;
			instance = NULL;
		}
		//-----------------------------------------------------------------------
		const std::string& MovableMovieFactory::_getButtonFactoryName() const
		{
			static std::string name = "BLUBBLBUB";
			return name;
		}
		//-----------------------------------------------------------------------
		const std::string& MovableMovieFactory::_getShapeFactoryName() const
		{
			static std::string name = "OgreShape";
			return name;
		}
		//-----------------------------------------------------------------------
		const std::string& MovableMovieFactory::_getTextureFactoryName() const
		{
			static std::string name = "OgreTexture";
			return name;
		}
		//-----------------------------------------------------------------------
		vtx::RenderStrategy* MovableMovieFactory::_createDataPool(File* file)
		{
			return new ogre::RenderStrategy(this, file);
		}
		//-----------------------------------------------------------------------
	}
}
