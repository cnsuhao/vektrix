#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

#######################################################################
# This file takes care of configuring Ogre to build with the settings
# given in CMake. It creates the necessary config.h file and will 
# also prepare package files for pkg-config and CMake.
#######################################################################

string(TOLOWER "${CMAKE_BUILD_TYPE}" VEKTRIX_BUILD_TYPE)
if (VEKTRIX_BUILD_TYPE STREQUAL "debug")
	add_definitions(-DDEBUG)
endif()

# should we build static libs?
if (VEKTRIX_STATIC)
  set(VEKTRIX_LIB_TYPE STATIC)
else ()
  set(VEKTRIX_LIB_TYPE SHARED)
endif ()

# configure threading options
set(VEKTRIX_THREAD_PROVIDER 0)
if (VEKTRIX_CONFIG_THREADS)
	if (UNIX)
		add_definitions(-pthread)
	endif ()

	if (VEKTRIX_CONFIG_THREAD_PROVIDER STREQUAL "boost")
		set(VEKTRIX_THREAD_PROVIDER 1)
		include_directories(${Boost_INCLUDE_DIRS})
		# On MSVC Boost usually tries to autolink boost libraries. However since
		# this behaviour is not available on all compilers, we need to find the libraries
		# ourselves, anyway. Disable auto-linking to avoid mess-ups.
		add_definitions(-DBOOST_ALL_NO_LIB)
		set(VEKTRIX_THREAD_LIBRARIES ${Boost_LIBRARIES})
	endif ()
endif()


#
# determine config values depending on build options 
#
set(VEKTRIX_SET_MEMTRACK_DEBUG 0)
set(VEKTRIX_SET_MEMTRACK_RELEASE 0)
set(VEKTRIX_SET_THREADS ${VEKTRIX_CONFIG_THREADS})
set(VEKTRIX_SET_THREAD_PROVIDER ${VEKTRIX_THREAD_PROVIDER})
set(VEKTRIX_STATIC_LIB 0)
set(VEKTRIX_SET_USE_BOOST 0)

if (VEKTRIX_CONFIG_MEMTRACK_DEBUG)
  set(VEKTRIX_SET_MEMTRACK_DEBUG 1)
endif()
if (VEKTRIX_CONFIG_MEMTRACK_RELEASE)
  set(VEKTRIX_SET_MEMTRACK_RELEASE 1)
endif()
if (NOT VEKTRIX_CONFIG_ENABLE_ZIP)
  set(VEKTRIX_SET_DISABLE_ZIP 1)
endif()
if (VEKTRIX_STATIC)
  set(VEKTRIX_STATIC_LIB 1)
endif()
if (VEKTRIX_USE_BOOST)
  set(VEKTRIX_SET_USE_BOOST 1)
endif()

if (VEKTRIX_TEST_BIG_ENDIAN)
  set(VEKTRIX_CONFIG_BIG_ENDIAN 1)
else ()
  set(VEKTRIX_CONFIG_LITTLE_ENDIAN 1)
endif ()

#
# generate vtxBuildSettings.h 
#
configure_file(${VEKTRIX_TEMPLATES_DIR}/vtxBuildSettings.h.in ${VEKTRIX_BINARY_DIR}/include/vtxBuildSettings.h @ONLY)
install(FILES ${VEKTRIX_BINARY_DIR}/include/vtxBuildSettings.h DESTINATION include/Vektrix)


#
# Create the pkg-config package files on Unix systems
#
if (UNIX)
  set(VEKTRIX_LIB_SUFFIX "")
  set(VEKTRIX_PLUGIN_PREFIX "")
  set(VEKTRIX_PLUGIN_EXT ".so")
  set(VEKTRIX_PAGING_ADDITIONAL_PACKAGES "")
  if (VEKTRIX_STATIC)
    set(VEKTRIX_LIB_SUFFIX "${VEKTRIX_LIB_SUFFIX}Static")
    set(VEKTRIX_PLUGIN_PREFIX "lib")
    set(VEKTRIX_PLUGIN_EXT ".a")
  endif ()
  if (VEKTRIX_BUILD_TYPE STREQUAL "debug")
    set(VEKTRIX_LIB_SUFFIX "${VEKTRIX_LIB_SUFFIX}_d")
  endif ()

  set(VEKTRIX_ADDITIONAL_LIBS "")
  set(VEKTRIX_CFLAGS "")
  set(VEKTRIX_PREFIX_PATH ${CMAKE_INSTALL_PREFIX})
  if (VEKTRIX_CONFIG_THREADS GREATER 0)
    set(VEKTRIX_CFLAGS "-pthread")
    set(VEKTRIX_ADDITIONAL_LIBS "${VEKTRIX_ADDITIONAL_LIBS} -lpthread")
  endif ()
  if (VEKTRIX_STATIC)
    if (VEKTRIX_CONFIG_THREADS)
      set(VEKTRIX_ADDITIONAL_LIBS "${VEKTRIX_ADDITIONAL_LIBS} -lboost-thread-mt")
    endif ()
    # there is no pkgconfig file for freeimage, so we need to add that lib manually
    set(VEKTRIX_ADDITIONAL_LIBS "${VEKTRIX_ADDITIONAL_LIBS} -lfreeimage")
    configure_file(${VEKTRIX_TEMPLATES_DIR}/VektrixStatic.pc.in ${VEKTRIX_BINARY_DIR}/pkgconfig/Vektrix.pc @ONLY)
  else ()
    configure_file(${VEKTRIX_TEMPLATES_DIR}/Vektrix.pc.in ${VEKTRIX_BINARY_DIR}/pkgconfig/Vektrix.pc @ONLY)
  endif ()
  install(FILES ${VEKTRIX_BINARY_DIR}/pkgconfig/Vektrix.pc DESTINATION ${VEKTRIX_LIB_DIRECTORY}/pkgconfig)
endif ()

if(VEKTRIX_CONFIG_STATIC_LINK_CRT)
#We statically link to reduce dependancies
foreach(flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    if(${flag_var} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endif(${flag_var} MATCHES "/MD")
    if(${flag_var} MATCHES "/MDd")
        string(REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
    endif(${flag_var} MATCHES "/MDd")
endforeach(flag_var)
endif(VEKTRIX_CONFIG_STATIC_LINK_CRT)
