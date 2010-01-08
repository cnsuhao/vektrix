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
#include "vtxswfParser.h"

#include "vtxButtonResource.h"
#include "vtxButtonState.h"
#include "vtxCreateObjectEvent.h"
#include "vtxCXForm.h"
#include "vtxMatrix.h"
#include "vtxStringHelper.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		void SwfParser2::handleDefineButton2()
		{
			UI16 btn_id = readU16();
			UI8 menu = readU8();
			UI16 action_offset = readU16();

			ButtonResource* button = new ButtonResource(StringHelper::toString(btn_id));

			UI8 state = readU8();
			while(state)	// state  -> parse ButtonRecord
			{
				ButtonState* btn_state = new ButtonState;
				String id = StringHelper::toString(readU16());
				uint layer = readU16();

				MATRIX m = readMatrix();
				CXFORM cx = readCxForm(true);

				Matrix matrix(
					m.sx/65536.0f, m.cx/65536.0f, m.tx/20.0f, 
					m.cy/65536.0f, m.sy/65536.0f, m.ty/20.0f);

				CXForm cxform(
					cx.mul_red/256.0f, cx.mul_green/256.0f, cx.mul_blue/256.0f, cx.mul_alpha/256.0f, 
					cx.add_red/256.0f, cx.add_green/256.0f, cx.add_blue/256.0f, cx.add_alpha/256.0f);

				btn_state->addEvent(new CreateObjectEvent(NULL, id, layer, matrix, cxform));

				if(state & 1) button->setState(btn_state, ButtonResource::SID_UP);
				if(state & 2) button->setState(btn_state, ButtonResource::SID_OVER);
				if(state & 4) button->setState(btn_state, ButtonResource::SID_DOWN);
				if(state & 8) button->setState(btn_state, ButtonResource::SID_HIT_AREA);

				state = readU8();
			}

			mCurrentFile->addResource(button);
		}
		//-----------------------------------------------------------------------
	}
}
