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
#pragma once

#include "vtxPrerequesites.h"
#include "vtxSingleton.h"

#define VTX_EXCEPT LogManager::getSingletonPtr()->file(__FILE__); LogManager::getSingletonPtr()->line(__LINE__); LogManager::getSingletonPtr()->exception
#define VTX_WARN LogManager::getSingletonPtr()->file(__FILE__); LogManager::getSingletonPtr()->warning
#define VTX_LOG LogManager::getSingletonPtr()->log

namespace vtx
{
	class vtxExport LogManager : public Singleton<LogManager>
	{
		friend Singleton;

	public:
		LogManager();
		virtual ~LogManager();

		void logToCout(bool log_to_cout);

		void exception(const char* format, ...);
		void warning(const char* format, ...);
		void log(const char* format, ...);

		void file(const String& source);
		void line(const uint& line);

	protected:
		bool mCout;
		char mMessageBuffer[16000];
		std::ofstream mLogFile;
		String mFilename;
		uint mLineNr;
	};
}
