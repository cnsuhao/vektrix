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
#include "vtxAtlasRastarizer.h"

#include "vtxAtlasNode.h"
#include "vtxRoot.h"
#include "vtxTexture.h"
#include "vtxMaterialResource.h"
#include "vtxShapeResource.h"
#include "vtxStringHelper.h"
#include "vtxSubshapeResource.h"
#include "vtxTextureFactory.h"

//#define _USE_MATH_DEFINES
//#include <cmath>

namespace vtx
{
	//-----------------------------------------------------------------------
	template<> AtlasRasterizer* Singleton<AtlasRasterizer>::sInstance = 0;
	//-----------------------------------------------------------------------
	AtlasRasterizer::AtlasRasterizer() 
		: mData(NULL)
	{
	}
	//-----------------------------------------------------------------------
	void AtlasRasterizer::renderShapeToTexture(Texture* texture, ShapeResource* shape, AtlasNode* node)
	{
		const Rect& rect = node->getRect();

		VTX_LOG("Rect: %d %d, %d %d", rect.left, rect.top, rect.right, rect.bottom);

		// fire up cairo
		//VTX_LOG("cairo_image_surface_create(CAIRO_FORMAT_ARGB32, %d, %d);", rect.w(), rect.h());
		mSurface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, rect.w(), rect.h());
		mCairo = cairo_create(mSurface);
		cairo_set_fill_rule(mCairo, CAIRO_FILL_RULE_EVEN_ODD);

		// start drawing
		const ShapeResource::SubshapeList& subshapes = shape->getSubshapeList();
		ShapeResource::SubshapeList::const_iterator subshape_it = subshapes.begin();

		Vector2 offset(-shape->getBoundingBox().getMinX(), -shape->getBoundingBox().getMinY());
		Vector2 scale(rect.w()/shape->getWidth(), rect.h()/shape->getHeight());

		for( ; subshape_it != subshapes.end(); ++subshape_it)
		{
			SubshapeResource* subshape = (*subshape_it);
			MaterialResource* material = subshape->getMaterial();

			const SubshapeResource::ShapeElement::List& elements = subshape->getElementList();
			SubshapeResource::ShapeElement::List::const_iterator element_it = elements.begin();

			if(material->getMaterialType() == MaterialResource::MT_COLOR)
			{
				const Color& color = material->getColor();

				// DEBUG
				//VTX_LOG("cairo_set_source_rgba(%s);", StringHelper::toString(color).c_str());
				cairo_set_source_rgba(mCairo, (double)color.r, (double)color.g, (double)color.b, (double)color.a);
			}
			else if(material->getMaterialType() == MaterialResource::MT_GRADIENT)
			{
				VTX_EXCEPT("UNIMPLEMENTED");
			}
			else if(material->getMaterialType() == MaterialResource::MT_IMAGE)
			{
				VTX_EXCEPT("UNIMPLEMENTED");
			}
			else
			{
				VTX_EXCEPT("Unknown material type.");
			}

			Vector2 last_position = Vector2::ZERO;

			for( ; element_it != elements.end(); ++element_it)
			{
				const SubshapeResource::ShapeElement& element = *element_it;

				if(element.type == SubshapeResource::ShapeElement::SID_MOVE_TO)
				{
					Vector2 pos = (element.pos.yInversedCopy() + offset) * scale;

					if(element_it != elements.begin())
					{
						//VTX_LOG("cairo_new_sub_path();");
						cairo_new_sub_path(mCairo);
					}

					// DEBUG
					//VTX_LOG("cairo_move_to(%4.2f, %4.2f);", pos.x, pos.y);
					cairo_move_to(mCairo, pos.x, pos.y);
					last_position = pos;
				}
				else if(element.type == SubshapeResource::ShapeElement::SID_LINE_TO)
				{
					Vector2 pos = (element.pos.yInversedCopy() + offset) * scale;

					// DEBUG
					//VTX_LOG("cairo_line_to(%4.2f, %4.2f);", pos.x, pos.y);
					cairo_line_to(mCairo, pos.x, pos.y);
					last_position = pos;
				}
				else if(element.type == SubshapeResource::ShapeElement::SID_CURVE_TO)
				{
					Vector2 pos = (element.pos.yInversedCopy() + offset) * scale;
					Vector2 ctrl = (element.ctrl.yInversedCopy() + offset) * scale;

					// DEBUG
					//VTX_LOG("cairo_curve_to(%4.2f, %4.2f, %4.2f, %4.2f, %4.2f, %4.2f);", last_position.x, last_position.y, ctrl.x, ctrl.y, pos.x, pos.y);
					cairo_curve_to(mCairo, last_position.x, last_position.y, ctrl.x, ctrl.y, pos.x, pos.y);
					last_position = pos;
				}
			} // elements

			// DEBUG
			//VTX_LOG("cairo_close_path();");
			//VTX_LOG("cairo_fill();");
			cairo_close_path(mCairo);
			cairo_fill(mCairo);

		} // subshapes

		VTX_LOG("Cairo status: %s", cairo_status_to_string(cairo_status(mCairo)));
		VTX_LOG("Surface status: %s", cairo_status_to_string(cairo_surface_status(mSurface)));

		// DEBUG
		//VTX_LOG("BLITTING...");
		texture->paintPixelsToRect(node->getRect(), cairo_image_surface_get_data(mSurface));

		// send cairo to sleep
		cairo_destroy(mCairo);
		cairo_surface_destroy(mSurface);
	}
	//-----------------------------------------------------------------------
}
