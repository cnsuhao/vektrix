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

#ifndef __vtxRoot_H__
#define __vtxRoot_H__

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
		typedef std::vector<Plugin*> PluginList;

		Root();
		virtual ~Root();

		// overridden from FactoryManager<MovieFactory>
		bool addFactory(MovieFactory* factory);

		/** Load a plugin from a shared library.
		@param
		name Name of the plugin that shall be loaded.
		*/
		void loadPlugin(const String& name);

		/** Create an instance of a movie.
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

		void _addPlugin(Plugin* plugin);

	protected:
		DynLibMap mLibraries;
		MovieMap mMovies;
		PluginList mPlugins;
		Tesselator* mDefaultTesselator;
	};
}

#endif
