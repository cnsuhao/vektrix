# top-level files
set (file_root
)

# _cmake_ files
set (file_root__cmake_
	CMakeLists.txt
	vektrix_cURLPlugin_src_files.cmake
	vektrix_cURLPlugin_src_files.cmake.rule
)

# Plugin files
set (file_root_plugin
	../include/vtxcurl.h
	../include/vtxcurlPlugin.h
	../src/vtxcurlPlugin.cpp
)

# Web Access files
set (file_root_web_access
	../include/vtxcurlWebFileContainer.h
	../include/vtxcurlWebRequest.h
	../src/vtxcurlWebFileContainer.cpp
	../src/vtxcurlWebRequest.cpp
)

# the source groups
source_group(""           FILES ${file_root})
source_group("_cmake_"    FILES ${file_root__cmake_})
source_group("Plugin"     FILES ${file_root_plugin})
source_group("Web Access" FILES ${file_root_web_access})

# append all files to the file_root
set (file_root
	${file_root}
	${file_root__cmake_}
	${file_root_plugin}
	${file_root_web_access}
)
