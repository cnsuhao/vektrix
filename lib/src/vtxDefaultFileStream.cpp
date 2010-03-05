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

#include "vtxDefaultFileStream.h"

#include "vtxLogManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	DefaultFileStream::DefaultFileStream(const String& path, const String& filename) 
		: FileStream(filename)
	{
		mStream.open((path + filename).c_str(), std::ios::in | std::ios::binary);

		if(mStream.fail())
		{
			VTX_EXCEPT("Unable to open file '%s'!", filename.c_str());
		}

		mStream.seekg(0, std::ios_base::end);
		mSize = mStream.tellg();
		mStream.seekg(0, std::ios_base::beg);
	}
	//-----------------------------------------------------------------------
	DefaultFileStream::~DefaultFileStream()
	{
		close();
	}
	//-----------------------------------------------------------------------
	void DefaultFileStream::seek(uint pos)
	{
		mStream.clear();
		mStream.seekg(static_cast<std::streamoff>(pos), std::ios::beg);
	}
	//-----------------------------------------------------------------------
	uint DefaultFileStream::tell()
	{
		mStream.clear();
		return mStream.tellg();
	}
	//-----------------------------------------------------------------------
	uint DefaultFileStream::read(void* buf, uint count)
	{
		mStream.read(static_cast<char*>(buf), static_cast<std::streamsize>(count));
		return mStream.gcount();
	}
	//-----------------------------------------------------------------------
	String& DefaultFileStream::getLine()
	{
		static String str;
		getline(mStream, str);
		return str;
	}
	//-----------------------------------------------------------------------
	bool DefaultFileStream::eof() const
	{
		return mStream.eof();
	}
	//-----------------------------------------------------------------------
	void DefaultFileStream::close()
	{
		mStream.close();
	}
	//-----------------------------------------------------------------------
}
