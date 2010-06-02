include_directories (
../include
../../../core/include
$ENV{OGRE_HOME}/include/OGRE
)

#link_libraries ($ENV{OGRE_HOME}/lib/libOgreMain.so)

set (LIBRARY_OUTPUT_PATH ../../../bin)

# add_definitions (-DVEKTRIX_STATIC_LIB)

file(GLOB VTXOP_SRC "../src/*.cpp")

add_library (vektrix_OgrePlugin SHARED ${VTXOP_SRC})

target_link_libraries(vektrix_OgrePlugin OgreMain)

set_target_properties(vektrix_OgrePlugin PROPERTIES PREFIX "")

