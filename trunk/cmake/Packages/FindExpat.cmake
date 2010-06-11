#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# - Try to find Expat
# Once done, this will define
#
#  Expat_FOUND - system has Expat
#  Expat_INCLUDE_DIRS - the Expat include directories 
#  Expat_LIBRARIES - link these to use Expat

include(FindPkgMacros)
findpkg_begin(Expat)

# Get path, convert backslashes as ${ENV_${var}}
getenv_path(EXPAT_HOME)

# construct search paths
set(Expat_PREFIX_PATH ${EXPAT_HOME} ${ENV_EXPAT_HOME})
create_search_paths(Expat)

# redo search if prefix path changed
clear_if_changed(Expat_PREFIX_PATH
  Expat_LIBRARY_FWK
  Expat_LIBRARY_REL
  Expat_LIBRARY_DBG
  Expat_INCLUDE_DIR
)

set(Expat_LIBRARY_NAMES libexpatMT)
get_debug_names(Expat_LIBRARY_NAMES)

use_pkgconfig(Expat_PKGC expat)

findpkg_framework(Expat)

find_path(Expat_INCLUDE_DIR NAMES expat/expat.h HINTS ${Expat_INC_SEARCH_PATH} ${Expat_PKGC_INCLUDE_DIRS})
find_library(Expat_LIBRARY_REL NAMES ${Expat_LIBRARY_NAMES} HINTS ${Expat_LIB_SEARCH_PATH} ${Expat_PKGC_LIBRARY_DIRS} PATH_SUFFIXES "" release relwithdebinfo minsizerel)
find_library(Expat_LIBRARY_DBG NAMES ${Expat_LIBRARY_NAMES_DBG} HINTS ${Expat_LIB_SEARCH_PATH} ${Expat_PKGC_LIBRARY_DIRS} PATH_SUFFIXES "" debug)
make_library_set(Expat_LIBRARY)

findpkg_finish(Expat)

