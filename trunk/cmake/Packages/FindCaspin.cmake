#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# - Try to find Caspin
# Once done, this will define
#
#  Caspin_FOUND - system has Caspin
#  Caspin_INCLUDE_DIRS - the Caspin include directories 
#  Caspin_LIBRARIES - link these to use Caspin

include(FindPkgMacros)
findpkg_begin(Caspin)

# Get path, convert backslashes as ${ENV_${var}}
getenv_path(CASPIN_HOME)

# construct search paths
set(Caspin_PREFIX_PATH ${CASPIN_HOME} ${ENV_CASPIN_HOME})
create_search_paths(Caspin)

# redo search if prefix path changed
clear_if_changed(Caspin_PREFIX_PATH
  Caspin_LIBRARY_FWK
  Caspin_LIBRARY_REL
  Caspin_LIBRARY_DBG
  Caspin_INCLUDE_DIR
)

set(Caspin_LIBRARY_NAMES caspin)
get_debug_names(Caspin_LIBRARY_NAMES)

use_pkgconfig(Caspin_PKGC caspin)

findpkg_framework(Caspin)

find_path(Caspin_INCLUDE_DIR NAMES caspin/caspin_base.h caspin/tamarin/core/avmplus.h caspin/tamarin/eval/eval.h caspin/tamarin/extensions/Selftest.h caspin/tamarin/mmgc/GC.h caspin/tamarin/nanojit/nanojit.h caspin/tamarin/platform/system-selection.h caspin/tamarin/shell/avmshell-features.h caspin/tamarin/vmpi/VMPI.h HINTS ${Caspin_INC_SEARCH_PATH} ${Caspin_PKGC_INCLUDE_DIRS})
find_library(Caspin_LIBRARY_REL NAMES ${Caspin_LIBRARY_NAMES} HINTS ${Caspin_LIB_SEARCH_PATH} ${Caspin_PKGC_LIBRARY_DIRS} PATH_SUFFIXES "" release relwithdebinfo minsizerel)
find_library(Caspin_LIBRARY_DBG NAMES ${Caspin_LIBRARY_NAMES_DBG} HINTS ${Caspin_LIB_SEARCH_PATH} ${Caspin_PKGC_LIBRARY_DIRS} PATH_SUFFIXES "" debug)
make_library_set(Caspin_LIBRARY)

findpkg_finish(Caspin)

