#pragma once

#include "cspPrerequesites.h"

namespace vtx
{
	namespace as3
	{
		using namespace avmplus;
		class EventDispatcherClass : public avmplus::ClassClosure
		{
		public:
			EventDispatcherClass(avmplus::VTable* cvtable);
			avmplus::ScriptObject* createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype);

			DECLARE_SLOTS_EventDispatcherClass;
		};

		class EventDispatcher : public avmplus::ScriptObject
		{
		public:
			EventDispatcher(avmplus::VTable* vtable, avmplus::ScriptObject* prototype);

			//bool dispatchEvent(ScriptObject* event);

			DECLARE_SLOTS_EventDispatcher;
		};
	}
}
