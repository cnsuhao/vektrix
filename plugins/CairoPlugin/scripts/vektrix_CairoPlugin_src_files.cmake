# top-level files
set (file_root
)

# _cmake_ files
set (file_root__cmake_
	CMakeLists.txt
	vektrix_CairoPlugin_src_files.cmake
	vektrix_CairoPlugin_src_files.cmake.rule
)

# Plugin files
set (file_root_plugin
	../include/vtxcai.h
	../include/vtxcaiPlugin.h
	../src/vtxcaiPlugin.cpp
)

# Rasterizer files
set (file_root_rasterizer
	../include/vtxcaiRasterizer.h
	../src/vtxcaiRasterizer.cpp
)

# the source groups
source_group(""           FILES ${file_root})
source_group("_cmake_"    FILES ${file_root__cmake_})
source_group("Plugin"     FILES ${file_root_plugin})
source_group("Rasterizer" FILES ${file_root_rasterizer})

# append all files to the file_root
set (file_root
	${file_root}
	${file_root__cmake_}
	${file_root_plugin}
	${file_root_rasterizer}
)
