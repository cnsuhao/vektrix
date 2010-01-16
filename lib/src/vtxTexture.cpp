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
#include "vtxShapeResource.h"
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
	AtlasNode* Texture::packShape(ShapeResource* shape)
	{
		if(shape->getMaximumWidth_PoT() > mSize || shape->getMaximumHeight_PoT() > mSize)
		{
			VTX_EXCEPT("The shape with the id '%s' exceeds the maximum atlas size of '%u'", shape->getID().c_str(), mSize);
			return NULL;
		}

		VTX_LOG("Trying to pack shape with dimensions [%4.2f , %4.2f / %u , %u] ...", 
			shape->getMaximumWidth(), shape->getMaximumHeight(), 
			shape->getMaximumWidth_PoT(), shape->getMaximumHeight_PoT());

		AtlasNode* node = mRoot->insert(shape);

		if(node)
		{
			node->setShape(shape);
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
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	DefaultTexture::DefaultTexture(uint size) 
		: Texture(size)
	{

	}
	//-----------------------------------------------------------------------
	void DefaultTexture::paintPixelsToRect(const Rect& coordinates, unsigned char* pixelData)
	{
		VTX_EXCEPT("Unimplemented DefaultTexture::paintPixelsToRect");
	}
	//-----------------------------------------------------------------------
}
