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

#include "vtxPrerequesites.h"
//#include "vtxFactory.h"
#include "vtxMovieFactory.h"
#include "vtxFactoryManager.h"
#include "vtxSingleton.h"

namespace vtx
{
	class vtxExport Root : public Singleton<Root>, public FactoryManagerNULL<MovieFactory>
	{
	public:
		typedef std::map<String, Movie*> MovieMap;

		Root();
		virtual ~Root();

		// overridden from FactoryManager<MovieFactory>
		bool addFactory(MovieFactory* factory);

		void loadPlugin(const String& name);
		void unloadPlugin(const String& name);
		void unloadAllPlugins();

		Movie* createMovie(const String& name, const String& filename, const String& factoryname);

		void update(float delta_time);

		Tesselator* getDefaultTesselator();

	protected:
		DynLibMap mLibraries;
		MovieMap mMovies;
		Tesselator* mDefaultTesselator;
	};
}
