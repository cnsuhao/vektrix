# include directories
include_directories (
../include
../../../core/include
)

# library directories
#link_libraries ($ENV{EXPAT_HOME}/lib/libexpat.so)

# output directory
set (LIBRARY_OUTPUT_PATH ../../../bin)

file(GLOB VTXXML_SRC "../src/*.cpp")

# build
add_library (vektrix_XmlPlugin SHARED ${VTXXML_SRC})

# remove "lib" prefix
set_target_properties(vektrix_XmlPlugin PROPERTIES PREFIX "")

