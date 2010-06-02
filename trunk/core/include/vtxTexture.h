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

#ifndef __vtxTexture_H__
#define __vtxTexture_H__

#include "vtxPrerequesites.h"
#include "vtxFactory.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** Represents a 2D texture which can be used for drawing visuals */
	class vtxExport Texture
	{
	public:
		Texture(uint size);
		virtual ~Texture();

		// TODO: refractor packing, this shouldn't be located here

		/** Pack an AtlasElement into this texture */
		AtlasNode* packElement(AtlasElement* element);
		/** Invalidiate previous packing results */
		void clear();
		/** Draw all contained elements to this texture */
		void renderAllShapes();

		const uint& getSize() const;
		uint getPackedSize();

		/** Paint a given RGBA pixel buffer to the given coordinates inside this texture */
		virtual void paintPixelsToRect(const Rect& coordinates, unsigned char* pixelData) = 0;

	protected:
		uint mSize;
		AtlasNode* mRoot;
	};
	//-----------------------------------------------------------------------
	/** The Factory for creating Texture objects */
	class vtxExport TextureFactory : public Factory<Texture> {};
	//-----------------------------------------------------------------------
}

#endif
