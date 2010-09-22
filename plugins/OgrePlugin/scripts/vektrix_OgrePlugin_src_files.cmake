# top-level files
set (file_root
)

# _cmake_ files
set (file_root__cmake_
	CMakeLists.txt
	vektrix_OgrePlugin_src_files.cmake
	vektrix_OgrePlugin_src_files.cmake.rule
)

# Debuggers files
set (file_root_debuggers
	../include/vtxopMovableMovieDebugger.h
	../src/vtxopMovableMovieDebugger.cpp
)

# Generic files
set (file_root_generic
	../include/vtxopTexture.h
	../src/vtxopTexture.cpp
)

# Movie Types files
set (file_root_movie_types
)

# Movie Types -> Movable files
set (file_root_movie_types_movable
	../include/vtxopMovableMovie.h
	../include/vtxopMovableMovieFactory.h
	../src/vtxopMovableMovie.cpp
	../src/vtxopMovableMovieFactory.cpp
)

# Movie Types -> Movable -> Instances files
set (file_root_movie_types_movable_instances
	../include/vtxogreMovableTextBase.h
	../include/vtxopMovableEditText.h
	../include/vtxopMovableInstanceBase.h
	../include/vtxopMovableShape.h
	../include/vtxopMovableStaticText.h
	../src/vtxogreMovableTextBase.cpp
	../src/vtxopMovableEditText.cpp
	../src/vtxopMovableInstanceBase.cpp
	../src/vtxopMovableShape.cpp
	../src/vtxopMovableStaticText.cpp
)

# Movie Types -> Movable -> Packing files
set (file_root_movie_types_movable_packing
	../include/vtxogreGlyphAtlasElement.h
	../include/vtxogreShapeAtlasElement.h
	../src/vtxogreGlyphAtlasElement.cpp
	../src/vtxogreShapeAtlasElement.cpp
)

# Movie Types -> Texture files
set (file_root_movie_types_texture
	../include/vtxopTextureMovie.h
	../include/vtxopTextureMovieFactory.h
	../src/vtxopTextureMovie.cpp
	../src/vtxopTextureMovieFactory.cpp
)

# Plugin files
set (file_root_plugin
	../include/vtxop.h
	../include/vtxopPlugin.h
	../src/vtxopPlugin.cpp
)

# the source groups
source_group(""                                FILES ${file_root})
source_group("_cmake_"                         FILES ${file_root__cmake_})
source_group("Debuggers"                       FILES ${file_root_debuggers})
source_group("Generic"                         FILES ${file_root_generic})
source_group("Movie Types"                     FILES ${file_root_movie_types})
source_group("Movie Types\\Movable"            FILES ${file_root_movie_types_movable})
source_group("Movie Types\\Movable\\Instances" FILES ${file_root_movie_types_movable_instances})
source_group("Movie Types\\Movable\\Packing"   FILES ${file_root_movie_types_movable_packing})
source_group("Movie Types\\Texture"            FILES ${file_root_movie_types_texture})
source_group("Plugin"                          FILES ${file_root_plugin})

# append all files to the file_root
set (file_root
	${file_root}
	${file_root__cmake_}
	${file_root_debuggers}
	${file_root_generic}
	${file_root_movie_types}
	${file_root_movie_types_movable}
	${file_root_movie_types_movable_instances}
	${file_root_movie_types_movable_packing}
	${file_root_movie_types_texture}
	${file_root_plugin}
)
