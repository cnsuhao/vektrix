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
#include "vtxMovieFactory.h"
#include "vtxFactoryManager.h"
#include "vtxSingleton.h"

namespace vtx
{
	/** The root class of the vektrix library
	@remarks
	The vtx::Root class is the class that gives you access to all
	underlying systems of vektrix and therefore has to be instanciated
	before you can use any of these. It's main tasks are the creation & 
	destruction of movie instances as well as the loading & unloading of plugins.
	The unique instance of the vtx::Root class, once constructed, is accessible via 
	the getSingletonPtr() method.
	*/
	class vtxExport Root : public Singleton<Root>, public FactoryManagerNULL<MovieFactory>
	{
	public:
		typedef std::map<String, Movie*> MovieMap;

		Root();
		virtual ~Root();

		// overridden from FactoryManager<MovieFactory>
		bool addFactory(MovieFactory* factory);

		/** Load a plugin from a shared library.
		@param
		name Name of the plugin that shall be loaded.
		*/
		void loadPlugin(const String& name);

		/** Unload a plugin that what previously loaded.
		@param
		name Name of the plugin that shall be unloaded.
		*/
		void unloadPlugin(const String& name);

		/** Unload all plugins that are currently loaded.
		*/
		void unloadAllPlugins();

		/** Create a instance of a movie.
		@param
		name A unique name that can be used to retrieve the movie instance from vtx::Root after creation.
		@param
		filename The file that defines the behaviour and appearance of the movie.
		@param
		factoryname The factory that shall be used to create the movie.
		@returns
		A pointer to the created vtx::Movie instance, NULL if an error occured.
		*/
		Movie* createMovie(const String& name, const String& filename, const String& factoryname);

		/** Method to update all underlying subsystems and movie instances of vektrix.
		@param
		delta_time Time that has passed till the last update.
		*/
		void update(float delta_time);

		Tesselator* getDefaultTesselator();

	protected:
		DynLibMap mLibraries;
		MovieMap mMovies;
		Tesselator* mDefaultTesselator;
	};
}
