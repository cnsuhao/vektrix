set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

#-----------------------------------------------------------------------
# CMAKE OPTIONS
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# PREPROCESSOR SETTINGS
#-----------------------------------------------------------------------

if(WIN32)
	# add uppercase export definition
	add_definitions (-DVEKTRIX_CAIROPLUGIN_EXPORTS)
endif()

#-----------------------------------------------------------------------
# SOURCE FILES & INCLUDE DIRECTORIES & LINK LIBRARIES
#-----------------------------------------------------------------------

# read the source-files list
include (vektrix_CairoPlugin_src_files)

# the required include directories
set (include_dirs
	../include
	../../../core/include
	${cairo_include_dirs}
)

# the required link libraries
set (libraries
	vektrix
	${cairo_libraries}
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

# add the plugin library
add_library (vektrix_CairoPlugin ${file_root})

# automatically update the source-files list with folders4cmake
auto_rebuild_src_files (vektrix_CairoPlugin)

#if(VTX_STATIC_LIB)
# remove "lib" prefix
set_target_properties (vektrix_CairoPlugin PROPERTIES PREFIX "")
#endif()

# link against the required libraries
target_link_libraries (vektrix_CairoPlugin ${libraries})
