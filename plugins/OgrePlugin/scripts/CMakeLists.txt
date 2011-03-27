set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

#-----------------------------------------------------------------------
# CMAKE OPTIONS
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# PREPROCESSOR SETTINGS
#-----------------------------------------------------------------------

if(WIN32)
	# add uppercase export definition
	add_definitions (-DVEKTRIX_OGREPLUGIN_EXPORTS)
endif()

#-----------------------------------------------------------------------
# SOURCE FILES & INCLUDE DIRECTORIES & LINK LIBRARIES
#-----------------------------------------------------------------------

# read the source-files list
include (vektrix_OgrePlugin_src_files)

# the required include directories
set (include_dirs
	../include
	../../../core/include
	${boost_include_dirs}
	${ogre_include_dirs}
)

# the required link libraries
set (libraries
	vektrix
	${ogre_libraries}
	${freetype_libraries}
)

#-----------------------------------------------------------------------
# BUILD SETTINGS & COMPILATION
#-----------------------------------------------------------------------

if(WIN32 AND BUILD_USE_STATIC_CRT)
	# link statically against the MSVCRT
	link_static_crt()
endif()

# output directory
set (LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# set the include directories
include_directories (${include_dirs})

link_directories (${boost_library_dirs})

# add the plugin library
add_library (vektrix_OgrePlugin ${file_root})

# automatically update the source-files list with folders4cmake
auto_rebuild_src_files (vektrix_OgrePlugin)

#if(VTX_STATIC_LIB)
# remove "lib" prefix
set_target_properties(vektrix_OgrePlugin PROPERTIES PREFIX "")
#endif()

# link against the required libraries
target_link_libraries (vektrix_OgrePlugin ${libraries})
