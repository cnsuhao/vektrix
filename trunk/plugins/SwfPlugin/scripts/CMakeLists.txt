# include directories
include_directories (
../include
../../../core/include
)

# output directory
set (LIBRARY_OUTPUT_PATH ../../../bin)

file(GLOB VTXSWF_SRC "../src/*.cpp")

# build
add_library (vektrix_SwfPlugin SHARED ${VTXSWF_SRC})

# remove "lib" prefix
set_target_properties(vektrix_SwfPlugin PROPERTIES PREFIX "")

