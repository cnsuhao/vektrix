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

#ifndef __vtxAtlasPacker_H__
#define __vtxAtlasPacker_H__

#include "vtxPrerequisites.h"
#include "vtxFile.h"
#include "vtxVector2.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** A class to pack two-dimensional objects into a given atlas */
	class vtxExport AtlasPacker
	{
	public:
		/** The class containing information about packed elements */
		class PackResult
		{
		public:
			PackResult(Texture* texture, AtlasNode* node) 
				: texture(texture), node(node) { }

			Texture* texture;
			AtlasNode* node;
		};
		typedef std::map<uint, PackResult> PackResultList;

		/** Listen to AtlasPacker events */
		class Listener
		{
		public:
			/** All packing information has been cleared */
			virtual void cleared(){}

			/** The atlas has been packed */
			virtual void packed(const PackResultList& pack_result) = 0;
		};
		typedef std::map<Listener*, Listener*> ListenerMap;

		typedef std::vector<Texture*> AtlasTextureList;
		typedef std::vector<AtlasElement*> AtlasElementList;

		AtlasPacker(TextureFactory* factory, uint atlasSize = 1024);
		virtual ~AtlasPacker();

		/** Sorts the elements that are registered to the atlas by area */
		static bool sortElement(AtlasElement* elem1, AtlasElement* elem2);

		/** Register an element to the atlas for packing */
		void addElement(AtlasElement* element);

		/** Check if a certain element is packed by this packer */
		bool containsElement(const uint& pack_id);

		/** Pack all registered elements to the atlas */
		const PackResultList& packAtlas();

		/** Render all registered elements to their assigned atlas */
		void renderAtlas();

		/** Invalidiate previous packing results & trees */
		void clearAtlas();

		/** Delete all atlas textures that have been used by the previous packing operation */
		void destroyAtlas();

		/** Get a list containing packing information for all packed elements */
		const PackResultList& getResultList();

		/** Add a Listener to this packer */
		bool addListener(Listener* listener);
		/** Remove a Listener from this packer */
		bool removeListener(Listener* listener);

	protected:
		uint mSize;
		AtlasTextureList mTextures;
		PackResultList mResult;
		AtlasElementList mElements;
		ListenerMap mListeners;

		TextureFactory* mTextureFactory;
	};
	//-----------------------------------------------------------------------
}

#endif
