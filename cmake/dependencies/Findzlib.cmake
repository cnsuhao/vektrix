# Try to find zlib
# Once done, this will define
#
#  zlib_found			- zlib has been found successfully
#  zlib_include_dirs	- the zlib include directories
#  zlib_libraries		- the zlib link libraries

set (zlib__path "<default>" CACHE STRING "You can use this option to specify an alternate path to the zlib dependency")

# win32 discovery
if(WIN32)

	if(zlib__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (zlib_path ${CMAKE_SOURCE_DIR}/dependencies CACHE INTERNAL "")
	
	else(zlib__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (zlib_path ${zlib__path} CACHE INTERNAL "")
	
	endif(zlib__path STREQUAL "<default>")
	
	# try to find the zlib libraries & headers from a pre-compiled package
	find_path(zlib_include_dirs	NAMES zlib.h PATHS ${zlib_path}/include/zlib)
	
	find_library(zlib_lib	NAMES zlib	PATHS ${zlib_path}/lib/Release)
	find_library(zlib_lib_d	NAMES zlibd	PATHS ${zlib_path}/lib/Debug)
	
	if(zlib_lib AND zlib_lib_d)
		set (zlib_libraries
			debug ${zlib_lib_d}
			optimized ${zlib_lib}
		)
	endif(zlib_lib AND zlib_lib_d)

endif(WIN32)

# unix discovery
if(UNIX)

	if(zlib__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (zlib_path /usr CACHE INTERNAL "")
		
	else(zlib__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (zlib_path ${zlib__path} CACHE INTERNAL "")
		
	endif(zlib__path STREQUAL "<default>")

	# try to find the zlib libraries & headers
	find_path(zlib_include_dirs	NAMES zlib.h PATHS ${zlib_path}/include/zlib ${zlib_path}/local/include/zlib)
	
	find_library(zlib_lib		NAMES libz.a PATHS ${zlib_path}/lib ${zlib_path}/local/lib)
	#find_library(zlib_lib_d	NAMES zlib PATHS ${zlib_path}/lib/Debug)
	
	if(zlib_lib)# AND zlib_lib_d)
		set (zlib_libraries
			#debug ${zlib_lib_d}
			optimized ${zlib_lib}
		)
	endif(zlib_lib)# AND zlib_lib_d)

endif()

# found zlib successfully
if(zlib_include_dirs AND zlib_libraries)
	set(zlib_found TRUE)
endif(zlib_include_dirs AND zlib_libraries)

# report find result
if(zlib_found)
	if(NOT zlib_FIND_QUIETLY)
		message(STATUS "Found zlib: ${zlib_path}")
	endif(NOT zlib_FIND_QUIETLY)
else(zlib_found)
	if(zlib_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find zlib")
	endif(zlib_FIND_REQUIRED)
endif(zlib_found)
