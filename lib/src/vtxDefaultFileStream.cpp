/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

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
#include "vtxDefaultFileStream.h"

#include "vtxLogManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	DefaultFileStream::DefaultFileStream(const String& path, const String& filename) 
		: FileStream(path, filename)
	{
		//struct stat tagStat;
		//int ret = stat(full_path.c_str(), &tagStat);
		//assert(ret == 0 && "Problem getting file size" );

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
	//uint DefaultFileStream::read(void* buf, uint count)
	//{
	//	mStream.read(static_cast<char*>(buf), static_cast<std::streamsize>(count));
	//	return mStream.gcount();
	//}
	////-----------------------------------------------------------------------
	//void DefaultFileStream::skip(long count)
	//{
	//	mStream.clear();
	//	mStream.seekg(static_cast<std::ifstream::pos_type>(count), std::ios::cur);
	//}
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
