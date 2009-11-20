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
		};

		typedef std::map<String, Resource*> ResourceMap;
		typedef std::vector<ShapeResource*> ShapeResourceList;

		File(const String& filename);
		virtual ~File();

		const String& getFilename();

		void setHeader(FileHeader header);
		const FileHeader& getHeader();

		void setMainMovieClip(MovieClipResource* movieclip);
		MovieClipResource* getMainMovieClip();

		//void setTimeline(Timeline* timeline);
		//Timeline* getTimeline();

		void addResource(Resource* res);
		Resource* getResource(const String& id);

		const ShapeResourceList& getShapeResourceList() const;

	protected:
		String mFilename;
		FileHeader mHeader;
		ResourceMap mResources;
		ShapeResourceList mShapes;

		MovieClipResource* mMainMovieClip;

		// TODO: deprecated
		//Timeline* mTimeline;
	};
}
