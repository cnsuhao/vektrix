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

#ifndef __vtxas3AS3ScriptEngine_H__
#define __vtxas3AS3ScriptEngine_H__

#include "vtxas3.h"

#include "vtxFactory.h"
#include "vtxScriptEngine.h"

#include "cspPrerequisites.h"
#include "cspOutputListener.h"

namespace vtx { namespace as3 {
	//-----------------------------------------------------------------------
	/** The ScriptEngine that wraps the Adobe ActionScript 3 virtual machine */
	class AS3ScriptEngine : public ScriptEngine, public csp::OutputListener
	{
	public:
		AS3ScriptEngine(Movie* parent);
		virtual ~AS3ScriptEngine();

		/** @copybrief ScriptEngine::executeCode */
		bool executeCode(const char* code, const uint& len);

		/** @copybrief ScriptEngine::getRootScriptObject */
		ScriptObject* getRootScriptObject(vtx::MovieClip* movieclip);

		/** @copybrief ScriptEngine::createScriptObject */
		ScriptObject* createScriptObject(Instance* instance);

		/** @copybrief ScriptEngine::destroyScriptObject */
		void destroyScriptObject(ScriptObject* script_object);

		Instance* getQueuedInstance() const;

	protected:
		csp::VmCore* mVmCore;
		as3::MovieClip* mRootObject;
		SymbolClassResource* mSymbols;

		Instance* mQueuedInstance;

		/** Receive output from the ActionScript 3 virtual machine */
		void output(const String& message);
	};
	//-----------------------------------------------------------------------
	FactoryImpl_P1(AS3ScriptEngine, ScriptEngine, Movie*);
	//-----------------------------------------------------------------------
}}
#endif
