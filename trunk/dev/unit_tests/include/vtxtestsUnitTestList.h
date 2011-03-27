
/* This is a machine generated file, DON'T ATTEMPT TO EDIT THIS !!! */

#ifndef __vtx_tests_UnitTestList_H__
#define __vtx_tests_UnitTestList_H__

//-----------------------------------------------------------------------
#include "as3/flash_display_DisplayObject/flash_display_DisplayObject.h"
#include "as3/flash_external_ExternalInterface/flash_external_ExternalInterface.h"
//-----------------------------------------------------------------------
#include "core/EditText/EditText.h"
//-----------------------------------------------------------------------
#include "opengl/Basic/Basic.h"
//-----------------------------------------------------------------------
#include "swf/ImageParsing/ImageParsing.h"
//-----------------------------------------------------------------------
const char* STR_TEST_LIST[] = 
{
	"as3::flash_display_DisplayObject", 
	"as3::flash_external_ExternalInterface", 
	"core::EditText", 
	"opengl::Basic", 
	"swf::ImageParsing"
};
//-----------------------------------------------------------------------
const int& STR_TEST_LIST_LEN = 5;
//-----------------------------------------------------------------------
#define RUN_TEST_FROM_STRING(host, str) \
	if(false){} \
	else if(str == "as3::flash_display_DisplayObject") \
		host.runTest<as3::flash_display_DisplayObject>(); \
	\
	else if(str == "as3::flash_external_ExternalInterface") \
		host.runTest<as3::flash_external_ExternalInterface>(); \
	\
	else if(str == "core::EditText") \
		host.runTest<core::EditText>(); \
	\
	else if(str == "opengl::Basic") \
		host.runTest<opengl::Basic>(); \
	\
	else if(str == "swf::ImageParsing") \
		host.runTest<swf::ImageParsing>(); \
	\
	else VTX_EXCEPT("Unknown test: %s", str.c_str())
//-----------------------------------------------------------------------

#endif
