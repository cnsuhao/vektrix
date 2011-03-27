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

#include "vtxopMovableEditText.h"
#include "vtxopMovableMovie.h"

#include "vtxEditTextResource.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		OgreMovableEditText::OgreMovableEditText() 
			: MovableTextBase(this)
		{
			_createBuffers();
		}
		//-----------------------------------------------------------------------
		OgreMovableEditText::~OgreMovableEditText()
		{

		}
		//-----------------------------------------------------------------------
		void OgreMovableEditText::_setParent(Movie* parent)
		{
			EditText::_setParent(parent);
			mParentMovable = static_cast<MovableMovie*>(parent);

			if(mParentMovable)
			{
				mPacker = mParentMovable->getPacker();

				if(mPacker)
				{
					mPacker->addListener(this);
				}
			}
			else
			{
				if(mPacker)
				{
					mPacker->removeListener(this);
				}
			}
		}
		//-----------------------------------------------------------------------
		void OgreMovableEditText::initFromResource(Resource* resource)
		{
			EditText::initFromResource(resource);

			if(resource->getType() == "EditText")
			{
				EditTextResource* res = static_cast<EditTextResource*>(resource);
				setHtmlText(res->getInitialText());
			}
		}
		//-----------------------------------------------------------------------
		void OgreMovableEditText::updateGraphics(const float& delta_time)
		{
			EditText::updateGraphics(delta_time);

			const Matrix& mat = getWorldMatrix();

			mWorldMatrix = Ogre::Matrix4(
				mat.m[0][0], -mat.m[0][1], 0,  mat.m[0][2], 
				-mat.m[1][0], mat.m[1][1], 0, -mat.m[1][2], 
				0,		  0,		   1,				0,
				0,		  0,		   0,				1);
		}
		//-----------------------------------------------------------------------
		void OgreMovableEditText::packed(const AtlasPacker::PackResultList& pack_result)
		{
			_updateGraphics();
		}
		//-----------------------------------------------------------------------
		void OgreMovableEditText::_updateGraphics()
		{
			_resizeBuffers(mGlyphCount);
			if(mParentMovie && mPacker)
			{
				_updateVertexBuffer(mGlyphStrips, mPacker->getResultList(), mParentMovie->getFile());
			}
		}
		//-----------------------------------------------------------------------
	}
}
