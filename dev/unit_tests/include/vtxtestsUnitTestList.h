
/* This is a machine generated file, DON'T ATTEMPT TO EDIT THIS !!! */

#ifndef __vtx_tests_UnitTestList_H__
#define __vtx_tests_UnitTestList_H__

//-----------------------------------------------------------------------
#include "as3/flash_display_DisplayObject/flash_display_DisplayObject.h"
#include "as3/flash_external_ExternalInterface/flash_external_ExternalInterface.h"
//-----------------------------------------------------------------------
#include "swf/ImageParsing/ImageParsing.h"
//-----------------------------------------------------------------------
#define RUN_TEST_FROM_STRING(host, str) \
	if(false){} \
	else if(str == "as3::flash_display_DisplayObject") \
		host.runTest<as3::flash_display_DisplayObject>(); \
	\
	else if(str == "as3::flash_external_ExternalInterface") \
		host.runTest<as3::flash_external_ExternalInterface>(); \
	\
	else if(str == "swf::ImageParsing") \
		host.runTest<swf::ImageParsing>(); \
	\
	else VTX_EXCEPT("Unknown test: %s", test_name.c_str())
//-----------------------------------------------------------------------

#endif
