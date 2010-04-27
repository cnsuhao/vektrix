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

#include "vtxopMovableStaticText.h"
#include "vtxopMovableMovie.h"
#include "vtxopTexture.h"

#include "vtxAtlasNode.h"
#include "vtxAtlasPacker.h"
#include "vtxFile.h"
#include "vtxFontResource.h"
#include "vtxGlyphResource.h"
#include "vtxTexture.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		OgreMovableStaticText::OgreMovableStaticText(vtx::Resource* resource) 
			: StaticText(resource), 
			MovableInstanceBase(this)
		{
			_createBuffers();
		}
		//-----------------------------------------------------------------------
		OgreMovableStaticText::~OgreMovableStaticText()
		{

		}
		//-----------------------------------------------------------------------
		void OgreMovableStaticText::_setParent(Movie* parent)
		{
			StaticText::_setParent(parent);

			mParentMovable = dynamic_cast<MovableMovie*>(parent);
		}
		//-----------------------------------------------------------------------
		void OgreMovableStaticText::_update(const float& delta_time)
		{
			StaticText::_update(delta_time);

			const Matrix& mat = getWorldMatrix();

			mWorldMatrix = Ogre::Matrix4(
				mat.m[0][0], -mat.m[0][1], 0,  mat.m[0][2], 
				-mat.m[1][0], mat.m[1][1], 0, -mat.m[1][2], 
				0,		  0,		   1,				0,
				0,		  0,		   0,				1);
		}
		//-----------------------------------------------------------------------
		void OgreMovableStaticText::setGlyphStrips(const GlyphStripList& glyph_strips, 
			const AtlasPacker::PackResultList& atlas_list)
		{
			uint glyph_count = 0;
			GlyphStripList::const_iterator it = glyph_strips.begin();
			GlyphStripList::const_iterator end = glyph_strips.end();
			while(it != end)
			{
				glyph_count += (*it).glyphs.size();
				++it;
			}

			_resizeBuffers(glyph_count);

			File* file = mResource->getFile();
			OgreTexture* texture = NULL;

			GlyphStrip::GlyphList::const_iterator glyph_it;
			GlyphStrip::GlyphList::const_iterator glyph_end;

			// update the buffer
			_lock();

			// x-Position of glyphs
			float glyph_x = 0.0f;

			// iterate GlyphStrips
			it = glyph_strips.begin();
			end = glyph_strips.end();
			while(it != end)
			{
				const GlyphStrip& glyph_strip = *it;
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

					// iterate Glyphs
					while(glyph_it != glyph_end)
					{
						const GlyphStrip::Glyph& glyph = *glyph_it;

						GlyphResource* glyph_res = font->getGlyphByIndex(glyph.index);
						if(glyph_res)
						{
							AtlasPacker::PackResultList::const_iterator atlas_it = atlas_list.find(glyph_res->getPackID());
							if(atlas_it != atlas_list.end())
							{
								const AtlasPacker::PackResult& atlas_quad = atlas_it->second;

								if(!texture)
								{
									texture = dynamic_cast<OgreTexture*>(atlas_quad.texture);
								}

								const float size = glyph_strip.size * 0.05f;
								const BoundingBox& bb = glyph_res->getBoundingBox();
								const RectF& uv_rect = atlas_quad.node->getRect().contractedCopy(1).relativeTo(
									atlas_quad.texture->getSize(), atlas_quad.texture->getSize());

								const RectF pos_rect(
									bb.getMinX() * size + glyph_x, // left
									-bb.getMinY() * size - glyph_strip.y, // top
									bb.getMaxX() * size + glyph_x, // right
									-bb.getMaxY() * size - glyph_strip.y // bottom
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

						glyph_x += glyph.x_advance;

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
		}
		//-----------------------------------------------------------------------
	}
}
