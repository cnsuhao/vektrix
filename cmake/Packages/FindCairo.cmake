#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# - Try to find Cairo
# Once done, this will define
#
#  Cairo_FOUND - system has Cairo
#  Cairo_INCLUDE_DIRS - the Cairo include directories 
#  Cairo_LIBRARIES - link these to use Cairo

include(FindPkgMacros)
findpkg_begin(Cairo)

# Get path, convert backslashes as ${ENV_${var}}
getenv_path(CAIRO_HOME)

# construct search paths
set(Cairo_PREFIX_PATH ${CAIRO_HOME} ${ENV_CAIRO_HOME})
create_search_paths(Cairo)

# redo search if prefix path changed
clear_if_changed(Cairo_PREFIX_PATH
  CAIRO_LIBRARY_FWK
  CAIRO_LIBRARY_REL
  CAIRO_LIBRARY_DBG
  CAIRO_INCLUDE_DIR
)

set(Cairo_LIBRARY_NAMES cairo)
get_debug_names(Cairo_LIBRARY_NAMES)

use_pkgconfig(Cairo_PKGC cairo)

findpkg_framework(Cairo)

find_path(Cairo_INCLUDE_DIR NAMES cairo/cairo.h HINTS ${Cairo_INC_SEARCH_PATH} ${Cairo_PKGC_INCLUDE_DIRS})
find_library(Cairo_LIBRARY_REL NAMES ${Cairo_LIBRARY_NAMES} HINTS ${Cairo_LIB_SEARCH_PATH} ${Cairo_PKGC_LIBRARY_DIRS} PATH_SUFFIXES "" release relwithdebinfo minsizerel)
find_library(Cairo_LIBRARY_DBG NAMES ${Cairo_LIBRARY_NAMES_DBG} HINTS ${Cairo_LIB_SEARCH_PATH} ${Cairo_PKGC_LIBRARY_DIRS} PATH_SUFFIXES "" debug)
make_library_set(Cairo_LIBRARY)

findpkg_finish(Cairo)

