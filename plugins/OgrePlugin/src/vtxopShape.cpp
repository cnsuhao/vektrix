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
		const Ogre::MaterialPtr& OgreShape::getMaterial(void) const
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
			//Ogre::Matrix4 vtx_mat;
			//vtx_mat
			//vtx_mat.makeTransform(mPosition, mSize * mScale, Ogre::Quaternion::IDENTITY);
			xform[0] = ogre_mat * mTransform;

			//Ogre::Vector3 node_pos = xform[0].getTrans();
			////Ogre::Quaternion rot = xform[0].extractQuaternion();
			////pos -= rot * Vector3(0, 0, mDepth);
			//xform[0].setTrans(node_pos + mPosition);
			//mat.extractQuaternion();
			//xform[0].setScale(mSize * mScale);
		}
		//-----------------------------------------------------------------------
		const Ogre::Quaternion& OgreShape::getWorldOrientation(void) const
		{
			Ogre::MovableObject* movable = dynamic_cast<Ogre::MovableObject*>(mParentMovie);

			return movable->getParentSceneNode()->_getDerivedOrientation();
		}
		//-----------------------------------------------------------------------
		const Ogre::Vector3& OgreShape::getWorldPosition(void) const
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
		const Ogre::LightList& OgreShape::getLights(void) const
		{
			Ogre::MovableObject* movable = dynamic_cast<Ogre::MovableObject*>(mParentMovie);

			return movable->queryLights();
		}
		//-----------------------------------------------------------------------
		//void OgreShape::setMatrix(const vtx::Matrix& m)
		//{
		//	mTransform = Ogre::Matrix4(
		//		m.sx, m.cx, 0,  m.tx, 
		//		m.cy, m.sy, 0, -m.ty, 
		//		0,    0,    1,     0,
		//		0,    0,    0,     1);
		//	//mPosition.x = m.tx;
		//	//mPosition.y = m.ty;
		//	//mPosition.z = 0;

		//	//mScale.x = m.sx;
		//	//mScale.y = m.sy;
		//	//mScale.z = 1;
		//}
		//-----------------------------------------------------------------------
		//void OgreShape::setCXForm(const vtx::CXForm& cx)
		//{
		//	mMULcolor = Ogre::ColourValue(cx.mul_red, cx.mul_green, cx.mul_blue, cx.mul_alpha);
		//	mADDcolor = Ogre::ColourValue(cx.add_red, cx.add_green, cx.add_blue, cx.add_alpha);
		//}
		//-----------------------------------------------------------------------
		void OgreShape::_update(const float& delta_time)
		{
			mTransform = Ogre::Matrix4(
				mMatrix.m[0][0], mMatrix.m[0][1], 0,  mMatrix.m[0][2], 
				mMatrix.m[1][0], mMatrix.m[1][1], 0, -mMatrix.m[1][2], 
				0,			  0,			   1,					0,
				0,			  0,			   0,					1);

			mMULcolor = Ogre::ColourValue(
				mCXForm.mul_red, 
				mCXForm.mul_green, 
				mCXForm.mul_blue, 
				mCXForm.mul_alpha);

			mADDcolor = Ogre::ColourValue(
				mCXForm.add_red, 
				mCXForm.add_green, 
				mCXForm.add_blue, 
				mCXForm.add_alpha);
		}
		//-----------------------------------------------------------------------
		BoundingBox& OgreShape::getWorldBoundingBox() const
		{
			static BoundingBox bb;
			return bb;
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
