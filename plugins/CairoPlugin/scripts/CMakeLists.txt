# include directories
include_directories (../include) 
include_directories (../../../lib/include)
include_directories ($ENV{CAIRO_HOME}/include/cairo)

# library directories
link_libraries ($ENV{CAIRO_HOME}/lib/libcairo.so)

# output directory
set (LIBRARY_OUTPUT_PATH ../../../bin)

# build
add_library (
vektrix_CairoPlugin SHARED  
../src/vtxcaiPlugin.cpp
../src/vtxcaiRasterizer.cpp
)

# remove "lib" prefix
set_target_properties(vektrix_CairoPlugin PROPERTIES PREFIX "")

