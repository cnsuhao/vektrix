#include "vtxswfParser2.h"

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
					m.sx/65536.0f, -m.cx/65536.0f, m.tx/20.0f, 
					-m.cy/65536.0f, m.sy/65536.0f, m.ty/20.0f);

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
