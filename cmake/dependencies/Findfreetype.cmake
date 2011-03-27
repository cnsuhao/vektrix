# Try to find freetype
# Once done, this will define
#
#  freetype_found			- freetype has been found successfully
#  freetype_include_dirs	- the freetype include directories
#  freetype_libraries		- the freetype link libraries

set (freetype__path "<default>" CACHE STRING "You can use this option to specify an alternate path to the freetype dependency")

# win32 discovery
if(WIN32)

	if(freetype__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (freetype_path ${CMAKE_SOURCE_DIR}/dependencies CACHE INTERNAL "")
		
	else(freetype__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (freetype_path ${freetype__path} CACHE INTERNAL "")
		
	endif(freetype__path STREQUAL "<default>")
	
	# try to find the freetype libraries & headers from a pre-compiled package
	find_path(freetype_include_dirs NAMES ft2build.h PATHS ${freetype_path}/include/freetype)
	
	find_library(freetype_lib	NAMES freetype244MT.lib		PATHS ${freetype_path}/lib/Release)
	find_library(freetype_lib_d	NAMES freetype244MT_D.lib	PATHS ${freetype_path}/lib/Debug)
	
	if(freetype_lib AND freetype_lib_d)
		set (freetype_libraries
			debug ${freetype_lib_d}
			optimized ${freetype_lib}
		)
	endif(freetype_lib AND freetype_lib_d)

endif(WIN32)

# unix discovery
if(UNIX)

	if(freetype__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (freetype_path /usr CACHE INTERNAL "")
		
	else(freetype__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (freetype_path ${freetype__path} CACHE INTERNAL "")
		
	endif(freetype__path STREQUAL "<default>")

	# try to find the freetype libraries & headers
	find_path(freetype_include_dirs	NAMES FreeType.h PATHS ${freetype_path}/include/freetype ${freetype_path}/local/include/freetype)
	
	find_library(freetype_lib		NAMES freetype PATHS ${freetype_path}/lib ${freetype_path}/local/lib)
	#find_library(freetype_lib_d	NAMES freetype PATHS ${freetype_path}/lib/Debug)
	
	if(freetype_lib)# AND freetype_lib_d)
		set (freetype_libraries
			#debug ${freetype_lib_d}
			optimized ${freetype_lib}
		)
	endif(freetype_lib)# AND freetype_lib_d)

endif()

# found freetype successfully
if(freetype_include_dirs AND freetype_libraries)
	set(freetype_found TRUE)
endif(freetype_include_dirs AND freetype_libraries)

# report find result
if(freetype_found)
	if(NOT freetype_FIND_QUIETLY)
		message(STATUS "Found freetype: ${freetype_path}")
	endif(NOT freetype_FIND_QUIETLY)
else(freetype_found)
	if(freetype_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find freetype")
	endif(freetype_FIND_REQUIRED)
endif(freetype_found)
