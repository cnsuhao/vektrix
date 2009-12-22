#pragma once

#include "cspPrerequesites.h"

namespace vtx
{
	namespace as3
	{
		class DisplayObjectClass : public avmplus::ClassClosure
		{
		public:
			DisplayObjectClass(avmplus::VTable* cvtable);
			avmplus::ScriptObject* createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype);

			DECLARE_SLOTS_DisplayObjectClass;
		};

		class DisplayObject : public EventDispatcher
		{
		public:
			DisplayObject(avmplus::VTable* vtable, avmplus::ScriptObject* prototype);

			double mValue;

			virtual double get_x();
			virtual void set_x(double val);

			DECLARE_SLOTS_DisplayObject;
		};
	}
}
