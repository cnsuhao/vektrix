# top-level files
set (file_root
)

# _cmake_ files
set (file_root__cmake_
	CMakeLists.txt
	vtxFlashPreview_src_files.cmake
	vtxFlashPreview_src_files.cmake.rule
)

# Application files
set (file_root_application
	../include/vtxFlashPreview.h
	../src/main.cpp
	../src/vtxFlashPreview.cpp
)

# Listeners files
set (file_root_listeners
	../include/vtxFrameListener.h
	../include/vtxKeyboardListener.h
	../include/vtxMouseListener.h
	../include/vtxMovieListener.h
	../src/vtxFrameListener.cpp
	../src/vtxKeyboardListener.cpp
	../src/vtxMouseListener.cpp
	../src/vtxMovieListener.cpp
)

# [$ogre_win32_res] files
set (file_root_ogre_win32_res
	${ogre_win32_res}
)

# the source groups
source_group(""                  FILES ${file_root})
source_group("_cmake_"           FILES ${file_root__cmake_})
source_group("Application"       FILES ${file_root_application})
source_group("Listeners"         FILES ${file_root_listeners})
source_group("[$ogre_win32_res]" FILES ${file_root_ogre_win32_res})

# append all files to the file_root
set (file_root
	${file_root}
	${file_root__cmake_}
	${file_root_application}
	${file_root_listeners}
	${file_root_ogre_win32_res}
)
