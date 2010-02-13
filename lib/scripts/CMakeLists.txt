# include directories
include_directories (../include) 

# preprocessor definitions
add_definitions (-DHAVE_EXPAT_CONFIG_H)

# output directory
set (LIBRARY_OUTPUT_PATH ../../bin)

file (GLOB VTX_SRC "../src/*.cpp")
file (GLOB EXPAT_SRC "../expat/*.c")

# build
add_library (vektrix SHARED ${VTX_SRC} ${EXPAT_SRC})

# remove "lib" prefix
set_target_properties(vektrix PROPERTIES PREFIX "")
