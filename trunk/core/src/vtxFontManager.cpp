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

#include "vtxFontManager.h"

#include "vtxFileManager.h"
#include "vtxFileStream.h"
#include "vtxFontParser.h"
#include "vtxFontResource.h"
#include "vtxStringHelper.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	template<> FontManager* Singleton<FontManager>::sInstance = 0;
	//-----------------------------------------------------------------------
	FontManager::FontManager()
	{

	}
	//-----------------------------------------------------------------------
	FontManager::~FontManager()
	{

	}
	//-----------------------------------------------------------------------
	void FontManager::addParser(FontParser* parser)
	{
		const StringList& extensions = parser->getExtensions();
		for_each_const(ext_it, StringList, extensions)
		{
			if(mParsers.find(*ext_it) == mParsers.end())
				mParsers.insert(std::make_pair(*ext_it, parser));
		}
	}
	//-----------------------------------------------------------------------
	bool FontManager::loadFontFile(const String& filename)
	{
		if(mFontFiles.find(filename) != mFontFiles.end())
			return false;

		// find the parser for the given filename
		String ext = StringHelper::getFileExtension(filename);
		ParserMap::iterator it = mParsers.find(ext);

		if(it == mParsers.end())
			return false;

		// open the font definition file
		FileStream* stream = FileManager::getSingletonPtr()->getFileStream(filename);

		if(!stream)
			return false;

		// parse the FontResource from the file stream
		FontResource* font = it->second->parse(stream);

		// store the parsed FontResource
		if(font)
			mFonts.insert(std::make_pair(font->getName(), font));

		stream->close();
		delete stream;

		return true;
	}
	//-----------------------------------------------------------------------
	FontResource* FontManager::getFont(const String& name)
	{
		FontMap::iterator it = mFonts.find(name);

		if(it != mFonts.end())
			return it->second;

		return NULL;
	}
	//-----------------------------------------------------------------------
}
