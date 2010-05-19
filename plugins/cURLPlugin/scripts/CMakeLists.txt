# include directories
include_directories (
../include
../../../core/include
$ENV{CURL_HOME}/include/curl
)

# library directories
#link_libraries ($ENV{CURL_HOME}/lib/libcurl.so)

file(GLOB VTXCURL_SRC "../src/*.cpp")

# output directory
set (LIBRARY_OUTPUT_PATH ../../../bin)

# build
add_library (vektrix_cURLPlugin SHARED ${VTXCURL_SRC})

target_link_libraries(vektrix_cURLPlugin curl)

# remove "lib" prefix
set_target_properties(vektrix_cURLPlugin PROPERTIES PREFIX "")

