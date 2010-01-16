# include directories
include_directories (../include) 
include_directories (../../../lib/include)
include_directories ($ENV{EXPAT_HOME}/include)

# library directories
link_libraries ($ENV{EXPAT_HOME}/lib/libexpat.so)

# output directory
set (LIBRARY_OUTPUT_PATH ../../../bin)

# build
add_library (
vektrix_XmlPlugin SHARED
../src/vtxxmlEventHandlerBase.cpp
../src/vtxxmlHeaderDataHandler.cpp
../src/vtxxmlMovieParser.cpp
../src/vtxxmlParser.cpp
../src/vtxxmlPlugin.cpp
../src/vtxxmlResourcesDataHandler.cpp
../src/vtxxmlShapeDataHandler.cpp
../src/vtxxmlTimelineDataHandler.cpp
)

# remove "lib" prefix
set_target_properties(vektrix_XmlPlugin PROPERTIES PREFIX "")

