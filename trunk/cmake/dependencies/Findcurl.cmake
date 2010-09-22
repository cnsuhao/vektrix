# Try to find curl
# Once done, this will define
#
#  curl_found			- curl has been found successfully
#  curl_include_dirs	- the curl include directories
#  curl_libraries		- the curl link libraries

set (curl__path "<default>" CACHE STRING "You can use this option to specify an alternate path to the curl dependency")

# win32 discovery
if(WIN32)

	if(curl__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (curl_path ${CMAKE_SOURCE_DIR}/dependencies CACHE INTERNAL "")
		
	else(curl__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (curl_path ${curl__path} CACHE INTERNAL "")
		
	endif(curl__path STREQUAL "<default>")
	
	# try to find the curl libraries & headers from a pre-compiled package
	find_path(curl_include_dirs	NAMES curl.h PATHS ${curl_path}/include/curl)
	
	find_library(curl_lib	NAMES libcurl PATHS ${curl_path}/lib/Release)
	find_library(curl_lib_d	NAMES libcurld PATHS ${curl_path}/lib/Debug)
	
	if(curl_lib AND curl_lib_d)
		set (curl_libraries
			debug ${curl_lib_d}
			optimized ${curl_lib}
			wldap32 ws2_32
		)
	endif(curl_lib AND curl_lib_d)

endif(WIN32)

# unix discovery
if(UNIX)

	if(curl__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (curl_path /usr CACHE INTERNAL "")
		
	else(curl__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (curl_path ${curl__path} CACHE INTERNAL "")
		
	endif(curl__path STREQUAL "<default>")

	# try to find the curl libraries & headers
	find_path(curl_include_dirs	NAMES curl.h PATHS ${curl_path}/include/curl ${curl_path}/local/include/curl)
	
	find_library(curl_lib		NAMES curl PATHS ${curl_path}/lib ${curl_path}/local/lib)
	#find_library(curl_lib_d	NAMES curl PATHS ${curl_path}/lib/Debug)
	
	if(curl_lib)# AND curl_lib_d)
		set (curl_libraries
			#debug ${curl_lib_d}
			optimized ${curl_lib}
		)
	endif(curl_lib)# AND curl_lib_d)

endif()

# found curl successfully
if(curl_include_dirs AND curl_libraries)
	set(curl_found TRUE)
endif(curl_include_dirs AND curl_libraries)

# report find result
if(curl_found)
	if(NOT curl_FIND_QUIETLY)
		message(STATUS "Found curl: ${curl_path}")
	endif(NOT curl_FIND_QUIETLY)
else(curl_found)
	if(curl_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find curl")
	endif(curl_FIND_REQUIRED)
endif(curl_found)
