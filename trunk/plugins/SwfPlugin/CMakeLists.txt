#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# Configure SWF Plugin build

set (HEADER_FILES
  include/vtxswf.h
  include/vtxswfContourElement.h
  include/vtxswfContourPoint.h
  include/vtxswfParser.h
  include/vtxswfParserTypes.h
  include/vtxswfPlugin.h
  include/vtxswfSubLine.h
  include/vtxswfSubShape.h
)

set (SOURCE_FILES
  src/vtxswfContourElement.cpp
  src/vtxswfContourPoint.cpp
  src/vtxswfDefineBitsLossless.cpp
  src/vtxswfDefineButton2.cpp
  src/vtxswfDefineEditText.cpp
  src/vtxswfDefineFont3.cpp
  src/vtxswfDefineJPEG.cpp
  src/vtxswfDefineShape.cpp
  src/vtxswfDefineSprite.cpp
  src/vtxswfDefineText.cpp
  src/vtxswfDoABC.cpp
  src/vtxswfEnd.cpp
  src/vtxswfParser.cpp
  src/vtxswfPlaceObject2.cpp
  src/vtxswfPlugin.cpp
  src/vtxswfShowFrame.cpp
  src/vtxswfSymbolClass.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_definitions(-D_USRDLL)

add_library(vektrix_SwfPlugin ${VEKTRIX_LIB_TYPE} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(vektrix_SwfPlugin vektrix)
if (NOT VEKTRIX_STATIC)
  set_target_properties(vektrix_SwfPlugin PROPERTIES
    COMPILE_DEFINITIONS VEKTRIX_SWFPLUGIN_EXPORTS
  ) 
endif ()

if (APPLE AND NOT VEKTRIX_BUILD_PLATFORM_IPHONE)
    # Set the INSTALL_PATH so that Plugins can be installed in the application package
    set_target_properties(vektrix_SwfPlugin
       PROPERTIES BUILD_WITH_INSTALL_RPATH 1
       INSTALL_NAME_DIR "@executable_path/../plugins"
    )

	# Copy headers into the main Vektrix framework
	add_custom_command(TARGET vektrix_SwfPlugin POST_BUILD
	  COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${VEKTRIX_BINARY_DIR}/lib/$(CONFIGURATION)/Vektrix.framework/Headers/
	)
endif()

install(FILES ${HEADER_FILES} DESTINATION include/Vektrix/plugin/SwfPlugin)

vektrix_config_plugin(vektrix_SwfPlugin)
