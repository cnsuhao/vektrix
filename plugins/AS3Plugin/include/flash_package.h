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

using namespace avmplus;
#include "flash.h"

// flash.events
#include "vtxas3EventDispatcher.h"

// flash.system
#include "vtxas3LoaderContext.h"

// flash.display
#include "vtxas3DisplayObject.h"
#include "vtxas3InteractiveObject.h"
#include "vtxas3SimpleButton.h"
#include "vtxas3DisplayObjectContainer.h"
#include "vtxas3Loader.h"
#include "vtxas3Sprite.h"
#include "vtxas3MovieClip.h"

// flash.net
#include "vtxas3URLRequest.h"

// flash.text
#include "vtxas3StaticText.h"
#include "vtxas3TextField.h"

// flash.utils
//#include "DictionaryGlue.h"

// vektrix.events
#include "vtxas3Event.h"
#include "vtxas3EventHandler.h"

#endif
