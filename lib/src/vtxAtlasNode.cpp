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

#include "vtxAtlasNode.h"

#include "vtxRastarizer.h"
#include "vtxShapeResource.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	AtlasNode::AtlasNode(const Rect& rect, Texture* parent) 
		: mRect(rect), 
		mRotated(false), 
		mParent(parent), 
		mChild_1(NULL), 
		mChild_2(NULL), 
		mShape(NULL)
	{

	}
	//-----------------------------------------------------------------------
	AtlasNode::~AtlasNode()
	{
		delete mChild_1;
		delete mChild_2;

		mChild_1 = NULL;
		mChild_2 = NULL;
	}
	//-----------------------------------------------------------------------
	void AtlasNode::renderShape(Rasterizer* rasterizer)
	{
		if(mShape)
		{
			rasterizer->renderShapeToTexture(mParent, mShape, this);
		}

		if(mChild_1)
		{
			mChild_1->renderShape(rasterizer);
		}

		if(mChild_2)
		{
			mChild_2->renderShape(rasterizer);
		}
	}
	//-----------------------------------------------------------------------
	void AtlasNode::setShape(ShapeResource* shape)
	{
		mShape = shape;
	}
	//-----------------------------------------------------------------------
	const Rect& AtlasNode::getRect() const
	{
		return mRect;
	}
	//-----------------------------------------------------------------------
	AtlasNode::FitMode AtlasNode::fits(ShapeResource* shape)
	{
		// check if it fits normally
		if(shape->getMaximumWidth_PoT() <= mRect.w() && shape->getMaximumHeight_PoT() <= mRect.h())
		{
			return FITS_NORMAL;
		}

		// ...no? -> check if it fits when rotated
		if(shape->getMaximumWidth_PoT() <= mRect.h() && shape->getMaximumHeight_PoT() <= mRect.w())
		{
			return FITS_ROTATED;
		}

		// it doesn't fit either way
		return DOESNT_FIT;
	}
	//-----------------------------------------------------------------------
	AtlasNode::FitMode AtlasNode::fitsExactly(ShapeResource* shape)
	{
		// check if it fits normally
		if(shape->getMaximumWidth_PoT() == mRect.w() && shape->getMaximumHeight_PoT() == mRect.h())
		{
			return FITS_NORMAL;
		}

		// ...no? -> check if it fits when rotated
		if(shape->getMaximumWidth_PoT() == mRect.h() && shape->getMaximumHeight_PoT() == mRect.w())
		{
			return FITS_ROTATED;
		}

		// it doesn't fit either way
		return DOESNT_FIT;
	}
	//-----------------------------------------------------------------------
	AtlasNode* AtlasNode::insert(ShapeResource* shape)
	{
		uint shape_width_PoT = shape->getMaximumWidth_PoT();
		uint shape_height_PoT = shape->getMaximumHeight_PoT();

		// this is not a leaf (i.e. there are children)
		if(mChild_1 || mChild_2)
		{
			// try to insert into first child node
			AtlasNode* foundNode = mChild_1->insert(shape);

			if(foundNode)
			{
				// enough space here
				return foundNode;
			}

			// try to insert into second child node
			return mChild_2->insert(shape);
		}
		// this is a leaf (i.e. no children)
		else
		{
			// this node already contains an image
			if(mShape)
			{
				return NULL;
			}

			const FitMode fit_normal = fits(shape);

			// image is too big for this node
			if(fit_normal == DOESNT_FIT)
			{
				return NULL;
			}

			const FitMode fit_exactly = fitsExactly(shape);

			// image fits exactly into this node
			if(fit_exactly == FITS_NORMAL)
			{
				return this;
			}
			// image fits exactly into this node when rotated
			else if(fit_exactly == FITS_ROTATED)
			{
				mRotated = true;
				return this;
			}

			// image fits, but not exactly ---> create child nodes
			//child_1 = new Node;
			//child_2 = new Node;

			// split the node for the image
			if(fit_normal == FITS_NORMAL)
			{
				// decide which way to split
				uint dw = mRect.w() - shape_width_PoT;
				uint dh = mRect.h() - shape_height_PoT;

				// delta width is bigger --> split by width
				if(dw > dh)
				{
					mChild_1 = new AtlasNode(Rect(mRect.left, mRect.top, mRect.left+shape_width_PoT, mRect.bottom), mParent);
					mChild_2 = new AtlasNode(Rect(mRect.left+shape_width_PoT, mRect.top, mRect.right, mRect.bottom), mParent);
				}
				// delta height is bigger --> split by height
				else
				{
					mChild_1 = new AtlasNode(Rect(mRect.left, mRect.top, mRect.right, mRect.top+shape_height_PoT), mParent);
					mChild_2 = new AtlasNode(Rect(mRect.left, mRect.top+shape_height_PoT, mRect.right, mRect.bottom), mParent);
				}
			}
			// split the node for the rotated image
			else if(fit_normal == FITS_ROTATED)
			{
				// decide which way to split
				uint dw = mRect.w() - shape_height_PoT;
				uint dh = mRect.h() - shape_width_PoT;

				// delta width is bigger --> split by width
				if(dw > dh)
				{
					mChild_1 = new AtlasNode(Rect(mRect.left, mRect.top, mRect.left+shape_height_PoT, mRect.bottom), mParent);
					mChild_2 = new AtlasNode(Rect(mRect.left+shape_height_PoT, mRect.top, mRect.right, mRect.bottom), mParent);
				}
				// delta height is bigger --> split by height
				else
				{
					mChild_1 = new AtlasNode(Rect(mRect.left, mRect.top, mRect.right, mRect.top+shape_width_PoT), mParent);
					mChild_2 = new AtlasNode(Rect(mRect.left, mRect.top+shape_width_PoT, mRect.right, mRect.bottom), mParent);
				}
			}

			// insert into the first child that we created
			return mChild_1->insert(shape);
		}

		// texture is full ?!
		return NULL;
	}
	//-----------------------------------------------------------------------
}
