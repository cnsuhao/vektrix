# include directories
include_directories (
../include
../../../core/include
$ENV{CASPIN_HOME}/include
$ENV{CASPIN_HOME}/tamarin/core
$ENV{CASPIN_HOME}/tamarin/VMPI
$ENV{CASPIN_HOME}/tamarin/shell
$ENV{CASPIN_HOME}/tamarin/platform
$ENV{CASPIN_HOME}/tamarin/MMgc
$ENV{CASPIN_HOME}/tamarin/eval
$ENV{CASPIN_HOME}/tamarin/extensions
)

link_directories (
$ENV{CASPIN_HOME}/lib
$ENV{CASPIN_HOME}/tamarin/bin
)

# library dependencies
link_libraries (
caspin
pthread
MMgc
avmplus
eval
zlib
)

set (CMAKE_CXX_FLAGS "-O -Wcast-align -Wdisabled-optimization -Wextra -Wformat=2 -Winit-self -Winvalid-pch -Wno-invalid-offsetof -Wno-switch -Wparentheses -Wpointer-arith -Wreorder -Wsign-compare -Wwrite-strings -Wno-ctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wno-char-subscripts -fmessage-length=0 -fno-exceptions -fno-check-new -fstrict-aliasing -fsigned-char  -Wstrict-null-sentinel -Wempty-body -Wno-logical-op -Wmissing-field-initializers -Wstrict-aliasing=3 -Wno-array-bounds -Wno-clobbered -Wstrict-overflow=0 -funit-at-a-time  -Wuninitialized")

# preprocessor definitions
add_definitions (-DAVMSHELL_BUILD -DUNIX -DAVMPLUS_UNIX -DSOFT_ASSERTS)

# output directory
set (LIBRARY_OUTPUT_PATH ../../../bin)

file (GLOB VTXAS3_SRC "../src/vtxas3*.cpp")

# build
add_library (
vektrix_AS3Plugin SHARED  
../src/flash_package.cpp
${VTXAS3_SRC}
)

target_link_libraries (
vektrix_AS3Plugin
caspin
pthread
MMgc
avmplus
eval
zlib
)

# remove "lib" prefix
set_target_properties(vektrix_AS3Plugin PROPERTIES PREFIX "")

