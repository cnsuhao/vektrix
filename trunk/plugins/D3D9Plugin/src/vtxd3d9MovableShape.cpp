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

#include "vtxd3d9MovableShape.h"
#include "vtxd3d9MovableMovie.h"
#include "vtxd3d9Texture.h"

#include "vtxAtlasNode.h"
#include "vtxRect.h"

namespace vtx
{
	namespace d3d9
	{
		//-----------------------------------------------------------------------
		D3D9MovableShape::D3D9MovableShape(vtx::Resource* resource) 
			: Shape(resource), 
			mParentMovable(NULL)
		{

		}
		//-----------------------------------------------------------------------
		D3D9MovableShape::~D3D9MovableShape()
		{

		}
		//-----------------------------------------------------------------------
		void D3D9MovableShape::_setParent(Movie* parent)
		{
			Shape::_setParent(parent);
			mParentMovable = dynamic_cast<MovableMovie*>(parent);
		}
		//-----------------------------------------------------------------------
		void D3D9MovableShape::_update(const float& delta_time)
		{
			Shape::_update(delta_time);

			const Matrix& mat = getWorldMatrix();

			// calculate d3d world matrix here
		}
		//-----------------------------------------------------------------------
		void D3D9MovableShape::setAtlasQuad(const AtlasPacker::PackResult& quad)
		{
			D3D9Texture* texture = dynamic_cast<D3D9Texture*>(quad.texture);
			RectF tex_coords = quad.node->getRect().relativeTo(quad.texture->getSize(), quad.texture->getSize());

			// update d3d vertex buffer here
		}
		//-----------------------------------------------------------------------
	}
}
