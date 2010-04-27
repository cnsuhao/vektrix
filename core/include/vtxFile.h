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
	/** Represents a template for creating Movie instances and contains all necessary resources */
	class vtxExport File
	{
	public:
		friend class FileManager;

		enum ResourceGroupType
		{
			RGT_Internal = 0, 
			RGT_External
		};

		/** The header of a File, which contains basic information such as width, height, fps, etc */
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

			FileHeader()
			{
				clear();
			}

			void clear()
			{
				version = script_root_class = "";
				fps = 1;
				frames = width = height = 0;
				bgcolor = Color();
			}
		};

		/** Listen to File events */
		class Listener
		{
		public:
			/** A Resource has been added to this File */
			virtual void resourceAdded(Resource* resource, const File::ResourceGroupType& group){}
			/** A Resource has been removed from this File */
			virtual void resourceRemoved(Resource* resource){}
		};
		typedef std::map<Listener*, Listener*> ListenerMap;

		File(const String& filename);
		virtual ~File();

		/** Get the file name from which this file has been parsed */
		const String& getFilename();

		/** Set the FileHeader for this file */
		void setHeader(FileHeader header);
		/** Get the FileHeader of this file */
		const FileHeader& getHeader();

		/** Set the name of the ScriptEngineFactory that shall be used for Movies created from this File */
		void setScriptEngine(const String& scriptEngineFactory);
		/** Get the name of the ScriptEngineFactory that shall be used for Movies created from this File */
		const String& getScriptEngine();

		/** Set the MovieClipResource which defines the main MovieClip for related Movie instances */
		void setMainMovieClip(MovieClipResource* movieclip);
		/** Get the MovieClipResource which defines the main MovieClip for related Movie instances */
		MovieClipResource* getMainMovieClip();

		/** Add a Resource instance to this File */
		void addResource(Resource* res, const ResourceGroupType& group = RGT_Internal);

		/** Retrieve a Resource instance from this File by its unique ID */
		Resource* getResource(const String& id);

		/** Query all resouces from this File that match the given type */
		const ResourceList& getResourcesByType(const String& type) const;

		/** Get all resources of this File */
		const ResourceMap& getResources() const;

		/** Get a particular FontResource by its font name */
		FontResource* getFontByName(const String& font_name);

		bool addListener(Listener* listener);
		bool removeListener(Listener* listener);

	protected:
		String mFilename;
		FileHeader mHeader;

		ResourceGroup* mResourceGroups[2];
		ListenerMap mListeners;

		String mScriptEngineFactory;
		MovieClipResource* mMainMovieClip;

		void _addResourceToGroup(
			ResourceMap& res_map, 
			ResourceTypeMap& res_type_map, 
			Resource* res);
	};
}

#endif
