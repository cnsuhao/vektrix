#pragma once

#include "cspPrerequesites.h"

namespace vtx
{
	namespace as3
	{
		class EventHandlerClass : public avmplus::ClassClosure
		{
		public:
			EventHandlerClass(avmplus::VTable* cvtable);
			avmplus::ScriptObject* createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype);

			void handle(avmplus::ScriptObject* evt);

			DECLARE_SLOTS_EventHandlerClass;
		};

		class EventHandler : public avmplus::ScriptObject
		{
		public:
			EventHandler(avmplus::VTable* vtable, avmplus::ScriptObject* prototype);

			DECLARE_SLOTS_EventHandler;
		};
	}
}
