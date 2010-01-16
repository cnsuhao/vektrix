# include directories
include_directories (../include)
include_directories (../../../lib/include)
include_directories ($ENV{CASPIN_HOME}/include)
include_directories ($ENV{CASPIN_HOME}/tamarin/core)
include_directories ($ENV{CASPIN_HOME}/tamarin/VMPI)
include_directories ($ENV{CASPIN_HOME}/tamarin/shell)
include_directories ($ENV{CASPIN_HOME}/tamarin/platform)
include_directories ($ENV{CASPIN_HOME}/tamarin/MMgc)
include_directories ($ENV{CASPIN_HOME}/tamarin/eval)
include_directories ($ENV{CASPIN_HOME}/tamarin/extensions)

# library dependencies
link_libraries ($ENV{CASPIN_HOME}/lib/caspin.a)

# preprocessor definitions
add_definitions (-DUNIX)

# output directory
set (LIBRARY_OUTPUT_PATH ../../../bin)

# build
add_library (
vektrix_AS3Plugin SHARED  
../src/flash_package.cpp
../src/vtxas3DisplayObject.cpp
../src/vtxas3DisplayObjectContainer.cpp
../src/vtxas3EventDispatcher.cpp
../src/vtxas3EventHandler.cpp
../src/vtxas3InteractiveObject.cpp
../src/vtxas3MovieClip.cpp
../src/vtxas3Plugin.cpp
../src/vtxas3ScriptEngine.cpp
../src/vtxas3SimpleButton.cpp
../src/vtxas3Sprite.cpp
)

# remove "lib" prefix
set_target_properties(vektrix_AS3Plugin PROPERTIES PREFIX "")

