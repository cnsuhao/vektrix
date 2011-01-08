cmake_minimum_required (VERSION 2.6)
project (vektrix)

# set up the module path
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/dependencies)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/tools)

# remove the MinSizeRel and RelWithDebInfo configurations
set (CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "limited configs" FORCE)

# load the folders4cmake utils
set (folders4cmake_path ${CMAKE_SOURCE_DIR}/cmake/tools/folders4cmake.jar)
include (folders4cmake)

# global build options
option (BUILD_AS3_PLUGIN "Include/exclude the AS3 plugin from the build" ON)
option (BUILD_EDITOR_PLUGIN "Include/exclude the vektrix Editor plugin from the build" ON)
option (BUILD_SWF_PLUGIN "Include/exclude the SWF plugin from the build" ON)
option (BUILD_FLASH_PREVIEW "Include/exclude the Flash IDE Plugin from the build" OFF)

# dependency discovery
# core
find_package (boost)
find_package (expat REQUIRED)

# plugins
# AS3 Plugin
if(BUILD_AS3_PLUGIN)
	find_package (caspin REQUIRED)
	add_subdirectory (plugins/AS3Plugin/scripts)
endif(BUILD_AS3_PLUGIN)

# Cairo Plugin
find_package (cairo REQUIRED)
add_subdirectory (plugins/CairoPlugin/scripts)

# cURL Plugin
find_package (curl REQUIRED)
add_subdirectory (plugins/cURLPlugin/scripts)

# FreeImage Plugin
find_package (freeimage REQUIRED)
add_subdirectory (plugins/FreeImgPlugin/scripts)

# Ogre3D Plugin
find_package (ogre REQUIRED)
add_subdirectory (plugins/OgrePlugin/scripts)

# SWF Plugin
if(BUILD_SWF_PLUGIN)
	find_package (zlib REQUIRED)
	add_subdirectory (plugins/SwfPlugin/scripts)
endif(BUILD_SWF_PLUGIN)

# core library
add_subdirectory (core/scripts)

# vektrix Editor Plugin
if(BUILD_EDITOR_PLUGIN)
	add_subdirectory (plugins/EditorPlugin/scripts)
endif(BUILD_EDITOR_PLUGIN)

#add_subdirectory (plugins/XmlPlugin/scripts)

# demos
find_package (ois REQUIRED)
add_subdirectory (demos/Ogre3D/scripts)

# tools
if(BUILD_FLASH_PREVIEW)
	add_subdirectory (tools/vtxFlashPreview/scripts)
endif(BUILD_FLASH_PREVIEW)
