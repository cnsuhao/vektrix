/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/vektrix

Copyright (c) 2009 Fuse-Software (tm)

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/gpl.txt.
-----------------------------------------------------------------------------
*/
#pragma once

#include "vtxPrerequesites.h"

#include "vtxswfStdHeader.h"
#include "vtxswfContourElement.h"
#include "vtxswfSubShape.h"
#include "vtxswfSubLine.h"
#include "vtxSubshapeResource.h"

namespace vtx
{
	namespace swf
	{
		class ShapeHandler
		{
		public:
			typedef std::map<unsigned int, ContourElementList> ContourChunkMap;

			ShapeHandler();
			virtual ~ShapeHandler();

			void handleShape(TAG* swfTag, File* file);

			static void debug_element(const ContourElement& element, FILE* file);

		protected:
			size_t mFlashID;
			File* mCurrentFile;
			ShapeResource* mShapeResource;

			// the lists
			ContourChunkMap mChunks;
			FillstyleList mFillstyleList; // the USED! fillstyles
			LinestyleList mLinestyleList; // the USED! linestyles
			SubShapeList mSubShapeList; // the sub-shapes
			SubLineList mSubLineList; // the sub-lines

			// preprocessing
			void get_flash_styles(const SHAPE2& shape); // process the flash fill- and linestyles

			void get_flash_chunks(const SHAPE2& shape); // get the flash elements from swftools

			void debug_shape_element(const SubshapeResource::ShapeElement& element, FILE* file);

			void generate_subshapes(); // generate the final subshapes
			void generate_sublines(); // generate the final sublines

			// writing
			void write_fillstyles();
			void write_subshapes();
		};
	}
}
