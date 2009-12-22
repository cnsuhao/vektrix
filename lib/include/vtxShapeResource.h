/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009 Fuse-Software (tm)

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/
#pragma once

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
