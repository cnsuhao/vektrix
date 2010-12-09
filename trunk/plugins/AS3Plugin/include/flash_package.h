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

#ifndef __flash_package_H__
#define __flash_package_H__

#include "vtxas3.h"
#include "cspPrerequisites.h"

///-------------------------------
/// ActionScript 3 HEADER Glue
///-------------------------------
#ifdef VTX_AS3_USE_SINGLE_ABC_PACKAGE
#
#	include "flash.h"
#
#else // VTX_AS3_USE_SINGLE_ABC_PACKAGE
#
#	include "flash_accessibility.h"
#	include "flash_display.h"
#	include "flash_events.h"
#	include "flash_filters.h"
#	include "flash_geom.h"
#	include "flash_media.h"
#	include "flash_net.h"
#	include "flash_system.h"
#	include "flash_text.h"
#	include "flash_ui.h"
#	include "flash_utils.h"
#	include "vektrix.h"
#
#endif // VTX_AS3_USE_SINGLE_ABC_PACKAGE



//-------------------------------
// flash.accessibility
//-------------------------------

//-------------------------------
// flash.display
//-------------------------------
#include "vtxas3Loader.h"
#include "vtxas3LoaderContext.h"
#include "vtxas3MovieClip.h"
#include "vtxas3SimpleButton.h"
#include "vtxas3Sprite.h"
#include "vtxas3Stage.h"

//-------------------------------
// flash.events
//-------------------------------
#include "vtxas3Event.h"
#include "vtxas3EventDispatcher.h"
#include "vtxas3MouseEvent.h"

//-------------------------------
// flash.filters
//-------------------------------

//-------------------------------
// flash.geom
//-------------------------------

//-------------------------------
// flash.media
//-------------------------------

//-------------------------------
// flash.net
//-------------------------------
#include "vtxas3URLRequest.h"

//-------------------------------
// flash.system
//-------------------------------

//-------------------------------
// flash.text
//-------------------------------
#include "vtxas3StaticText.h"
#include "vtxas3TextField.h"

//-------------------------------
// flash.ui
//-------------------------------
#include "vtxas3Mouse.h"

//-------------------------------
// flash.utils
//-------------------------------
#include "vtxas3Dictionary.h"
#include "vtxas3FlashUtils.h"
#include "vtxas3Timer.h"

//-------------------------------
// vektrix
//-------------------------------
#include "vtxas3EventHandler.h"



///-------------------------------
/// ActionScript 3 CPP Glue
///-------------------------------
#ifdef VTX_AS3_USE_SINGLE_ABC_PACKAGE
#
#	include "flash.cpp"
#
#else // VTX_AS3_USE_SINGLE_ABC_PACKAGE
#
#	include "flash_accessibility.cpp"
#	include "flash_display.cpp"
#	include "flash_events.cpp"
#	include "flash_filters.cpp"
#	include "flash_geom.cpp"
#	include "flash_media.cpp"
#	include "flash_net.cpp"
#	include "flash_system.cpp"
#	include "flash_text.cpp"
#	include "flash_ui.cpp"
#	include "flash_utils.cpp"
#	include "vektrix.cpp"
#
#endif // VTX_AS3_USE_SINGLE_ABC_PACKAGE

#endif
