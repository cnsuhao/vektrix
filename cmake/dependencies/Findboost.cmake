# Try to find boost
# Once done, this will define
#
#  boost_found			- boost has been found successfully
#  boost_include_dirs	- the boost include directories
#  boost_library_dirs	- the boost link library directories

#-----------------------------------------------------------------------
# WIN32 DISCOVERY
#-----------------------------------------------------------------------
if(WIN32)

	set (boost__path "<default>" CACHE STRING "You can use this option to specify an alternate path to the boost dependency")
	set (boost__version "1_42" CACHE STRING "You can use this option to specify an alternate boost version")
	option (boost__multi_threaded "Use the multithreaded versions of the boostlibraries" ON)
	
	if(MSVC90)
		set (vcvers vc90)
	endif(MSVC90)
	
	if(MSVC10)
		set (vcvers vc100)
	endif(MSVC10)
	
	if(boost__multi_threaded)
		set (boost_mt mt)
	endif(boost__multi_threaded)
	
	if(boost__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (boost_path ${CMAKE_SOURCE_DIR}/dependencies CACHE INTERNAL "")
		
	else(boost__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (boost_path ${boost__path} CACHE INTERNAL "")
		
	endif(boost__path STREQUAL "<default>")
	
	# try to find the boost libraries & headers from a pre-compiled package
	find_path(boost_include_dirs	NAMES boost/version.hpp PATHS ${boost_path}/include/boost)
	
	find_path(boost_release_library_dirs 
		NAMES libboost_thread-${vcvers}-${boost_mt}-${boost__version}.lib 
		PATHS ${boost_path}/lib/Release
	)
	
	find_path(boost_debug_library_dirs 
		NAMES libboost_thread-${vcvers}-${boost_mt}-gd-${boost__version}.lib 
		PATHS ${boost_path}/lib/Debug
	)
	
	if(boost_release_library_dirs AND boost_debug_library_dirs)
		set (boost_library_dirs
			${boost_release_library_dirs}
			${boost_debug_library_dirs}
		)
	endif(boost_release_library_dirs AND boost_debug_library_dirs)

endif(WIN32)

# unix discovery
if(UNIX)
endif()

# found boost successfully
if(boost_include_dirs AND boost_library_dirs)
	set(boost_found TRUE)
endif(boost_include_dirs AND boost_library_dirs)

# report find result
if(boost_found)
	if(NOT boost_FIND_QUIETLY)
		message(STATUS "Found boost: ${boost_path}")
	endif(NOT boost_FIND_QUIETLY)
else(boost_found)
	if(boost_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find boost")
	endif(boost_FIND_REQUIRED)
endif(boost_found)
