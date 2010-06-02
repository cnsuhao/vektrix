# include directories
include_directories (
../include
$ENV{EXPAT_HOME}/lib
) 

# library dependencies
#link_libraries ($ENV{EXPAT_HOME}/lib/libexpat.so)

# output directory
set (LIBRARY_OUTPUT_PATH ../../bin)

file (GLOB VTX_SRC "../src/*.cpp")

# build
add_library (vektrix SHARED ${VTX_SRC})

target_link_libraries(vektrix expat)
