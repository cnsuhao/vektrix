include_directories (../include)
include_directories (../../../lib/include)

include_directories (../../../plugins/AS3Plugin/include)
include_directories (../../../plugins/Direct3D9Plugin/include)
include_directories (../../../plugins/CairoPlugin/include)
include_directories (../../../plugins/OgrePlugin/include)
include_directories (../../../plugins/SwfPlugin/include)
include_directories (../../../plugins/XmlPlugin/include)

include_directories ($ENV{OGRE_HOME}/include/OGRE)

link_libraries ($ENV{OGRE_HOME}/lib/libOgreMain.so)
link_libraries ($ENV{OIS_HOME}/lib/libOIS.so)

set (EXECUTABLE_OUTPUT_PATH ../../../bin)

add_executable (vektrix_Ogre3D_demo
../src/Ogre3D_Demo.cpp
)

set_target_properties(vektrix_Ogre3D_demo PROPERTIES PREFIX "")

target_link_libraries (vektrix_Ogre3D_demo vektrix)

