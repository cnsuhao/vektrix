#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

#######################################################################
# This file determines which threading options are available for the
# build, depending on the dependencies found.
#######################################################################

set(VEKTRIX_THREAD_SUPPORT_AVAILABLE FALSE)
set(VEKTRIX_THREAD_DEFAULT_PROVIDER "none")

if (Boost_THREAD_FOUND)
	set(Boost_THREADING TRUE)
endif ()

if (Boost_THREADING AND NOT VEKTRIX_THREAD_SUPPORT_AVAILABLE)
	set(VEKTRIX_THREAD_SUPPORT_AVAILABLE TRUE)
	set(VEKTRIX_THREAD_DEFAULT_PROVIDER "boost")
endif ()

if (VEKTRIX_THREAD_SUPPORT_AVAILABLE)
	set(VEKTRIX_CONFIG_THREADS 2 CACHE STRING 
		"Enable Vektrix thread support for background loading. Possible values:
		0 - Threading off.
		1 - Full background loading.
		2 - Background resource preparation."
	)
	set(VEKTRIX_CONFIG_THREAD_PROVIDER ${VEKTRIX_THREAD_DEFAULT_PROVIDER} CACHE STRING
		"Select the library to use for thread support. Possible values:
		boost - Boost thread library."
	)
else ()
	set(VEKTRIX_CONFIG_THREADS 0)
	set(VEKTRIX_CONFIG_THREAD_PROVIDER "none")
endif ()


# sanitise threading choices
if (NOT VEKTRIX_CONFIG_THREADS)
	set(VEKTRIX_CONFIG_THREAD_PROVIDER "none")
	include_directories(${VEKTRIX_SOURCE_DIR}/core/include)
else ()
	if (VEKTRIX_CONFIG_THREAD_PROVIDER STREQUAL "boost")
		if (NOT Boost_THREADING)
			message(STATUS "Warning: boost-thread is not available. Using ${VEKTRIX_THREAD_DEFAULT_PROVIDER} as thread provider.")
			set(VEKTRIX_CONFIG_THREAD_PROVIDER ${VEKTRIX_THREAD_DEFAULT_PROVIDER})
		endif ()
	else ()
		message(STATUS "Warning: Unknown thread provider chosen. Defaulting to ${VEKTRIX_THREAD_DEFAULT_PROVIDER}.")
	endif ()	
endif ()
