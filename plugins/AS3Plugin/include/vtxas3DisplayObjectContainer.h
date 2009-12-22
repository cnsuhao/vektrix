#pragma once

#include "cspPrerequesites.h"

namespace vtx
{
	namespace as3
	{
		class DisplayObjectContainerClass : public avmplus::ClassClosure
		{
		public:
			DisplayObjectContainerClass(avmplus::VTable* cvtable);
			avmplus::ScriptObject* createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype);

			DECLARE_SLOTS_DisplayObjectContainerClass;
		};

		class DisplayObjectContainer : public InteractiveObject
		{
		public:
			DisplayObjectContainer(avmplus::VTable* vtable, avmplus::ScriptObject* prototype);

			DECLARE_SLOTS_DisplayObjectContainer;
		};
	}
}
