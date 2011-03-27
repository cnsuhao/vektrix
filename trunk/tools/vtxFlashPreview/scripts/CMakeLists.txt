set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

#-----------------------------------------------------------------------
# SOURCE FILES & INCLUDE DIRECTORIES & LINK LIBRARIES
#-----------------------------------------------------------------------

# read the source-files list
include (vtxFlashPreview_src_files)

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
	${directx_include_dirs}
)

# the required link libraries
set (libraries
	vektrix
	${ois_libraries}
	${ogre_libraries}
	${freetype_libraries}
	${vtx_plugins_list}
	${directx_libraries}
	OpenGL32.lib
)

#-----------------------------------------------------------------------
# BUILD SETTINGS & COMPILATION
#-----------------------------------------------------------------------

if(WIN32 AND BUILD_USE_STATIC_CRT)
	# link statically against the MSVCRT
	link_static_crt()
endif()

# output directory
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# set the include directories
include_directories (${include_dirs})

link_directories (${boost_library_dirs})

# add the tool executable
add_executable (vtxFlashPreview ${file_root})

# automatically update the source-files list with folders4cmake
auto_rebuild_src_files (vtxFlashPreview)

# link against the required libraries
target_link_libraries (vtxFlashPreview ${libraries})
