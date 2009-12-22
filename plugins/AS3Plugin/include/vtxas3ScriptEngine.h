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

#ifndef __vtxas3AS3ScriptEngine_H__
#define __vtxas3AS3ScriptEngine_H__

#include "vtxas3.h"
#include "vtxPrerequesites.h"

#include "vtxFactory.h"
#include "vtxScriptEngine.h"

#undef FAILED

#include "cspPrerequesites.h"
#include "cspOutputListener.h"

namespace vtx
{
	namespace as3
	{
		//-----------------------------------------------------------------------
		class AS3ScriptEngine : public ScriptEngine, public csp::OutputListener
		{
		public:
			AS3ScriptEngine(Movie* parent);
			virtual ~AS3ScriptEngine();

			bool executeCode(const char* code, const uint& len);
			ScriptObject* getRootScriptObject();

		protected:
			csp::VmCore* mVmCore;
			csp::ScriptObject* mRoot;
			vtx::as3::MovieClip* mRootObject;

			void output(const std::string& message);
		};
		//-----------------------------------------------------------------------
		FactoryImpl_P1(AS3ScriptEngine, ScriptEngine, Movie*);
		//-----------------------------------------------------------------------
	}
}

#endif
