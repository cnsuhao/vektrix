#pragma once

#include "cspPrerequesites.h"

namespace vtx
{
	namespace as3
	{
		class SpriteClass : public avmplus::ClassClosure
		{
		public:
			SpriteClass(avmplus::VTable* cvtable);
			avmplus::ScriptObject* createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype);

			DECLARE_SLOTS_SpriteClass;
		};

		class Sprite : public DisplayObjectContainer
		{
		public:
			Sprite(avmplus::VTable* vtable, avmplus::ScriptObject* prototype);

			DECLARE_SLOTS_Sprite;
		};
	}
}
