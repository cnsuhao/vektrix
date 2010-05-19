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

// TODO
#include "vtxResource.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		OgreMovableEditText::OgreMovableEditText(Resource* resource) 
			: EditText(resource), 
			MovableTextBase(this)
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

			mParentMovable = dynamic_cast<MovableMovie*>(parent);
		}
		//-----------------------------------------------------------------------
		void OgreMovableEditText::_update(const float& delta_time)
		{
			EditText::_update(delta_time);

			const Matrix& mat = getWorldMatrix();

			mWorldMatrix = Ogre::Matrix4(
				mat.m[0][0], -mat.m[0][1], 0,  mat.m[0][2], 
				-mat.m[1][0], mat.m[1][1], 0, -mat.m[1][2], 
				0,		  0,		   1,				0,
				0,		  0,		   0,				1);
		}
		//-----------------------------------------------------------------------
		void OgreMovableEditText::setAtlasList(const AtlasPacker::PackResultList& atlas_list)
		{
			mAtlasList = atlas_list;
		}
		//-----------------------------------------------------------------------
		void OgreMovableEditText::packed(const AtlasPacker::PackResultList& pack_result)
		{
			setAtlasList(pack_result);
			_updateGraphics();
		}
		//-----------------------------------------------------------------------
		void OgreMovableEditText::_updateGraphics()
		{
			_resizeBuffers(mGlyphCount);
			_updateVertexBuffer(mGlyphStrips, mAtlasList, mResource->getFile());
		}
		//-----------------------------------------------------------------------
	}
}
