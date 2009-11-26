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
#include "vtxopTextureMovieFactory.h"

#include "vtxopTextureMovie.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		const std::string& TextureMovieFactory::getName() const
		{
			static std::string name = "OgreTextureMovie";
			return name;
		}
		//-----------------------------------------------------------------------
		vtx::Movie* TextureMovieFactory::createObject(std::string name, vtx::File* file)
		{
			return new TextureMovie(name, file, this);
		}
		//-----------------------------------------------------------------------
		void TextureMovieFactory::destroyObject(vtx::Movie* instance)
		{
			delete instance;
			instance = NULL;
		}
		//-----------------------------------------------------------------------
		const std::string& TextureMovieFactory::_getButtonFactoryName() const
		{
			static std::string name = "BLUBBLBUB";
			return name;
		}
		//-----------------------------------------------------------------------
		const std::string& TextureMovieFactory::_getShapeFactoryName() const
		{
			static std::string name = "OgreShape";
			return name;
		}
		//-----------------------------------------------------------------------
		const std::string& TextureMovieFactory::_getTextureFactoryName() const
		{
			static std::string name = "OgreTexture";
			return name;
		}
		//-----------------------------------------------------------------------
		RenderStrategy* TextureMovieFactory::_createDataPool(File* file)
		{
			return NULL;
		}
		//-----------------------------------------------------------------------
		MovieDebugger* TextureMovieFactory::_newDebugger(Movie* movie)
		{
			return NULL;
		}
		//-----------------------------------------------------------------------
	}
}
