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

#ifndef __vtxopShape_H__
#define __vtxopShape_H__

#include "vtxop.h"

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
			Ogre::Matrix4 mWorldMatrix;
	
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

#endif
