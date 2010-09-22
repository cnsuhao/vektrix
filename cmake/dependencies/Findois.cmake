# Try to find ois
# Once done, this will define
#
#  ois_found			- ois has been found successfully
#  ois_include_dirs	- the ois include directories
#  ois_libraries		- the ois link libraries

set (ois__path "<default>" CACHE STRING "You can use this option to specify an alternate path to the ois dependency")

#-----------------------------------------------------------------------
# WIN32 DISCOVERY
#-----------------------------------------------------------------------
if(WIN32)

	if(ois__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (ois_path ${CMAKE_SOURCE_DIR}/dependencies CACHE INTERNAL "")
		
	else(ois__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (ois_path ${ois__path} CACHE INTERNAL "")
		
	endif(ois__path STREQUAL "<default>")
	
	# try to find the ois libraries & headers from a pre-compiled package
	find_path(ois_include_dirs	NAMES OIS/OIS.h PATHS ${ois_path}/include/ois)
	
	find_library(ois_lib	NAMES OIS	PATHS ${ois_path}/lib/Release)
	find_library(ois_lib_d	NAMES OIS_d	PATHS ${ois_path}/lib/Debug)
	
	if(ois_lib AND ois_lib_d)
		set (ois_libraries
			debug ${ois_lib_d}
			optimized ${ois_lib}
		)
	endif(ois_lib AND ois_lib_d)

endif(WIN32)

# unix discovery
if(UNIX)

	if(ois__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (ois_path /usr CACHE INTERNAL "")
		
	else(ois__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (ois_path ${ois__path} CACHE INTERNAL "")
		
	endif(ois__path STREQUAL "<default>")

	# try to find the ois libraries & headers
	find_path(ois_include_dirs	NAMES OIS.h PATHS ${ois_path}/include/OIS ${ois_path}/local/include/OIS)
	
	find_library(ois_lib		NAMES OIS PATHS ${ois_path}/lib ${ois_path}/local/lib)
	#find_library(ois_lib_d	NAMES ois PATHS ${ois_path}/lib/Debug)
	
	if(ois_lib)# AND ois_lib_d)
		set (ois_libraries
			#debug ${ois_lib_d}
			optimized ${ois_lib}
		)
	endif(ois_lib)# AND ois_lib_d)

endif()

# found ois successfully
if(ois_include_dirs AND ois_libraries)
	set(ois_found TRUE)
endif(ois_include_dirs AND ois_libraries)

# report find result
if(ois_found)
	if(NOT ois_FIND_QUIETLY)
		message(STATUS "Found ois: ${ois_path}")
	endif(NOT ois_FIND_QUIETLY)
else(ois_found)
	if(ois_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find ois")
	endif(ois_FIND_REQUIRED)
endif(ois_found)
