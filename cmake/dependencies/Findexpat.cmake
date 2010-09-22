# Try to find expat
# Once done, this will define
#
#  expat_found			- expat has been found successfully
#  expat_include_dirs	- the expat include directories
#  expat_libraries		- the expat link libraries

set (expat__path "<default>" CACHE STRING "You can use this option to specify an alternate path to the expat dependency")

# win32 discovery
if(WIN32)

	if(expat__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (expat_path ${CMAKE_SOURCE_DIR}/dependencies CACHE INTERNAL "")
		
	else(expat__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (expat_path ${expat__path} CACHE INTERNAL "")
		
	endif(expat__path STREQUAL "<default>")
	
	# try to find the expat libraries & headers from a pre-compiled package
	find_path(expat_include_dirs	NAMES expat.h PATHS ${expat_path}/include/expat)
	
	find_library(expat_lib		NAMES libexpatMT PATHS ${expat_path}/lib/Release)
	find_library(expat_lib_d	NAMES libexpatMT PATHS ${expat_path}/lib/Debug)
	
	if(expat_lib AND expat_lib_d)
		set (expat_libraries
			debug ${expat_lib_d}
			optimized ${expat_lib}
		)
	endif(expat_lib AND expat_lib_d)

endif(WIN32)

# unix discovery
if(UNIX)

	if(expat__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (expat_path /usr CACHE INTERNAL "")
		
	else(expat__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (expat_path ${expat__path} CACHE INTERNAL "")
		
	endif(expat__path STREQUAL "<default>")

	# try to find the expat libraries & headers
	find_path(expat_include_dirs	NAMES expat.h PATHS ${expat_path}/include/expat ${expat_path}/local/include/expat)
	
	find_library(expat_lib		NAMES expat PATHS ${expat_path}/lib ${expat_path}/local/lib)
	#find_library(expat_lib_d	NAMES expat PATHS ${expat_path}/lib/Debug)
	
	if(expat_lib)# AND expat_lib_d)
		set (expat_libraries
			#debug ${expat_lib_d}
			optimized ${expat_lib}
		)
	endif(expat_lib)# AND expat_lib_d)

endif()

# found expat successfully
if(expat_include_dirs AND expat_libraries)
	set(expat_found TRUE)
endif(expat_include_dirs AND expat_libraries)

# report find result
if(expat_found)
	if(NOT expat_FIND_QUIETLY)
		message(STATUS "Found expat: ${expat_path}")
	endif(NOT expat_FIND_QUIETLY)
else(expat_found)
	if(expat_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find expat")
	endif(expat_FIND_REQUIRED)
endif(expat_found)
