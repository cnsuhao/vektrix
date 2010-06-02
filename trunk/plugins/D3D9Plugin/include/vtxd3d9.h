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

#ifndef __vtxd3d9_H__
#define __vtxd3d9_H__

#include "vtxPrerequesites.h"

#if VTX_OS == VTX_WIN32
#	ifdef VTX_STATIC_LIB
#		define vtxd3d9Export
#	else
#		ifdef VEKTRIX_D3D9PLUGIN_EXPORTS
#			define vtxd3d9Export __declspec(dllexport)
#		else
#			define vtxd3d9Export __declspec(dllimport)
#		endif
#	endif
#endif

#if VTX_OS == VTX_LINUX
#	define vtxd3d9Export
#endif

namespace vtx
{
	namespace d3d9
	{
		// MovableMovie
		class MovableMovie;
		class MovableMovieFactory;
		class MovableStrategy;
		// Instances
		class D3D9MovableShape;
		class D3D9MovableShapeFactory;

		// Generic
		class D3D9Texture;
		class D3D9TextureFactory;
	}
}

#endif
