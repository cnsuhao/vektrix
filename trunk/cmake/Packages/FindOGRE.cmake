#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# - Try to find OGRE
# If you have multiple versions of Ogre installed, use the CMake or
# the environment variable OGRE_HOME to point to the path where the
# desired Ogre version can be found.
# By default this script will look for a dynamic Ogre build. If you
# need to link against static Ogre libraries, set the CMake variable
# OGRE_STATIC to TRUE.
#
# Once done, this will define
#
#  OGRE_FOUND - system has OGRE
#  OGRE_INCLUDE_DIRS - the OGRE include directories 
#  OGRE_LIBRARIES - link these to use the OGRE core
#  OGRE_BINARY_REL - location of the main Ogre binary (win32 non-static only, release)
#  OGRE_BINARY_DBG - location of the main Ogre binaries (win32 non-static only, debug)

include(FindPkgMacros)
include(PreprocessorUtils)
findpkg_begin(OGRE)


# Get path, convert backslashes as ${ENV_${var}}
getenv_path(OGRE_HOME)
getenv_path(OGRE_SDK)
getenv_path(OGRE_SOURCE)
getenv_path(OGRE_BUILD)
getenv_path(OGRE_DEPENDENCIES_DIR)
getenv_path(PROGRAMFILES)

# Determine whether to search for a dynamic or static build
if (OGRE_STATIC)
  set(OGRE_LIB_SUFFIX "Static")
else ()
  set(OGRE_LIB_SUFFIX "")
endif ()


set(OGRE_LIBRARY_NAMES "OgreMain${OGRE_LIB_SUFFIX}")
get_debug_names(OGRE_LIBRARY_NAMES)

# construct search paths from environmental hints and
# OS specific guesses
if (WIN32)
  set(OGRE_PREFIX_GUESSES
    ${ENV_PROGRAMFILES}/OGRE
    C:/OgreSDK
  )
elseif (UNIX)
  set(OGRE_PREFIX_GUESSES
    /opt/ogre
    /opt/OGRE
    /usr/lib/ogre
    /usr/lib/OGRE
    /usr/local/lib/ogre
    /usr/local/lib/OGRE
    $ENV{HOME}/ogre
    $ENV{HOME}/OGRE
  )
endif ()
set(OGRE_PREFIX_PATH
  ${OGRE_HOME} ${OGRE_SDK} ${ENV_OGRE_HOME} ${ENV_OGRE_SDK}
  ${OGRE_PREFIX_GUESSES}
)
create_search_paths(OGRE)
# If both OGRE_BUILD and OGRE_SOURCE are set, prepare to find Ogre in a build dir
set(OGRE_PREFIX_SOURCE ${OGRE_SOURCE} ${ENV_OGRE_SOURCE})
set(OGRE_PREFIX_BUILD ${OGRE_BUILD} ${ENV_OGRE_BUILD})
set(OGRE_PREFIX_DEPENDENCIES_DIR ${OGRE_DEPENDENCIES_DIR} ${ENV_OGRE_DEPENDENCIES_DIR})
if (OGRE_PREFIX_SOURCE AND OGRE_PREFIX_BUILD)
  foreach(dir ${OGRE_PREFIX_SOURCE})
    set(OGRE_INC_SEARCH_PATH ${dir}/OgreMain/include ${dir}/Dependencies/include ${dir}/iPhoneDependencies/include ${OGRE_INC_SEARCH_PATH})
    set(OGRE_LIB_SEARCH_PATH ${dir}/lib ${dir}/Dependencies/lib ${dir}/iPhoneDependencies/lib ${OGRE_LIB_SEARCH_PATH})
    set(OGRE_BIN_SEARCH_PATH ${dir}/Samples/Common/bin ${OGRE_BIN_SEARCH_PATH})
  endforeach(dir)
  foreach(dir ${OGRE_PREFIX_BUILD})
    set(OGRE_INC_SEARCH_PATH ${dir}/include ${OGRE_INC_SEARCH_PATH})
    set(OGRE_LIB_SEARCH_PATH ${dir}/lib ${OGRE_LIB_SEARCH_PATH})
    set(OGRE_BIN_SEARCH_PATH ${dir}/bin ${OGRE_BIN_SEARCH_PATH})
	set(OGRE_BIN_SEARCH_PATH ${dir}/Samples/Common/bin ${OGRE_BIN_SEARCH_PATH})
  endforeach(dir)
  
  if (OGRE_PREFIX_DEPENDENCIES_DIR)
    set(OGRE_INC_SEARCH_PATH ${OGRE_PREFIX_DEPENDENCIES_DIR}/include ${OGRE_INC_SEARCH_PATH})
    set(OGRE_LIB_SEARCH_PATH ${OGRE_PREFIX_DEPENDENCIES_DIR}/lib ${OGRE_LIB_SEARCH_PATH})
    set(OGRE_BIN_SEARCH_PATH ${OGRE_PREFIX_DEPENDENCIES_DIR}/bin ${OGRE_BIN_SEARCH_PATH})
  endif()
else()
  set(OGRE_PREFIX_SOURCE "NOTFOUND")
  set(OGRE_PREFIX_BUILD "NOTFOUND")
endif ()

# redo search if any of the environmental hints changed
set(OGRE_PREFIX_WATCH ${OGRE_PREFIX_PATH} ${OGRE_PREFIX_SOURCE} ${OGRE_PREFIX_BUILD})
clear_if_changed(OGRE_PREFIX_WATCH ${OGRE_RESET_VARS})

# try to locate Ogre via pkg-config
use_pkgconfig(OGRE_PKGC "OGRE${OGRE_LIB_SUFFIX}")

if(NOT OGRE_BUILD_PLATFORM_IPHONE)
  # try to find framework on OSX
  findpkg_framework(OGRE)
else()
	set(OGRE_LIBRARY_FWK "")
endif()

# locate Ogre include files
find_path(OGRE_CONFIG_INCLUDE_DIR NAMES OgreBuildSettings.h HINTS ${OGRE_INC_SEARCH_PATH} ${OGRE_FRAMEWORK_INCLUDES} ${OGRE_PKGC_INCLUDE_DIRS} PATH_SUFFIXES "OGRE")
find_path(OGRE_INCLUDE_DIR NAMES OgreRoot.h HINTS ${OGRE_CONFIG_INCLUDE_DIR} ${OGRE_INC_SEARCH_PATH} ${OGRE_FRAMEWORK_INCLUDES} ${OGRE_PKGC_INCLUDE_DIRS} PATH_SUFFIXES "OGRE")
set(OGRE_INCOMPATIBLE FALSE)

if (OGRE_INCLUDE_DIR)
  if (NOT OGRE_CONFIG_INCLUDE_DIR)
    set(OGRE_CONFIG_INCLUDE_DIR ${OGRE_INCLUDE_DIR})
  endif ()
  # determine Ogre version
  file(READ ${OGRE_INCLUDE_DIR}/OgrePrerequisites.h OGRE_TEMP_VERSION_CONTENT)
  get_preprocessor_entry(OGRE_TEMP_VERSION_CONTENT OGRE_VERSION_MAJOR OGRE_VERSION_MAJOR)
  get_preprocessor_entry(OGRE_TEMP_VERSION_CONTENT OGRE_VERSION_MINOR OGRE_VERSION_MINOR)
  get_preprocessor_entry(OGRE_TEMP_VERSION_CONTENT OGRE_VERSION_PATCH OGRE_VERSION_PATCH)
  get_preprocessor_entry(OGRE_TEMP_VERSION_CONTENT OGRE_VERSION_NAME OGRE_VERSION_NAME)
  set(OGRE_VERSION "${OGRE_VERSION_MAJOR}.${OGRE_VERSION_MINOR}.${OGRE_VERSION_PATCH}")
  pkg_message(OGRE "Found Ogre ${OGRE_VERSION_NAME} (${OGRE_VERSION})")

  # determine configuration settings
  set(OGRE_CONFIG_HEADERS
    ${OGRE_CONFIG_INCLUDE_DIR}/OgreBuildSettings.h
    ${OGRE_CONFIG_INCLUDE_DIR}/OgreConfig.h
  )
  foreach(CFG_FILE ${OGRE_CONFIG_HEADERS})
    if (EXISTS ${CFG_FILE})
      set(OGRE_CONFIG_HEADER ${CFG_FILE})
      break()
    endif()
  endforeach()
  if (OGRE_CONFIG_HEADER)
    file(READ ${OGRE_CONFIG_HEADER} OGRE_TEMP_CONFIG_CONTENT)
    has_preprocessor_entry(OGRE_TEMP_CONFIG_CONTENT OGRE_STATIC_LIB OGRE_CONFIG_STATIC)
    get_preprocessor_entry(OGRE_TEMP_CONFIG_CONTENT OGRE_THREAD_SUPPORT OGRE_CONFIG_THREADS)
    get_preprocessor_entry(OGRE_TEMP_CONFIG_CONTENT OGRE_THREAD_PROVIDER OGRE_CONFIG_THREAD_PROVIDER)
    get_preprocessor_entry(OGRE_TEMP_CONFIG_CONTENT OGRE_NO_FREEIMAGE OGRE_CONFIG_FREEIMAGE)
    if (OGRE_CONFIG_STATIC AND OGRE_STATIC)
    elseif (OGRE_CONFIG_STATIC OR OGRE_STATIC)
      pkg_message(OGRE "Build type (static, dynamic) does not match the requested one.")
      set(OGRE_INCOMPATIBLE TRUE)
    endif ()
  else ()
    pkg_message(OGRE "Could not determine Ogre build configuration.")
    set(OGRE_INCOMPATIBLE TRUE)
  endif ()
else ()
  set(OGRE_INCOMPATIBLE FALSE)
endif ()

find_library(OGRE_LIBRARY_REL NAMES ${OGRE_LIBRARY_NAMES} HINTS ${OGRE_LIB_SEARCH_PATH} ${OGRE_PKGC_LIBRARY_DIRS} ${OGRE_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "release" "relwithdebinfo" "minsizerel")
find_library(OGRE_LIBRARY_DBG NAMES ${OGRE_LIBRARY_NAMES_DBG} HINTS ${OGRE_LIB_SEARCH_PATH} ${OGRE_PKGC_LIBRARY_DIRS} ${OGRE_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "debug")
make_library_set(OGRE_LIBRARY)

if(APPLE)
  set(OGRE_LIBRARY_DBG ${OGRE_LIB_SEARCH_PATH})
endif()
if (OGRE_INCOMPATIBLE)
  set(OGRE_LIBRARY "NOTFOUND")
endif ()

set(OGRE_INCLUDE_DIR ${OGRE_CONFIG_INCLUDE_DIR} ${OGRE_INCLUDE_DIR})
list(REMOVE_DUPLICATES OGRE_INCLUDE_DIR)
findpkg_finish(OGRE)
add_parent_dir(OGRE_INCLUDE_DIRS OGRE_INCLUDE_DIR)
if (OGRE_SOURCE)
	# If working from source rather than SDK, add samples include
	set(OGRE_INCLUDE_DIRS ${OGRE_INCLUDE_DIRS} "${OGRE_SOURCE}/Samples/Common/include")
endif()

mark_as_advanced(OGRE_CONFIG_INCLUDE_DIR OGRE_MEDIA_DIR OGRE_PLUGIN_DIR_REL OGRE_PLUGIN_DIR_DBG)

if (NOT OGRE_FOUND)
  return()
endif ()


# look for required Ogre dependencies in case of static build and/or threading
if (OGRE_STATIC)
  set(OGRE_DEPS_FOUND TRUE)
  find_package(Cg QUIET)
  find_package(DirectX QUIET)
  find_package(FreeImage QUIET)
  find_package(Freetype QUIET)
  find_package(OpenGL QUIET)
  find_package(OpenGLES QUIET)
  find_package(ZLIB QUIET)
  find_package(ZZip QUIET)
  if (UNIX AND NOT APPLE)
    find_package(X11 QUIET)
    find_library(XAW_LIBRARY NAMES Xaw Xaw7 PATHS ${DEP_LIB_SEARCH_DIR} ${X11_LIB_SEARCH_PATH})
    if (NOT XAW_LIBRARY OR NOT X11_Xt_FOUND)
      set(X11_FOUND FALSE)
    endif ()
  endif ()
  if (APPLE AND NOT OGRE_BUILD_PLATFORM_IPHONE)
    find_package(Cocoa QUIET)
    find_package(Carbon QUIET)
    if (NOT Cocoa_FOUND OR NOT Carbon_FOUND)
      set(OGRE_DEPS_FOUND FALSE)
    endif ()
  endif ()
  if (APPLE AND OGRE_BUILD_PLATFORM_IPHONE)
    find_package(iPhoneSDK QUIET)
    if (NOT iPhoneSDK_FOUND)
      set(OGRE_DEPS_FOUND FALSE)
    endif ()
  endif ()

  set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${OGRE_LIBRARY_FWK} ${ZZip_LIBRARIES} ${ZLIB_LIBRARIES} 
    ${FreeImage_LIBRARIES} ${FREETYPE_LIBRARIES} 
    ${X11_LIBRARIES} ${X11_Xt_LIBRARIES} ${XAW_LIBRARY} ${X11_Xrandr_LIB}
    ${Cocoa_LIBRARIES} ${Carbon_LIBRARIES})

  if (NOT ZLIB_FOUND OR NOT ZZip_FOUND)
    set(OGRE_DEPS_FOUND FALSE)
  endif ()
  if (NOT FreeImage_FOUND AND NOT OGRE_CONFIG_FREEIMAGE)
    set(OGRE_DEPS_FOUND FALSE)
  endif ()
  if (NOT FREETYPE_FOUND)
    set(OGRE_DEPS_FOUND FALSE)
  endif ()
  if (UNIX AND NOT APPLE)
	if (NOT X11_FOUND)
      set(OGRE_DEPS_FOUND FALSE)
	endif ()
  endif ()

  if (OGRE_CONFIG_THREADS)
    if (OGRE_CONFIG_THREAD_PROVIDER EQUAL 1)
      find_package(Boost COMPONENTS thread QUIET)
      if (NOT Boost_THREAD_FOUND)
        set(OGRE_DEPS_FOUND FALSE)
      else ()
        set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
      endif ()
    elseif (OGRE_CONFIG_THREAD_PROVIDER EQUAL 2)
      find_package(POCO QUIET)
      if (NOT POCO_FOUND)
        set(OGRE_DEPS_FOUND FALSE)
      else ()
        set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${POCO_LIBRARIES})
      endif ()
    elseif (OGRE_CONFIG_THREAD_PROVIDER EQUAL 3)
      find_package(TBB QUIET)
      if (NOT TBB_FOUND)
        set(OGRE_DEPS_FOUND FALSE)
      else ()
        set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${TBB_LIBRARIES})
      endif ()
    endif ()
  endif ()
  
  if (NOT OGRE_DEPS_FOUND)
    pkg_message(OGRE "Could not find all required dependencies for the Ogre package.")
    set(OGRE_FOUND FALSE)
  endif ()
endif ()

if (NOT OGRE_FOUND)
  return()
endif ()


get_filename_component(OGRE_LIBRARY_DIR_REL "${OGRE_LIBRARY_REL}" PATH)
get_filename_component(OGRE_LIBRARY_DIR_DBG "${OGRE_LIBRARY_DBG}" PATH)
set(OGRE_LIBRARY_DIRS ${OGRE_LIBRARY_DIR_REL} ${OGRE_LIBRARY_DIR_DBG})

# find binaries
if (NOT OGRE_STATIC)
	if (WIN32)
		find_file(OGRE_BINARY_REL NAMES "OgreMain.dll" HINTS ${OGRE_BIN_SEARCH_PATH}
          PATH_SUFFIXES "" release relwithdebinfo minsizerel)
		find_file(OGRE_BINARY_DBG NAMES "OgreMain_d.dll" HINTS ${OGRE_BIN_SEARCH_PATH}
          PATH_SUFFIXES "" debug )
	endif()
	mark_as_advanced(OGRE_BINARY_REL OGRE_BINARY_DBG)
endif()

if (OGRE_STATIC)
  # check if dependencies for plugins are met
  if (NOT DirectX_FOUND)
    set(OGRE_RenderSystem_Direct3D9_FOUND FALSE)
  endif ()
  if (NOT DirectX_D3D10_FOUND)
    set(OGRE_RenderSystem_Direct3D10_FOUND FALSE)
  endif ()
  if (NOT DirectX_D3D11_FOUND)
    set(OGRE_RenderSystem_Direct3D11_FOUND FALSE)
  endif ()
  if (NOT OPENGL_FOUND)
    set(OGRE_RenderSystem_GL_FOUND FALSE)
  endif ()
  if (NOT OPENGLES_FOUND AND NOT OPENGLES2_FOUND)
    set(OGRE_RenderSystem_GLES_FOUND FALSE)
  endif ()
  if (NOT Cg_FOUND)
    set(OGRE_Plugin_CgProgramManager_FOUND FALSE)
  endif ()
  
  set(OGRE_RenderSystem_Direct3D9_LIBRARIES ${OGRE_RenderSystem_Direct3D9_LIBRARIES}
    ${DirectX_LIBRARIES}
  )
  set(OGRE_RenderSystem_Direct3D10_LIBRARIES ${OGRE_RenderSystem_Direct3D10_LIBRARIES}
    ${DirectX_D3D10_LIBRARIES}
  )
  set(OGRE_RenderSystem_Direct3D11_LIBRARIES ${OGRE_RenderSystem_Direct3D11_LIBRARIES}
    ${DirectX_D3D11_LIBRARIES}
  )
  set(OGRE_RenderSystem_GL_LIBRARIES ${OGRE_RenderSystem_GL_LIBRARIES}
    ${OPENGL_LIBRARIES}
  )
  set(OGRE_RenderSystem_GLES_LIBRARIES ${OGRE_RenderSystem_GLES_LIBRARIES}
    ${OPENGLES_LIBRARIES}
  )
  set(OGRE_Plugin_CgProgramManager_LIBRARIES ${OGRE_Plugin_CgProgramManager_LIBRARIES}
    ${Cg_LIBRARIES}
  )
endif ()

# look for the media directory
set(OGRE_MEDIA_SEARCH_PATH
  ${OGRE_SOURCE}
  ${OGRE_LIBRARY_DIR_REL}/..
  ${OGRE_LIBRARY_DIR_DBG}/..
  ${OGRE_LIBRARY_DIR_REL}/../..
  ${OGRE_LIBRARY_DIR_DBG}/../..
  ${OGRE_PREFIX_SOURCE}
)
set(OGRE_MEDIA_SEARCH_SUFFIX
  Samples/Media
  Media
  media
  share/OGRE/media
)

clear_if_changed(OGRE_PREFIX_WATCH OGRE_MEDIA_DIR)
find_path(OGRE_MEDIA_DIR NAMES packs/cubemapsJS.zip HINTS ${OGRE_MEDIA_SEARCH_PATH}
  PATHS ${OGRE_PREFIX_PATH} PATH_SUFFIXES ${OGRE_MEDIA_SEARCH_SUFFIX})
