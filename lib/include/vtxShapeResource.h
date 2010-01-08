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

#ifndef __vtxShapeResource_H__
#define __vtxShapeResource_H__

#include "vtxPrerequesites.h"
#include "vtxBoundingBox.h"
#include "vtxResource.h"

namespace vtx
{
	class vtxExport ShapeResource : public Resource
	{
	public:
		typedef std::vector<SubshapeResource*> SubshapeList;

		ShapeResource(const String& id);
		virtual ~ShapeResource();

		bool operator<(const ShapeResource& shape) const;
		bool operator>(const ShapeResource& shape) const;

		bool _checkPointInside(const Matrix& world_mat, const Vector2& point);

		const String& getType() const;

		const float getArea() const;

		const float getWidth() const;
		const float getHeight() const;

		const float getMaximumWidth() const;
		const float getMaximumHeight() const;

		const uint getMaximumWidth_PoT() const;
		const uint getMaximumHeight_PoT() const;

		void setBoundingBox(const BoundingBox& bb);
		const BoundingBox& getBoundingBox() const;

		void addSubshapeResource(SubshapeResource* res);
		const SubshapeList& getSubshapeList() const;

		void _injectScale(const Vector2& scale);

	protected:
		BoundingBox mBoundingBox;
		Vector2 mMaximumScale;
		SubshapeList mSubshapes;
	};
}

#endif
