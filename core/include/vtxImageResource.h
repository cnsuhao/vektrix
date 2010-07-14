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

#ifndef __vtxImageResource_H__
#define __vtxImageResource_H__

#include "vtxPrerequisites.h"
#include "vtxResource.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** A Resource which contains all necessary data for rendering an image */
	class vtxExport ImageResource : public Resource
	{
	public:
		ImageResource(const String& id);
		virtual ~ImageResource();

		/** @copybrief Resource::getType */
		const String& getType() const;

		/** Set the image data for this resource */
		void setImageData(const uint& width, const uint& height, char* pixel_data);

		/** Get the width of the image */
		const uint& getWidth() const;

		/** Get the height of the image */
		const uint& getHeight() const;

		/** Get the pixel data of the image */
		const char* getPixelData() const;

	protected:
		uint mWidth;
		uint mHeight;
		char* mPixelData;
	};
	//-----------------------------------------------------------------------
}

#endif
