set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

#-----------------------------------------------------------------------
# CMAKE OPTIONS
#-----------------------------------------------------------------------

option (PLUGINS_AS3_use_runtime_debugger "Use runtime debugger for the ActionScript 3 plugin" ON)

#-----------------------------------------------------------------------
# PREPROCESSOR SETTINGS
#-----------------------------------------------------------------------

# unix g++ flags
if(UNIX)
	set (CMAKE_CXX_FLAGS "-O -Wcast-align -Wdisabled-optimization -Wextra -Wformat=2 -Winit-self -Winvalid-pch -Wno-invalid-offsetof -Wno-switch -Wparentheses -Wpointer-arith -Wreorder -Wsign-compare -Wwrite-strings -Wno-ctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wno-char-subscripts -fmessage-length=0 -fno-exceptions -fno-rtti -fno-check-new -fstrict-aliasing -fsigned-char -Wstrict-null-sentinel -Werror -Wempty-body -Wno-logical-op -Wmissing-field-initializers -Wstrict-aliasing=3 -Wno-array-bounds -Wno-clobbered -Wstrict-overflow=0 -funit-at-a-time -Wuninitialized")
endif(UNIX)

# generic compiler switches
add_definitions (-DAVMSHELL_BUILD)

if(PLUGINS_AS3_use_runtime_debugger)
	add_definitions (-DCSP_USE_RUNTIME_DEBUGGER)
endif(PLUGINS_AS3_use_runtime_debugger)

# unix compiler switches
if(UNIX)
	add_definitions (-DUNIX -DAVMPLUS_UNIX -DSOFT_ASSERTS)
endif(UNIX)

if(WIN32)
#{
	# disable win32 warnings
	add_definitions ("/wd4291 /wd4996")

	# add uppercase export definition
	add_definitions (-DVEKTRIX_AS3PLUGIN_EXPORTS)
#}
endif(WIN32)

#-----------------------------------------------------------------------
# SOURCE FILES & INCLUDE DIRECTORIES & LINK LIBRARIES
#-----------------------------------------------------------------------

# read the source-files list
include (vektrix_AS3Plugin_src_files)

# the required include directories
set (include_dirs
	../include
	../../../core/include
	${caspin_include_dirs}
)

# the required link libraries
if(PLUGINS_AS3_use_runtime_debugger)
#{
	set (libraries vektrix ${caspin_debugger_libraries})
#}
else(PLUGINS_AS3_use_runtime_debugger)
#{
	set (libraries vektrix ${caspin_libraries})
#}
endif(PLUGINS_AS3_use_runtime_debugger)

#-----------------------------------------------------------------------
# BUILD SETTINGS & COMPILATION
#-----------------------------------------------------------------------

# output directory
set (LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# set the include directories
include_directories (${include_dirs})

# necessary hack to link tamarin on unix
link_libraries (${libraries})

# add the plugin library
add_library (vektrix_AS3Plugin SHARED ${file_root})

# automatically update the source-files list with folders4cmake
auto_rebuild_src_files (vektrix_AS3Plugin)

#if(VTX_STATIC_LIB)
# remove "lib" prefix
set_target_properties (vektrix_AS3Plugin PROPERTIES PREFIX "")
#endif()

# link against the required libraries
target_link_libraries (vektrix_AS3Plugin ${libraries})
