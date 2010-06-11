#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

include(PreprocessorUtils)

macro(vektrix_get_version HEADER)
  file(READ ${HEADER} TEMP_VAR_CONTENTS)
  get_preprocessor_entry(TEMP_VAR_CONTENTS VTX_VERSION_MAJOR VTX_VERSION_MAJOR)
  get_preprocessor_entry(TEMP_VAR_CONTENTS VTX_VERSION_MINOR VTX_VERSION_MINOR)
  get_preprocessor_entry(TEMP_VAR_CONTENTS VTX_VERSION_PATCH VTX_VERSION_PATCH)
  get_preprocessor_entry(TEMP_VAR_CONTENTS VTX_VERSION_NAME VTX_VERSION_NAME)
  get_preprocessor_entry(TEMP_VAR_CONTENTS VTX_VERSION_SUFFIX VTX_VERSION_SUFFIX)
  set(VEKTRIX_VERSION "${VTX_VERSION_MAJOR}.${VTX_VERSION_MINOR}.${VTX_VERSION_PATCH}${VTX_VERSION_SUFFIX}")
  set(VEKTRIX_SOVERSION "${VTX_VERSION_MAJOR}.${VTX_VERSION_MINOR}.${VTX_VERSION_PATCH}")
  set(VEKTRIX_VERSION_DASH_SEPARATED "${VTX_VERSION_MAJOR}-${VTX_VERSION_MINOR}-${VTX_VERSION_PATCH}${VTX_VERSION_SUFFIX}")

endmacro()
