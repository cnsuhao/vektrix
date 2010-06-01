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

#ifndef __vtxPrerequesites_H__
#define __vtxPrerequesites_H__

#include <stdarg.h>
#include <assert.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "vtxConfig.h"
#include "vtxAssert.h"

// version
#define VTX_VERSION_MAJOR 0
#define VTX_VERSION_MINOR 1
#define VTX_VERSION_PATCH 0
#define VTX_VERSION_NAME "Valus"

#define VTX_VERSION ((VTX_VERSION_MAJOR << 16) | (VTX_VERSION_MINOR << 8) | VTX_VERSION_PATCH)

#ifdef VTX_STATIC_LIB
#	define VTX_LOAD_PLUGIN(name) name##_startPlugin()
#else
#	define VTX_LOAD_PLUGIN(name) vtx::Root::getSingletonPtr()->loadLibrary(#name)
#endif

// defines what operating system is used
#define VTX_WIN32 1
#define VTX_LINUX 2
#define VTX_APPLE 3

#if defined __WIN32__ || defined _WIN32
#	define VTX_OS VTX_WIN32

#elif defined __APPLE_CC__
#	define VTX_OS VTX_APPLE
#else
#	define VTX_OS VTX_LINUX
#endif

#include "vtxLinux.h"
#include "vtxWin32.h"

#ifndef F_OK
# define F_OK 0
# define X_OK 1
# define W_OK 2
# define R_OK 4
#endif

namespace vtx
{
	class AtlasNode;
	class AtlasElement;
	class AtlasPacker;
	class BoundingBox;
	class Button;
	class ButtonResource;
	class ButtonState;
	class Color;
	class CXForm;
	class DefaultFileContainer;
	class DefaultFileContainerFactory;
	class DisplayObject;
	class DisplayObjectContainer;
	class DynLib;
	class EditText;
	class EditTextFactory;
	class EditTextResource;
	class Event;
	class EventContainer;
	class EventListener;
	class File;
	class FileContainer;
	class FileContainerFactory;
	class FileParser;
	class FileManager;
	class FileStream;
	class FontResource;
	class FrameEvent;
	class GlyphResource;
	class HtmlElement;
	class HtmlFont;
	class HtmlImage;
	class HtmlParagraph;
	class HtmlParser;
	class HtmlText;
	class ImageResource;
	class Instance;
	class InstanceFactory;
	class InstanceManager;
	class InstancePool;
	class InteractiveObject;
	class KeyboardEvent;
	class Keyframe;
	class LogManager;
	class Material;
	class MaterialResource;
	class Matrix;
	class MouseEvent;
	class Movie;
	class MovieClip;
	class MovieClipResource;
	class MovieDebugger;
	class MovieFactory;
	class OpSysHelper;
	class Plugin;
	class Rasterizer;
	class Rect;
	class RectF;
	class RenderStrategy;
	class Resource;
	class ResourceGroup;
	class Root;
	class ScriptEngine;
	class ScriptEngineFactory;
	class ScriptObject;
	class ScriptResource;
	class Shape;
	class ShapeElement;
	class ShapeFactory;
	class ShapeResource;
	class StaticText;
	class StaticTextFactory;
	class StaticTextResource;
	class StringHelper;
	class SubshapeResource;
	class TextLine;
	class TextLineElement;
	class Texture;
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

	typedef std::vector<Resource*> ResourceList;
	typedef std::map<String, Resource*> ResourceMap;
	typedef std::map<String, ResourceList> ResourceTypeMap;
	typedef std::map<String, FontResource*> FontMap;

	// plugin functions
	typedef void (*START_PLUGIN_FUNCTION)();
}

#endif
