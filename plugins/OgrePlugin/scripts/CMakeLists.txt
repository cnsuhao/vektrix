include_directories (../include) 
include_directories (../../../lib/include)

include_directories (/home/stone/Desktop/ogre/OgreMain/include)

link_libraries (/home/stone/Desktop/ogre/OgreMain/src/.libs/libOgreMain.so)

set (LIBRARY_OUTPUT_PATH ../../../bin)

# add_definitions (-DVEKTRIX_STATIC_LIB)

add_library (
vektrix_OgrePlugin SHARED  
../src/vtxopMovableMovie.cpp
../src/vtxopMovableMovieDebugger.cpp
../src/vtxopMovableMovieFactory.cpp
../src/vtxopPlugin.cpp
../src/vtxopRenderStrategy.cpp
../src/vtxopShape.cpp
../src/vtxopShapeFactory.cpp
../src/vtxopTexture.cpp
../src/vtxopTextureFactory.cpp
../src/vtxopTextureMovie.cpp
../src/vtxopTextureMovieFactory.cpp
)

set_target_properties(vektrix_OgrePlugin PROPERTIES PREFIX "")

