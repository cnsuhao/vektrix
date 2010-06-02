# include directories
include_directories (
../include
../../../core/include
$ENV{CAIRO_HOME}/include/cairo
)

# library directories
#link_libraries ($ENV{CAIRO_HOME}/lib/libcairo.so)

file(GLOB VTXCAI_SRC "../src/*.cpp")

# output directory
set (LIBRARY_OUTPUT_PATH ../../../bin)

# build
add_library (vektrix_CairoPlugin SHARED ${VTXCAI_SRC})

target_link_libraries(vektrix_CairoPlugin cairo)

# remove "lib" prefix
set_target_properties(vektrix_CairoPlugin PROPERTIES PREFIX "")

