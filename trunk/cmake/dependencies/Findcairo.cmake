# Try to find cairo
# Once done, this will define
#
#  cairo_found			- cairo has been found successfully
#  cairo_include_dirs	- the cairo include directories
#  cairo_libraries		- the cairo link libraries

set (cairo__path "<default>" CACHE STRING "You can use this option to specify an alternate path to the cairo dependency")

# win32 discovery
if(WIN32)

	if(cairo__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (cairo_path ${CMAKE_SOURCE_DIR}/dependencies CACHE INTERNAL "")
		
	else(cairo__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (cairo_path ${cairo__path} CACHE INTERNAL "")
		
	endif(cairo__path STREQUAL "<default>")
	
	# try to find the cairo libraries & headers from a pre-compiled package
	find_path(cairo_include_dirs	NAMES cairo.h PATHS ${cairo_path}/include/cairo)
	
	find_library(cairo_lib		NAMES cairo PATHS ${cairo_path}/lib/Release)
	find_library(cairo_lib_d	NAMES cairo PATHS ${cairo_path}/lib/Debug)
	
	if(cairo_lib AND cairo_lib_d)
		set (cairo_libraries
			debug ${cairo_lib_d}
			optimized ${cairo_lib}
		)
	endif(cairo_lib AND cairo_lib_d)

endif(WIN32)

# unix discovery
if(UNIX)

	if(cairo__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (cairo_path /usr CACHE INTERNAL "")
		
	else(cairo__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (cairo_path ${cairo__path} CACHE INTERNAL "")
		
	endif(cairo__path STREQUAL "<default>")

	# try to find the cairo libraries & headers
	find_path(cairo_include_dirs	NAMES cairo.h PATHS ${cairo_path}/include/cairo ${cairo_path}/local/include/cairo)
	
	find_library(cairo_lib		NAMES cairo PATHS ${cairo_path}/lib ${cairo_path}/local/lib)
	#find_library(cairo_lib_d	NAMES cairo PATHS ${cairo_path}/lib/Debug)
	
	if(cairo_lib)# AND cairo_lib_d)
		set (cairo_libraries
			#debug ${cairo_lib_d}
			optimized ${cairo_lib}
		)
	endif(cairo_lib)# AND cairo_lib_d)

endif()

# found cairo successfully
if(cairo_include_dirs AND cairo_libraries)
	set(cairo_found TRUE)
endif(cairo_include_dirs AND cairo_libraries)

# report find result
if(cairo_found)
	if(NOT cairo_FIND_QUIETLY)
		message(STATUS "Found cairo: ${cairo_path}")
	endif(NOT cairo_FIND_QUIETLY)
else(cairo_found)
	if(cairo_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find cairo")
	endif(cairo_FIND_REQUIRED)
endif(cairo_found)
