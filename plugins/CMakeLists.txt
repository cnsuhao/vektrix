#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# Configure Plugins build

if (VEKTRIX_BUILD_PLUGIN_AS3)
  if (NOT Caspin_FOUND)
    message(STATUS "Could not find dependency: Caspin")
    message(STATUS "Skipping Plugin AS3")
    set(VEKTRIX_BUILD_PLUGIN_AS3 0)
  else (NOT Caspin_FOUND)
    add_subdirectory(AS3Plugin)
  endif (NOT Caspin_FOUND)
endif (VEKTRIX_BUILD_PLUGIN_AS3)

if (VEKTRIX_BUILD_PLUGIN_CAIRO)
  if (NOT Cairo_FOUND)
    message(STATUS "Could not find dependency: Cairo")
    message(STATUS "Skipping Plugin Cairo")
    set(VEKTRIX_BUILD_PLUGIN_CAIRO 0)
  else (NOT Cairo_FOUND)
    add_subdirectory(CairoPlugin)
  endif (NOT Cairo_FOUND)
endif (VEKTRIX_BUILD_PLUGIN_CAIRO)

if (VEKTRIX_BUILD_PLUGIN_CURL)
  if (NOT Curl_FOUND)
    message(STATUS "Could not find dependency: cURL")
    message(STATUS "Skipping Plugin cURL")
    set(VEKTRIX_BUILD_PLUGIN_CURL 0)
  else (NOT Curl_FOUND)
    add_subdirectory(cURLPlugin)
  endif (NOT Curl_FOUND)
endif (VEKTRIX_BUILD_PLUGIN_CURL)

if (VEKTRIX_BUILD_PLUGIN_D3D9)
  if (NOT DirectX_FOUND)
    message(STATUS "Could not find dependency: DirectX 9")
    message(STATUS "Skipping Plugin D3D9")
    set(VEKTRIX_BUILD_PLUGIN_D3D9 0)
  else (NOT DirectX_FOUND)
    add_subdirectory(D3D9Plugin)
  endif (NOT DirectX_FOUND)
endif (VEKTRIX_BUILD_PLUGIN_D3D9)

if (VEKTRIX_BUILD_PLUGIN_FREEIMG)
  if (NOT FreeImage_FOUND)
    message(STATUS "Could not find dependency: FreeImage")
    message(STATUS "Skipping Plugin FreeImg")
    set(VEKTRIX_BUILD_PLUGIN_FREEIMG 0)
  else (NOT FreeImage_FOUND)
    add_subdirectory(FreeImgPlugin)
  endif (NOT FreeImage_FOUND)
endif (VEKTRIX_BUILD_PLUGIN_FREEIMG)

if (VEKTRIX_BUILD_PLUGIN_OGRE)
  if (NOT OGRE_FOUND)
    message(STATUS "Could not find dependency: OGRE")
    message(STATUS "Skipping Plugin OGRE")
    set(VEKTRIX_BUILD_PLUGIN_OGRE 0)
  else (NOT OGRE_FOUND)
    add_subdirectory(OGREPlugin)
  endif (NOT OGRE_FOUND)
endif (VEKTRIX_BUILD_PLUGIN_OGRE)

if (VEKTRIX_BUILD_PLUGIN_SWF)
  add_subdirectory(SwfPlugin)
endif (VEKTRIX_BUILD_PLUGIN_SWF)

if (VEKTRIX_BUILD_PLUGIN_XML)
  if (NOT Expat_FOUND)
    message(STATUS "Could not find dependency: Expat")
    message(STATUS "Skipping Plugin Expat")
    set(VEKTRIX_BUILD_PLUGIN_XML 0)
  else (NOT Expat_FOUND)
    add_subdirectory(XmlPlugin)
  endif (NOT Expat_FOUND)
endif (VEKTRIX_BUILD_PLUGIN_XML)
