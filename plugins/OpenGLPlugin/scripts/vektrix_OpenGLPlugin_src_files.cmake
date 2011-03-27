# top-level files
set (file_root
)

# _cmake_ files
set (file_root__cmake_
	CMakeLists.txt
	vektrix_OpenGLPlugin_src_files.cmake
	vektrix_OpenGLPlugin_src_files.cmake.rule
)

# Generic files
set (file_root_generic
	../include/vtxopenglTexture.h
	../src/vtxopenglTexture.cpp
)

# Movie Types files
set (file_root_movie_types
)

# Movie Types -> Movable files
set (file_root_movie_types_movable
	../include/vtxopenglMovableMovie.h
	../include/vtxopenglMovableMovieFactory.h
	../src/vtxopenglMovableMovie.cpp
	../src/vtxopenglMovableMovieFactory.cpp
)

# Plugin files
set (file_root_plugin
	../include/vtxopengl.h
	../include/vtxopenglPlugin.h
	../src/vtxopenglPlugin.cpp
)

# the source groups
source_group(""                     FILES ${file_root})
source_group("_cmake_"              FILES ${file_root__cmake_})
source_group("Generic"              FILES ${file_root_generic})
source_group("Movie Types"          FILES ${file_root_movie_types})
source_group("Movie Types\\Movable" FILES ${file_root_movie_types_movable})
source_group("Plugin"               FILES ${file_root_plugin})

# append all files to the file_root
set (file_root
	${file_root}
	${file_root__cmake_}
	${file_root_generic}
	${file_root_movie_types}
	${file_root_movie_types_movable}
	${file_root_plugin}
)
