#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# - Try to find Curl
# Once done, this will define
#
#  Curl_FOUND - system has Curl
#  Curl_INCLUDE_DIRS - the Curl include directories 
#  Curl_LIBRARIES - link these to use Curl

include(FindPkgMacros)
findpkg_begin(Curl)

# Get path, convert backslashes as ${ENV_${var}}
getenv_path(CURL_HOME)

# construct search paths
set(Curl_PREFIX_PATH ${CURL_HOME} ${ENV_CURL_HOME})
create_search_paths(Curl)
# redo search if prefix path changed
clear_if_changed(Curl_PREFIX_PATH
  Curl_LIBRARY_FWK
  Curl_LIBRARY_REL
  Curl_LIBRARY_DBG
  Curl_INCLUDE_DIR
)

set(Curl_LIBRARY_NAMES libcurl)
get_debug_names(Curl_LIBRARY_NAMES)

use_pkgconfig(Curl_PKGC libcurl)

findpkg_framework(Curl)

find_path(Curl_INCLUDE_DIR NAMES curl/curl.h HINTS ${Curl_INC_SEARCH_PATH} ${Curl_PKGC_INCLUDE_DIRS})
find_library(Curl_LIBRARY_REL NAMES ${Curl_LIBRARY_NAMES} HINTS ${Curl_LIB_SEARCH_PATH} ${Curl_PKGC_LIBRARY_DIRS} PATH_SUFFIXES "" release relwithdebinfo minsizerel)
find_library(Curl_LIBRARY_DBG NAMES ${Curl_LIBRARY_NAMES_DBG} HINTS ${Curl_LIB_SEARCH_PATH} ${Curl_PKGC_LIBRARY_DIRS} PATH_SUFFIXES "" debug)
make_library_set(Curl_LIBRARY)

findpkg_finish(Curl)

