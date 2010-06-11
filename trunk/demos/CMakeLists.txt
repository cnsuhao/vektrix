# Configure Samples build

if (VEKTRIX_BUILD_SAMPLES)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Common/include)

  # Make sure all plugins are built
  if (VEKTRIX_BUILD_PLUGIN_AS3)
	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} vektrix_AS3Plugin)
  endif ()
  if (VEKTRIX_BUILD_PLUGIN_CAIRO)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} vektrix_CairoPlugin)
  endif ()
  if (VEKTRIX_BUILD_PLUGIN_CURL)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} vektrix_CurlPlugin)
  endif ()
  if (VEKTRIX_BUILD_PLUGIN_D3D9)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} vektrix_D3D9Plugin)
  endif ()
  if (VEKTRIX_BUILD_PLUGIN_FREEIMG)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} vektrix_FreeImagePlugin)
  endif ()
  if (VEKTRIX_BUILD_PLUGIN_OGRE)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} vektrix_OgrePlugin)
  endif ()
  if (VEKTRIX_BUILD_PLUGIN_SWF)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} vektrix_SwfPlugin)
  endif ()
  if (VEKTRIX_BUILD_PLUGIN_XML)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} vektrix_XmlPlugin)
  endif ()

  if (APPLE)
  	set(VEKTRIX_LIBRARIES ${VEKTRIX_LIBRARIES} IOKit)
  endif ()

  if (VEKTRIX_STATIC)
  	# Static linking means we need to directly use plugins
  	include_directories(${VEKTRIX_SOURCE_DIR}/plugins/AS3Plugin/include)
  	include_directories(${VEKTRIX_SOURCE_DIR}/plugins/CairoPlugin/include)
  	include_directories(${VEKTRIX_SOURCE_DIR}/plugins/cURLPlugin/include)
  	include_directories(${VEKTRIX_SOURCE_DIR}/plugins/D3D9Plugin/include)
  	include_directories(${VEKTRIX_SOURCE_DIR}/plugins/FreeImgPlugin/include)
  	include_directories(${VEKTRIX_SOURCE_DIR}/plugins/OgrePlugin/include)
  	include_directories(${VEKTRIX_SOURCE_DIR}/plugins/SwfPlugin/include)
  	include_directories(${VEKTRIX_SOURCE_DIR}/plugins/XmlPlugin/include)

	# Link to all enabled plugins
	set(VEKTRIX_LIBRARIES ${VEKTRIX_LIBRARIES} ${SAMPLE_DEPENDENCIES})
  endif ()
  
  add_subdirectory(Direct3D9)
  add_subdirectory(Ogre3D)
endif ()


  
# Install sample sources
if (VEKTRIX_INSTALL_SAMPLES_SOURCE)
  if (WIN32 OR APPLE)
    set(VEKTRIX_SAMPLES_DIR demos)
  elseif (UNIX)
    set(VEKTRIX_SAMPLES_DIR share/Vektrix/demos)
  endif ()
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ DESTINATION ${VEKTRIX_SAMPLES_DIR}
    REGEX "^CMakeLists.txt$" EXCLUDE
    PATTERN "Makefile.am" EXCLUDE
    PATTERN "media" EXCLUDE
    PATTERN "bin" EXCLUDE
    PATTERN "setup" EXCLUDE
    PATTERN ".svn" EXCLUDE
	PATTERN "obj" EXCLUDE
	PATTERN "scripts" EXCLUDE
  )
  # install a new CMakeLists.txt file to allow building of samples
  configure_file(${VEKTRIX_TEMPLATES_DIR}/SDK_CMakeLists.txt.in ${CMAKE_CURRENT_BINARY_DIR}/../CMakeLists.txt @ONLY)
  configure_file(${VEKTRIX_TEMPLATES_DIR}/SDK_Samples_CMakeLists.txt.in ${CMAKE_CURRENT_BINARY_DIR}/CMakeLists.txt @ONLY)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/../CMakeLists.txt DESTINATION ${VEKTRIX_SAMPLES_DIR}/../)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/CMakeLists.txt DESTINATION ${VEKTRIX_SAMPLES_DIR})
endif ()

if (MSVC)
  #find_package(Wix)
  if (Wix_FOUND)
    # Create WiX setup for demo build
    configure_file(${VEKTRIX_TEMPLATES_DIR}/demos.wxs.in ${CMAKE_CURRENT_BINARY_DIR}/demos.wxs @ONLY)
    configure_file(${VEKTRIX_TEMPLATES_DIR}/demomedia.wxi.in ${CMAKE_CURRENT_BINARY_DIR}/demomedia.wxi @ONLY)
    configure_file(${VEKTRIX_TEMPLATES_DIR}/DemoLicense.rtf ${CMAKE_CURRENT_BINARY_DIR}/DemoLicense.rtf COPYONLY)
    if (MSVC_VERSION EQUAL 1400)
      configure_file(${VEKTRIX_TEMPLATES_DIR}/vcrt_vc8.wxi.in ${CMAKE_CURRENT_BINARY_DIR}/vcrt.wxi @ONLY)
    elseif(MSVC_VERSION EQUAL 1500)
      configure_file(${VEKTRIX_TEMPLATES_DIR}/vcrt_vc9.wxi.in ${CMAKE_CURRENT_BINARY_DIR}/vcrt.wxi @ONLY)
    endif()
	# Configure files, set media dir temporarily
	set(VEKTRIX_MEDIA_DIR_TMP ${VEKTRIX_MEDIA_DIR_REL})
	set(VEKTRIX_MEDIA_DIR_REL "media")
	# restore
	set(VEKTRIX_MEDIA_DIR_REL ${VEKTRIX_MEDIA_DIR_TMP})
    add_custom_target(demo_installer 
	  COMMAND ${Wix_BINARY_DIR}/candle demos.wxs 
	  COMMAND ${Wix_BINARY_DIR}/light -ext WixUIExtension -cultures:en-us -out VektrixDemos_v${VEKTRIX_VERSION_DASH_SEPARATED}.msi demos.wixobj
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Building demo installer" VERBATIM
    )
	# Make sure we build samples first
	add_dependencies(demo_installer SampleBrowser)
  endif()
endif()
