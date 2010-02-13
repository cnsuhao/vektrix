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
#include "vtxAtlasPackable.h"
#include "vtxRasterizerManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	Texture::Texture(uint size) 
		: mSize(size), 
		mRoot(NULL)
	{
		mRoot = new AtlasNode(Rect(0, 0, size, size), this);
	}
	//-----------------------------------------------------------------------
	Texture::~Texture()
	{
		delete mRoot;
	}
	//-----------------------------------------------------------------------
	AtlasNode* Texture::packShape(AtlasPackable* element)
	{
		if(element->getPackableWidth() > mSize || element->getPackableHeight() > mSize)
		{
			VTX_EXCEPT("An AtlasPackable exceeds the maximum atlas size of '%u'", mSize);
			return NULL;
		}

		VTX_LOG("Trying to pack AtlasPackable with dimensions [%u , %u] ...", 
			element->getPackableWidth(), element->getPackableHeight());

		AtlasNode* node = mRoot->insert(element);

		if(node)
		{
			node->setShape(element);
			return node;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	void Texture::clear()
	{
		delete mRoot;
		mRoot = new AtlasNode(Rect(0, 0, mSize, mSize), this);
	}
	//-----------------------------------------------------------------------
	void Texture::renderAllShapes()
	{
		// TODO: implement dynamic rasterizer assignment
		Rasterizer* rst = RasterizerManager::getSingletonPtr()->getRasterizer("Cairo");
		mRoot->renderShape(rst);
	}
	//-----------------------------------------------------------------------
	const uint& Texture::getSize() const
	{
		return mSize;
	}
	//-----------------------------------------------------------------------
	uint Texture::getPackedSize()
	{
		return mRoot->getPackedSize();
	}
	//-----------------------------------------------------------------------
}
