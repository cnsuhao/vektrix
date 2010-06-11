#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

##################################################################
# Generate and install the config files needed for the demos
##################################################################

if (WIN32)
  set(VEKTRIX_MEDIA_PATH "media")
  set(VEKTRIX_MEDIA_DIR_REL "../../${VEKTRIX_MEDIA_PATH}")
  set(VEKTRIX_MEDIA_DIR_DBG "../../${VEKTRIX_MEDIA_PATH}")
  set(VEKTRIX_PLUGIN_DIR_REL ".")
  set(VEKTRIX_PLUGIN_DIR_DBG ".")
  set(VEKTRIX_SAMPLES_DIR_REL ".")
  set(VEKTRIX_SAMPLES_DIR_DBG ".")
  set(VEKTRIX_CFG_INSTALL_PATH "bin")
elseif (UNIX)
  set(VEKTRIX_MEDIA_PATH "share/Vektrix/media")
  set(VEKTRIX_MEDIA_DIR_REL "${CMAKE_INSTALL_PREFIX}/${VEKTRIX_MEDIA_PATH}")
  set(VEKTRIX_MEDIA_DIR_DBG "${CMAKE_INSTALL_PREFIX}/${VEKTRIX_MEDIA_PATH}")
  set(VEKTRIX_PLUGIN_DIR_REL "${CMAKE_INSTALL_PREFIX}/lib/Vektrix")
  set(VEKTRIX_PLUGIN_DIR_DBG "${CMAKE_INSTALL_PREFIX}/lib/Vektrix")
  set(VEKTRIX_SAMPLES_DIR_REL "${CMAKE_INSTALL_PREFIX}/lib/Vektrix/demos")
  set(VEKTRIX_SAMPLES_DIR_DBG "${CMAKE_INSTALL_PREFIX}/lib/Vektrix/demos")
  set(VEKTRIX_CFG_INSTALL_PATH "share/Vektrix")
endif ()

#
# configure plugins.cfg
#
if (NOT VEKTRIX_BUILD_PLUGIN_D3D9)
  set(VEKTRIX_BUILD_PLUGIN_D3D9 "#")
endif ()
if (NOT VEKTRIX_BUILD_PLUGIN_OGRE)
  set(VEKTRIX_BUILD_PLUGIN_OGRE "#")
endif ()
if (NOT VEKTRIX_BUILD_PLUGIN_AS3)
  set(VEKTRIX_BUILD_PLUGIN_AS3 "#")
endif ()
if (NOT VEKTRIX_BUILD_PLUGIN_CAIRO)
  set(VEKTRIX_BUILD_PLUGIN_CAIRO "#")
endif ()
if (NOT VEKTRIX_BUILD_PLUGIN_CURL)
  set(VEKTRIX_BUILD_PLUGIN_CURL "#")
endif ()
if (NOT VEKTRIX_BUILD_PLUGIN_FREEIMG)
  set(VEKTRIX_BUILD_PLUGIN_FREEIMG "#")
endif ()
if (NOT VEKTRIX_BUILD_PLUGIN_SWF)
  set(VEKTRIX_BUILD_PLUGIN_SWF "#")
endif ()
if (NOT VEKTRIX_BUILD_PLUGIN_XML)
  set(VEKTRIX_BUILD_PLUGIN_XML "#")
endif ()

# install resource files
if (VEKTRIX_INSTALL_SAMPLES OR VEKTRIX_INSTALL_SAMPLES_SOURCE)
  install(FILES 
    DESTINATION "${VEKTRIX_CFG_INSTALL_PATH}${VEKTRIX_DEBUG_PATH}"
    CONFIGURATIONS Debug
  )
  install(FILES 
    DESTINATION "${VEKTRIX_CFG_INSTALL_PATH}${VEKTRIX_RELEASE_PATH}" CONFIGURATIONS Release None ""
  )
  install(FILES 
	DESTINATION "${VEKTRIX_CFG_INSTALL_PATH}${VEKTRIX_RELWDBG_PATH}" CONFIGURATIONS RelWithDebInfo
  )
  install(FILES 
	DESTINATION "${VEKTRIX_CFG_INSTALL_PATH}${VEKTRIX_MINSIZE_PATH}" CONFIGURATIONS MinSizeRel
  )
endif ()


# CREATE CONFIG FILES - BUILD DIR VERSIONS
set(VEKTRIX_MEDIA_DIR_REL "${VEKTRIX_SOURCE_DIR}/demos/Media")
set(VEKTRIX_MEDIA_DIR_DBG "${VEKTRIX_SOURCE_DIR}/demos/Media")
if (WIN32)
  set(VEKTRIX_PLUGIN_DIR_REL ".")
  set(VEKTRIX_PLUGIN_DIR_DBG ".")
  set(VEKTRIX_SAMPLES_DIR_REL ".")
  set(VEKTRIX_SAMPLES_DIR_DBG ".")
elseif (UNIX)
  set(VEKTRIX_PLUGIN_DIR_REL "${VEKTRIX_BINARY_DIR}/lib")
  set(VEKTRIX_PLUGIN_DIR_DBG "${VEKTRIX_BINARY_DIR}/lib")
  set(VEKTRIX_SAMPLES_DIR_REL "${VEKTRIX_BINARY_DIR}/lib")
  set(VEKTRIX_SAMPLES_DIR_DBG "${VEKTRIX_BINARY_DIR}/lib")
endif ()
