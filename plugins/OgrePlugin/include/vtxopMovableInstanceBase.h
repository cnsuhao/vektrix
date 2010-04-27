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

#ifndef __vtxopMovableInstanceBase_H__
#define __vtxopMovableInstanceBase_H__

#include "vtxop.h"

#include "OgreRenderable.h"

#pragma warning (disable : 4355)

namespace vtx
{
	namespace ogre
	{
		class vtxopExport MovableInstanceBase : public Ogre::Renderable
		{
		public:
			MovableInstanceBase(DisplayObject* display_object);
			virtual ~MovableInstanceBase();

			// Ogre functions
			const Ogre::MaterialPtr& getMaterial() const;
			void getRenderOperation(Ogre::RenderOperation& op);
			void getWorldTransforms(Ogre::Matrix4* xform) const;
			const Ogre::Quaternion& getWorldOrientation() const;
			const Ogre::Vector3& getWorldPosition() const;
			Ogre::Real getSquaredViewDepth(const Ogre::Camera* cam) const;
			const Ogre::LightList& getLights() const;

		private:
			// rendering
			float* mVertex;
			Ogre::HardwareVertexBufferSharedPtr mBuffer;
			Ogre::RenderOperation mRenderOp;
			Ogre::VertexDeclaration* mVertexDecl;
			Ogre::VertexBufferBinding* mVertexBufferBind;

		protected:
			DisplayObject* mDisplayObject;
			Ogre::MaterialPtr mMaterial;
			Ogre::Matrix4 mWorldMatrix;
			MovableMovie* mParentMovable;

			void _lock();
			void _unlock();

			void _createBuffers();
			void _resizeBuffers(uint num_quads);
			void _addVertex(
				const Vector2& position, 
				const Vector2& texcoord, 
				const Color& diffuse, 
				const Color& specular);
		};
	}
}

#endif
