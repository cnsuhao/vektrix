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
#pragma once

#include <stdarg.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#pragma warning (disable : 4251)
#pragma warning (disable : 4661)
#pragma warning (disable : 4996) // disable "vsprintf" warning
#pragma warning (disable : 4482) // disable enum "used in qualified name" warning

#ifndef F_OK
# define F_OK 0
# define X_OK 1
# define W_OK 2
# define R_OK 4
#endif

namespace vtx
{
	#define VTX_DEFAULT_MOVIE_FACTORY "NULL"

	// defines dll interface
	#if defined VEKTRIX_EXPORTS
		#define vtxExport __declspec(dllexport)
	#else
		#define vtxExport __declspec(dllimport)
	#endif

	// defines what operating system is used
	#define VTX_WIN32 1
	#define VTX_LINUX 2
	#define VTX_APPLE 3

	#if defined __WIN32__ || defined _WIN32
		#define VTX_OS VTX_WIN32

	#elif defined __APPLE_CC__
		#define VTX_OS VTX_APPLE

	#else
		#define VTX_OS VTX_LINUX
	#endif

	class AtlasNode;
	class Texture;
	class AtlasPacker;
	class BoundingBox;
	class Button;
	class ButtonFactory;
	class ButtonResource;
	class ButtonState;
	class Color;
	class CXForm;
	class DefaultButton;
	class DefaultFileContainer;
	class DefaultFileContainerFactory;
	class DynLib;
	class EventContainer;
	class File;
	class FileContainer;
	class FileContainerFactory;
	class FileParser;
	class FileManager;
	class FileStream;
	class FrameEvent;
	class Instance;
	class InstancePool;
	class Keyframe;
	class LogManager;
	class Material;
	class MaterialResource;
	class Matrix;
	class MovableObject;
	class Movie;
	class RenderStrategy;
	class MovieFactory;
	class Rect;
	class RectF;
	class RenderStrategy;
	class Resource;
	class Root;
	class Shape;
	class ShapeFactory;
	class ShapeResource;
	class StringHelper;
	class SubshapeResource;
	class Tesselator;
	class TextureFactory;
	class Timeline;
	class Vector2;

	// typedefs
	typedef unsigned char uchar;
	typedef unsigned short ushort;
	typedef unsigned int uint;
	typedef long long int64;
	typedef unsigned long long uint64;
	typedef std::string String;
	typedef std::wstring WString;
	typedef std::pair<String, String> StringPair;

	typedef String String;
	typedef std::vector<String> StringList;
	typedef std::map<String, String> StringMap;
	typedef std::pair<String, String> StringPair;
	typedef std::vector<StringPair> StringPairList;
	typedef std::map<String, DynLib*> DynLibMap;
}
