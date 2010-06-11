#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

############################################################
# Vektrix core library
############################################################

PROJECT(VektrixCore)

include(PrecompiledHeader)


# define header and source files for the library
set (HEADER_FILES
  include/vektrix.h
  include/vtxAssert.h
  include/vtxAtlasElement.h
  include/vtxAtlasNode.h
  include/vtxAtlasPacker.h
  include/vtxBoundingBox.h
  include/vtxButton.h
  include/vtxButtonResource.h
  include/vtxButtonState.h
  include/vtxColor.h
  include/vtxConfig.h
  include/vtxCreateObjectEvent.h
  include/vtxCXForm.h
  include/vtxDefaultFileContainer.h
  include/vtxDefaultFileStream.h
  include/vtxDisplayObject.h
  include/vtxDisplayObjectContainer.h
  include/vtxDynLib.h
  include/vtxEditText.h
  include/vtxEditTextResource.h
  include/vtxEvent.h
  include/vtxEventContainer.h
  include/vtxEventListener.h
  include/vtxFactory.h
  include/vtxFactoryManager.h
  include/vtxFile.h
  include/vtxFileContainer.h
  include/vtxFileHelper.h
  include/vtxFileManager.h
  include/vtxFileParser.h
  include/vtxFileParsingJob.h
  include/vtxFileStream.h
  include/vtxFocusEvent.h
  include/vtxFontResource.h
  include/vtxFrameEvent.h
  include/vtxGlyphResource.h
  include/vtxGlyphStrip.h
  include/vtxHtmlElement.h
  include/vtxHtmlFont.h
  include/vtxHtmlImage.h
  include/vtxHtmlOperations.h
  include/vtxHtmlParagraph.h
  include/vtxHtmlParser.h
  include/vtxHtmlRenderable.h
  include/vtxHtmlText.h
  include/vtxImageResource.h
  include/vtxInstance.h
  include/vtxInstanceManager.h
  include/vtxInstancePool.h
  include/vtxInteractiveObject.h
  include/vtxKeyboardEvent.h
  include/vtxKeyCodes.h
  include/vtxKeyframe.h
  include/vtxLogManager.h
  include/vtxMaterial.h
  include/vtxMaterialFactory.h
  include/vtxMaterialResource.h
  include/vtxMathHelper.h
  include/vtxMatrix.h
  include/vtxMemoryFileStream.h
  include/vtxMouseEvent.h
  include/vtxMoveObjectEvent.h
  include/vtxMovie.h
  include/vtxMovieClip.h
  include/vtxMovieClipResource.h
  include/vtxMovieDebugger.h
  include/vtxMovieFactory.h
  include/vtxOpSysHelper.h
  include/vtxPlugin.h
  include/vtxPrerequisites.h
  include/vtxRastarizer.h
  include/vtxRasterizerManager.h
  include/vtxRect.h
  include/vtxRemoveObjectEvent.h
  include/vtxRenderStrategy.h
  include/vtxResource.h
  include/vtxResourceGroup.h
  include/vtxRoot.h
  include/vtxScriptEngine.h
  include/vtxScriptResource.h
  include/vtxShape.h
  include/vtxShapeElement.h
  include/vtxShapeResource.h
  include/vtxSingleton.h
  include/vtxStaticText.h
  include/vtxStaticTextResource.h
  include/vtxStringHelper.h
  include/vtxSubshapeResource.h
  include/vtxTextLine.h
  include/vtxTextLineElement.h
  include/vtxTexture.h
  include/vtxTimeline.h
  include/vtxTransform.h
  include/vtxVector2.h
  include/vtxXmlParser.h
)

set (SOURCE_FILES
  src/vtxAtlasElement.cpp
  src/vtxAtlasNode.cpp
  src/vtxAtlasPacker.cpp
  src/vtxBoundingBox.cpp
  src/vtxButton.cpp
  src/vtxButtonResource.cpp
  src/vtxButtonState.cpp
  src/vtxColor.cpp
  src/vtxCreateObjectEvent.cpp
  src/vtxCXForm.cpp
  src/vtxDefaultFileContainer.cpp
  src/vtxDefaultFileStream.cpp
  src/vtxDisplayObject.cpp
  src/vtxDisplayObjectContainer.cpp
  src/vtxDynLib.cpp
  src/vtxEditText.cpp
  src/vtxEditTextResource.cpp
  src/vtxEvent.cpp
  src/vtxEventContainer.cpp
  src/vtxFile.cpp
  src/vtxFileHelper.cpp
  src/vtxFileManager.cpp
  src/vtxFileParser.cpp
  src/vtxFileParsingJob.cpp
  src/vtxFocusEvent.cpp
  src/vtxFontResource.cpp
  src/vtxGlyphResource.cpp
  src/vtxHtmlElement.cpp
  src/vtxHtmlFont.cpp
  src/vtxHtmlImage.cpp
  src/vtxHtmlOperations.cpp
  src/vtxHtmlParagraph.cpp
  src/vtxHtmlParser.cpp
  src/vtxHtmlRenderable.cpp
  src/vtxHtmlText.cpp
  src/vtxImageResource.cpp
  src/vtxInstance.cpp
  src/vtxInstanceManager.cpp
  src/vtxInstancePool.cpp
  src/vtxInteractiveObject.cpp
  src/vtxKeyboardEvent.cpp
  src/vtxKeyframe.cpp
  src/vtxLogManager.cpp
  src/vtxMaterial.cpp
  src/vtxMaterialFactory.cpp
  src/vtxMaterialResource.cpp
  src/vtxMathHelper.cpp
  src/vtxMatrix.cpp
  src/vtxMemoryFileStream.cpp
  src/vtxMouseEvent.cpp
  src/vtxMoveObjectEvent.cpp
  src/vtxMovie.cpp
  src/vtxMovieClip.cpp
  src/vtxMovieClipResource.cpp
  src/vtxMovieDebugger.cpp
  src/vtxMovieFactory.cpp
  src/vtxRastarizer.cpp
  src/vtxRasterizerManager.cpp
  src/vtxRect.cpp
  src/vtxRemoveObjectEvent.cpp
  src/vtxRenderStrategy.cpp
  src/vtxResource.cpp
  src/vtxResourceGroup.cpp
  src/vtxRoot.cpp
  src/vtxScriptEngine.cpp
  src/vtxScriptObject.cpp
  src/vtxScriptResource.cpp
  src/vtxShape.cpp
  src/vtxShapeResource.cpp
  src/vtxStaticText.cpp
  src/vtxStaticTextResource.cpp
  src/vtxStringHelper.cpp
  src/vtxSubshapeResource.cpp
  src/vtxTexture.cpp
  src/vtxTimeline.cpp
  src/vtxTransform.cpp
  src/vtxVector2.cpp
  src/vtxXmlParser.cpp
)

# Add platform specific files
if (WIN32)
  set(PLATFORM_HEADER_FILES
    include/vtxWin32.h
  )
  set(PLATFORM_SOURCE_FILES
    src/vtxWin32Helper.cpp
  )
elseif (UNIX)
  set(PLATFORM_HEADER_FILES
    include/vtxLinux.h
  )
  set(PLATFORM_SOURCE_FILES
    src/vtxLinuxHelper.cpp
  )
endif(WIN32)


# Configure threading files
set(THREAD_HEADER_FILES
  include/vtxThreadingDefines.h
  include/vtxThreadingDefinesBoost.h
  include/vtxThreadingDefinesNone.h
  include/vtxThreadingHeaders.h
  include/vtxThreadingHeadersBoost.h
  include/vtxThreadJob.h
)


# Add needed definitions and nedmalloc include dir
add_definitions(-DVEKTRIX_NONCLIENT_BUILD -DFREEIMAGE_LIB -D_MT -D_USRDLL)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/nedmalloc)

set(LIBRARIES
  ${FREETYPE_LIBRARIES}
  ${BOOST_LIBRARIES}
  ${EXPAT_LIBRARIES}
  ${PLATFORM_LIBS}
)

if (VEKTRIX_CONFIG_THREADS)
  list(APPEND LIBRARIES ${VEKTRIX_THREAD_LIBRARIES})
endif ()

if (VEKTRIX_CONFIG_ENABLE_ZIP)
  list(APPEND LIBRARIES "${ZLIB_LIBRARIES}")
endif ()

# setup VektrixCore target
add_library(VektrixCore ${VEKTRIX_LIB_TYPE} ${PREC_HEADER} ${HEADER_FILES} ${SOURCE_FILES} ${PLATFORM_HEADER_FILES} ${PLATFORM_SOURCE_FILES} ${THREAD_HEADER_FILES} ${THREAD_SOURCE_FILES})
set_target_properties(VektrixCore PROPERTIES VERSION ${VEKTRIX_SOVERSION})
target_link_libraries(VektrixCore ${LIBRARIES})

# specify a precompiled header to use
#use_precompiled_header(VektrixCore 
#  "${CMAKE_CURRENT_SOURCE_DIR}/include/OgreStableHeaders.h"
#  "${CMAKE_CURRENT_SOURCE_DIR}/src/OgrePrecompiledHeaders.cpp"
#)

# install VektrixCore
vektrix_config_lib(VektrixCore TRUE)
install(FILES ${HEADER_FILES}
  DESTINATION include/Vektrix
)
