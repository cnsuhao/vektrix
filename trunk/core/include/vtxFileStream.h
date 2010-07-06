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

#ifndef __vtxFileStream_H__
#define __vtxFileStream_H__

#include "vtxPrerequisites.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** An interface representing a data stream */
	class vtxExport FileStream
	{
	public:
		FileStream(const String& filename) : mFilename(filename) {}

		/** Jump to a given read/write position */
		virtual void seek(uint pos) = 0;
		/** Get the current read/write position */
		virtual uint tell() = 0;
		/** Read a specified amount of bytes */
		virtual uint read(void* buf, uint count) = 0;
		/** Read a single line */
		virtual String& getLine() = 0;
		/** Check if the end of the stream has been reached */
		virtual bool eof() const = 0;
		/** Close the stream and and release resources */
		virtual void close() = 0;

		/** Get the size in bytes of the whole stream */
		uint size() const { return mSize; }
		/** Get the file name from which the stream has been created */
		const String& getFilename() { return mFilename; }

	protected:
		uint mSize;
		String mFilename;
	};
	//-----------------------------------------------------------------------
}

#endif
