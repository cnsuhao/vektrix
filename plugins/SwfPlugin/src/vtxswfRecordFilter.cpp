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
#include "vtxswfRecordFilter.h"
#include "vtxswfRecordBevelFilter.h"
#include "vtxswfRecordBlurFilter.h"
#include "vtxswfRecordColorMatrixFilter.h"
#include "vtxswfRecordConvolutionFilter.h"
#include "vtxswfRecordDropShadowFilter.h"
#include "vtxswfRecordGlowFilter.h"
#include "vtxswfRecordGradientBevelFilter.h"
#include "vtxswfRecordGradientGlowFilter.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		SwfRecordFilter::SwfRecordFilter()
		{}
		//-----------------------------------------------------------------------
		SwfRecordFilter::SwfRecordFilter(FilterType type)
			: mType(type)
		{}
		//-----------------------------------------------------------------------
		SwfRecordFilter::FilterList SwfRecordFilter::readFilters(MemoryBlockReader& memoryReader)
		{
			FilterList mFilters;
			int count = memoryReader.readUI8();
			for (int i = 0; i < count; i++)
			{
				FilterType filterType = (FilterType)memoryReader.readUI8();
				SwfRecordFilter* filter = NULL;
				switch (filterType)
				{
				  case FT_BEVEL:
					  filter = new SwfRecordBevelFilter(memoryReader);
					  break;
				  case FT_BLUR:
					  filter = new SwfRecordBlurFilter(memoryReader);
					  break;
				  case FT_COLOR_MATRIX:
					  filter = new SwfRecordColorMatrixFilter(memoryReader);
					  break;
				  case FT_CONVOLUTION:
					  filter = new SwfRecordConvolutionFilter(memoryReader);
					  break;
				  case FT_DROP_SHADOW:
					  filter = new SwfRecordDropShadowFilter(memoryReader);
					  break;
				  case FT_GLOW:
					  filter = new SwfRecordGlowFilter(memoryReader);
					  break;
				  case FT_GRADIENT_BEVEL:
					  filter = new SwfRecordGradientBevelFilter(memoryReader);
					  break;
				  case FT_GRADIENT_GLOW:
					  filter = new SwfRecordGradientGlowFilter(memoryReader);
					  break;
				  default:
					  VTX_DEBUG_FAIL("Unhandled filter");
				}
				mFilters.push_back(filter);
			}
			return mFilters;
		}
		//-----------------------------------------------------------------------
		SwfRecordFilter::~SwfRecordFilter()
		{}
		//-----------------------------------------------------------------------
	}
}
