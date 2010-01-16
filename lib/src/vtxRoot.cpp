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

#include "vtxRoot.h"

#include "vtxDynLib.h"
#include "vtxFileManager.h"
#include "vtxInstanceFactory.h"
#include "vtxLogManager.h"
#include "vtxMovie.h"
#include "vtxMovieFactory.h"
#include "vtxPlugin.h"
#include "vtxStringHelper.h"
#include "vtxTextureFactory.h"

#include "vtxRasterizerManager.h"
#include "vtxMaterialManager.h"
#include "vtxScriptEngineManager.h"
#include "vtxShapeManager.h"
#include "vtxTextureManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	template<> Root* Singleton<Root>::sInstance = 0;
	//-----------------------------------------------------------------------
	Root::Root() 
		: FactoryManagerNULL<MovieFactory>("Movie")
	{
		new LogManager();

		VTX_LOG("<< vektrix %s started >>", StringHelper::versionString(VTX_VERSION).c_str());
		VTX_LOG("<< Codename: %s >>", VTX_VERSION_NAME);

		new RasterizerManager();
		new MaterialManager();
		new ScriptEngineManager();
		new ShapeManager();
		new TextureManager();
		new FileManager();
	}
	//-----------------------------------------------------------------------
	Root::~Root()
	{
		VTX_LOG("<< shutting down vektrix... >>");

		MovieMap::iterator it = mMovies.begin();
		MovieMap::iterator end = mMovies.end();
		while(it != end)
		{
			delete it->second;
			++it;
		}

		// unload plugins
		PluginList::iterator plugin_it = mPlugins.begin();
		PluginList::iterator plugin_end = mPlugins.end();
		while(plugin_it != plugin_end)
		{
			delete *plugin_it;
			++plugin_it;
		}

		delete FileManager::getSingletonPtr();
		delete RasterizerManager::getSingletonPtr();
		delete MaterialManager::getSingletonPtr();
		delete ScriptEngineManager::getSingletonPtr();
		delete ShapeManager::getSingletonPtr();
		delete TextureManager::getSingletonPtr();

		// unload dynamic libraries
		DynLibMap::iterator dynlib_it = mLibraries.begin();
		DynLibMap::iterator dynlib_end = mLibraries.end();
		while(dynlib_it != dynlib_end)
		{
			dynlib_it->second->unload();
			delete dynlib_it->second;
			++dynlib_it;
		}

		VTX_LOG("<< vektrix successfully shut down >>");

		delete LogManager::getSingletonPtr();
	}
	//-----------------------------------------------------------------------
	bool Root::addFactory(MovieFactory* factory)
	{
		factory->_initialize();
		return FactoryManagerNULL<MovieFactory>::addFactory(factory);
	}
	//-----------------------------------------------------------------------
	void Root::loadPlugin(const String& name)
	{
#ifndef VTX_STATIC_LIB
		if(mLibraries.find(name) != mLibraries.end())
		{
			VTX_WARN("The Library \"%s\" was already loaded", name.c_str());
			return;
		}

		DynLib* library = new DynLib(name);
		library->load();
		mLibraries.insert(DynLibMap::value_type(name, library));
		START_PLUGIN_FUNCTION startPluginFunc = (START_PLUGIN_FUNCTION)library->getSymbol("startPlugin");

		if(!startPluginFunc)
		{
			VTX_EXCEPT("Cannot find symbol \"startPlugin()\" in library \"%s\"", name.c_str());
		}
		else
		{
			startPluginFunc();
		}
#else
		VTX_WARN("Tried to dynamically load plugin \"%s\", but vektrix was statically linked.", name.c_str());
#endif
	}
	//-----------------------------------------------------------------------
	Movie* Root::createMovie(const String& name, const String& filename, const String& factoryname)
	{
		if(mMovies.find(name) == mMovies.end())
		{
			File* file = FileManager::getSingletonPtr()->getFile(filename);

			MovieFactory* factory = getFactory(factoryname);

			if(!factory)
			{
				VTX_EXCEPT("A MovieFactory with the name \"%s\" was not found", factoryname.c_str());
				return NULL;
			}

			Movie* movie = factory->createObject(name, file);
			movie->_initialize(factory);
			//movie->goto_frame(1);

			mMovies.insert(MovieMap::value_type(name, movie));
			return movie;
		}

		// LOG: name already exists
		VTX_EXCEPT("A movie with the name '%s' already exists!", name.c_str());
		return NULL;
	}
	//-----------------------------------------------------------------------
	void Root::update(float delta_time)
	{
		MovieMap::iterator it = mMovies.begin();

		for( ; it != mMovies.end(); ++it)
		{
			it->second->addTime(delta_time);
		}
	}
	//-----------------------------------------------------------------------
	Tesselator* Root::getDefaultTesselator()
	{
		return mDefaultTesselator;
	}
	//-----------------------------------------------------------------------
	void Root::_addPlugin(Plugin* plugin)
	{
		mPlugins.push_back(plugin);
	}
	//-----------------------------------------------------------------------
}
