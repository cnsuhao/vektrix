#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# Configure settings and install targets

#
# Default build output paths
#
if (NOT VEKTRIX_ARCHIVE_OUTPUT)
  set(VEKTRIX_ARCHIVE_OUTPUT ${VEKTRIX_BINARY_DIR}/lib)
endif ()
if (NOT VEKTRIX_LIBRARY_OUTPUT)
  set(VEKTRIX_LIBRARY_OUTPUT ${VEKTRIX_BINARY_DIR}/lib)
endif ()
if (NOT VEKTRIX_RUNTIME_OUTPUT)
  set(VEKTRIX_RUNTIME_OUTPUT ${VEKTRIX_BINARY_DIR}/bin)
endif ()

if (WIN32)
  set(VEKTRIX_RELEASE_PATH "/Release")
  set(VEKTRIX_RELWDBG_PATH "/RelWithDebInfo")
  set(VEKTRIX_MINSIZE_PATH "/MinSizeRel")
  set(VEKTRIX_DEBUG_PATH "/Debug")
  set(VEKTRIX_LIB_RELEASE_PATH "/Release")
  set(VEKTRIX_LIB_RELWDBG_PATH "/RelWithDebInfo")
  set(VEKTRIX_LIB_MINSIZE_PATH "/MinSizeRel")
  set(VEKTRIX_LIB_DEBUG_PATH "/Debug")
  set(VEKTRIX_PLUGIN_PATH "/opt")
  set(VEKTRIX_SAMPLE_PATH "/opt/demos")
elseif (UNIX)
  set(VEKTRIX_RELEASE_PATH "")
  set(VEKTRIX_RELWDBG_PATH "")
  set(VEKTRIX_MINSIZE_PATH "")
  set(VEKTRIX_DEBUG_PATH "/debug")
  if (NOT APPLE)
	set(VEKTRIX_DEBUG_PATH "")
  endif ()
  set(VEKTRIX_LIB_RELEASE_PATH "")
  set(VEKTRIX_LIB_RELWDBG_PATH "")
  set(VEKTRIX_LIB_MINSIZE_PATH "")
  set(VEKTRIX_LIB_DEBUG_PATH "")
  if (APPLE)
    set(VEKTRIX_PLUGIN_PATH "/")
  else()
    set(VEKTRIX_PLUGIN_PATH "/Vektrix")
  endif(APPLE)
  set(VEKTRIX_SAMPLE_PATH "/Vektrix/demos")
endif ()

#
# create vcproj.user file for Visual Studio to set debug working directory
#
function(vektrix_create_vcproj_userfile TARGETNAME)
  if (MSVC)
    configure_file(
	  ${VEKTRIX_TEMPLATES_DIR}/VisualStudioUserFile.vcproj.user.in
	  ${CMAKE_CURRENT_BINARY_DIR}/${TARGETNAME}.vcproj.user
	  @ONLY
	)
  endif ()
endfunction(vektrix_create_vcproj_userfile)

#
# install targets according to current build type
#
function(vektrix_install_target TARGETNAME SUFFIX EXPORT)
	# Skip all install targets in SDK
	if (VEKTRIX_SDK_BUILD)
		return()
	endif()

	if(EXPORT)
	  install(TARGETS ${TARGETNAME} #EXPORT Vektrix-exports
		BUNDLE DESTINATION "bin${VEKTRIX_RELEASE_PATH}" CONFIGURATIONS Release None ""
		RUNTIME DESTINATION "bin${VEKTRIX_RELEASE_PATH}" CONFIGURATIONS Release None ""
		LIBRARY DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_RELEASE_PATH}${SUFFIX}" CONFIGURATIONS Release None ""
		ARCHIVE DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_RELEASE_PATH}${SUFFIX}" CONFIGURATIONS Release None ""
		FRAMEWORK DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_RELEASE_PATH}/Release" CONFIGURATIONS Release None ""
      )
	  install(TARGETS ${TARGETNAME} #EXPORT Vektrix-exports
		BUNDLE DESTINATION "bin${VEKTRIX_RELWDBG_PATH}" CONFIGURATIONS RelWithDebInfo
		RUNTIME DESTINATION "bin${VEKTRIX_RELWDBG_PATH}" CONFIGURATIONS RelWithDebInfo
		LIBRARY DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_RELWDBG_PATH}${SUFFIX}" CONFIGURATIONS RelWithDebInfo
		ARCHIVE DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_RELWDBG_PATH}${SUFFIX}" CONFIGURATIONS RelWithDebInfo
		FRAMEWORK DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_RELWDBG_PATH}/RelWithDebInfo" CONFIGURATIONS RelWithDebInfo
      )
	  install(TARGETS ${TARGETNAME} #EXPORT Vektrix-exports
		BUNDLE DESTINATION "bin${VEKTRIX_MINSIZE_PATH}" CONFIGURATIONS MinSizeRel
		RUNTIME DESTINATION "bin${VEKTRIX_MINSIZE_PATH}" CONFIGURATIONS MinSizeRel
		LIBRARY DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_MINSIZE_PATH}${SUFFIX}" CONFIGURATIONS MinSizeRel
		ARCHIVE DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_MINSIZE_PATH}${SUFFIX}" CONFIGURATIONS MinSizeRel
		FRAMEWORK DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_MINSIZE_PATH}/MinSizeRel" CONFIGURATIONS MinSizeRel
      )
	  install(TARGETS ${TARGETNAME} #EXPORT Vektrix-exports
		BUNDLE DESTINATION "bin${VEKTRIX_DEBUG_PATH}" CONFIGURATIONS Debug
		RUNTIME DESTINATION "bin${VEKTRIX_DEBUG_PATH}" CONFIGURATIONS Debug
		LIBRARY DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_DEBUG_PATH}${SUFFIX}" CONFIGURATIONS Debug
		ARCHIVE DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_DEBUG_PATH}${SUFFIX}" CONFIGURATIONS Debug
		FRAMEWORK DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_DEBUG_PATH}/Debug" CONFIGURATIONS Debug
	  )
	  #install(EXPORT Vektrix-exports DESTINATION ${VEKTRIX_LIB_DIRECTORY})
	else()
	  install(TARGETS ${TARGETNAME}
		BUNDLE DESTINATION "bin${VEKTRIX_RELEASE_PATH}" CONFIGURATIONS Release None ""
		RUNTIME DESTINATION "bin${VEKTRIX_RELEASE_PATH}" CONFIGURATIONS Release None ""
		LIBRARY DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_RELEASE_PATH}${SUFFIX}" CONFIGURATIONS Release None ""
		ARCHIVE DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_RELEASE_PATH}${SUFFIX}" CONFIGURATIONS Release None ""
		FRAMEWORK DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_RELEASE_PATH}/Release" CONFIGURATIONS Release None ""
      )
	  install(TARGETS ${TARGETNAME}
		BUNDLE DESTINATION "bin${VEKTRIX_RELWDBG_PATH}" CONFIGURATIONS RelWithDebInfo
		RUNTIME DESTINATION "bin${VEKTRIX_RELWDBG_PATH}" CONFIGURATIONS RelWithDebInfo
		LIBRARY DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_RELWDBG_PATH}${SUFFIX}" CONFIGURATIONS RelWithDebInfo
		ARCHIVE DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_RELWDBG_PATH}${SUFFIX}" CONFIGURATIONS RelWithDebInfo
		FRAMEWORK DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_RELWDBG_PATH}/RelWithDebInfo" CONFIGURATIONS RelWithDebInfo
      )
	  install(TARGETS ${TARGETNAME}
		BUNDLE DESTINATION "bin${VEKTRIX_MINSIZE_PATH}" CONFIGURATIONS MinSizeRel
		RUNTIME DESTINATION "bin${VEKTRIX_MINSIZE_PATH}" CONFIGURATIONS MinSizeRel
		LIBRARY DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_MINSIZE_PATH}${SUFFIX}" CONFIGURATIONS MinSizeRel
		ARCHIVE DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_MINSIZE_PATH}${SUFFIX}" CONFIGURATIONS MinSizeRel
		FRAMEWORK DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_MINSIZE_PATH}/MinSizeRel" CONFIGURATIONS MinSizeRel
      )
	  install(TARGETS ${TARGETNAME}
		BUNDLE DESTINATION "bin${VEKTRIX_DEBUG_PATH}" CONFIGURATIONS Debug
		RUNTIME DESTINATION "bin${VEKTRIX_DEBUG_PATH}" CONFIGURATIONS Debug
		LIBRARY DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_DEBUG_PATH}${SUFFIX}" CONFIGURATIONS Debug
		ARCHIVE DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_DEBUG_PATH}${SUFFIX}" CONFIGURATIONS Debug
		FRAMEWORK DESTINATION "${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_DEBUG_PATH}/Debug" CONFIGURATIONS Debug
	  )
	endif()

endfunction(vektrix_install_target)

#
# setup common target settings
#
function(vektrix_config_common TARGETNAME)
  set_target_properties(${TARGETNAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${VEKTRIX_ARCHIVE_OUTPUT}
    LIBRARY_OUTPUT_DIRECTORY ${VEKTRIX_LIBRARY_OUTPUT}
    RUNTIME_OUTPUT_DIRECTORY ${VEKTRIX_RUNTIME_OUTPUT}
  )
  if(VEKTRIX_BUILD_PLATFORM_IPHONE)
    set_target_properties(${TARGETNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_THUMB_SUPPORT "NO")
    set_target_properties(${TARGETNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_UNROLL_LOOPS "YES")
    set_target_properties(${TARGETNAME} PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer")
    set_target_properties(${TARGETNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES")
  endif(VEKTRIX_BUILD_PLATFORM_IPHONE)

  vektrix_create_vcproj_userfile(${TARGETNAME})
endfunction(vektrix_config_common)

#
# setup library build
#
function(vektrix_config_lib LIBNAME EXPORT)
  vektrix_config_common(${LIBNAME})
  if (VEKTRIX_STATIC)
    # add static prefix, if compiling static version
    set_target_properties(${LIBNAME} PROPERTIES OUTPUT_NAME ${LIBNAME}Static)
  else (VEKTRIX_STATIC)
    if (CMAKE_COMPILER_IS_GNUCXX)
      # add GCC visibility flags to shared library build
      set_target_properties(${LIBNAME} PROPERTIES COMPILE_FLAGS "${VEKTRIX_GCC_VISIBILITY_FLAGS}")
	endif (CMAKE_COMPILER_IS_GNUCXX)
	if (MINGW)
	  # remove lib prefix from DLL outputs
	  set_target_properties(${LIBNAME} PROPERTIES PREFIX "")
	endif ()
  endif (VEKTRIX_STATIC)
  vektrix_install_target(${LIBNAME} "" ${EXPORT})
  
  if (VEKTRIX_INSTALL_PDB)
    # install debug pdb files
    if (VEKTRIX_STATIC)
	  install(FILES ${VEKTRIX_BINARY_DIR}/lib${VEKTRIX_LIB_DEBUG_PATH}/${LIBNAME}Static_d.pdb
	    DESTINATION ${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_DEBUG_PATH}
		CONFIGURATIONS Debug
	  )
	  install(FILES ${VEKTRIX_BINARY_DIR}/lib${VEKTRIX_LIB_RELWDBG_PATH}/${LIBNAME}Static.pdb
	    DESTINATION ${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_RELWDBG_PATH}
		CONFIGURATIONS RelWithDebInfo
	  )
	else ()
	  install(FILES ${VEKTRIX_BINARY_DIR}/bin${VEKTRIX_DEBUG_PATH}/${LIBNAME}_d.pdb
	    DESTINATION bin${VEKTRIX_DEBUG_PATH}
		CONFIGURATIONS Debug
	  )
	  install(FILES ${VEKTRIX_BINARY_DIR}/bin${VEKTRIX_RELWDBG_PATH}/${LIBNAME}.pdb
	    DESTINATION bin${VEKTRIX_RELWDBG_PATH}
		CONFIGURATIONS RelWithDebInfo
	  )
	endif ()
  endif ()
endfunction(vektrix_config_lib)

function(vektrix_config_component LIBNAME)
  vektrix_config_lib(${LIBNAME} FALSE)
endfunction(vektrix_config_component)


#
# setup plugin build
#
function(vektrix_config_plugin PLUGINNAME)
  vektrix_config_common(${PLUGINNAME})
  if (VEKTRIX_STATIC)
    # add static prefix, if compiling static version
    set_target_properties(${PLUGINNAME} PROPERTIES OUTPUT_NAME ${PLUGINNAME}Static)

    if(VEKTRIX_BUILD_PLATFORM_IPHONE)
      set_target_properties(${PLUGINNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_THUMB_SUPPORT "NO")
      set_target_properties(${PLUGINNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_UNROLL_LOOPS "YES")
      set_target_properties(${PLUGINNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES")
    endif(VEKTRIX_BUILD_PLATFORM_IPHONE)
  else (VEKTRIX_STATIC)
    if (CMAKE_COMPILER_IS_GNUCXX)
      # add GCC visibility flags to shared library build
      set_target_properties(${PLUGINNAME} PROPERTIES COMPILE_FLAGS "${VEKTRIX_GCC_VISIBILITY_FLAGS}")
      # disable "lib" prefix on Unix
      set_target_properties(${PLUGINNAME} PROPERTIES PREFIX "")
	endif (CMAKE_COMPILER_IS_GNUCXX)	
  endif (VEKTRIX_STATIC)
  # export only if static
  vektrix_install_target(${PLUGINNAME} ${VEKTRIX_PLUGIN_PATH} ${VEKTRIX_STATIC})

  if (VEKTRIX_INSTALL_PDB)
    # install debug pdb files
    if (VEKTRIX_STATIC)
	  install(FILES ${VEKTRIX_BINARY_DIR}/lib${VEKTRIX_LIB_DEBUG_PATH}/${PLUGINNAME}Static_d.pdb
	    DESTINATION ${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_DEBUG_PATH}/opt
		CONFIGURATIONS Debug
	  )
	  install(FILES ${VEKTRIX_BINARY_DIR}/lib${VEKTRIX_LIB_RELWDBG_PATH}/${PLUGINNAME}Static.pdb
	    DESTINATION ${VEKTRIX_LIB_DIRECTORY}${VEKTRIX_LIB_RELWDBG_PATH}/opt
		CONFIGURATIONS RelWithDebInfo
	  )
	else ()
	  install(FILES ${VEKTRIX_BINARY_DIR}/bin${VEKTRIX_DEBUG_PATH}/${PLUGINNAME}_d.pdb
	    DESTINATION bin${VEKTRIX_DEBUG_PATH}
		CONFIGURATIONS Debug
	  )
	  install(FILES ${VEKTRIX_BINARY_DIR}/bin${VEKTRIX_RELWDBG_PATH}/${PLUGINNAME}.pdb
	    DESTINATION bin${VEKTRIX_RELWDBG_PATH}
		CONFIGURATIONS RelWithDebInfo
	  )
	endif ()
  endif ()
endfunction(vektrix_config_plugin)

#
# setup Vektrix demo build
#
function(vektrix_config_sample_common SAMPLENAME)
  # The PRODUCT_NAME target setting cannot contain underscores.  Just remove them
  # Known bug in Xcode CFBundleIdentifier processing rdar://6187020
  # Can cause an instant App Store rejection. Also, code signing will fail. 
  #if (VEKTRIX_BUILD_PLATFORM_IPHONE)
#    string (REPLACE "_" "" SAMPLENAME ${SAMPLENAME})
  #endif()
  vektrix_config_common(${SAMPLENAME})

  # set install RPATH for Unix systems
  if (UNIX AND VEKTRIX_FULL_RPATH)
    set_property(TARGET ${SAMPLENAME} APPEND PROPERTY
      INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${VEKTRIX_LIB_DIRECTORY})
    set_property(TARGET ${SAMPLENAME} PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)
  endif ()
  
  if (APPLE)
    # On OS X, create .app bundle
    set_property(TARGET ${SAMPLENAME} PROPERTY MACOSX_BUNDLE TRUE)
    if (NOT VEKTRIX_BUILD_PLATFORM_IPHONE)
      # Add the path where the Ogre framework was found
      if(${VEKTRIX_FRAMEWORK_PATH})
        set_target_properties(${SAMPLENAME} PROPERTIES
          COMPILE_FLAGS "-F${VEKTRIX_FRAMEWORK_PATH}"
          LINK_FLAGS "-F${VEKTRIX_FRAMEWORK_PATH}"
        )
      endif()
    endif(NOT VEKTRIX_BUILD_PLATFORM_IPHONE)
  endif (APPLE)
  if (CMAKE_COMPILER_IS_GNUCXX)
    # add GCC visibility flags to shared library build
    set_target_properties(${SAMPLENAME} PROPERTIES COMPILE_FLAGS "${VEKTRIX_GCC_VISIBILITY_FLAGS}")
    # disable "lib" prefix on Unix
    set_target_properties(${SAMPLENAME} PROPERTIES PREFIX "")
  endif (CMAKE_COMPILER_IS_GNUCXX)	
  if (VEKTRIX_INSTALL_DEMOS)
	vektrix_install_target(${SAMPLENAME} ${VEKTRIX_SAMPLE_PATH} FALSE)
  endif()
  
endfunction(vektrix_config_sample_common)

function(vektrix_config_sample_exe SAMPLENAME)
  vektrix_config_sample_common(${SAMPLENAME})
  if (VEKTRIX_INSTALL_PDB AND VEKTRIX_INSTALL_DEMOS)
	  # install debug pdb files - no _d on exe
	  install(FILES ${VEKTRIX_BINARY_DIR}/bin${VEKTRIX_DEBUG_PATH}/${SAMPLENAME}.pdb
		  DESTINATION bin${VEKTRIX_DEBUG_PATH}
		  CONFIGURATIONS Debug
		  )
	  install(FILES ${VEKTRIX_BINARY_DIR}/bin${VEKTRIX_RELWDBG_PATH}/${SAMPLENAME}.pdb
		  DESTINATION bin${VEKTRIX_RELWDBG_PATH}
		  CONFIGURATIONS RelWithDebInfo
		  )
  endif ()

  if (APPLE AND NOT VEKTRIX_BUILD_PLATFORM_IPHONE AND VEKTRIX_SDK_BUILD)
    # Add the path where the Ogre framework was found
    if(NOT ${VEKTRIX_FRAMEWORK_PATH} STREQUAL "")
      set_target_properties(${SAMPLENAME} PROPERTIES
        COMPILE_FLAGS "-F${VEKTRIX_FRAMEWORK_PATH}"
        LINK_FLAGS "-F${VEKTRIX_FRAMEWORK_PATH}"
      )
    endif()
  endif(APPLE AND NOT VEKTRIX_BUILD_PLATFORM_IPHONE AND VEKTRIX_SDK_BUILD)
endfunction(vektrix_config_sample_exe)

function(vektrix_config_sample_lib SAMPLENAME)
  vektrix_config_sample_common(${SAMPLENAME})
  if (VEKTRIX_INSTALL_PDB AND VEKTRIX_INSTALL_DEMOS)
	  # install debug pdb files - with a _d on lib
	  install(FILES ${VEKTRIX_BINARY_DIR}/bin${VEKTRIX_DEBUG_PATH}/${SAMPLENAME}_d.pdb
		  DESTINATION bin${VEKTRIX_DEBUG_PATH}
		  CONFIGURATIONS Debug
		  )
	  install(FILES ${VEKTRIX_BINARY_DIR}/bin${VEKTRIX_RELWDBG_PATH}/${SAMPLENAME}.pdb
		  DESTINATION bin${VEKTRIX_RELWDBG_PATH}
		  CONFIGURATIONS RelWithDebInfo
		  )
  endif ()

  if (APPLE AND NOT VEKTRIX_BUILD_PLATFORM_IPHONE AND VEKTRIX_SDK_BUILD)
    # Add the path where the Ogre framework was found
    if(NOT ${VEKTRIX_FRAMEWORK_PATH} STREQUAL "")
      set_target_properties(${SAMPLENAME} PROPERTIES
        COMPILE_FLAGS "-F${VEKTRIX_FRAMEWORK_PATH}"
        LINK_FLAGS "-F${VEKTRIX_FRAMEWORK_PATH}"
      )
    endif()
  endif(APPLE AND NOT VEKTRIX_BUILD_PLATFORM_IPHONE AND VEKTRIX_SDK_BUILD)

  # Add sample to the list of link targets
  # Global property so that we can build this up across entire sample tree
  # since vars are local to containing scope of directories / functions
  get_property(VEKTRIX_DEMOS_LIST GLOBAL PROPERTY "VEKTRIX_DEMOS_LIST")
  set_property (GLOBAL PROPERTY "VEKTRIX_DEMOS_LIST" ${VEKTRIX_DEMOS_LIST} ${SAMPLENAME})

endfunction(vektrix_config_sample_lib)


#
# setup Ogre tool build
#
function(vektrix_config_tool TOOLNAME)
  vektrix_config_common(${TOOLNAME})

  #set _d debug postfix
  if (NOT APPLE)
	set_property(TARGET ${TOOLNAME} APPEND PROPERTY DEBUG_POSTFIX "_d")
  endif ()

  # set install RPATH for Unix systems
  if (UNIX AND VEKTRIX_FULL_RPATH)
    set_property(TARGET ${TOOLNAME} APPEND PROPERTY
      INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${VEKTRIX_LIB_DIRECTORY})
    set_property(TARGET ${TOOLNAME} PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)
  endif ()

  if (VEKTRIX_INSTALL_TOOLS)
    vektrix_install_target(${TOOLNAME} "" FALSE)
    if (VEKTRIX_INSTALL_PDB)
      # install debug pdb files
      install(FILES ${VEKTRIX_BINARY_DIR}/bin${VEKTRIX_DEBUG_PATH}/${TOOLNAME}_d.pdb
        DESTINATION bin${VEKTRIX_DEBUG_PATH}
        CONFIGURATIONS Debug
        )
      install(FILES ${VEKTRIX_BINARY_DIR}/bin${VEKTRIX_RELWDBG_PATH}/${TOOLNAME}.pdb
        DESTINATION bin${VEKTRIX_RELWDBG_PATH}
        CONFIGURATIONS RelWithDebInfo
        )
    endif ()
  endif ()	

endfunction(vektrix_config_tool)

#
# Get component include dir (different when referencing SDK)
#
function(vektrix_add_component_include_dir COMPONENTNAME)
	if (VEKTRIX_SDK_BUILD)
		include_directories("${VEKTRIX_INCLUDE_DIR}/${COMPONENTNAME}")
	else()
		include_directories("${VEKTRIX_SOURCE_DIR}/Components/${COMPONENTNAME}/include")	
	endif()
endfunction(vektrix_add_component_include_dir)
