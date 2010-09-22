# Try to find freeimage
# Once done, this will define
#
#  freeimage_found			- freeimage has been found successfully
#  freeimage_include_dirs	- the freeimage include directories
#  freeimage_libraries		- the freeimage link libraries

set (freeimage__path "<default>" CACHE STRING "You can use this option to specify an alternate path to the freeimage dependency")

# win32 discovery
if(WIN32)

	if(freeimage__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (freeimage_path ${CMAKE_SOURCE_DIR}/dependencies CACHE INTERNAL "")
		
	else(freeimage__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (freeimage_path ${freeimage__path} CACHE INTERNAL "")
		
	endif(freeimage__path STREQUAL "<default>")
	
	# try to find the freeimage libraries & headers from a pre-compiled package
	find_path(freeimage_include_dirs NAMES freeimage.h PATHS ${freeimage_path}/include/freeimage)
	
	find_library(freeimage_lib		NAMES freeimage		PATHS ${freeimage_path}/lib/Release)
	find_library(freeimage_lib_d	NAMES freeimaged	PATHS ${freeimage_path}/lib/Debug)
	
	if(freeimage_lib AND freeimage_lib_d)
		set (freeimage_libraries
			debug ${freeimage_lib_d}
			optimized ${freeimage_lib}
		)
	endif(freeimage_lib AND freeimage_lib_d)

endif(WIN32)

# unix discovery
if(UNIX)

	if(freeimage__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (freeimage_path /usr CACHE INTERNAL "")
		
	else(freeimage__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (freeimage_path ${freeimage__path} CACHE INTERNAL "")
		
	endif(freeimage__path STREQUAL "<default>")

	# try to find the freeimage libraries & headers
	find_path(freeimage_include_dirs	NAMES FreeImage.h PATHS ${freeimage_path}/include/freeimage ${freeimage_path}/local/include/freeimage)
	
	find_library(freeimage_lib		NAMES freeimage PATHS ${freeimage_path}/lib ${freeimage_path}/local/lib)
	#find_library(freeimage_lib_d	NAMES freeimage PATHS ${freeimage_path}/lib/Debug)
	
	if(freeimage_lib)# AND freeimage_lib_d)
		set (freeimage_libraries
			#debug ${freeimage_lib_d}
			optimized ${freeimage_lib}
		)
	endif(freeimage_lib)# AND freeimage_lib_d)

endif()

# found freeimage successfully
if(freeimage_include_dirs AND freeimage_libraries)
	set(freeimage_found TRUE)
endif(freeimage_include_dirs AND freeimage_libraries)

# report find result
if(freeimage_found)
	if(NOT freeimage_FIND_QUIETLY)
		message(STATUS "Found freeimage: ${freeimage_path}")
	endif(NOT freeimage_FIND_QUIETLY)
else(freeimage_found)
	if(freeimage_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find freeimage")
	endif(freeimage_FIND_REQUIRED)
endif(freeimage_found)
