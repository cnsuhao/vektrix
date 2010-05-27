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

#ifndef __vtxInstanceManager_H__
#define __vtxInstanceManager_H__

#include "vtxPrerequesites.h"
#include "vtxEditText.h"
#include "vtxFactoryManager.h"
#include "vtxScriptEngine.h"
#include "vtxShape.h"
#include "vtxStaticText.h"
#include "vtxTexture.h"
#include "vtxSingleton.h"

namespace vtx
{
	/** The manager that keeps track of all different kinds of Instance factories */
	class vtxExport InstanceManager : public Singleton<InstanceManager>, public FactoryManager<InstanceFactory>
	{
		friend class Root;

	public:
		/** The ScriptEngineFactory sub-manager */
		FactoryManagerImpl(ScriptEngines, ScriptEngine);
		/** The TextureFactory sub-manager */
		FactoryManagerImpl(Textures, Texture);

		/** Get the ScriptEngineFactory sub-manager */
		ScriptEngines* scriptEngines();
		/** Get the TextureFactory sub-manager */
		Textures* textures();

	protected:
		ScriptEngines* mScriptEngines;
		Textures* mTextures;

		InstanceManager();
		virtual ~InstanceManager();
	};
}

#endif
