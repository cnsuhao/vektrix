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

#ifndef __vtxButtonResource_H__
#define __vtxButtonResource_H__

#include "vtxPrerequisites.h"
#include "vtxResource.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** A Resource which contains all necessary data for creating a Button instance */
	class vtxExport ButtonResource : public Resource
	{
	public:
		enum StateID
		{
			SID_UP = 0,
			SID_OVER, 
			SID_DOWN, 
			SID_HIT_AREA, 
		};

		ButtonResource(const String& id);
		virtual ~ButtonResource();

		/** @copybrief Resource::getType */
		const String& getType() const;

		/** Set the different states for the button */
		void setState(ButtonState* state, const StateID& id);
		/** Get the different states of the button */
		ButtonState* getState(const StateID& id);

	protected:
		// 3 visual states + 1 special "state" for collision checking
		ButtonState* mStates[4];

	};
	//-----------------------------------------------------------------------
}

#endif
