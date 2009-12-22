#pragma once

#include "cspPrerequesites.h"

namespace vtx
{
	namespace as3
	{
		class InteractiveObjectClass : public avmplus::ClassClosure
		{
		public:
			InteractiveObjectClass(avmplus::VTable* cvtable);
			avmplus::ScriptObject* createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype);

			DECLARE_SLOTS_InteractiveObjectClass;
		};

		class InteractiveObject : public DisplayObject
		{
		public:
			InteractiveObject(avmplus::VTable* vtable, avmplus::ScriptObject* prototype);

			DECLARE_SLOTS_InteractiveObject;
		};
	}
}
