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

#include "vtxopShape.h"
#include "vtxAtlasNode.h"
#include "vtxResource.h"
#include "vtxShapeResource.h"

#include "vtxopMovableMovie.h"
#include "vtxopTexture.h"

#include "OgreCamera.h"
#include "OgreHardwareBufferManager.h"
#include "OgreMaterialManager.h"
#include "OgreMovableObject.h"
#include "OgreSceneNode.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		OgreShape::OgreShape(vtx::Resource* resource) 
			: vtx::Shape(resource), 
			mBoundingBox(dynamic_cast<vtx::ShapeResource*>(resource)->getBoundingBox()), 
			mUVs(0, 0, 1, 1), 
			mLayer(0.0f)
		{
			mRenderOp.vertexData = NULL;
			mRenderOp.indexData = NULL;

			mRenderOp.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST; 
			mRenderOp.useIndexes = true;

			_createGeometry();
		}
		//-----------------------------------------------------------------------
		OgreShape::~OgreShape()
		{
			delete mRenderOp.vertexData;
			delete mRenderOp.indexData;

			mRenderOp.vertexData = NULL;
			mRenderOp.indexData = NULL;
		}
		//-----------------------------------------------------------------------
		const Ogre::MaterialPtr& OgreShape::getMaterial() const
		{
			return mMaterial;
		}
		//-----------------------------------------------------------------------
		void OgreShape::getRenderOperation(Ogre::RenderOperation& op)
		{
			op = mRenderOp;
		}
		//-----------------------------------------------------------------------
		void OgreShape::getWorldTransforms(Ogre::Matrix4* xform) const
		{
			Ogre::MovableObject* movable = dynamic_cast<Ogre::MovableObject*>(mParentMovie);

			Ogre::Matrix4 ogre_mat = movable->_getParentNodeFullTransform();
			xform[0] = ogre_mat * mWorldMatrix;
		}
		//-----------------------------------------------------------------------
		const Ogre::Quaternion& OgreShape::getWorldOrientation() const
		{
			Ogre::MovableObject* movable = dynamic_cast<Ogre::MovableObject*>(mParentMovie);

			return movable->getParentSceneNode()->_getDerivedOrientation();
		}
		//-----------------------------------------------------------------------
		const Ogre::Vector3& OgreShape::getWorldPosition() const
		{
			Ogre::MovableObject* movable = dynamic_cast<Ogre::MovableObject*>(mParentMovie);

			return movable->getParentSceneNode()->_getDerivedPosition();
		}
		//-----------------------------------------------------------------------
		Ogre::Real OgreShape::getSquaredViewDepth(const Ogre::Camera* cam) const
		{
			Ogre::MovableObject* movable = dynamic_cast<Ogre::MovableObject*>(mParentMovie);

			return cam->getDerivedPosition().squaredDistance(movable->getParentNode()->_getDerivedPosition()) - mLayer;
		}
		//-----------------------------------------------------------------------
		const Ogre::LightList& OgreShape::getLights() const
		{
			Ogre::MovableObject* movable = dynamic_cast<Ogre::MovableObject*>(mParentMovie);

			return movable->queryLights();
		}
		//-----------------------------------------------------------------------
		void OgreShape::_update(const float& delta_time)
		{
			Shape::_update(delta_time);

			const Matrix& mat = getWorldMatrix();

			mWorldMatrix = Ogre::Matrix4(
				mat.m[0][0], -mat.m[0][1], 0,  mat.m[0][2], 
				-mat.m[1][0], mat.m[1][1], 0, -mat.m[1][2], 
				0,		  0,		   1,				0,
				0,		  0,		   0,				1);

			mMULcolor = Ogre::ColourValue(
				mTransform.getColor().mul_red, 
				mTransform.getColor().mul_green, 
				mTransform.getColor().mul_blue, 
				mTransform.getColor().mul_alpha);

			mADDcolor = Ogre::ColourValue(
				mTransform.getColor().add_red, 
				mTransform.getColor().add_green, 
				mTransform.getColor().add_blue, 
				mTransform.getColor().add_alpha);
		}
		//-----------------------------------------------------------------------
		void OgreShape::setAtlasQuad(const AtlasPacker::PackResult& quad)
		{
			mMaterial = dynamic_cast<OgreTexture*>(quad.texture)->getMaterial();
			mUVs = quad.node->getRect().relativeTo(Rect(0, 0, quad.texture->getSize(), quad.texture->getSize()));
			_updateGeometry();

			//std::cout << StringHelper::toString(quad.node->getRect()) << std::endl;
			//std::cout << quad.texture->getSize() << std::endl;
			//std::cout << mUVs.left << ", " << mUVs.top << ", " << mUVs.right << ", " << mUVs.bottom << std::endl;
		}
		//-----------------------------------------------------------------------
		//bool OgreShape::supportsAlpha() const
		//{
		//	return false;
		//}
		//-----------------------------------------------------------------------
		void OgreShape::_createGeometry()
		{
			mRenderOp.vertexData = new Ogre::VertexData;
			mRenderOp.indexData = new Ogre::IndexData;

			mRenderOp.vertexData->vertexStart = 0;
			mRenderOp.vertexData->vertexCount = 4;

			mRenderOp.indexData->indexStart = 0;
			mRenderOp.indexData->indexCount = 6;

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

			mBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
				mVertexDecl->getVertexSize(0), 
				mRenderOp.vertexData->vertexCount, 
				Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);

			mVertexBufferBind->setBinding(0, mBuffer);

			Ogre::HardwareIndexBufferSharedPtr ibuffer = Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
				Ogre::HardwareIndexBuffer::IT_16BIT, // type of index
				mRenderOp.indexData->indexCount, // number of indexes
				Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, // usage
				false); // no shadow buffer	

			unsigned short* index = static_cast<unsigned short*>(ibuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));

			*index++ = 0;
			*index++ = 1;
			*index++ = 2;

			*index++ = 0;
			*index++ = 2;
			*index++ = 3;

			ibuffer->unlock();

			mRenderOp.indexData->indexBuffer = ibuffer;
		}
		//-----------------------------------------------------------------------
		void OgreShape::_updateGeometry()
		{
			float* vertex = static_cast<float*>(mBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));

			//----------
			// TOP-LEFT
			//----------
			// position
			*vertex++ = mBoundingBox.getMinX();
			*vertex++ = -mBoundingBox.getMinY();
			*vertex++ = 0;

			// normal
			*vertex++ = 0;
			*vertex++ = 0;
			*vertex++ = -1;

			// diffuse
			*vertex++ = mMULcolor.r;
			*vertex++ = mMULcolor.g;
			*vertex++ = mMULcolor.b;
			*vertex++ = mMULcolor.a;

			// specular
			*vertex++ = mADDcolor.r;
			*vertex++ = mADDcolor.g;
			*vertex++ = mADDcolor.b;
			*vertex++ = mADDcolor.a;

			// texture coordinate
			*vertex++ = mUVs.left;
			*vertex++ = mUVs.top;

			//----------
			// BOTTOM-LEFT
			//----------
			// position
			*vertex++ = mBoundingBox.getMinX();
			*vertex++ = -mBoundingBox.getMaxY();
			*vertex++ = 0;

			// normal
			*vertex++ = 0;
			*vertex++ = 0;
			*vertex++ = -1;

			// diffuse
			*vertex++ = mMULcolor.r;
			*vertex++ = mMULcolor.g;
			*vertex++ = mMULcolor.b;
			*vertex++ = mMULcolor.a;

			// specular
			*vertex++ = mADDcolor.r;
			*vertex++ = mADDcolor.g;
			*vertex++ = mADDcolor.b;
			*vertex++ = mADDcolor.a;

			// texture coordinate
			*vertex++ = mUVs.left;
			*vertex++ = mUVs.bottom;

			//----------
			// BOTTOM-RIGHT
			//----------
			// position
			*vertex++ = mBoundingBox.getMaxX();
			*vertex++ = -mBoundingBox.getMaxY();
			*vertex++ = 0;

			// normal
			*vertex++ = 0;
			*vertex++ = 0;
			*vertex++ = -1;

			// diffuse
			*vertex++ = mMULcolor.r;
			*vertex++ = mMULcolor.g;
			*vertex++ = mMULcolor.b;
			*vertex++ = mMULcolor.a;

			// specular
			*vertex++ = mADDcolor.r;
			*vertex++ = mADDcolor.g;
			*vertex++ = mADDcolor.b;
			*vertex++ = mADDcolor.a;

			// texture coordinate
			*vertex++ = mUVs.right;
			*vertex++ = mUVs.bottom;

			//----------
			// TOP-RIGHT
			//----------
			// position
			*vertex++ = mBoundingBox.getMaxX();
			*vertex++ = -mBoundingBox.getMinY();
			*vertex++ = 0;

			// normal
			*vertex++ = 0;
			*vertex++ = 0;
			*vertex++ = -1;

			// diffuse
			*vertex++ = mMULcolor.r;
			*vertex++ = mMULcolor.g;
			*vertex++ = mMULcolor.b;
			*vertex++ = mMULcolor.a;

			// specular
			*vertex++ = mADDcolor.r;
			*vertex++ = mADDcolor.g;
			*vertex++ = mADDcolor.b;
			*vertex++ = mADDcolor.a;

			// texture coordinate
			*vertex++ = mUVs.right;
			*vertex++ = mUVs.top;

			mBuffer->unlock();
		}
		//-----------------------------------------------------------------------
	}
}
