# top-level files
set (file_root
)

# _cmake_ files
set (file_root__cmake_
	CMakeLists.txt
	vektrix_Ogre3D_demo_src_files.cmake
	vektrix_Ogre3D_demo_src_files.cmake.rule
)

# Application files
set (file_root_application
	../src/Ogre3D_Demo.cpp
)

# [$ogre_win32_res] files
set (file_root_ogre_win32_res
	${ogre_win32_res}
)

# the source groups
source_group(""                  FILES ${file_root})
source_group("_cmake_"           FILES ${file_root__cmake_})
source_group("Application"       FILES ${file_root_application})
source_group("[$ogre_win32_res]" FILES ${file_root_ogre_win32_res})

# append all files to the file_root
set (file_root
	${file_root}
	${file_root__cmake_}
	${file_root_application}
	${file_root_ogre_win32_res}
)
