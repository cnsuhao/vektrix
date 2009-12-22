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

#include "defines.h"
#include "vtxPrerequesites.h"

#include "vtxAtlasPacker.h"
#include "vtxRect.h"
#include "vtxShape.h"

#include "OgreRenderable.h"
#include "OgreVector3.h"

namespace vtx
{
	namespace ogre
	{
		class vtxopExport OgreShape : public vtx::Shape, public Ogre::Renderable
		{
		public:
			OgreShape(vtx::Resource* resource);
			virtual ~OgreShape();

			// Ogre functions
			const Ogre::MaterialPtr& getMaterial() const;
			void getRenderOperation(Ogre::RenderOperation& op);
			void getWorldTransforms(Ogre::Matrix4* xform) const;
			const Ogre::Quaternion& getWorldOrientation() const;
			const Ogre::Vector3& getWorldPosition() const;
			Ogre::Real getSquaredViewDepth(const Ogre::Camera* cam) const;
			const Ogre::LightList& getLights() const;

			//void setMatrix(const vtx::Matrix& m);
			//void setCXForm(const vtx::CXForm& cx);
			void _update(const float& delta_time);

			void setAtlasQuad(const AtlasPacker::PackResult& quad);

			//bool supportsAlpha() const;

		protected:
			float mLayer;

			// bounding box
			const BoundingBox& mBoundingBox;

			// transforms
			Ogre::Matrix4 mTransform;
	
			// texture UVs
			RectF mUVs;

			// colors
			Ogre::ColourValue mMULcolor;
			Ogre::ColourValue mADDcolor;

			// rendering
			Ogre::HardwareVertexBufferSharedPtr mBuffer;
			Ogre::MaterialPtr mMaterial;
			Ogre::RenderOperation mRenderOp;
			Ogre::VertexDeclaration* mVertexDecl;
			Ogre::VertexBufferBinding* mVertexBufferBind;

			void _createGeometry();
			void _updateGeometry();
		};
	}
}
