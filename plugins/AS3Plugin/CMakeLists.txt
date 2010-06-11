#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# Configure AS3 Plugin build

set (HEADER_FILES
  include/flash.h
  include/flash_package.h
  include/vtxas3.h
  include/vtxas3DisplayObject.h
  include/vtxas3DisplayObjectContainer.h
  include/vtxas3Event.h
  include/vtxas3EventDispatcher.h
  include/vtxas3EventHandler.h
  include/vtxas3InteractiveObject.h
  include/vtxas3MovieClip.h
  include/vtxas3Plugin.h
  include/vtxas3ScriptEngine.h
  include/vtxas3SimpleButton.h
  include/vtxas3Sprite.h
  include/vtxas3StaticText.h
  include/vtxas3TextField.h
)

set (SOURCE_FILES
  src/flash.cpp
  src/flash_package.cpp
  src/vtxas3DisplayObject.cpp
  src/vtxas3DisplayObjectContainer.cpp
  src/vtxas3Event.cpp
  src/vtxas3EventDispatcher.cpp
  src/vtxas3EventHandler.cpp
  src/vtxas3InteractiveObject.cpp
  src/vtxas3MovieClip.cpp
  src/vtxas3Plugin.cpp
  src/vtxas3ScriptEngine.cpp
  src/vtxas3SimpleButton.cpp
  src/vtxas3Sprite.cpp
  src/vtxas3StaticText.cpp
  src/vtxas3TextField.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_definitions(-D_USRDLL)

add_library(vektrix_AS3Plugin ${VEKTRIX_LIB_TYPE} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(vektrix_AS3Plugin vektrix)
if (NOT VEKTRIX_STATIC)
  set_target_properties(vektrix_AS3Plugin PROPERTIES
    COMPILE_DEFINITIONS VEKTRIX_AS3PLUGIN_EXPORTS
  ) 
endif ()

if (APPLE AND NOT VEKTRIX_BUILD_PLATFORM_IPHONE)
    # Set the INSTALL_PATH so that Plugins can be installed in the application package
    set_target_properties(vektrix_AS3Plugin
       PROPERTIES BUILD_WITH_INSTALL_RPATH 1
       INSTALL_NAME_DIR "@executable_path/../Plugins"
    )

	# Copy headers into the main Vektrix framework
	add_custom_command(TARGET vektrix_AS3Plugin POST_BUILD
	  COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${VEKTRIX_BINARY_DIR}/lib/$(CONFIGURATION)/Vektrix.framework/Headers/
	)
endif()

install(FILES ${HEADER_FILES} DESTINATION include/Vektrix/plugins/AS3Plugin)

vektrix_config_plugin(vektrix_AS3Plugin)
