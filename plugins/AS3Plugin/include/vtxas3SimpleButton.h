#pragma once

#include "cspPrerequesites.h"

#include "vtxScriptButton.h"

namespace vtx
{
	namespace as3
	{
		class SimpleButtonClass : public avmplus::ClassClosure
		{
		public:
			SimpleButtonClass(avmplus::VTable* cvtable);
			avmplus::ScriptObject* createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype);

			DECLARE_SLOTS_SimpleButtonClass;
		};

		class SimpleButton : public InteractiveObject, public vtx::ScriptButton
		{
		public:
			SimpleButton(avmplus::VTable* vtable, avmplus::ScriptObject* prototype);
			virtual ~SimpleButton();

			vtx::ScriptObject* getChildScriptObject(const String& name);

			void buttonUp();

			virtual double get_x();
			virtual void set_x(double val);

			DECLARE_SLOTS_SimpleButton;

		protected:
			csp::VmCore* mCore;
			csp::ScriptObject* mObject;
		};
	}
}
