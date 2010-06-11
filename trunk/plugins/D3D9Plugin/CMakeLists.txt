#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# Configure D3D9 Plugin build

set (HEADER_FILES
  include/vtxd3d9.h
  include/vtxd3d9MovableMovie.h
  include/vtxd3d9MovableMovieFactory.h
  include/vtxd3d9MovableShape.h
  include/vtxd3d9MovableStrategy.h
  include/vtxd3d9Plugin.h
  include/vtxd3d9Texture.h
)

set (SOURCE_FILES
  src/vtxd3d9MovableMovie.cpp
  src/vtxd3d9MovableMovieFactory.cpp
  src/vtxd3d9MovableShape.cpp
  src/vtxd3d9MovableStrategy.cpp
  src/vtxd3d9Plugin.cpp
  src/vtxd3d9Texture.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_definitions(-D_USRDLL)

add_library(vektrix_D3D9Plugin ${VEKTRIX_LIB_TYPE} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(vektrix_D3D9Plugin vektrix)
if (NOT VEKTRIX_STATIC)
  set_target_properties(vektrix_D3D9Plugin PROPERTIES
    COMPILE_DEFINITIONS VEKTRIX_D3D9PLUGIN_EXPORTS
  ) 
endif ()

if (APPLE AND NOT VEKTRIX_BUILD_PLATFORM_IPHONE)
    # Set the INSTALL_PATH so that Plugins can be installed in the application package
    set_target_properties(vektrix_D3D9Plugin
       PROPERTIES BUILD_WITH_INSTALL_RPATH 1
       INSTALL_NAME_DIR "@executable_path/../Plugins"
    )

	# Copy headers into the main Vektrix framework
	add_custom_command(TARGET vektrix_D3D9Plugin POST_BUILD
	  COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${VEKTRIX_BINARY_DIR}/lib/$(CONFIGURATION)/Vektrix.framework/Headers/
	)
endif()

install(FILES ${HEADER_FILES} DESTINATION include/Vektrix/plugins/D3D9Plugin)

vektrix_config_plugin(vektrix_D3D9Plugin)
