# include directories
include_directories (../include) 
include_directories (../../../lib/include)
include_directories ($ENV{CAIRO_HOME}/include/cairo)

# library directories
link_libraries ($ENV{CAIRO_HOME}/lib/libcairo.so)

file(GLOB VTXCAI_SRC "../src/*.cpp")

# output directory
set (LIBRARY_OUTPUT_PATH ../../../bin)

# build
add_library (vektrix_CairoPlugin SHARED ${VTXCAI_SRC})

# remove "lib" prefix
set_target_properties(vektrix_CairoPlugin PROPERTIES PREFIX "")

