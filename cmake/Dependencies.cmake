#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

#######################################################################
# Find all necessary and optional OGRE dependencies
#######################################################################

# VEKTRIX_DEPENDENCIES_DIR can be used to specify a single base
# folder where the required dependencies may be found.
set(VEKTRIX_DEPENDENCIES_DIR "" CACHE PATH "Path to prebuilt Vektrix dependencies")
include(FindPkgMacros)
getenv_path(VEKTRIX_DEPENDENCIES_DIR)

set(VEKTRIX_DEP_SEARCH_PATH 
  ${VEKTRIX_DEPENDENCIES_DIR}
  ${ENV_VEKTRIX_DEPENDENCIES_DIR}
  "${VEKTRIX_BINARY_DIR}/dependencies"
  "${VEKTRIX_SOURCE_DIR}/dependencies"
  "${VEKTRIX_BINARY_DIR}/../dependencies"
  "${VEKTRIX_SOURCE_DIR}/../dependencies"
)

message(STATUS "Search path: ${VEKTRIX_DEP_SEARCH_PATH}")

# Set hardcoded path guesses for various platforms
if (UNIX)
  set(VEKTRIX_DEP_SEARCH_PATH ${VEKTRIX_DEP_SEARCH_PATH} /usr/local)
endif ()

# give guesses as hints to the find_package calls
set(CMAKE_PREFIX_PATH ${VEKTRIX_DEP_SEARCH_PATH} ${CMAKE_PREFIX_PATH})
set(CMAKE_FRAMEWORK_PATH ${VEKTRIX_DEP_SEARCH_PATH} ${CMAKE_FRAMEWORK_PATH})

#######################################################################
# Core dependencies
#######################################################################

# Find zlib
find_package(ZLIB)
macro_log_feature(ZLIB_FOUND "zlib" "Simple data compression library" "http://www.zlib.net" FALSE "" "")

# Find X11
if (UNIX)
	find_package(X11)
	macro_log_feature(X11_FOUND "X11" "X Window system" "http://www.x.org" TRUE "" "")
	macro_log_feature(X11_Xt_FOUND "Xt" "X Toolkit" "http://www.x.org" TRUE "" "")
	find_library(XAW_LIBRARY NAMES Xaw Xaw7 PATHS ${DEP_LIB_SEARCH_DIR} ${X11_LIB_SEARCH_PATH})
	macro_log_feature(XAW_LIBRARY "Xaw" "X11 Athena widget set" "http://www.x.org" TRUE "" "")
  mark_as_advanced(XAW_LIBRARY)
endif ()


#######################################################################
# Plugin dependencies
#######################################################################

# Find Cairo
find_package(Cairo)
macro_log_feature(Cairo_FOUND "cairo" "Support for vector graphics output" "http://cairographics.org/" FALSE "" "")

# Find Caspin
find_package(Caspin)
macro_log_feature(Caspin_FOUND "caspin" "Support for ActionScript3" "http://fuse-software.com/" FALSE "" "")

# Find cURL
find_package(Curl)
macro_log_feature(Curl_FOUND "curl" "Support for accessing HTTP external resources" "http://curl.haxx.se/" FALSE "" "")

# Find expat
find_package(Expat)
macro_log_feature(Expat_FOUND "expat" "Support for parsing XML files" "http://expat.sourceforge.net/" FALSE "" "")

# Find FreeImage
find_package(FreeImage)
macro_log_feature(FreeImage_FOUND "freeimage" "Support for commonly used graphics image formats" "http://freeimage.sourceforge.net" FALSE "" "")

# Find OGRE
find_package(OGRE)
macro_log_feature(OGRE_FOUND "ogre" "Support for the open source graphics engine" "http://ogre3d.com/" FALSE "" "")

# Find Boost
# Prefer static linking in all cases
if (WIN32 OR APPLE)
	set(Boost_USE_STATIC_LIBS TRUE)
else ()
	# Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
	set(Boost_USE_STATIC_LIBS ${VEKTRIX_STATIC})
endif ()
if (APPLE)
	if(VEKTRIX_BUILD_PLATFORM_IPHONE)
		set(Boost_COMPILER "-xgcc42")
	else()
	    # Boost tries to detect the gcc compiler version by calling the command-line
	    # However we build with gcc 4.0 for OS X 10.4 compatibility, command-line default might be different
		set(Boost_COMPILER "-xgcc40")
	endif()
endif()
set(Boost_ADDITIONAL_VERSIONS "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
# Components that need linking (NB does not include header-only components like bind)
set(VEKTRIX_BOOST_COMPONENTS thread date_time)
find_package(Boost COMPONENTS ${VEKTRIX_BOOST_COMPONENTS} QUIET)
if (NOT Boost_FOUND)
	# Try again with the other type of libs
	if(Boost_USE_STATIC_LIBS)
		set(Boost_USE_STATIC_LIBS)
	else()
		set(Boost_USE_STATIC_LIBS ON)
	endif()
	find_package(Boost COMPONENTS ${VEKTRIX_BOOST_COMPONENTS} QUIET)
endif()
find_package(Boost QUIET)

# Optional Boost libs (Boost_${COMPONENT}_FOUND
macro_log_feature(Boost_FOUND "boost" "Boost (general)" "http://boost.org" FALSE "" "")
macro_log_feature(Boost_THREAD_FOUND "boost-thread" "Used for threading support" "http://boost.org" FALSE "" "")
macro_log_feature(Boost_DATE_TIME_FOUND "boost-date_time" "Used for threading support" "http://boost.org" FALSE "" "")

#######################################################################
# Samples dependencies
#######################################################################

# Find DirectX
if(WIN32)
	find_package(DirectX)
	macro_log_feature(DirectX_FOUND "DirectX" "Support for the DirectX demo" "http://msdn.microsoft.com/en-us/directx/" FALSE "" "")
endif()

#######################################################################
# Tools
#######################################################################

find_package(Doxygen)
macro_log_feature(DOXYGEN_FOUND "Doxygen" "Tool for building API documentation" "http://doxygen.org" FALSE "" "")

# Display results, terminate if anything required is missing
MACRO_DISPLAY_FEATURE_LOG()

# Add library and include paths from the dependencies
include_directories(
  ${ZLIB_INCLUDE_DIRS}
  ${Cairo_INCLUDE_DIRS}
  ${Caspin_INCLUDE_DIRS}
  ${Curl_INCLUDE_DIRS}
  ${Expat_INCLUDE_DIRS}
  ${FreeImage_INCLUDE_DIRS}
  ${OGRE_INCLUDE_DIRS}
  ${DirectX_INCLUDE_DIRS}
)

link_directories(
  ${DirectX_LIBRARY_DIRS}
)

if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
endif ()

# provide option to install dependencies on Windows
include(InstallDependencies)
