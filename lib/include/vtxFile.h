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

#ifndef __vtxFile_H__
#define __vtxFile_H__

#include "vtxPrerequesites.h"

#include "vtxColor.h"

namespace vtx
{
	class vtxExport File
	{
	public:
		friend class FileManager;

		class FileHeader
		{
		public:
			String version;
			uint fps;
			uint frames;
			uint width;
			uint height;
			Color bgcolor;
			String script_root_class;

			void clear()
			{
				version = script_root_class = "";
				fps = frames = width = height = 0;
				bgcolor = Color();
			}
		};

		typedef std::map<String, Resource*> ResourceMap;
		typedef std::vector<ShapeResource*> ShapeResourceList;

		File(const String& filename);
		virtual ~File();

		const String& getFilename();

		void setHeader(FileHeader header);
		const FileHeader& getHeader();

		void setScriptEngine(const String& scriptEngineFactory);
		const String& getScriptEngine();

		void setMainMovieClip(MovieClipResource* movieclip);
		MovieClipResource* getMainMovieClip();

		void addResource(Resource* res);
		Resource* getResource(const String& id);

		const ShapeResourceList& getShapeResourceList() const;

	protected:
		String mFilename;
		FileHeader mHeader;
		ResourceMap mResources;
		ShapeResourceList mShapes;

		String mScriptEngineFactory;
		MovieClipResource* mMainMovieClip;
	};
}

#endif
