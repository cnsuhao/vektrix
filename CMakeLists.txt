cmake_minimum_required (VERSION 2.6)
project (vektrix)

# set up the module path
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/dependencies)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/tools)

# remove the MinSizeRel and RelWithDebInfo configurations
#set (CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "limited configs" FORCE)

# common build utilities
include (build_tools)

# load the folders4cmake utils
set (folders4cmake_path ${CMAKE_SOURCE_DIR}/cmake/tools/folders4cmake.jar)
include (folders4cmake)

# global build options
option (BUILD_USE_STATIC_CRT "Build against the static version of the MSVCRT" ON)

# plugins
option (BUILD_AS3_PLUGIN "Include/exclude the AS3 plugin from the build" ON)
option (BUILD_CAIRO_PLUGIN "Include/exclude the cairo-graphics plugin from the build" ON)
option (BUILD_CURL_PLUGIN "Include/exclude the cURL plugin from the build" ON)
option (BUILD_EDITOR_PLUGIN "Include/exclude the vektrix editor plugin from the build" ON)
option (BUILD_FREEIMAGE_PLUGIN "Include/exclude the FreeImage plugin from the build" ON)
option (BUILD_FREETYPE_PLUGIN "Include/exclude the FreeType plugin from the build" ON)
option (BUILD_OGRE_PLUGIN "Include/exclude the Ogre3D plugin from the build" ON)
option (BUILD_OPENGL_PLUGIN "Include/exclude the OpenGL plugin from the build" ON)
option (BUILD_SWF_PLUGIN "Include/exclude the SWF plugin from the build" ON)
# apps & utils
option (BUILD_FLASH_PREVIEW "Include/exclude the Flash IDE Plugin from the build" ON)
option (BUILD_UNIT_TESTS "Include/exclude the unit test components from the build" ON)

#-----------------------------------------------------------------------
# vektrix Core
#-----------------------------------------------------------------------
find_package (boost)
find_package (expat REQUIRED)

# core library
add_subdirectory (core/scripts)

#-----------------------------------------------------------------------
# Plugins
#-----------------------------------------------------------------------
set (vtx_plugins_list "")
set (vtx_plugins_include "")

# AS3 Plugin
if(BUILD_AS3_PLUGIN)
	find_package (caspin REQUIRED)
	vtx_add_plugin (AS3Plugin)
endif(BUILD_AS3_PLUGIN)

# Cairo Plugin
if(BUILD_CAIRO_PLUGIN)
	find_package (cairo REQUIRED)
	vtx_add_plugin (CairoPlugin)
endif(BUILD_CAIRO_PLUGIN)

# cURL Plugin
if(BUILD_CURL_PLUGIN)
	find_package (curl REQUIRED)
	vtx_add_plugin (cURLPlugin)
endif(BUILD_CURL_PLUGIN)

# FreeImage Plugin
if(BUILD_FREEIMAGE_PLUGIN)
	find_package (freeimage REQUIRED)
	vtx_add_plugin (FreeImgPlugin)
endif(BUILD_FREEIMAGE_PLUGIN)

# FreeType Plugin
if(BUILD_FREETYPE_PLUGIN)
	find_package (freetype REQUIRED)
	vtx_add_plugin (FreeTypePlugin)
endif(BUILD_FREETYPE_PLUGIN)

# Ogre3D Plugin
if(BUILD_OGRE_PLUGIN)
	find_package (directx REQUIRED)
	find_package (ogre REQUIRED)
	vtx_add_plugin (OgrePlugin)
endif(BUILD_OGRE_PLUGIN)

# OpenGL Plugin
if(BUILD_OPENGL_PLUGIN)
	vtx_add_plugin (OpenGLPlugin)
endif(BUILD_OPENGL_PLUGIN)

# SWF Plugin
if(BUILD_SWF_PLUGIN)
	find_package (zlib REQUIRED)
	vtx_add_plugin (SwfPlugin)
endif(BUILD_SWF_PLUGIN)

# vektrix Editor Plugin
if(BUILD_EDITOR_PLUGIN)
	vtx_add_plugin (EditorPlugin)
endif(BUILD_EDITOR_PLUGIN)

#add_subdirectory (plugins/XmlPlugin/scripts)
#-----------------------------------------------------------------------
# Applications & Utilities
#-----------------------------------------------------------------------
find_package (ois REQUIRED)

if(BUILD_UNIT_TESTS)
	add_subdirectory (dev/unit_tests/scripts)
endif(BUILD_UNIT_TESTS)

# demos
add_subdirectory (demos/Ogre3D/scripts)

# tools
if(BUILD_FLASH_PREVIEW)
	add_subdirectory (tools/vtxFlashPreview/scripts)
endif(BUILD_FLASH_PREVIEW)

