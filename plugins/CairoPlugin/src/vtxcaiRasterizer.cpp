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

#include "vtxcaiRasterizer.h"

#include "vtxAtlasNode.h"
#include "vtxFile.h"
#include "vtxGlyphResource.h"
#include "vtxImageResource.h"
#include "vtxLogManager.h"
#include "vtxShapeResource.h"
#include "vtxSubshapeResource.h"
#include "vtxMaterialResource.h"
#include "vtxStringHelper.h"
#include "vtxTexture.h"

namespace vtx
{
	namespace cai
	{
		//-----------------------------------------------------------------------
		CairoRasterizer::CairoRasterizer()
		{

		}
		//-----------------------------------------------------------------------
		CairoRasterizer::~CairoRasterizer()
		{

		}
		//-----------------------------------------------------------------------
		const String& CairoRasterizer::getName() const
		{
			static String name = "Cairo";
			return name;
		}
		//-----------------------------------------------------------------------
		void CairoRasterizer::renderElementToTexture(Texture* texture, AtlasElement* element, AtlasNode* node)
		{
			GlyphResource* glyph = dynamic_cast<GlyphResource*>(element);
			if(glyph)
			{
				renderGlyph(texture, glyph, node);
				return;
			}

			ShapeResource* shape = dynamic_cast<ShapeResource*>(element);
			if(shape)
			{
				renderShape(texture, shape, node);
				return;
			}
		}
		//-----------------------------------------------------------------------
		void CairoRasterizer::renderGlyph(Texture* texture, GlyphResource* glyph, AtlasNode* node)
		{
			Rect rect = node->getRect();

			// pixel border to avoid texture bleeding
			rect.contract(1);

			// fire up cairo
			mSurface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, rect.w(), rect.h());
			mCairo = cairo_create(mSurface);
			cairo_set_fill_rule(mCairo, CAIRO_FILL_RULE_EVEN_ODD);

			Vector2 offset(-glyph->getBoundingBox().getMinX(), -glyph->getBoundingBox().getMinY());
			Vector2 scale(rect.w()/glyph->getBoundingBox().getWidth(), rect.h()/glyph->getBoundingBox().getHeight());

			Vector2 last_position = Vector2::ZERO;

			// start drawing
			const ShapeElementList& elements = glyph->getElementList();
			ShapeElementList::const_iterator elem_it = elements.begin();
			ShapeElementList::const_iterator elem_end = elements.end();

			// color RED
			cairo_set_source_rgba(mCairo, 1, 1, 1, 1);

			while(elem_it != elem_end)
			{
				const ShapeElement& element = *elem_it;

				if(element.type == ShapeElement::SID_MOVE_TO)
				{
					Vector2 pos = (element.pos + offset) * scale;

					if(elem_it != elements.begin())
					{
						cairo_new_sub_path(mCairo);
					}

					//VTX_LOG("%4.2f %4.2f", pos.x, pos.y);

					cairo_move_to(mCairo, pos.x, pos.y);
					last_position = pos;
				}
				else if(element.type == ShapeElement::SID_LINE_TO)
				{
					Vector2 pos = (element.pos + offset) * scale;

					//VTX_LOG("%4.2f %4.2f", pos.x, pos.y);

					cairo_line_to(mCairo, pos.x, pos.y);
					last_position = pos;
				}
				else if(element.type == ShapeElement::SID_CURVE_TO)
				{
					Vector2 pos = (element.pos + offset) * scale;
					Vector2 ctrl = (element.ctrl + offset) * scale;

					//VTX_LOG("%4.2f %4.2f", ctrl.x, ctrl.y);
					//VTX_LOG("%4.2f %4.2f", pos.x, pos.y);

					cairo_curve_to(mCairo, last_position.x, last_position.y, ctrl.x, ctrl.y, pos.x, pos.y);
					last_position = pos;
				}

				++elem_it;
			} // while(elements)

			cairo_close_path(mCairo);
			cairo_fill(mCairo);

			texture->paintPixelsToRect(rect, cairo_image_surface_get_data(mSurface));

			// send cairo to sleep
			cairo_destroy(mCairo);
			cairo_surface_destroy(mSurface);
		}
		//-----------------------------------------------------------------------
		void CairoRasterizer::renderShape(Texture* texture, ShapeResource* shape, AtlasNode* node)
		{
			Rect rect = node->getRect();

			// pixel border to avoid texture bleeding
			rect.contract(1);

			// fire up cairo
			mSurface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, rect.w(), rect.h());
			mCairo = cairo_create(mSurface);
			cairo_set_fill_rule(mCairo, CAIRO_FILL_RULE_EVEN_ODD);

			Vector2 offset(-shape->getBoundingBox().getMinX(), -shape->getBoundingBox().getMinY());
			Vector2 scale(rect.w()/shape->getWidth(), rect.h()/shape->getHeight());

			// start drawing
			const ShapeResource::SubshapeList& subshapes = shape->getSubshapeList();
			ShapeResource::SubshapeList::const_iterator subshape_it = subshapes.begin();
			ShapeResource::SubshapeList::const_iterator subshape_end = subshapes.end();

			while(subshape_it != subshape_end)
			{
				SubshapeResource* subshape = (*subshape_it);
				MaterialResource* material = subshape->getMaterial();

				cairo_pattern_t* cairo_pattern = NULL;

				switch(material->getMaterialType())
				{
				case MaterialResource::MT_COLOR:
					{
						const Color& color = material->getColor();
						cairo_set_source_rgba(mCairo, (double)color.r, (double)color.g, (double)color.b, (double)color.a);
					}
					break;

				case MaterialResource::MT_IMAGE:
					{
						ImageResource* img = dynamic_cast<ImageResource*>(shape->getFile()->getResource(material->getImageID()));
						cairo_surface_t* cairo_surf = cairo_image_surface_create_for_data((uchar*)img->getPixelData(), 
							CAIRO_FORMAT_ARGB32, img->getWidth(), img->getHeight(), 
							4 * img->getWidth());

						cairo_pattern = cairo_pattern_create_for_surface(cairo_surf);
						cairo_pattern_set_extend(cairo_pattern, CAIRO_EXTEND_NONE);

						cairo_matrix_t matrix;
						cairo_matrix_init_scale(&matrix, 1.0f/scale.x, 1.0f/scale.y);
						cairo_pattern_set_matrix(cairo_pattern, &matrix);
						cairo_set_source(mCairo, cairo_pattern);
					}
					break;

				case MaterialResource::MT_LINEAR_GRADIENT:
					{
						const MaterialResource::GradientMap& gradient = material->getGradientMap();
						MaterialResource::GradientMap::const_iterator grd_it = gradient.begin();
						MaterialResource::GradientMap::const_iterator grd_end = gradient.end();

						Matrix matrix = material->getTransformMatrix();

#define WORK_ARROUND
#ifdef WORK_ARROUND
						Vector2 x1(-819.2f, 0);
						Vector2 x2(819.2f, 0);

						Vector2 unit_scale = scale;
						unit_scale.normalize();

						//matrix.m[0][0] = matrix.m[0][0] * unit_scale.x;
						matrix.m[0][1] = matrix.m[0][1] * unit_scale.y;
						//matrix.m[0][2] = matrix.m[0][2] * unit_scale.x;

						matrix.m[1][0] = matrix.m[1][0] * unit_scale.x;
						//matrix.m[1][1] = matrix.m[1][1] * unit_scale.y;
						//matrix.m[1][2] = matrix.m[1][2] * unit_scale.y;

						x1 = matrix.transformAffine(x1);
						x2 = matrix.transformAffine(x2);

						// TODO: fix scaling
						x1 = (x1 + offset) * scale;
						x2 = (x2 + offset) * scale;

						cairo_pattern = cairo_pattern_create_linear(
							x1.x, 
							x1.y, 
							x2.x, 
							x2.y);
#else
						cairo_pattern = cairo_pattern_create_linear(
							(-50 + offset.x) * scale.x, 
							(-50 + offset.y) * scale.y, 
							(+150 + offset.x) * scale.x, 
							(-50 + offset.y) * scale.y);

						//Matrix scale_mat(
						//	1.0f/256.0f, 0, 0, 
						//	0, 1.0f/256.0f, 0);

						//float angle = 0;
						//Matrix rot_mat(
						//	cos(angle), sin(angle), 0, 
						//	-sin(angle), cos(angle), 0);

						//Matrix trans_mat(
						//	1, 0, -128.0f, 
						//	0, 1, 128);

						//cairo_matrix_t cr_mat;
						//cairo_matrix_t cr_scale_mat = convertMatrix(scale_mat);
						//cairo_matrix_t cr_rot_mat = convertMatrix(rot_mat);
						//cairo_matrix_t cr_trans_mat = convertMatrix(trans_mat);

						//cairo_matrix_multiply(&cr_mat, &cr_trans_mat, &cr_scale_mat);
						//cairo_matrix_multiply(&cr_mat, &cr_mat, &cr_rot_mat);

						//cairo_pattern_set_matrix(cairo_pattern, &cr_mat);
#endif

						while(grd_it != grd_end)
						{
							cairo_pattern_add_color_stop_rgba(cairo_pattern, 
								(float)grd_it->first/255.0f, 
								grd_it->second.r, 
								grd_it->second.g, 
								grd_it->second.b, 
								grd_it->second.a);
							++grd_it;
						}

						cairo_set_source(mCairo, cairo_pattern);
					}
					break;

				default:
					VTX_WARN("Unimplemented Material Type");
					break;
				}

				Vector2 last_position = Vector2::ZERO;

				const ShapeElementList& elements = subshape->getElementList();
				ShapeElementList::const_iterator element_it = elements.begin();
				ShapeElementList::const_iterator element_end = elements.end();
				while(element_it != element_end)
				{
					const ShapeElement& element = *element_it;

					if(element.type == ShapeElement::SID_MOVE_TO)
					{
						Vector2 pos = (element.pos + offset) * scale;

						if(element_it != elements.begin())
						{
							cairo_new_sub_path(mCairo);
						}

						cairo_move_to(mCairo, pos.x, pos.y);
						last_position = pos;
					}
					else if(element.type == ShapeElement::SID_LINE_TO)
					{
						Vector2 pos = (element.pos + offset) * scale;

						cairo_line_to(mCairo, pos.x, pos.y);
						last_position = pos;
					}
					else if(element.type == ShapeElement::SID_CURVE_TO)
					{
						Vector2 pos = (element.pos + offset) * scale;
						Vector2 ctrl = (element.ctrl + offset) * scale;

						cairo_curve_to(mCairo, last_position.x, last_position.y, ctrl.x, ctrl.y, pos.x, pos.y);
						last_position = pos;
					}

					++element_it;

				} // elements

				cairo_close_path(mCairo);
				cairo_fill(mCairo);

				if(cairo_pattern)
				{
					cairo_pattern_destroy(cairo_pattern);
					cairo_pattern = NULL;
				}


				++subshape_it;

			} // subshapes

			texture->paintPixelsToRect(rect, cairo_image_surface_get_data(mSurface));

			// send cairo to sleep
			cairo_destroy(mCairo);
			cairo_surface_destroy(mSurface);
		}
		//-----------------------------------------------------------------------
		cairo_matrix_t CairoRasterizer::convertMatrix(const Matrix& matrix)
		{
			cairo_matrix_t result;

			result.xx = matrix.m[0][0];
			result.xy = matrix.m[0][1];
			result.x0 = matrix.m[0][2];

			result.yx = matrix.m[1][0];
			result.yy = matrix.m[1][1];
			result.y0 = matrix.m[1][2];

			return result;
		}
		//-----------------------------------------------------------------------
	}
}
