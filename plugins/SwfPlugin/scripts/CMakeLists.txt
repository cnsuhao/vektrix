# include directories
include_directories (../include) 
include_directories (../../../lib/include)

# output directory
set (LIBRARY_OUTPUT_PATH ../../../bin)

# build
add_library (
vektrix_SwfPlugin SHARED  
../src/vtxswfContourElement.cpp
../src/vtxswfContourPoint.cpp
../src/vtxswfHandleDefineButton2.cpp
../src/vtxswfHandleDefineShape.cpp
../src/vtxswfHandlePlaceObject2.cpp
../src/vtxswfHandleShowFrame.cpp
../src/vtxswfHandleSymbolClass.cpp
../src/vtxswfParser.cpp
../src/vtxswfPlugin.cpp
)

# remove "lib" prefix
set_target_properties(vektrix_SwfPlugin PROPERTIES PREFIX "")

