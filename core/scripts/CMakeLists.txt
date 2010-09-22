set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

#-----------------------------------------------------------------------
# CMAKE OPTIONS
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# PREPROCESSOR SETTINGS
#-----------------------------------------------------------------------

if(WIN32)
#{
	# disable win32 warnings
	add_definitions ("/wd4244")
	
	# add uppercase export definition
	add_definitions (-DVEKTRIX_EXPORTS)
#}
endif(WIN32)

#disable_RTTI()

#-----------------------------------------------------------------------
# SOURCE FILES & INCLUDE DIRECTORIES & LINK LIBRARIES
#-----------------------------------------------------------------------

# read the source-files list
include (vektrix_src_files)

# the required include directories
set (include_dirs
	../include
	${expat_include_dirs}
)

# the required link libraries
set (libraries ${expat_libraries})

#-----------------------------------------------------------------------
# BUILD SETTINGS & COMPILATION
#-----------------------------------------------------------------------

# output directory
set (LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# set the include directories
include_directories (${include_dirs})

# add the vektrix core library
add_library (vektrix SHARED ${file_root})

# automatically update the source-files list with folders4cmake
auto_rebuild_src_files (vektrix)

# link against the required libraries
target_link_libraries (vektrix ${libraries})
