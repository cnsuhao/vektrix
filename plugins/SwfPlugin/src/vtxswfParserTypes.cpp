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

#include "vtxswfParserTypes.h"

namespace vtx { namespace swf {
	//-----------------------------------------------------------------------
	const char* TagNames::getTagName(const uint& tag_type)
	{
		if(tag_type > 91)
			return "__OutOfKnownRange__";

		return mNames[tag_type];
	}
	//-----------------------------------------------------------------------
	const char* TagNames::mNames[] = 
	{
		/* 00 */ "End", 
		/* 01 */ "ShowFrame", 
		/* 02 */ "DefineShape", 
		/* 03 */ "__NotAssigned__", 
		/* 04 */ "PlaceObject", 
		/* 05 */ "RemoveObject", 
		/* 06 */ "DefineBits", 
		/* 07 */ "DefineButton", 
		/* 08 */ "JPEGTables", 
		/* 09 */ "SetBackgroundColor", 
		/* 10 */ "DefineFont", 
		/* 11 */ "DefineText", 
		/* 12 */ "DoAction", 
		/* 13 */ "DefineFontInfo", 
		/* 14 */ "DefineSound", 
		/* 15 */ "StartSound", 
		/* 16 */ "__NotAssigned__", 
		/* 17 */ "DefineButtonSound", 
		/* 18 */ "SoundStreamHead", 
		/* 19 */ "SoundStreamBlock", 
		/* 20 */ "DefineBitsLossless", 
		/* 21 */ "DefineBitsJPEG2", 
		/* 22 */ "DefineShape2", 
		/* 23 */ "DefineButtonCxform", 
		/* 24 */ "Protect", 
		/* 25 */ "__NotAssigned__", 
		/* 26 */ "PlaceObject2", 
		/* 27 */ "__NotAssigned__", 
		/* 28 */ "RemoveObject2", 
		/* 29 */ "__NotAssigned__", 
		/* 30 */ "__NotAssigned__", 
		/* 31 */ "__NotAssigned__", 
		/* 32 */ "DefineShape3", 
		/* 33 */ "DefineText2", 
		/* 34 */ "DefineButton2", 
		/* 35 */ "DefineBitsJPEG3", 
		/* 36 */ "DefineBitsLossless2", 
		/* 37 */ "DefineEditText", 
		/* 38 */ "__NotAssigned__", 
		/* 39 */ "DefineSprite", 
		/* 40 */ "__NotAssigned__", 
		/* 41 */ "__NotAssigned__", 
		/* 42 */ "__NotAssigned__", 
		/* 43 */ "FrameLabel", 
		/* 44 */ "__NotAssigned__", 
		/* 45 */ "SoundStreamHead2", 
		/* 46 */ "DefineMorphShape", 
		/* 47 */ "__NotAssigned__", 
		/* 48 */ "DefineFont2", 
		/* 49 */ "__NotAssigned__", 
		/* 50 */ "__NotAssigned__", 
		/* 51 */ "__NotAssigned__", 
		/* 52 */ "__NotAssigned__", 
		/* 53 */ "__NotAssigned__", 
		/* 54 */ "__NotAssigned__", 
		/* 55 */ "__NotAssigned__", 
		/* 56 */ "ExportAssets", 
		/* 57 */ "ImportAssets", 
		/* 58 */ "EnableDebugger", 
		/* 59 */ "DoInitAction", 
		/* 60 */ "DefineVideoStream", 
		/* 61 */ "VideoFrame", 
		/* 62 */ "DefineFontInfo2", 
		/* 63 */ "__NotAssigned__", 
		/* 64 */ "EnableDebugger2", 
		/* 65 */ "ScriptLimits", 
		/* 66 */ "SetTabIndex", 
		/* 67 */ "__NotAssigned__", 
		/* 68 */ "__NotAssigned__", 
		/* 69 */ "FileAttributes", 
		/* 70 */ "PlaceObject3", 
		/* 71 */ "ImportAssets2", 
		/* 72 */ "__NotAssigned__", 
		/* 73 */ "DefineFontAlignZones", 
		/* 74 */ "CSMTextSettings", 
		/* 75 */ "DefineFont3", 
		/* 76 */ "SymbolClass", 
		/* 77 */ "Metadata", 
		/* 78 */ "DefineScalingGrid", 
		/* 79 */ "__NotAssigned__", 
		/* 80 */ "__NotAssigned__", 
		/* 81 */ "__NotAssigned__", 
		/* 82 */ "DoABC", 
		/* 83 */ "DefineShape4", 
		/* 84 */ "DefineMorphShape2", 
		/* 85 */ "__NotAssigned__", 
		/* 86 */ "DefineSceneAndFrameLabelData", 
		/* 87 */ "DefineBinaryData", 
		/* 88 */ "DefineFontName", 
		/* 89 */ "StartSound2", 
		/* 90 */ "DefineBitsJPEG4", 
		/* 91 */ "DefineFont4"
	};
	//-----------------------------------------------------------------------
}}
