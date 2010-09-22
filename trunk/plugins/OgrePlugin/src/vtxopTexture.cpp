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
		OgreTexture::OgreTexture(uint size) 
			: Texture(size)
		{
			mTexture = Ogre::TextureManager::getSingletonPtr()->createManual(
				vtx::StringHelper::toString((int)this), 
				"General", 
				Ogre::TEX_TYPE_2D, 
				size, size, 5, 
				0, 
				Ogre::PF_A8R8G8B8, 
				Ogre::TU_DYNAMIC_WRITE_ONLY, 
				this);

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
					data[pitch*y + x] = 0x00000000;
				}
			}

			buffer->unlock();

			// create the ogre material
			mMaterial = Ogre::MaterialManager::getSingleton().create(vtx::StringHelper::toString((int)this), "General");
			Ogre::Pass* pass = mMaterial->getTechnique(0)->getPass(0);
			Ogre::TextureUnitState* texture_unit = pass->createTextureUnitState();

			// DEBUG
			//pass->setSelfIllumination(Ogre::ColourValue::White);
			// use (1, 1-src_alpha) blending for the pre-multiplied alpha images from cairo
			pass->setSceneBlending(Ogre::SBF_ONE, Ogre::SBF_ONE_MINUS_SOURCE_ALPHA);
			pass->setDepthWriteEnabled(false);
			pass->setVertexColourTracking(Ogre::TVC_AMBIENT);

			texture_unit->setTextureName(mTexture->getName());
			//texture_unit->setTextureFiltering(Ogre::TFO_NONE);

			pass->setCullingMode(Ogre::CULL_NONE);
		}
		//-----------------------------------------------------------------------
		OgreTexture::~OgreTexture()
		{
#ifdef _DEBUG
			debugOgreTexture();
#endif

			mTexture.setNull();
		}
		//-----------------------------------------------------------------------
		void OgreTexture::paintPixelsToRect(const Rect& coordinates, unsigned char* pixelData)
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

			buffer->blitFromMemory(image.getPixelBox(), box);
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
		const Ogre::MaterialPtr& OgreTexture::getMaterial() const
		{
			return mMaterial;
		}
		//-----------------------------------------------------------------------
		void OgreTexture::loadResource(Ogre::Resource* resource)
		{
			renderAllShapes();

			// DEBUG
			debugOgreTexture();
		}
		//-----------------------------------------------------------------------
	}
}
