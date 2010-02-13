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

#include "vtxopMovableEditText.h"
#include "vtxopMovableMovie.h"
#include "vtxopTexture.h"

#include "vtxAtlasNode.h"
#include "vtxFile.h"
#include "vtxFontResource.h"
#include "vtxGlyphResource.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		OgreMovableEditText::OgreMovableEditText(vtx::Resource* resource) 
			: EditText(resource)
		{
			_createBuffers();
		}
		//-----------------------------------------------------------------------
		OgreMovableEditText::~OgreMovableEditText()
		{

		}
		//-----------------------------------------------------------------------
		void OgreMovableEditText::_setParent(Movie* parent)
		{
			EditText::_setParent(parent);

			mParentMovable = dynamic_cast<MovableMovie*>(parent);
		}
		//-----------------------------------------------------------------------
		void OgreMovableEditText::_update(const float& delta_time)
		{
			EditText::_update(delta_time);

			const Matrix& mat = getWorldMatrix();

			mWorldMatrix = Ogre::Matrix4(
				mat.m[0][0], -mat.m[0][1], 0,  mat.m[0][2], 
				-mat.m[1][0], mat.m[1][1], 0, -mat.m[1][2], 
				0,		  0,		   1,				0,
				0,		  0,		   0,				1);
		}
		//-----------------------------------------------------------------------
		void OgreMovableEditText::setAtlasList(const AtlasPacker::PackResultList& atlas_list)
		{
			mAtlasList = atlas_list;
		}
		//-----------------------------------------------------------------------
		void OgreMovableEditText::_updateGraphics()
		{
			_resizeBuffers(mGlyphCount);

			File* file = mResource->getFile();
			OgreTexture* texture = NULL;

			StaticTextResource::GlyphList::const_iterator glyph_it;
			StaticTextResource::GlyphList::const_iterator glyph_end;

			// update the buffer
			_lock();

			// x-Position of glyphs
			float glyph_x = 0.0f;

			// iterate GlyphStrips
			StaticTextResource::GlyphStripList::const_iterator it = mGlyphStrips.begin();
			StaticTextResource::GlyphStripList::const_iterator end = mGlyphStrips.end();
			while(it != end)
			{
				const StaticTextResource::GlyphStrip& glyph_strip = *it;
				FontResource* font = dynamic_cast<FontResource*>(file->getResource(glyph_strip.fontid));

				// jump to a new line
				if(glyph_strip.newline)
				{
					glyph_x = 0.0f;
				}

				glyph_x += glyph_strip.x;

				if(font)
				{
					glyph_it = glyph_strip.glyphs.begin();
					glyph_end = glyph_strip.glyphs.end();

					// iterate individual Glyphs
					while(glyph_it != glyph_end)
					{
						const StaticTextResource::Glyph& glyph = *glyph_it;

						GlyphResource* glyph_res = font->getGlyphByIndex(glyph.index);
						if(glyph_res)
						{
							AtlasPacker::PackResultList::const_iterator atlas_it = mAtlasList.find(glyph_res->getPackID());
							if(atlas_it != mAtlasList.end())
							{
								const AtlasPacker::PackResult& atlas_quad = atlas_it->second;

								if(!texture)
								{
									texture = dynamic_cast<OgreTexture*>(atlas_quad.texture);
								}

								const float size = glyph_strip.size * 0.05f;
								const BoundingBox& bb = glyph_res->getBoundingBox();
								const RectF& uv_rect = atlas_quad.node->getRect().relativeTo(
									atlas_quad.texture->getSize(), atlas_quad.texture->getSize());

								const RectF pos_rect(
									bb.getMinX() * size + glyph_x, // left
									-bb.getMinY() * size - glyph_strip.y - mMaxSize, // top
									bb.getMaxX() * size + glyph_x, // right
									-bb.getMaxY() * size - glyph_strip.y - mMaxSize // bottom
									);

								// TOP-LEFT
								_addVertex(
									Vector2(pos_rect.left, pos_rect.top), 
									Vector2(uv_rect.left, uv_rect.top), 
									glyph_strip.color, glyph_strip.color);

								// BOTTOM-LEFT
								_addVertex(
									Vector2(pos_rect.left, pos_rect.bottom), 
									Vector2(uv_rect.left, uv_rect.bottom), 
									glyph_strip.color, glyph_strip.color);

								// BOTTOM-RIGHT
								_addVertex(
									Vector2(pos_rect.right, pos_rect.bottom), 
									Vector2(uv_rect.right, uv_rect.bottom), 
									glyph_strip.color, glyph_strip.color);

								// TOP-RIGHT
								_addVertex(
									Vector2(pos_rect.right, pos_rect.top), 
									Vector2(uv_rect.right, uv_rect.top), 
									glyph_strip.color, glyph_strip.color);

							} // if(atlas_list_result)

						} // if(glyph_res)

						glyph_x += glyph.x;

						++glyph_it;

					} // while(glyphs)

				} // if(font)

				++it;

			} // while(glyph_strips)

			_unlock();

			if(texture)
			{
				mMaterial = texture->getMaterial();
			}
			//mMaterial = Ogre::MaterialManager::getSingletonPtr()->getByName("BaseWhiteNoLighting");
		}
		//-----------------------------------------------------------------------
	}
}
