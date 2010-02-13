include_directories (../include) 
include_directories (../../../lib/include)

include_directories (/home/stone/Desktop/ogre/OgreMain/include)

link_libraries (/home/stone/Desktop/ogre/OgreMain/src/.libs/libOgreMain.so)

set (LIBRARY_OUTPUT_PATH ../../../bin)

# add_definitions (-DVEKTRIX_STATIC_LIB)

file(GLOB VTXOP_SRC "../src/*.cpp")

add_library (vektrix_OgrePlugin SHARED ${VTXOP_SRC})

set_target_properties(vektrix_OgrePlugin PROPERTIES PREFIX "")

