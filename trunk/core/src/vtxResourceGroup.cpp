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

#include "vtxResourceGroup.h"
#include "vtxFile.h"
#include "vtxFontResource.h"
#include "vtxLogManager.h"
#include "vtxResource.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	ResourceGroup::ResourceGroup(File* file) 
		: mParent(file)
	{

	}
	//-----------------------------------------------------------------------
	ResourceGroup::~ResourceGroup()
	{

	}
	//-----------------------------------------------------------------------
	bool ResourceGroup::addResource(vtx::Resource* res)
	{
		ResourceMap::iterator it = mResources.find(res->getID());

		if(it != mResources.end())
		{
			VTX_WARN("\"%s\": Tried to add Resource with id \"%s\" twice!", 
				mParent->getFilename().c_str(), res->getID().c_str());
			return false;
		}

		mResources[res->getID()] = res;
		mResourcesByType[res->getType()].push_back(res);

		FontResource* font = dynamic_cast<FontResource*>(res);
		if(font)
		{
			mFonts[font->getName()] = font;
		}

		return true;

		//if(!external)
		//{
		//	res->_setFile(this);
		//}
	}
	//-----------------------------------------------------------------------
	Resource* ResourceGroup::getResource(const String& id)
	{
		ResourceMap::iterator it = mResources.find(id);

		if(it != mResources.end())
		{
			return it->second;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	const ResourceList& ResourceGroup::getResourcesByType(const String& type) const
	{
		ResourceTypeMap::const_iterator it = mResourcesByType.find(type);
		if(it != mResourcesByType.end())
		{
			return it->second;
		}

		static ResourceList empty;
		return empty;
	}
	//-----------------------------------------------------------------------
	const ResourceMap& ResourceGroup::getResources() const
	{
		return mResources;
	}
	//-----------------------------------------------------------------------
	void ResourceGroup::destroyResources()
	{
		ResourceMap::iterator it = mResources.begin();
		ResourceMap::iterator end = mResources.end();
		while(it != end)
		{
			delete it->second;
			++it;
		}
	}
	//-----------------------------------------------------------------------
	FontResource* ResourceGroup::getFontByName(const String& font_name)
	{
		FontMap::iterator it = mFonts.find(font_name);
		if(it != mFonts.end())
		{
			return it->second;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
}
