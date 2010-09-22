# top-level files
set (file_root
)

# _cmake_ files
set (file_root__cmake_
	CMakeLists.txt
	vektrix_FreeImgPlugin_src_files.cmake
	vektrix_FreeImgPlugin_src_files.cmake.rule
)

# Parser files
set (file_root_parser
	../include/vtxfreeimgParser.h
	../src/vtxfreeimgParser.cpp
)

# Plugin files
set (file_root_plugin
	../include/vtxfreeimg.h
	../include/vtxfreeimgPlugin.h
	../src/vtxfreeimgPlugin.cpp
)

# the source groups
source_group(""        FILES ${file_root})
source_group("_cmake_" FILES ${file_root__cmake_})
source_group("Parser"  FILES ${file_root_parser})
source_group("Plugin"  FILES ${file_root_plugin})

# append all files to the file_root
set (file_root
	${file_root}
	${file_root__cmake_}
	${file_root_parser}
	${file_root_plugin}
)
