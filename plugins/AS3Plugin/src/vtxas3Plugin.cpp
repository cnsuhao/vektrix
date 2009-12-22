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
#include "vtxas3Plugin.h"
#include "vtxas3ScriptEngine.h"

#include "vtxScriptEngineManager.h"

namespace vtx
{
	namespace as3
	{
		//-----------------------------------------------------------------------
		AS3Plugin* plugin = NULL;
		//-----------------------------------------------------------------------
		extern "C" void vtxas3Export startPlugin() throw()
		{
			plugin = new AS3Plugin();
		}

		//-----------------------------------------------------------------------
		extern "C" void vtxas3Export stopPlugin()
		{
			delete plugin;
		}
		//-----------------------------------------------------------------------
		AS3Plugin::AS3Plugin() 
			: mAS3ScriptEngine(new AS3ScriptEngineFactory)
		{
			ScriptEngineManager::getSingletonPtr()->addFactory(mAS3ScriptEngine);
		}
		//-----------------------------------------------------------------------
		AS3Plugin::~AS3Plugin()
		{
			delete mAS3ScriptEngine;
		}
		//-----------------------------------------------------------------------
	}
}
