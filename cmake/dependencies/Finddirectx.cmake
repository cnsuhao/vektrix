# Try to find directx
# Once done, this will define
#
#  directx_found			- directx has been found successfully
#  directx_include_dirs	- the directx include directories
#  directx_libraries		- the directx link libraries

set (directx__path "<default>" CACHE STRING "You can use this option to specify an alternate path to the directx dependency")

# win32 discovery
if(WIN32)

	if(directx__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (directx_path "" CACHE INTERNAL "")
		
	else(directx__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (directx_path ${directx__path} CACHE INTERNAL "")
		
	endif(directx__path STREQUAL "<default>")
	
	# try to find the directx libraries & headers from a pre-compiled package
	find_path(directx_include_dirs	NAMES d3d9.h PATHS ${directx_path}/include)

	find_library(directx_d3d9_lib		NAMES d3d9 PATHS ${directx_path}/Lib/x86)
	find_library(directx_d3dx9_lib		NAMES d3dx9 PATHS ${directx_path}/Lib/x86)
	find_library(directx_dxerr_lib		NAMES dxerr PATHS ${directx_path}/Lib/x86)
	find_library(directx_dxguid_lib		NAMES dxguid PATHS ${directx_path}/Lib/x86)

	if(directx_d3d9_lib AND directx_d3dx9_lib AND directx_dxerr_lib AND directx_dxguid_lib)
		set (directx_libraries
			${directx_d3d9_lib}
			${directx_d3dx9_lib}
			${directx_dxerr_lib}
			${directx_dxguid_lib}
		)
	endif(directx_d3d9_lib AND directx_d3dx9_lib AND directx_dxerr_lib AND directx_dxguid_lib)

endif(WIN32)

# found directx successfully
if(directx_include_dirs AND directx_libraries)
	set(directx_found TRUE)
endif(directx_include_dirs AND directx_libraries)

# report find result
if(directx_found)
	if(NOT directx_FIND_QUIETLY)
		message(STATUS "Found directx: ${directx_path}")
	endif(NOT directx_FIND_QUIETLY)
else(directx_found)
	if(directx_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find directx")
	endif(directx_FIND_REQUIRED)
endif(directx_found)
