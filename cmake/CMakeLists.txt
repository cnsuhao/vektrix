#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

#############################################################
# Install useful CMake modules.
# These are necessary to compile the samples from the install
# directory, but can also be used for custom projects.
#############################################################

if(WIN32 OR APPLE)
	set(VEKTRIX_CMAKE_DIR "cmake")
else()
	set(VEKTRIX_CMAKE_DIR "${VEKTRIX_LIB_DIRECTORY}/Vektrix/cmake")
endif()

set(INST_FILES
  Packages/FindOGRE.cmake
  Utils/FindPkgMacros.cmake
  Utils/PreprocessorUtils.cmake
  Utils/VektrixConfigTargets.cmake
  Utils/VektrixGetVersion.cmake
  Utils/VektrixFindFrameworks.cmake
) 
set(STATIC_INST_FILES
  Packages/FindCairo.cmake
  Packages/FindCaspin.cmake
  Packages/FindCurl.cmake
  Packages/FindDirectX.cmake
  Packages/FindDoxygen.cmake
  Packages/FindExpat.cmake
  Packages/FindFreeImage.cmake
  Packages/FindOGRE.cmake
  Packages/FindVektrix.cmake
  Packages/FindZLIB.cmake
)
if (WIN32)
  set(INST_FILES ${INST_FILES}
    Templates/VisualStudioUserFile.vcproj.user.in
  )
endif ()

install(FILES ${INST_FILES} DESTINATION ${VEKTRIX_CMAKE_DIR})
if (VEKTRIX_STATIC)
  install(FILES ${STATIC_INST_FILES} DESTINATION ${VEKTRIX_CMAKE_DIR})
endif ()
