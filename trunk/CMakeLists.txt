#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

######################################################################
# VEKTRIX BUILD SYSTEM
# Welcome to the CMake build system for Vektrix.
# This is the main file where we prepare the general build environment
# and provide build configuration options.
######################################################################

cmake_minimum_required(VERSION 2.6)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
cmake_policy(SET CMP0003 NEW)

# Use relative paths
# This is mostly to reduce path size for command-line limits on windows
if(WIN32)
  # This seems to break Xcode projects so definitely don't enable on Apple builds
  set(CMAKE_USE_RELATIVE_PATHS true)
  set(CMAKE_SUPPRESS_REGENERATION true)
endif()

project(VEKTRIX)

# Include necessary submodules
set(CMAKE_MODULE_PATH 
  "${VEKTRIX_SOURCE_DIR}/cmake"
  "${VEKTRIX_SOURCE_DIR}/cmake/Utils" 
  "${VEKTRIX_SOURCE_DIR}/cmake/Packages"
)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)
include(MacroLogFeature)
include(VektrixConfigTargets)
include(PreprocessorUtils)
set(VEKTRIX_TEMPLATES_DIR "${VEKTRIX_SOURCE_DIR}/cmake/Templates")
set(VEKTRIX_WORK_DIR ${VEKTRIX_BINARY_DIR})


#####################################################################
# Set up the basic build environment
#####################################################################

if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

# determine Vektrix version numbers
include(VektrixGetVersion)
vektrix_get_version(${VEKTRIX_SOURCE_DIR}/core/include/vtxPrerequisites.h)
message(STATUS "Configuring VEKTRIX ${VEKTRIX_VERSION}")

# Configure version file for use by scripts
configure_file("${VEKTRIX_TEMPLATES_DIR}/version.txt.in" "${VEKTRIX_BINARY_DIR}/version.txt" @ONLY)

# Set compiler specific build flags
if (CMAKE_COMPILER_IS_GNUCXX)
  check_cxx_compiler_flag(-msse VEKTRIX_GCC_HAS_SSE)
  if (VEKTRIX_GCC_HAS_SSE)
    add_definitions(-msse)
  endif ()
endif ()
if (MSVC)
  if (CMAKE_BUILD_TOOL STREQUAL "nmake")
    # set variable to state that we are using nmake makefiles
	set(NMAKE TRUE)
  endif ()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:fast")
  # Enable intrinsics on MSVC in debug mode
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Oi")
  if (CMAKE_CL_64)
    # Visual Studio bails out on debug builds in 64bit mode unless
	# this flag is set...
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /bigobj")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /bigobj")
  endif ()
endif ()
if (MINGW)
  add_definitions(-D_WIN32_WINNT=0x0500)
endif ()

if (CMAKE_COMPILER_IS_GNUCXX AND NOT MINGW)
  # Test for GCC visibility
  include(CheckCXXCompilerFlag)
  check_cxx_compiler_flag(-fvisibility=hidden VEKTRIX_GCC_VISIBILITY)
  if (VEKTRIX_GCC_VISIBILITY)
    # determine gcc version
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion 
      OUTPUT_VARIABLE VEKTRIX_GCC_VERSION)
    message(STATUS "Detected g++ ${VEKTRIX_GCC_VERSION}")
    message(STATUS "Enabling GCC visibility flags")
    set(VEKTRIX_GCC_VISIBILITY_FLAGS "-DVEKTRIX_GCC_VISIBILITY -fvisibility=hidden")
  
    # check if we can safely add -fvisibility-inlines-hidden
    string(TOLOWER "${CMAKE_BUILD_TYPE}" VEKTRIX_BUILD_TYPE)
    if (VEKTRIX_BUILD_TYPE STREQUAL "debug" AND VEKTRIX_GCC_VERSION VERSION_LESS "4.2")
      message(STATUS "Skipping -fvisibility-inlines-hidden due to possible bug in g++ < 4.2")
    else ()
      set(VEKTRIX_GCC_VISIBILITY_FLAGS "${VEKTRIX_GCC_VISIBILITY_FLAGS} -fvisibility-inlines-hidden")
    endif ()
  endif (VEKTRIX_GCC_VISIBILITY)
  
  # Fix x64 issues on Linux
  if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" AND NOT APPLE)
    add_definitions(-fPIC)
  endif()  
endif (CMAKE_COMPILER_IS_GNUCXX AND NOT MINGW)

# determine system endianess
include(TestBigEndian)
test_big_endian(VEKTRIX_TEST_BIG_ENDIAN)

# Add Vektrix include path
include_directories("${VEKTRIX_SOURCE_DIR}/core/include")
include_directories("${VEKTRIX_BINARY_DIR}/include")

# Find dependencies
include(Dependencies)

# definitions for samples
set(VEKTRIX_LIBRARIES Vektrix) 
set(VEKTRIX_D3D9_LIBRARIES vektrix_D3D9_Demo)
set(VEKTRIX_Ogre_LIBRARIES vektrix_Ogre_Demo)

set(VEKTRIX_Plugin_AS3_LIBRARIES vektrix_AS3Plugin)
set(VEKTRIX_Plugin_Cairo_LIBRARIES vektrix_CairoPlugin)
set(VEKTRIX_Plugin_Curl_LIBRARIES vektrix_CurlPlugin)
set(VEKTRIX_Plugin_D3D9_LIBRARIES vektrix_D3D9Plugin)
set(VEKTRIX_Plugin_FreeImg_LIBRARIES vektrix_FreeImgPlugin)
set(VEKTRIX_Plugin_Ogre_LIBRARIES vektrix_OgrePlugin)
set(VEKTRIX_Plugin_Swf_LIBRARIES vektrix_SwfPlugin)
set(VEKTRIX_Plugin_Xml_LIBRARIES vektrix_XmlPlugin)

# Specify build paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${VEKTRIX_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${VEKTRIX_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${VEKTRIX_BINARY_DIR}/bin")
if (WIN32 OR APPLE)
  if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    # We don't want to install in default system location, install is really for the SDK, so call it that
    set(CMAKE_INSTALL_PREFIX
	  "${VEKTRIX_BINARY_DIR}/sdk" CACHE PATH "VEKTRIX install prefix" FORCE
    )
  endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
endif(WIN32 OR APPLE)


######################################################################
# Provide user options to customise the build process
######################################################################

# Customise what to build
option(VEKTRIX_STATIC "Static build" FALSE)
cmake_dependent_option(VEKTRIX_BUILD_PLUGIN_D3D9 "Build Direct3D9 Plugin" TRUE "WIN32;DirectX_FOUND" FALSE)
cmake_dependent_option(VEKTRIX_BUILD_PLUGIN_OGRE "Build OGRE Plugin" TRUE "OGRE_FOUND" FALSE)
cmake_dependent_option(VEKTRIX_BUILD_PLUGIN_AS3 "Build ActionScript3 plugin" TRUE "Caspin_FOUND" FALSE)
cmake_dependent_option(VEKTRIX_BUILD_PLUGIN_CAIRO "Build Cairo plugin" TRUE "Cairo_FOUND" FALSE)
cmake_dependent_option(VEKTRIX_BUILD_PLUGIN_CURL "Build cURL plugin" TRUE "Curl_FOUND" FALSE)
cmake_dependent_option(VEKTRIX_BUILD_PLUGIN_FREEIMG "Build FreeImg plugin" TRUE "Freeimg_FOUND" FALSE)
cmake_dependent_option(VEKTRIX_BUILD_PLUGIN_SWF "Build Swf plugin" TRUE "Caspin_FOUND" FALSE)
cmake_dependent_option(VEKTRIX_BUILD_PLUGIN_XML "Build XML plugin" TRUE "Expat_FOUND" FALSE)
option(VEKTRIX_BUILD_SAMPLES "Build Vektrix demos" TRUE)
cmake_dependent_option(VEKTRIX_BUILD_TOOLS "Build the command-line tools" TRUE "NOT VEKTRIX_BUILD_PLATFORM_IPHONE" FALSE)
option(VEKTRIX_BUILD_PLAYPEN "Build the PlayPen" TRUE)
option(VEKTRIX_CONFIG_MEMTRACK_DEBUG "Enable Vektrix's memory tracker in debug mode" FALSE)
option(VEKTRIX_CONFIG_MEMTRACK_RELEASE "Enable Vektrix's memory tracker in release mode" FALSE)

# determine threading options
include(PrepareThreadingOptions)
cmake_dependent_option(VEKTRIX_CONFIG_ENABLE_ZIP "Build ZIP archive support. If you disable this option, you cannot use ZIP archives resource locations. The samples won't work." TRUE "ZZip_FOUND" FALSE)
cmake_dependent_option(VEKTRIX_USE_BOOST "Use Boost extensions" TRUE "Boost_FOUND" FALSE)

# Customise what to install
option(VEKTRIX_INSTALL_SAMPLES "Install Vektrix demos." FALSE)
option(VEKTRIX_INSTALL_TOOLS "Install Vektrix tools." FALSE)
option(VEKTRIX_INSTALL_DOCS "Install documentation." FALSE)
option(VEKTRIX_INSTALL_SAMPLES_SOURCE "Install samples source files." FALSE)
cmake_dependent_option(VEKTRIX_INSTALL_PDB "Install debug pdb files" FALSE "MSVC" FALSE)
cmake_dependent_option(VEKTRIX_FULL_RPATH "Build executables with the full required RPATH to run from their install location." FALSE "NOT WIN32" FALSE)
option(VEKTRIX_PROFILING "Enable internal profiling support." FALSE)
cmake_dependent_option(VEKTRIX_CONFIG_STATIC_LINK_CRT "Statically link the MS CRT dlls (msvcrt)" FALSE "MSVC" FALSE)
set(VEKTRIX_LIB_DIRECTORY "lib" CACHE STRING "Install path for libraries, e.g. 'lib64' on some 64-bit Linux distros.")

# hide advanced options
mark_as_advanced(
  VEKTRIX_CONFIG_MEMTRACK_DEBUG
  VEKTRIX_CONFIG_MEMTRACK_RELEASE
  VEKTRIX_CONFIG_ENABLE_ZIP
  VEKTRIX_USE_BOOST
  VEKTRIX_INSTALL_SAMPLES_SOURCE
  VEKTRIX_FULL_RPATH
  VEKTRIX_CONFIG_STATIC_LINK_CRT
  VEKTRIX_LIB_DIRECTORY
)


###################################################################
# configure global build settings based on selected build options
###################################################################
include(ConfigureBuild)


##################################################################
# Now setup targets
##################################################################

# install resource files
include(InstallResources)

# Setup OgreMain project
add_subdirectory(core)

# Setup Plugins
add_subdirectory(plugins)

# Setup samples
add_subdirectory(demos) 

# Setup command-line tools
if (VEKTRIX_BUILD_TOOLS)
  add_subdirectory(tools)
endif ()

# Install documentation
add_subdirectory(docs)

# Install media files
if (VEKTRIX_INSTALL_SAMPLES OR VEKTRIX_INSTALL_SAMPLES_SOURCE)
  add_subdirectory(demos/media)
endif ()

# Install CMake modules
add_subdirectory(cmake)

# Provide CPack packaging target
include(Packaging)


# Show feature summary
include(FeatureSummary)

