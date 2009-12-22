#pragma once

#include "cspPrerequesites.h"

#include "vtxScriptMovieClip.h"

namespace vtx
{
	namespace as3
	{
		class MovieClipClass : public avmplus::ClassClosure
		{
		public:
			MovieClipClass(avmplus::VTable* cvtable);
			avmplus::ScriptObject* createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype);

			DECLARE_SLOTS_MovieClipClass;
		};

		class MovieClip : public Sprite, public vtx::ScriptMovieClip
		{
		public:
			MovieClip(avmplus::VTable* vtable, avmplus::ScriptObject* prototype);
			virtual ~MovieClip();

			vtx::ScriptObject* getChildScriptObject(const String& name);

			DECLARE_SLOTS_MovieClip;
		};
	}
}
