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
#include "vtxRoot.h"

#include "vtxDynLib.h"
#include "vtxFileManager.h"
#include "vtxInstanceFactory.h"
#include "vtxLogManager.h"
#include "vtxMovie.h"
#include "vtxMovieFactory.h"
#include "vtxPlugin.h"
#include "vtxTextureFactory.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	template<> Root* Singleton<Root>::sInstance = 0;
	//-----------------------------------------------------------------------
	Root::Root()
	{
		VTX_LOG(" -------------------------------");
		VTX_LOG("|     VEKTRIX 0.0.1 started     |");
		VTX_LOG(" -------------------------------");
	}
	//-----------------------------------------------------------------------
	bool Root::addFactory(MovieFactory* factory)
	{
		factory->_initialize();
		return FactoryManagerNULL::addFactory(factory);
	}
	//-----------------------------------------------------------------------
	void Root::loadPlugin(const String& name)
	{
		if(mLibraries.find(name) != mLibraries.end())
		{
			VTX_WARN("The Library \"%s\" was already loaded", name.c_str());
			return;
		}

		DynLib* library = new DynLib(name);
		library->load();
		mLibraries.insert(DynLibMap::value_type(name, library));
		START_PLUGIN_FUNCTION startPlugin = (START_PLUGIN_FUNCTION)library->getSymbol("startPlugin");

		if(!startPlugin)
		{
			VTX_EXCEPT("Cannot find symbol \"startPlugin()\" in library \"%s\"", name.c_str());
		}
		else
		{
			startPlugin();
		}
	}
	//-----------------------------------------------------------------------
	void Root::unloadPlugin(const String& name)
	{
		DynLibMap::iterator it = mLibraries.find(name);

		if(it != mLibraries.end())
		{
			STOP_PLUGIN_FUNCTION stopPlugin = (STOP_PLUGIN_FUNCTION)it->second->getSymbol("stopPlugin");
			stopPlugin();
			it->second->unload();
			delete it->second;
			mLibraries.erase(it);
		}
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
			movie->_setCreator(factory);

			movie->_initialize(factory->getDataPool(file));

			// TODO: deprecated ?
			//movie->_initialize(file);

			mMovies.insert(MovieMap::value_type(name, movie));

			// TODO: REMOVE
			//movie->_initialize();

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
}
