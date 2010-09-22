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

# dependency discovery
# core
find_package (boost)
find_package (expat REQUIRED)
# plugins
find_package (cairo REQUIRED)
find_package (caspin REQUIRED)
find_package (curl REQUIRED)
find_package (freeimage REQUIRED)
find_package (ogre REQUIRED)
find_package (ois REQUIRED)
find_package (zlib REQUIRED)

# core library
add_subdirectory (core/scripts)

# plugins
add_subdirectory (plugins/AS3Plugin/scripts)
add_subdirectory (plugins/CairoPlugin/scripts)
add_subdirectory (plugins/cURLPlugin/scripts)
add_subdirectory (plugins/FreeImgPlugin/scripts)
add_subdirectory (plugins/OgrePlugin/scripts)
add_subdirectory (plugins/SwfPlugin/scripts)
#add_subdirectory (plugins/XmlPlugin/scripts)

# demos
add_subdirectory (demos/Ogre3D/scripts)

# tools
add_subdirectory (tools/vtxFlashPreview/scripts)
