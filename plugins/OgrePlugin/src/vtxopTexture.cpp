/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/vektrix

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
#include "vtxopTexture.h"

#include "vtxLogManager.h"
#include "vtxRect.h"
#include "vtxStringHelper.h"

#include "OgreHardwarePixelBuffer.h"
#include "OgreImage.h"
#include "OgreMaterialManager.h"
#include "OgrePass.h"
#include "OgreRenderTexture.h"
#include "OgreTechnique.h"
#include "OgreTextureManager.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		OgreTexture::OgreTexture(size_t size) 
			: Texture(size)
		{
			mTexture = Ogre::TextureManager::getSingletonPtr()->createManual(
				vtx::StringHelper::toString((int)this), 
				"General", 
				Ogre::TEX_TYPE_2D, 
				size, size, 1, 
				0, 
				Ogre::PF_A8R8G8B8, 
				Ogre::TU_DYNAMIC_WRITE_ONLY);

			Ogre::HardwarePixelBufferSharedPtr buffer = mTexture->getBuffer();

			buffer->lock(Ogre::HardwarePixelBuffer::HBL_NORMAL);

			const Ogre::PixelBox& pixelBox = buffer->getCurrentLock();

			size_t* data = static_cast<size_t*>(pixelBox.data);

			size_t height = pixelBox.getHeight();
			size_t width = pixelBox.getWidth();
			size_t pitch = pixelBox.rowPitch; // Skip between rows of image

			for(size_t y=0; y<height; ++y)
			{
				for(size_t x=0; x<width; ++x)
				{
					// 0xRRGGBB -> fill the buffer with yellow pixels
					//data[pitch*y + x] = 0xFFFF8800;
					data[pitch*y + x] = 0x00000000;
				}
			}

			buffer->unlock();

			// create the ogre material
			mMaterial = Ogre::MaterialManager::getSingleton().create(vtx::StringHelper::toString((int)this), "General");
			Ogre::Pass* pass = mMaterial->getTechnique(0)->getPass(0);
			Ogre::TextureUnitState* texture_unit = pass->createTextureUnitState();

			// DEBUG
			pass->setSelfIllumination(Ogre::ColourValue::White);
			//pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
			// use (1, 1-src_alpha) blending for the pre-multiplied alpha images from cairo
			pass->setSceneBlending(Ogre::SBF_ONE, Ogre::SBF_ONE_MINUS_SOURCE_ALPHA);
			pass->setDepthWriteEnabled(false);
			//pass->setCullingMode(Ogre::CULL_NONE);

			texture_unit->setTextureName(mTexture->getName());
		}
		//-----------------------------------------------------------------------
		OgreTexture::~OgreTexture()
		{
			Ogre::TextureManager::getSingletonPtr()->remove(static_cast<Ogre::ResourcePtr>(mTexture));
		}
		//-----------------------------------------------------------------------
		void OgreTexture::paintPixelsToRect(const vtx::Rect& coordinates, unsigned char* pixelData)
		{
			Ogre::HardwarePixelBufferSharedPtr buffer = mTexture->getBuffer();

			Ogre::Image image;
			image.loadDynamicImage(pixelData, coordinates.w(), coordinates.h(), 1, Ogre::PF_BYTE_BGRA);

			Ogre::Box box;
			box.left = coordinates.left;
			box.top = coordinates.top;
			box.right = coordinates.right;
			box.bottom = coordinates.bottom;
			box.front = 0;
			box.back = 1;

			vtx::VTX_LOG("PaintPixelsToRect: min: %u %u max: %u %u", coordinates.left, coordinates.top, coordinates.right, coordinates.bottom);

			buffer->blitFromMemory(image.getPixelBox(), box);

			// DEBUG
			//debugOgreTexture();

			//vtx::VTX_LOG("NUM MIPMAPS: %u", mTexture->getNumMipmaps());
		}
		//-----------------------------------------------------------------------
		void OgreTexture::debugOgreTexture()
		{
			Ogre::HardwarePixelBufferSharedPtr buffer = mTexture->getBuffer();

			buffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY);
			const Ogre::PixelBox& pixelBox = buffer->getCurrentLock();

			// Load Image and then save to file
			Ogre::Image image;
			image.loadDynamicImage(static_cast<unsigned char*>(pixelBox.data),
				mTexture->getWidth(), mTexture->getHeight(),
				mTexture->getDepth(), mTexture->getFormat(),false,1,0);

			image.save("blit.png");

			buffer->unlock();
		}
		//-----------------------------------------------------------------------
		const Ogre::MaterialPtr& OgreTexture::getMaterial(void) const
		{
			return mMaterial;
		}
		//-----------------------------------------------------------------------
	}
}
