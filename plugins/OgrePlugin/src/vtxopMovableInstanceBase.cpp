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

#include "vtxopMovableInstanceBase.h"
#include "vtxopMovableMovie.h"

#include "vtxColor.h"

#include "OgreCamera.h"
#include "OgreHardwareBufferManager.h"
#include "OgreMovableObject.h"
#include "OgreSceneNode.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		MovableInstanceBase::MovableInstanceBase() 
			: mVertex(NULL), 
			mParentMovable(NULL)
		{
			mRenderOp.vertexData = NULL;
			mRenderOp.indexData = NULL;

			mRenderOp.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST; 
			mRenderOp.useIndexes = true;
		}
		//-----------------------------------------------------------------------
		MovableInstanceBase::~MovableInstanceBase()
		{
			delete mRenderOp.vertexData;
			delete mRenderOp.indexData;

			mRenderOp.vertexData = NULL;
			mRenderOp.indexData = NULL;
		}
		//-----------------------------------------------------------------------
		const Ogre::MaterialPtr& MovableInstanceBase::getMaterial() const
		{
			return mMaterial;
		}
		//-----------------------------------------------------------------------
		void MovableInstanceBase::getRenderOperation(Ogre::RenderOperation& op)
		{
			op = mRenderOp;
		}
		//-----------------------------------------------------------------------
		void MovableInstanceBase::getWorldTransforms(Ogre::Matrix4* xform) const
		{
			Ogre::Matrix4 ogre_mat = mParentMovable->_getParentNodeFullTransform();
			xform[0] = ogre_mat * mWorldMatrix;
		}
		//-----------------------------------------------------------------------
		const Ogre::Quaternion& MovableInstanceBase::getWorldOrientation() const
		{
			return mParentMovable->getParentSceneNode()->_getDerivedOrientation();
		}
		//-----------------------------------------------------------------------
		const Ogre::Vector3& MovableInstanceBase::getWorldPosition() const
		{
			return mParentMovable->getParentSceneNode()->_getDerivedPosition();
		}
		//-----------------------------------------------------------------------
		Ogre::Real MovableInstanceBase::getSquaredViewDepth(const Ogre::Camera* cam) const
		{
			return cam->getDerivedPosition().squaredDistance(
				mParentMovable->getParentNode()->_getDerivedPosition());
		}
		//-----------------------------------------------------------------------
		const Ogre::LightList& MovableInstanceBase::getLights() const
		{
			return mParentMovable->queryLights();
		}
		//-----------------------------------------------------------------------
		void MovableInstanceBase::_lock()
		{
			mVertex = static_cast<float*>(mBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));
		}
		//-----------------------------------------------------------------------
		void MovableInstanceBase::_unlock()
		{
			mBuffer->unlock();
			mVertex = NULL;
		}
		//-----------------------------------------------------------------------
		void MovableInstanceBase::_createBuffers()
		{
			mRenderOp.vertexData = new Ogre::VertexData;
			mRenderOp.indexData = new Ogre::IndexData;

			mRenderOp.vertexData->vertexStart = 0;
			mRenderOp.indexData->indexStart = 0;

			size_t offset = 0;
			mVertexDecl = mRenderOp.vertexData->vertexDeclaration;
			mVertexBufferBind = mRenderOp.vertexData->vertexBufferBinding;

			// position
			if(!mVertexDecl->findElementBySemantic(Ogre::VES_POSITION))
			{
				mVertexDecl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
			}
			offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

			// normal
			if(!mVertexDecl->findElementBySemantic(Ogre::VES_NORMAL))
			{
				mVertexDecl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
			}
			offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

			// diffuse
			if(!mVertexDecl->findElementBySemantic(Ogre::VES_DIFFUSE))
			{
				mVertexDecl->addElement(0, offset, Ogre::VET_FLOAT4, Ogre::VES_DIFFUSE);
			}
			offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT4);

			// specular
			if(!mVertexDecl->findElementBySemantic(Ogre::VES_SPECULAR))
			{
				mVertexDecl->addElement(0, offset, Ogre::VET_FLOAT4, Ogre::VES_SPECULAR);
			}
			offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT4);

			// texture coordinates
			if(!mVertexDecl->findElementBySemantic(Ogre::VES_TEXTURE_COORDINATES))
			{
				mVertexDecl->addElement(0, offset, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES, 0);
			}
		}
		//-----------------------------------------------------------------------
		void MovableInstanceBase::_resizeBuffers(uint num_quads)
		{
			if(!num_quads)
			{
				num_quads = 1;
			}

			mRenderOp.vertexData->vertexCount = num_quads * 4;
			mRenderOp.indexData->indexCount = num_quads * 6;

			mBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
				mVertexDecl->getVertexSize(0), 
				mRenderOp.vertexData->vertexCount, 
				Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

			mVertexBufferBind->setBinding(0, mBuffer);

			Ogre::HardwareIndexBufferSharedPtr ibuffer = Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
				Ogre::HardwareIndexBuffer::IT_16BIT, // type of index
				mRenderOp.indexData->indexCount, // number of indexes
				Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, // usage
				false); // no shadow buffer

			unsigned short* index = static_cast<unsigned short*>(ibuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));

			for(uint i=0; i<num_quads; ++i)
			{
				*index++ = 0+i*4;
				*index++ = 1+i*4;
				*index++ = 2+i*4;

				*index++ = 0+i*4;
				*index++ = 2+i*4;
				*index++ = 3+i*4;
			}

			ibuffer->unlock();

			mRenderOp.indexData->indexBuffer = ibuffer;
		}
		//-----------------------------------------------------------------------
		void MovableInstanceBase::_addVertex(
			const Vector2& position, 
			const Vector2& texcoord, 
			const Color& diffuse, 
			const Color& specular)
		{
			// position
			*mVertex++ = position.x;
			*mVertex++ = position.y;
			*mVertex++ = 0;

			// normal
			*mVertex++ = 0;
			*mVertex++ = 0;
			*mVertex++ = -1;

			// diffuse
			*mVertex++ = diffuse.r;
			*mVertex++ = diffuse.g;
			*mVertex++ = diffuse.b;
			*mVertex++ = diffuse.a;

			// specular
			*mVertex++ = specular.r;
			*mVertex++ = specular.g;
			*mVertex++ = specular.b;
			*mVertex++ = specular.a;

			// texture coordinate
			*mVertex++ = texcoord.x;
			*mVertex++ = texcoord.y;
		}
		//-----------------------------------------------------------------------
	}
}
