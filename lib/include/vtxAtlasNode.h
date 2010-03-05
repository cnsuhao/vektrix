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

#ifndef __vtxAtlasNode_H__
#define __vtxAtlasNode_H__

#include "vtxPrerequesites.h"
#include "vtxRect.h"

namespace vtx
{
	/** A node of the space partitioning tree that is beeing created during the packing of an atlas */
	class vtxExport AtlasNode
	{
	public:

		enum FitMode
		{
			DOESNT_FIT = 0, 
			FITS_NORMAL, 
			FITS_ROTATED
		};

		AtlasNode(const Rect& rect, Texture* parent);
		virtual ~AtlasNode();

		/** Tells the element(s) associated with this node to render their contents to the atlas */
		void renderElement(Rasterizer* rasterizer);
		/** Set the element, that shall be associated with this node */
		void setElement(AtlasElement* element);
		/** Get the rectangle that this node occupies */
		const Rect& getRect() const;

		/** Get the size in pixel of the rectangle that this node occupies */
		uint getPackedSize();

		/** Check if the given element fits into one of the leafs of this node */
		FitMode fits(AtlasElement* element);
		/** Check if the given element fits into one of the leafs of this node, without needing to create new sub-nodes */
		FitMode fitsExactly(AtlasElement* element);

		/** Insert the given element into the sub-tree of this node */
		AtlasNode* insert(AtlasElement* element);

	protected:
		Rect mRect;
		bool mRotated;

		Texture* mParent;
		AtlasNode* mChild_1;
		AtlasNode* mChild_2;
		AtlasElement* mElement;
	};
}

#endif
