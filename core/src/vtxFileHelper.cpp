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

#include "vtxFileHelper.h"
#include "vtxLogManager.h"

#include <direct.h>

namespace vtx
{
	//-----------------------------------------------------------------------
	String FileHelper::getWorkingDirectory()
	{
		char cwd[1024];
		if(getcwd(cwd, 1024) == cwd)
			return cwd;

		static String res("<unknown>");
		return res;
	}
	//-----------------------------------------------------------------------
	bool FileHelper::doesFileExist(String name)
	{
		return (access(name.c_str(), F_OK) != -1);
	}
	//-----------------------------------------------------------------------
	bool FileHelper::doesDirectoryExist(String name)
	{
		if(!name.length())
			return false;

		char last_char = name.at(name.length()-1);

		if(last_char == '\\' || last_char == '/')
			name = name.substr(0, name.length()-1);

		struct stat buf;
		if(stat(name.c_str(), &buf))
		{
			VTX_WARN("Error \"%d\" while running stat() for \"%s\"", errno, name.c_str());
			return false;
		}

		return (buf.st_mode & S_IFDIR) != 0;
	}
	//-----------------------------------------------------------------------
}
