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

#ifndef __vtxScriptEngine_H__
#define __vtxScriptEngine_H__

#include "vtxPrerequisites.h"
#include "vtxFactory.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** The base interface for all implementations of scripting virtual machines */
	class vtxExport ScriptEngine
	{
	public:
		ScriptEngine(Movie* parent);
		virtual ~ScriptEngine();

		/** Execute a given script code buffer */
		virtual bool executeCode(const char* code, const uint& len) = 0;

		/** Get the root ScriptObject that will be associated with the main MovieClip of a Movie */
		virtual ScriptObject* getRootScriptObject(MovieClip* movieclip) = 0;

		/** Create a ScriptObject for the given Instance */
		virtual ScriptObject* createScriptObject(Instance* instance) = 0;

		/** Destroy the given ScriptObject */
		virtual void destroyScriptObject(ScriptObject* script_object) = 0;

		/** Get the Movie that uses this ScriptEngine */
		Movie* getParentMovie() const;

	protected:
		Movie* mParent;
	};
	//-----------------------------------------------------------------------
	/** The Factory for creating ScriptEngine objects */
	FactoryDecl_P1(ScriptEngine, Movie*);
	//-----------------------------------------------------------------------
}

#endif
