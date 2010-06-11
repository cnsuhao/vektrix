#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# Configure Tools build

# Tools can't be run on the iPhone so don't build them
if (NOT VEKTRIX_BUILD_PLATFORM_IPHONE)
  add_subdirectory(vtxConverter)
endif (NOT VEKTRIX_BUILD_PLATFORM_IPHONE)
