#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# - helper module to find OSX frameworks
# Adapted from standard CMake version, but added dependencies
# Standard finder does not look in any variable locations such as 
# CMAKE_FRAMEWORK_PATH (not sure why not)

IF(NOT VEKTRIX_FIND_FRAMEWORKS_INCLUDED)
  SET(VEKTRIX_FIND_FRAMEWORKS_INCLUDED 1)
  MACRO(VEKTRIX_FIND_FRAMEWORKS fwk)
    IF(APPLE)
      SET(${fwk}_FRAMEWORKS)
      SET(VEKTRIX_FRAMEWORK_PATH
		${VEKTRIX_DEPENDENCIES_DIR}
    	~/Library/Frameworks
    	/Library/Frameworks
    	/System/Library/Frameworks
    	/Network/Library/Frameworks
	  )
	  FOREACH(dir ${VEKTRIX_FRAMEWORK_PATH})
	    SET(fwkpath ${dir}/${fwk}.framework)
	    IF(EXISTS ${fwkpath})
          SET(${fwk}_FRAMEWORKS ${${fwk}_FRAMEWORKS} ${fwkpath})
        ENDIF(EXISTS ${fwkpath})
      ENDFOREACH(dir)
    ENDIF(APPLE)
  ENDMACRO(OGRE_FIND_FRAMEWORKS)
ENDIF(NOT VEKTRIX_FIND_FRAMEWORKS_INCLUDED)
