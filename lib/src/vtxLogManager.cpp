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
#include "vtxLogManager.h"

#include "vtxStringHelper.h"

#ifdef WIN32
#include "windows.h"
#endif

namespace vtx
{
	//-----------------------------------------------------------------------
	template<> LogManager* Singleton<LogManager>::sInstance = 0;
	//-----------------------------------------------------------------------
	LogManager::LogManager() 
		: mCout(false), 
		mFilename("NULL"), 
		mLineNr(0)
	{
		mLogFile.open("vektrix.log");
	}
	//-----------------------------------------------------------------------
	LogManager::~LogManager()
	{
		mLogFile.close();
	}
	//-----------------------------------------------------------------------
	void LogManager::logToCout(bool log_to_cout)
	{
		mCout = log_to_cout;
	}
	//-----------------------------------------------------------------------
	void LogManager::exception(const char* format, ...)
	{
		va_list argptr;
		va_start(argptr, format);
		vsprintf(mMessageBuffer, format, argptr);
		va_end(argptr);

		String temp = "EXCEPTION: " + String(mMessageBuffer) + 
			"\n(occured in '" + mFilename + " at line " + StringHelper::toString(mLineNr) + "')";

		mLogFile << temp << std::endl;

		if(mCout)
		{
			std::cout << "<VTX> " << temp << std::endl;
		}

#ifdef WIN32
		MessageBox(NULL, temp.c_str(), "vektrix exception", MB_OK | MB_ICONSTOP);
#else
		std::cout << "Press any key to exit..." << std::endl;
		getch();
#endif
		exit(1);
	}
	//-----------------------------------------------------------------------
	void LogManager::warning(const char* format, ...)
	{
		va_list argptr;
		va_start(argptr, format);
		vsprintf(mMessageBuffer, format, argptr);
		va_end(argptr);

		mLogFile << "Warning: " << mMessageBuffer << std::endl;

		if(mCout)
		{
			std::cout << "<VTX> Warning: " << mMessageBuffer << "    (" << mFilename << ")" << std::endl;
		}
	}
	//-----------------------------------------------------------------------
	void LogManager::log(const char* format, ...)
	{
		va_list argptr;
		va_start(argptr, format);
		vsprintf(mMessageBuffer, format, argptr);
		va_end(argptr);

		if(mCout)
		{
			std::cout << "<VTX> " << mMessageBuffer << std::endl;
		}

		mLogFile << mMessageBuffer << std::endl;
	}
	//-----------------------------------------------------------------------
	void LogManager::file(const String& source)
	{
		uint pos = (uint)source.find_last_of('\\')+1;
		mFilename = source.substr(pos, source.length()-pos);
	}
	//-----------------------------------------------------------------------
	void LogManager::line(const uint& line)
	{
		mLineNr = line;
	}
	//-----------------------------------------------------------------------
}
