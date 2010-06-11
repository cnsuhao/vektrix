#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# - Try to find Vektrix
#
# Once done, this will define
#
#  Vektrix_FOUND - system has Vektrix
#  Vektrix_INCLUDE_DIRS - the Vektrix include directories 
#  Vektrix_LIBRARIES - link these to use the Vektrix core
#  Vektrix_BINARY_REL - location of the main Vektrix binary (win32 non-static only, release)
#  Vektrix_BINARY_DBG - location of the main Vektrix binaries (win32 non-static only, debug)
#
# Additionally this script searches for the following optional
# parts of the Vektrix package:
#  vektrix_AS3Plugin,
#  vektrix_CairoPlugin,
#  vektrix_cURLPlugin,
#  vektrix_D3D9Plugin,
#  vektrix_FreeImgPlugin,
#  vektrix_OgrePlugin,
#  vektrix_SwfPlugin,
#  vektrix_XmlPlugin,
#
# For each of these components, the following variables are defined:
#
#  Vektrix_${COMPONENT}_FOUND - ${COMPONENT} is available
#  Vektrix_${COMPONENT}_INCLUDE_DIRS - additional include directories for ${COMPONENT}
#  Vektrix_${COMPONENT}_LIBRARIES - link these to use ${COMPONENT} 
#  Vektrix_${COMPONENT}_BINARY_REL - location of the component binary (win32 non-static only, release)
#  Vektrix_${COMPONENT}_BINARY_DBG - location of the component binary (win32 non-static only, debug)
#
# Finally, the following variables are defined:
#
#  Vektrix_PLUGIN_DIR_REL - The directory where the release versions of
#       the Vektrix plugins are located
#  Vektrix_PLUGIN_DIR_DBG - The directory where the debug versions of
#       the Vektrix plugins are located
#  Vektrix_MEDIA_DIR - The directory where the Vektrix sample media is
#       located, if available

include(FindPkgMacros)
include(PreprocessorUtils)
findpkg_begin(Vektrix)


# Get path, convert backslashes as ${ENV_${var}}
getenv_path(VEKTRIX_HOME)
getenv_path(VEKTRIX_SDK)
getenv_path(VEKTRIX_SOURCE)
getenv_path(VEKTRIX_BUILD)
getenv_path(VEKTRIX_DEPENDENCIES_DIR)
getenv_path(PROGRAMFILES)

# Determine whether to search for a dynamic or static build
if (VEKTRIX_STATIC)
  set(VEKTRIX_LIB_SUFFIX "Static")
else ()
  set(VEKTRIX_LIB_SUFFIX "")
endif ()


set(VEKTRIX_LIBRARY_NAMES "VektrixCore${VEKTRIX_LIB_SUFFIX}")
get_debug_names(VEKTRIX_LIBRARY_NAMES)

# construct search paths from environmental hints and
# OS specific guesses
if (WIN32)
  set(VEKTRIX_PREFIX_GUESSES
    ${ENV_PROGRAMFILES}/Vektrix
    C:/VektrixSDK
  )
elseif (UNIX)
  set(VEKTRIX_PREFIX_GUESSES
    /opt/vektrix
    /opt/VEKTRIX
    /usr/lib/vektrix
    /usr/lib/VEKTRIX
    /usr/local/lib/vektrix
    /usr/local/lib/VEKTRIX
    $ENV{HOME}/vektrix
    $ENV{HOME}/VEKTRIX
  )
endif ()
set(VEKTRIX_PREFIX_PATH
  ${VEKTRIX_HOME} ${VEKTRIX_SDK} ${ENV_VEKTRIX_HOME} ${ENV_VEKTRIX_SDK}
  ${VEKTRIX_PREFIX_GUESSES}
)
create_search_paths(VEKTRIX)
# If both VEKTRIX_BUILD and VEKTRIX_SOURCE are set, prepare to find Ogre in a build dir
set(VEKTRIX_PREFIX_SOURCE ${VEKTRIX_SOURCE} ${ENV_VEKTRIX_SOURCE})
set(VEKTRIX_PREFIX_BUILD ${VEKTRIX_BUILD} ${ENV_VEKTRIX_BUILD})
set(VEKTRIX_PREFIX_DEPENDENCIES_DIR ${VEKTRIX_DEPENDENCIES_DIR} ${ENV_VEKTRIX_DEPENDENCIES_DIR})
if (VEKTRIX_PREFIX_SOURCE AND VEKTRIX_PREFIX_BUILD)
  foreach(dir ${VEKTRIX_PREFIX_SOURCE})
    set(VEKTRIX_INC_SEARCH_PATH ${dir}/OgreMain/include ${dir}/Dependencies/include ${dir}/iPhoneDependencies/include ${VEKTRIX_INC_SEARCH_PATH})
    set(VEKTRIX_LIB_SEARCH_PATH ${dir}/lib ${dir}/Dependencies/lib ${dir}/iPhoneDependencies/lib ${VEKTRIX_LIB_SEARCH_PATH})
    set(VEKTRIX_BIN_SEARCH_PATH ${dir}/Samples/Common/bin ${VEKTRIX_BIN_SEARCH_PATH})
  endforeach(dir)
  foreach(dir ${VEKTRIX_PREFIX_BUILD})
    set(VEKTRIX_INC_SEARCH_PATH ${dir}/include ${VEKTRIX_INC_SEARCH_PATH})
    set(VEKTRIX_LIB_SEARCH_PATH ${dir}/lib ${VEKTRIX_LIB_SEARCH_PATH})
    set(VEKTRIX_BIN_SEARCH_PATH ${dir}/bin ${VEKTRIX_BIN_SEARCH_PATH})
	set(VEKTRIX_BIN_SEARCH_PATH ${dir}/Samples/Common/bin ${VEKTRIX_BIN_SEARCH_PATH})
  endforeach(dir)
  
  if (VEKTRIX_PREFIX_DEPENDENCIES_DIR)
    set(VEKTRIX_INC_SEARCH_PATH ${VEKTRIX_PREFIX_DEPENDENCIES_DIR}/include ${VEKTRIX_INC_SEARCH_PATH})
    set(VEKTRIX_LIB_SEARCH_PATH ${VEKTRIX_PREFIX_DEPENDENCIES_DIR}/lib ${VEKTRIX_LIB_SEARCH_PATH})
    set(VEKTRIX_BIN_SEARCH_PATH ${VEKTRIX_PREFIX_DEPENDENCIES_DIR}/bin ${VEKTRIX_BIN_SEARCH_PATH})
  endif()
else()
  set(VEKTRIX_PREFIX_SOURCE "NOTFOUND")
  set(VEKTRIX_PREFIX_BUILD "NOTFOUND")
endif ()

# redo search if any of the environmental hints changed
set(VEKTRIX_COMPONENTS Paging Terrain 
  Plugin_BSPSceneManager Plugin_CgProgramManager Plugin_OctreeSceneManager
  Plugin_OctreeZone Plugin_PCZSceneManager Plugin_ParticleFX
  RenderSystem_Direct3D10 RenderSystem_Direct3D9 RenderSystem_GL RenderSystem_GLES)
set(VEKTRIX_RESET_VARS 
  VEKTRIX_CONFIG_INCLUDE_DIR VEKTRIX_INCLUDE_DIR 
  VEKTRIX_LIBRARY_FWK VEKTRIX_LIBRARY_REL VEKTRIX_LIBRARY_DBG
  VEKTRIX_PLUGIN_DIR_DBG VEKTRIX_PLUGIN_DIR_REL VEKTRIX_MEDIA_DIR)
foreach (comp ${VEKTRIX_COMPONENTS})
  set(VEKTRIX_RESET_VARS ${VEKTRIX_RESET_VARS}
    VEKTRIX_${comp}_INCLUDE_DIR VEKTRIX_${comp}_LIBRARY_FWK
    VEKTRIX_${comp}_LIBRARY_DBG VEKTRIX_${comp}_LIBRARY_REL
  )
endforeach (comp)
set(VEKTRIX_PREFIX_WATCH ${VEKTRIX_PREFIX_PATH} ${VEKTRIX_PREFIX_SOURCE} ${VEKTRIX_PREFIX_BUILD})
clear_if_changed(VEKTRIX_PREFIX_WATCH ${VEKTRIX_RESET_VARS})

# try to locate Ogre via pkg-config
use_pkgconfig(VEKTRIX_PKGC "OGRE${VEKTRIX_LIB_SUFFIX}")

if(NOT VEKTRIX_BUILD_PLATFORM_IPHONE)
  # try to find framework on OSX
  findpkg_framework(OGRE)
else()
	set(VEKTRIX_LIBRARY_FWK "")
endif()

# locate Ogre include files
find_path(VEKTRIX_CONFIG_INCLUDE_DIR NAMES OgreBuildSettings.h HINTS ${VEKTRIX_INC_SEARCH_PATH} ${VEKTRIX_FRAMEWORK_INCLUDES} ${VEKTRIX_PKGC_INCLUDE_DIRS} PATH_SUFFIXES "OGRE")
find_path(VEKTRIX_INCLUDE_DIR NAMES OgreRoot.h HINTS ${VEKTRIX_CONFIG_INCLUDE_DIR} ${VEKTRIX_INC_SEARCH_PATH} ${VEKTRIX_FRAMEWORK_INCLUDES} ${VEKTRIX_PKGC_INCLUDE_DIRS} PATH_SUFFIXES "OGRE")
set(VEKTRIX_INCOMPATIBLE FALSE)

if (VEKTRIX_INCLUDE_DIR)
  if (NOT VEKTRIX_CONFIG_INCLUDE_DIR)
    set(VEKTRIX_CONFIG_INCLUDE_DIR ${VEKTRIX_INCLUDE_DIR})
  endif ()
  # determine Ogre version
  file(READ ${VEKTRIX_INCLUDE_DIR}/OgrePrerequisites.h VEKTRIX_TEMP_VERSION_CONTENT)
  get_preprocessor_entry(VEKTRIX_TEMP_VERSION_CONTENT VEKTRIX_VERSION_MAJOR VEKTRIX_VERSION_MAJOR)
  get_preprocessor_entry(VEKTRIX_TEMP_VERSION_CONTENT VEKTRIX_VERSION_MINOR VEKTRIX_VERSION_MINOR)
  get_preprocessor_entry(VEKTRIX_TEMP_VERSION_CONTENT VEKTRIX_VERSION_PATCH VEKTRIX_VERSION_PATCH)
  get_preprocessor_entry(VEKTRIX_TEMP_VERSION_CONTENT VEKTRIX_VERSION_NAME VEKTRIX_VERSION_NAME)
  set(VEKTRIX_VERSION "${VEKTRIX_VERSION_MAJOR}.${VEKTRIX_VERSION_MINOR}.${VEKTRIX_VERSION_PATCH}")
  pkg_message(OGRE "Found Ogre ${VEKTRIX_VERSION_NAME} (${VEKTRIX_VERSION})")

  # determine configuration settings
  set(VEKTRIX_CONFIG_HEADERS
    ${VEKTRIX_CONFIG_INCLUDE_DIR}/OgreBuildSettings.h
    ${VEKTRIX_CONFIG_INCLUDE_DIR}/OgreConfig.h
  )
  foreach(CFG_FILE ${VEKTRIX_CONFIG_HEADERS})
    if (EXISTS ${CFG_FILE})
      set(VEKTRIX_CONFIG_HEADER ${CFG_FILE})
      break()
    endif()
  endforeach()
  if (VEKTRIX_CONFIG_HEADER)
    file(READ ${VEKTRIX_CONFIG_HEADER} VEKTRIX_TEMP_CONFIG_CONTENT)
    has_preprocessor_entry(VEKTRIX_TEMP_CONFIG_CONTENT VEKTRIX_STATIC_LIB VEKTRIX_CONFIG_STATIC)
    get_preprocessor_entry(VEKTRIX_TEMP_CONFIG_CONTENT VEKTRIX_THREAD_SUPPORT VEKTRIX_CONFIG_THREADS)
    get_preprocessor_entry(VEKTRIX_TEMP_CONFIG_CONTENT VEKTRIX_THREAD_PROVIDER VEKTRIX_CONFIG_THREAD_PROVIDER)
    get_preprocessor_entry(VEKTRIX_TEMP_CONFIG_CONTENT VEKTRIX_NO_FREEIMAGE VEKTRIX_CONFIG_FREEIMAGE)
    if (VEKTRIX_CONFIG_STATIC AND VEKTRIX_STATIC)
    elseif (VEKTRIX_CONFIG_STATIC OR VEKTRIX_STATIC)
      pkg_message(OGRE "Build type (static, dynamic) does not match the requested one.")
      set(VEKTRIX_INCOMPATIBLE TRUE)
    endif ()
  else ()
    pkg_message(OGRE "Could not determine Ogre build configuration.")
    set(VEKTRIX_INCOMPATIBLE TRUE)
  endif ()
else ()
  set(VEKTRIX_INCOMPATIBLE FALSE)
endif ()

find_library(VEKTRIX_LIBRARY_REL NAMES ${VEKTRIX_LIBRARY_NAMES} HINTS ${VEKTRIX_LIB_SEARCH_PATH} ${VEKTRIX_PKGC_LIBRARY_DIRS} ${VEKTRIX_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "release" "relwithdebinfo" "minsizerel")
find_library(VEKTRIX_LIBRARY_DBG NAMES ${VEKTRIX_LIBRARY_NAMES_DBG} HINTS ${VEKTRIX_LIB_SEARCH_PATH} ${VEKTRIX_PKGC_LIBRARY_DIRS} ${VEKTRIX_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "debug")
make_library_set(VEKTRIX_LIBRARY)

if(APPLE)
  set(VEKTRIX_LIBRARY_DBG ${VEKTRIX_LIB_SEARCH_PATH})
endif()
if (VEKTRIX_INCOMPATIBLE)
  set(VEKTRIX_LIBRARY "NOTFOUND")
endif ()

set(VEKTRIX_INCLUDE_DIR ${VEKTRIX_CONFIG_INCLUDE_DIR} ${VEKTRIX_INCLUDE_DIR})
list(REMOVE_DUPLICATES VEKTRIX_INCLUDE_DIR)
findpkg_finish(OGRE)
add_parent_dir(VEKTRIX_INCLUDE_DIRS VEKTRIX_INCLUDE_DIR)
if (VEKTRIX_SOURCE)
	# If working from source rather than SDK, add samples include
	set(VEKTRIX_INCLUDE_DIRS ${VEKTRIX_INCLUDE_DIRS} "${VEKTRIX_SOURCE}/Samples/Common/include")
endif()

mark_as_advanced(VEKTRIX_CONFIG_INCLUDE_DIR VEKTRIX_MEDIA_DIR VEKTRIX_PLUGIN_DIR_REL VEKTRIX_PLUGIN_DIR_DBG)

if (NOT VEKTRIX_FOUND)
  return()
endif ()


# look for required Ogre dependencies in case of static build and/or threading
if (VEKTRIX_STATIC)
  set(VEKTRIX_DEPS_FOUND TRUE)
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
  if (APPLE AND NOT VEKTRIX_BUILD_PLATFORM_IPHONE)
    find_package(Cocoa QUIET)
    find_package(Carbon QUIET)
    if (NOT Cocoa_FOUND OR NOT Carbon_FOUND)
      set(VEKTRIX_DEPS_FOUND FALSE)
    endif ()
  endif ()
  if (APPLE AND VEKTRIX_BUILD_PLATFORM_IPHONE)
    find_package(iPhoneSDK QUIET)
    if (NOT iPhoneSDK_FOUND)
      set(VEKTRIX_DEPS_FOUND FALSE)
    endif ()
  endif ()

  set(VEKTRIX_LIBRARIES ${VEKTRIX_LIBRARIES} ${VEKTRIX_LIBRARY_FWK} ${ZZip_LIBRARIES} ${ZLIB_LIBRARIES} 
    ${FreeImage_LIBRARIES} ${FREETYPE_LIBRARIES} 
    ${X11_LIBRARIES} ${X11_Xt_LIBRARIES} ${XAW_LIBRARY} ${X11_Xrandr_LIB}
    ${Cocoa_LIBRARIES} ${Carbon_LIBRARIES})

  if (NOT ZLIB_FOUND OR NOT ZZip_FOUND)
    set(VEKTRIX_DEPS_FOUND FALSE)
  endif ()
  if (NOT FreeImage_FOUND AND NOT VEKTRIX_CONFIG_FREEIMAGE)
    set(VEKTRIX_DEPS_FOUND FALSE)
  endif ()
  if (NOT FREETYPE_FOUND)
    set(VEKTRIX_DEPS_FOUND FALSE)
  endif ()
  if (UNIX AND NOT APPLE)
	if (NOT X11_FOUND)
      set(VEKTRIX_DEPS_FOUND FALSE)
	endif ()
  endif ()

  if (VEKTRIX_CONFIG_THREADS)
    if (VEKTRIX_CONFIG_THREAD_PROVIDER EQUAL 1)
      find_package(Boost COMPONENTS thread QUIET)
      if (NOT Boost_THREAD_FOUND)
        set(VEKTRIX_DEPS_FOUND FALSE)
      else ()
        set(VEKTRIX_LIBRARIES ${VEKTRIX_LIBRARIES} ${Boost_LIBRARIES})
      endif ()
    elseif (VEKTRIX_CONFIG_THREAD_PROVIDER EQUAL 2)
      find_package(POCO QUIET)
      if (NOT POCO_FOUND)
        set(VEKTRIX_DEPS_FOUND FALSE)
      else ()
        set(VEKTRIX_LIBRARIES ${VEKTRIX_LIBRARIES} ${POCO_LIBRARIES})
      endif ()
    elseif (VEKTRIX_CONFIG_THREAD_PROVIDER EQUAL 3)
      find_package(TBB QUIET)
      if (NOT TBB_FOUND)
        set(VEKTRIX_DEPS_FOUND FALSE)
      else ()
        set(VEKTRIX_LIBRARIES ${VEKTRIX_LIBRARIES} ${TBB_LIBRARIES})
      endif ()
    endif ()
  endif ()
  
  if (NOT VEKTRIX_DEPS_FOUND)
    pkg_message(OGRE "Could not find all required dependencies for the Ogre package.")
    set(VEKTRIX_FOUND FALSE)
  endif ()
endif ()

if (NOT VEKTRIX_FOUND)
  return()
endif ()


get_filename_component(VEKTRIX_LIBRARY_DIR_REL "${VEKTRIX_LIBRARY_REL}" PATH)
get_filename_component(VEKTRIX_LIBRARY_DIR_DBG "${VEKTRIX_LIBRARY_DBG}" PATH)
set(VEKTRIX_LIBRARY_DIRS ${VEKTRIX_LIBRARY_DIR_REL} ${VEKTRIX_LIBRARY_DIR_DBG})

# find binaries
if (NOT VEKTRIX_STATIC)
	if (WIN32)
		find_file(VEKTRIX_BINARY_REL NAMES "OgreMain.dll" HINTS ${VEKTRIX_BIN_SEARCH_PATH}
          PATH_SUFFIXES "" release relwithdebinfo minsizerel)
		find_file(VEKTRIX_BINARY_DBG NAMES "OgreMain_d.dll" HINTS ${VEKTRIX_BIN_SEARCH_PATH}
          PATH_SUFFIXES "" debug )
	endif()
	mark_as_advanced(VEKTRIX_BINARY_REL VEKTRIX_BINARY_DBG)
endif()


#########################################################
# Find Vektrix plugins
#########################################################

macro(vektrix_find_plugin PLUGIN HEADER)
  # On Unix, the plugins might have no prefix
  if (CMAKE_FIND_LIBRARY_PREFIXES)
    set(TMP_CMAKE_LIB_PREFIX ${CMAKE_FIND_LIBRARY_PREFIXES})
    set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
  endif()
  
  # strip RenderSystem_ or Plugin_ prefix from plugin name
  string(REPLACE "RenderSystem_" "" PLUGIN_TEMP ${PLUGIN})
  string(REPLACE "Plugin_" "" PLUGIN_NAME ${PLUGIN_TEMP})
  
  # header files for plugins are not usually needed, but find them anyway if they are present
  set(VEKTRIX_PLUGIN_PATH_SUFFIXES
    PlugIns PlugIns/${PLUGIN_NAME} Plugins Plugins/${PLUGIN_NAME} ${PLUGIN} 
    RenderSystems RenderSystems/${PLUGIN_NAME} ${ARGN})
  find_path(VEKTRIX_${PLUGIN}_INCLUDE_DIR NAMES ${HEADER} 
    HINTS ${VEKTRIX_INCLUDE_DIRS} ${VEKTRIX_PREFIX_SOURCE}  
    PATH_SUFFIXES ${VEKTRIX_PLUGIN_PATH_SUFFIXES})
  # find link libraries for plugins
  set(VEKTRIX_${PLUGIN}_LIBRARY_NAMES "${PLUGIN}${VEKTRIX_LIB_SUFFIX}")
  get_debug_names(VEKTRIX_${PLUGIN}_LIBRARY_NAMES)
  set(VEKTRIX_${PLUGIN}_LIBRARY_FWK ${VEKTRIX_LIBRARY_FWK})
  find_library(VEKTRIX_${PLUGIN}_LIBRARY_REL NAMES ${VEKTRIX_${PLUGIN}_LIBRARY_NAMES}
    HINTS ${VEKTRIX_LIBRARY_DIRS} PATH_SUFFIXES "" OGRE opt release release/opt relwithdebinfo relwithdebinfo/opt minsizerel minsizerel/opt)
  find_library(VEKTRIX_${PLUGIN}_LIBRARY_DBG NAMES ${VEKTRIX_${PLUGIN}_LIBRARY_NAMES_DBG}
    HINTS ${VEKTRIX_LIBRARY_DIRS} PATH_SUFFIXES "" OGRE opt debug debug/opt)
  make_library_set(VEKTRIX_${PLUGIN}_LIBRARY)

  if (VEKTRIX_${PLUGIN}_LIBRARY OR VEKTRIX_${PLUGIN}_INCLUDE_DIR)
    set(VEKTRIX_${PLUGIN}_FOUND TRUE)
    if (VEKTRIX_${PLUGIN}_INCLUDE_DIR)
      set(VEKTRIX_${PLUGIN}_INCLUDE_DIRS ${VEKTRIX_${PLUGIN}_INCLUDE_DIR})
    endif()
    set(VEKTRIX_${PLUGIN}_LIBRARIES ${VEKTRIX_${PLUGIN}_LIBRARY})
  endif ()

  mark_as_advanced(VEKTRIX_${PLUGIN}_INCLUDE_DIR VEKTRIX_${PLUGIN}_LIBRARY_REL VEKTRIX_${PLUGIN}_LIBRARY_DBG VEKTRIX_${PLUGIN}_LIBRARY_FWK)

  # look for plugin dirs
  if (VEKTRIX_${PLUGIN}_FOUND)
    if (NOT VEKTRIX_PLUGIN_DIR_REL OR NOT VEKTRIX_PLUGIN_DIR_DBG)
      if (WIN32)
        set(VEKTRIX_PLUGIN_SEARCH_PATH_REL 
          ${VEKTRIX_LIBRARY_DIR_REL}/..
          ${VEKTRIX_LIBRARY_DIR_REL}/../..
		  ${VEKTRIX_BIN_SEARCH_PATH}
        )
        set(VEKTRIX_PLUGIN_SEARCH_PATH_DBG
          ${VEKTRIX_LIBRARY_DIR_DBG}/..
          ${VEKTRIX_LIBRARY_DIR_DBG}/../..
		  ${VEKTRIX_BIN_SEARCH_PATH}
        )
        find_path(VEKTRIX_PLUGIN_DIR_REL NAMES "${PLUGIN}.dll" HINTS ${VEKTRIX_PLUGIN_SEARCH_PATH_REL}
          PATH_SUFFIXES "" bin bin/release bin/relwithdebinfo bin/minsizerel release)
        find_path(VEKTRIX_PLUGIN_DIR_DBG NAMES "${PLUGIN}_d.dll" HINTS ${VEKTRIX_PLUGIN_SEARCH_PATH_DBG}
          PATH_SUFFIXES "" bin bin/debug debug)
      elseif (UNIX)
        get_filename_component(VEKTRIX_PLUGIN_DIR_TMP ${VEKTRIX_${PLUGIN}_LIBRARY_REL} PATH)
        set(VEKTRIX_PLUGIN_DIR_REL ${VEKTRIX_PLUGIN_DIR_TMP} CACHE STRING "Ogre plugin dir (release)")
        get_filename_component(VEKTRIX_PLUGIN_DIR_TMP ${VEKTRIX_${PLUGIN}_LIBRARY_DBG} PATH)
        set(VEKTRIX_PLUGIN_DIR_DBG ${VEKTRIX_PLUGIN_DIR_TMP} CACHE STRING "Ogre plugin dir (debug)")
      endif ()
    endif ()
	
	# find binaries
	if (NOT VEKTRIX_STATIC)
		if (WIN32)
			find_file(VEKTRIX_${PLUGIN}_REL NAMES "${PLUGIN}.dll" HINTS ${VEKTRIX_PLUGIN_DIR_REL})
			find_file(VEKTRIX_${PLUGIN}_DBG NAMES "${PLUGIN}_d.dll" HINTS ${VEKTRIX_PLUGIN_DIR_DBG})
		endif()
		mark_as_advanced(VEKTRIX_${PLUGIN}_REL VEKTRIX_${PLUGIN}_DBG)
	endif()
	
  endif ()

  if (TMP_CMAKE_LIB_PREFIX)
    set(CMAKE_FIND_LIBRARY_PREFIXES ${TMP_CMAKE_LIB_PREFIX})
  endif ()
endmacro(vektrix_find_plugin)

vektrix_find_plugin(vektrix_AS3Plugin vtxas3Plugin.h PCZ plugins/AS3Plugin/include)
vektrix_find_plugin(vektrix_CairoPlugin vtxcaiPlugin.h PCZ plugins/CairoPlugin/include)
vektrix_find_plugin(vektrix_cURLPlugin vtxcurlPlugin.h PCZ plugins/cURLPlugin/include)
vektrix_find_plugin(vektrix_D3D9Plugin vtxd3d9Plugin.h PCZ plugins/D3D9Plugin/include)
vektrix_find_plugin(vektrix_FreeImgPlugin vtxfreeimgPlugin.h PCZ plugins/FreeImgPlugin/include)
vektrix_find_plugin(vektrix_OgrePlugin vtxopPlugin.h PCZ plugins/OgrePlugin/include)
vektrix_find_plugin(vektrix_SwfPlugin vtxswfPlugin.h PCZ plugins/SwfPlugin/include)
vektrix_find_plugin(vektrix_XmlPlugin vtxxmlPlugin.h PCZ plugins/XmlPlugin/include)

if (VEKTRIX_STATIC)
  # check if dependencies for plugins are met
  if (NOT DirectX_FOUND)
    set(VEKTRIX_RenderSystem_Direct3D9_FOUND FALSE)
  endif ()
  
  set(VEKTRIX_RenderSystem_Direct3D9_LIBRARIES ${VEKTRIX_RenderSystem_Direct3D9_LIBRARIES}
    ${DirectX_LIBRARIES}
  )
endif ()

# look for the media directory
set(VEKTRIX_MEDIA_SEARCH_PATH
  ${VEKTRIX_SOURCE}
  ${VEKTRIX_LIBRARY_DIR_REL}/..
  ${VEKTRIX_LIBRARY_DIR_DBG}/..
  ${VEKTRIX_LIBRARY_DIR_REL}/../..
  ${VEKTRIX_LIBRARY_DIR_DBG}/../..
  ${VEKTRIX_PREFIX_SOURCE}
)
set(VEKTRIX_MEDIA_SEARCH_SUFFIX
  demos/media
  media
  media
  share/Vektrix/media
)

clear_if_changed(VEKTRIX_PREFIX_WATCH VEKTRIX_MEDIA_DIR)
find_path(VEKTRIX_MEDIA_DIR NAMES fuse_logo.png HINTS ${VEKTRIX_MEDIA_SEARCH_PATH}
  PATHS ${VEKTRIX_PREFIX_PATH} PATH_SUFFIXES ${VEKTRIX_MEDIA_SEARCH_SUFFIX})

