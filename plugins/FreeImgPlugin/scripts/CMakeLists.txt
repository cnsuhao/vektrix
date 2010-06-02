# include directories
include_directories (
../include
../../../core/include
/usr/include
)

# library directories
#link_libraries (/usr/lib/libfreeimage.so)

file(GLOB VTXFREEIMG_SRC "../src/*.cpp")

# output directory
set (LIBRARY_OUTPUT_PATH ../../../bin)

# build
add_library (vektrix_FreeImgPlugin SHARED ${VTXFREEIMG_SRC})

target_link_libraries(vektrix_FreeImgPlugin freeimage)

# remove "lib" prefix
set_target_properties(vektrix_FreeImgPlugin PROPERTIES PREFIX "")

