# Try to find caspin
# Once done, this will define
#
#  caspin_found					- caspin has been found successfully
#  caspin_include_dirs			- the caspin include directories
#  caspin_libraries				- the caspin link libraries
#  caspin_debugger_libraries	- the caspin link libraries (runtime debugger enabled)

set (caspin__path "<default>" CACHE STRING "You can use this option to specify an alternate path to the caspin dependency")

# win32 discovery
if(WIN32)

	if(caspin__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (caspin_path ${CMAKE_SOURCE_DIR}/dependencies CACHE INTERNAL "")
		
	else(caspin__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (caspin_path ${caspin__path} CACHE INTERNAL "")
		
	endif(caspin__path STREQUAL "<default>")
	
	# try to find the caspin libraries & headers from a pre-compiled package
	find_library(caspin_lib		NAMES caspin	PATHS ${caspin_path}/lib/Release)
	find_library(caspin_lib_d	NAMES caspin	PATHS ${caspin_path}/lib/Debug)
	
	find_library(caspin_debugger_lib	NAMES caspin_debugger	PATHS ${caspin_path}/lib/Release)
	find_library(caspin_debugger_lib_d	NAMES caspin_debugger	PATHS ${caspin_path}/lib/Debug)
	
	find_path(caspin_include_dirs	NAMES cspPrerequisites.h PATHS ${caspin_path}/include/caspin)
	
	# try to find the caspin libraries from a default caspin source directory
	if(NOT caspin_lib OR NOT caspin_lib_d OR NOT caspin_debugger_lib OR NOT caspin_debugger_lib_d OR NOT caspin_include_dirs)
		
		if(EXISTS "${caspin__path}/cmake/caspin_import_${CMAKE_GENERATOR}.cmake")
			
			# import caspin dependency settings from cmake
			set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${caspin_path}/cmake)
			include (caspin_import_${CMAKE_GENERATOR})
						
			set (caspin_debugger_lib caspin_debugger)
			set (caspin_debugger_lib_d caspin_debugger)
			
			set (caspin_lib caspin)
			set (caspin_lib_d caspin)
			
		endif(EXISTS "${caspin__path}/cmake/caspin_import_${CMAKE_GENERATOR}.cmake")
		
	endif(NOT caspin_lib OR NOT caspin_lib_d OR NOT caspin_debugger_lib OR NOT caspin_debugger_lib_d OR NOT caspin_include_dirs)
	
	# the default libraries
	set (caspin_libraries
		debug ${caspin_lib_d}
		optimized ${caspin_lib}
	)
	
	# the runtime debugger enabled libraries
	set (caspin_debugger_libraries
		debug ${caspin_debugger_lib_d}
		optimized ${caspin_debugger_lib}
	)

endif(WIN32)

# unix discovery
if(UNIX)

	if(caspin__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (caspin_path /usr CACHE INTERNAL "")
		
	else(caspin__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (caspin_path ${caspin__path} CACHE INTERNAL "")
		
	endif(caspin__path STREQUAL "<default>")
	
	# try to find the caspin libraries & headers from a pre-compiled package
	find_library(caspin_lib		NAMES caspin	PATHS ${caspin_path}/lib ${caspin_path}/local/lib)
	#find_library(caspin_lib_d	NAMES caspin	PATHS ${caspin_path}/lib/Debug)

	find_library(caspin_debugger_lib	NAMES caspin_debugger	PATHS ${caspin_path}/lib)
	#find_library(caspin_debugger_lib_d	NAMES caspin_debugger	PATHS ${caspin_path}/lib/Debug)
	
	find_path(caspin_include_dirs	NAMES cspPrerequisites.h PATHS ${caspin_path}/include/caspin ${caspin_path}/local/include/caspin)
	
	# try to find the caspin libraries from a default caspin source directory
	if(NOT caspin_lib OR NOT caspin_include_dirs)
	#if(NOT caspin_lib OR NOT caspin_lib_d OR NOT caspin_debugger_lib OR NOT caspin_debugger_lib_d OR NOT caspin_include_dirs)
		
		if(EXISTS "${caspin__path}/cmake/caspin_import_${CMAKE_GENERATOR}.cmake")
			
			# import caspin dependency settings from cmake
			set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${caspin_path}/cmake)
			include (caspin_import_${CMAKE_GENERATOR})
						
			set (caspin_debugger_lib caspin_debugger)
			#set (caspin_debugger_lib_d caspin_debugger)
			
			set (caspin_lib caspin)
			#set (caspin_lib_d caspin)
			
		endif(EXISTS "${caspin__path}/cmake/caspin_import_${CMAKE_GENERATOR}.cmake")
		
	#endif(NOT caspin_lib OR NOT caspin_lib_d OR NOT caspin_debugger_lib OR NOT caspin_debugger_lib_d OR NOT caspin_include_dirs)
	endif(NOT caspin_lib OR NOT caspin_include_dirs)

	# the default libraries
	set (caspin_libraries
		${caspin_lib}
	)
	
	# the runtime debugger enabled libraries
	set (caspin_debugger_libraries
		${caspin_debugger_lib}
	)

endif()

# found caspin successfully
if(caspin_include_dirs AND caspin_libraries AND caspin_debugger_libraries)
	set(caspin_found TRUE)
endif(caspin_include_dirs AND caspin_libraries AND caspin_debugger_libraries)

# report find result
if(caspin_found)
	if(NOT caspin_FIND_QUIETLY)
		message(STATUS "Found caspin: ${caspin_path}")
	endif(NOT caspin_FIND_QUIETLY)
else(caspin_found)
	if(caspin_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find caspin")
	endif(caspin_FIND_REQUIRED)
endif(caspin_found)

# search for the tamarin dependency
find_package (tamarin REQUIRED)

# append tamarin include directories
set (caspin_include_dirs
	${tamarin_include_dirs}
	${caspin_include_dirs}
)

# append tamarin default libraries
set (caspin_libraries
	${tamarin_libs}
	${caspin_libraries}
)

# append tamarin debugger libraries
set (caspin_debugger_libraries
	${tamarin_debugger_libs}
	${caspin_debugger_libraries}
)
