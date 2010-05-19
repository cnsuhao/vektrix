include_directories (
../include
../../../core/include
../../../plugins/AS3Plugin/include
../../../plugins/CairoPlugin/include
../../../plugins/cURLPlugin/include
../../../plugins/D3D9Plugin/include
../../../plugins/FreeImgPlugin/include
../../../plugins/OgrePlugin/include
../../../plugins/SwfPlugin/include
../../../plugins/XmlPlugin/include
$ENV{OGRE_HOME}/include/OGRE
)

#link_libraries ($ENV{OGRE_HOME}/lib/libOgreMain.so)
#link_libraries ($ENV{OIS_HOME}/lib/libOIS.so)

set (EXECUTABLE_OUTPUT_PATH ../../../bin)

add_executable (vektrix_Ogre3D_demo
../src/Ogre3D_Demo.cpp
)

set_target_properties(vektrix_Ogre3D_demo PROPERTIES PREFIX "")

target_link_libraries (
vektrix_Ogre3D_demo
vektrix
OgreMain
OIS
)

