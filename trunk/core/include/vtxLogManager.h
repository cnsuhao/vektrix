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

#ifndef __vtxLogManager_H__
#define __vtxLogManager_H__

#include "vtxPrerequisites.h"
#include "vtxSingleton.h"
#include "vtxThreadingDefines.h"
#include "vtxThreadingHeaders.h"

#define VTX_EXCEPT(...)	do { vtx::LogManager* log = vtx::LogManager::getSingletonPtr(); log->file(__FILE__); log->line(__LINE__); log->exception(__VA_ARGS__); } while(false)
#define VTX_WARN(...)	do { vtx::LogManager* log = vtx::LogManager::getSingletonPtr(); log->file(__FILE__); log->warning(__VA_ARGS__); } while(false)
#define VTX_LOG(...)	do { vtx::LogManager::getSingletonPtr()->log(__VA_ARGS__); } while(false)

#ifdef _DEBUG
#	define VTX_DEBUG vtx::LogManager::getSingletonPtr()->log
#else
#	define VTX_DEBUG
#endif

namespace vtx
{
	//-----------------------------------------------------------------------
	/** The manager for logging events, warnings and errors */
	class vtxExport LogManager : public AutoSingleton<LogManager>
	{
		friend class AutoSingleton<LogManager>;
		friend class Root;

	protected:
		LogManager();
		virtual ~LogManager();

	public:
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
		VTX_MUTEX(mLogMutex);
	};
	//-----------------------------------------------------------------------
}

#endif
