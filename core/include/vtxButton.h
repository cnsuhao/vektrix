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

#ifndef __vtxButton_H__
#define __vtxButton_H__

#include "vtxPrerequesites.h"
#include "vtxDisplayObjectContainer.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** Represents a visual button */
	class vtxExport Button : public DisplayObjectContainer
	{
	public:
		Button(Resource* resource);
		virtual ~Button();

		enum MouseState
		{
			MS_OUT_UP = 0, 
			MS_OUT_DOWN, 
			MS_IN_UP, 
			MS_IN_DOWN
		};

		/** @copybrief DisplayObjectContainer::_update */
		virtual void _update(const float& delta_time = 0.0f);
		/** @copybrief DisplayObject::getBoundingBox */
		const BoundingBox& getBoundingBox() const;

		/** @copybrief Instance::_setParent */
		virtual void _setParent(Movie* parent);

		// inherited from EventListener
		void eventFired(const Event& evt);

	protected:
		bool mMouseDown;
		bool mMouseOver;
		BoundingBox mBB;

		MouseState mMouseState;

		ButtonState* mUp;
		ButtonState* mOver;
		ButtonState* mDown;
	};
	//-----------------------------------------------------------------------
}

#endif
