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

#include "vtxPrerequisites.h"
#include "vtxMovieFactory.h"
#include "vtxFactoryManager.h"
#include "vtxSingleton.h"

namespace vtx
{
	/** The root class of the vektrix library */
	class vtxExport Root : public Singleton<Root>, public FactoryManager<MovieFactory>
	{
	public:
		typedef std::map<String, Movie*> MovieMap;
		typedef std::vector<Plugin*> PluginList;

		Root();
		virtual ~Root();

		// overridden from FactoryManager<MovieFactory>
		bool addFactory(MovieFactory* factory);

		/** Load a plugin from a shared library */
		void loadLibrary(const String& name);

		/** Register a Plugin to the vektrix library */
		void registerPlugin(Plugin* plugin);

		/** Create an instance of a movie */
		Movie* createMovie(const String& name, const String& filename, const String& factoryname);

		/** Destroy an instance of a movie by name */
		bool destroyMovie(const String& name);

		/** Destroy an instance of a movie by pointer */
		bool destroyMovie(Movie* instance);

		/** Method to update all underlying subsystems and movie instances of vektrix */
		void update(float delta_time);

	protected:
		DynLibMap mLibraries;
		MovieMap mMovies;
		PluginList mPlugins;
		FileManager* mFileManager;
	};
}

#endif
