/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/vektrix

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
#include "vtxTexture.h"

#include "vtxAtlasNode.h"
#include "vtxLogManager.h"
#include "vtxRect.h"
#include "vtxShapeResource.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	Texture::Texture(uint size) 
		: mSize(size), 
		mRoot(new AtlasNode(Rect(0, 0, size, size), this))
	{

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
		mRoot->renderShape();
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
