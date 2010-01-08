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

#include "vtxCreateObjectEvent.h"
#include "vtxCXForm.h"
#include "vtxKeyframe.h"
#include "vtxLogManager.h"
#include "vtxMatrix.h"
#include "vtxMoveObjectEvent.h"
#include "vtxStringHelper.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		void SwfParser2::handlePlaceObject2()
		{
			resetReadBits();
			UI8 has_clip_actions = readUBits(1);
			UI8 has_clip_depth = readUBits(1);
			UI8 has_name = readUBits(1);
			UI8 has_ratio = readUBits(1);
			UI8 has_color_transform = readUBits(1);
			UI8 has_matrix = readUBits(1);
			UI8 has_character = readUBits(1);
			UI8 has_move = readUBits(1);

			UI16 depth = readU16();

			Matrix matrix;
			CXForm cxform;

			UI16 character = 0;
			if(has_character)
			{
				character = readU16();
			}

			if(has_matrix)
			{
				MATRIX m = readMatrix();
				matrix = Matrix(
					m.sx/65536.0f, m.cx/65536.0f, m.tx/20.0f, 
					m.cy/65536.0f, m.sy/65536.0f, m.ty/20.0f);
			}

			if(has_color_transform)
			{
				CXFORM cx = readCxForm(true);
				cxform = CXForm(
					cx.mul_red/256.0f, cx.mul_green/256.0f, cx.mul_blue/256.0f, cx.mul_alpha/256.0f, 
					cx.add_red/256.0f, cx.add_green/256.0f, cx.add_blue/256.0f, cx.add_alpha/256.0f);
			}

			UI16 ratio = 0;
			if(has_ratio)
			{
				ratio = readU16();
			}

			String name = "";
			if(has_name)
			{
				name = readString();
			}

			UI16 clip_depth = 0;
			if(has_clip_depth)
			{
				clip_depth = readU16();
			}

			if(has_clip_actions)
			{
				assert(false && "Currently not supporting clip actions");
			}

			if(has_move)
			{
				// move
				mCurrentKeyframe->addEvent(new MoveObjectEvent(NULL, depth, matrix, cxform));
			}
			else if(has_character)
			{
				// place
				String id = StringHelper::toString(character);
				mCurrentKeyframe->addEvent(new CreateObjectEvent(NULL, id, depth, matrix, cxform, name));
			}
		}
		//-----------------------------------------------------------------------
	}
}
