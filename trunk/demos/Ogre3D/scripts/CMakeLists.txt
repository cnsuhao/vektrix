set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

#-----------------------------------------------------------------------
# SOURCE FILES & INCLUDE DIRECTORIES & LINK LIBRARIES
#-----------------------------------------------------------------------

# read the source-files list
include (vektrix_Ogre3D_demo_src_files)

# the required include directories
set (include_dirs
	../include
	../../../core/include
	../../../plugins/AS3Plugin/include
	../../../plugins/CairoPlugin/include
	../../../plugins/cURLPlugin/include
	../../../plugins/D3D9Plugin/include
	../../../plugins/FreeImgPlugin/include
	../../../plugins/OgrePlugin/include
	../../../plugins/SwfPlugin/include
	../../../plugins/XmlPlugin/include
	${ois_include_dirs}
	${ogre_include_dirs}
	${boost_include_dirs}
)

# the required link libraries
set (libraries
	vektrix
	#vektrix_AS3Plugin
	#vektrix_CairoPlugin
	${ois_libraries}
	${ogre_libraries}
)

#-----------------------------------------------------------------------
# BUILD SETTINGS & COMPILATION
#-----------------------------------------------------------------------

# output directory
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# set the include directories
include_directories (${include_dirs})

# set additional link directories
link_directories (${boost_library_dirs})

# add the tool executable
add_executable (vektrix_Ogre3D_demo ${file_root})

# automatically update the source-files list with folders4cmake
auto_rebuild_src_files (vektrix_Ogre3D_demo)

# link against the required libraries
target_link_libraries (vektrix_Ogre3D_demo ${libraries})
