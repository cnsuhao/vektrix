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
#include "vtxFileHelper.h"

#include <io.h>
#include <sys/stat.h>

namespace vtx
{
	//-----------------------------------------------------------------------
	bool FileHelper::doesFileExist(String name)
	{
		return (access(name.c_str(), F_OK ) != -1);
	}
	//-----------------------------------------------------------------------
	bool FileHelper::doesDirectoryExist(String name)
	{
		struct stat buf;
		stat(name.c_str(), &buf);
		return (buf.st_mode & S_IFDIR);
	}
	//-----------------------------------------------------------------------
}
