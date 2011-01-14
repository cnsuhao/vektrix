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

#include "vtxTexture.h"

#include "vtxAtlasNode.h"
#include "vtxLogManager.h"
#include "vtxRect.h"
#include "vtxAtlasElement.h"
#include "vtxRasterizerManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	Texture::Texture(const uint& width, const uint& height)
		: mWidth(width), 
		mHeight(height), 
		mRoot(NULL)
	{
		mRoot = new AtlasNode(Rect(0, 0, width, height), this);
	}
	//-----------------------------------------------------------------------
	Texture::~Texture()
	{
		delete mRoot;
	}
	//-----------------------------------------------------------------------
	AtlasNode* Texture::packElement(AtlasElement* element)
	{
		if(element->getPackableWidth() > mWidth || element->getPackableHeight() > mHeight)
		{
			VTX_EXCEPT("An AtlasPackable exceeds the maximum atlas size of '%u x %u'", mWidth, mHeight);
			return NULL;
		}

		AtlasNode* node = mRoot->insert(element);

		if(node)
		{
			node->setElement(element);
			return node;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	void Texture::clear()
	{
		delete mRoot;
		mRoot = new AtlasNode(Rect(0, 0, mWidth, mHeight), this);
	}
	//-----------------------------------------------------------------------
	void Texture::renderAllShapes()
	{
		// TODO: implement dynamic rasterizer assignment
		Rasterizer* rst = RasterizerManager::getSingletonPtr()->getRasterizer("Cairo");

		if(rst)
			mRoot->renderElement(rst);
	}
	//-----------------------------------------------------------------------
	const uint& Texture::getWidth() const
	{
		return mWidth;
	}
	//-----------------------------------------------------------------------
	const uint& Texture::getHeight() const
	{
		return mHeight;
	}
	//-----------------------------------------------------------------------
	uint Texture::getPackedSize()
	{
		return mRoot->getPackedSize();
	}
	//-----------------------------------------------------------------------
}
