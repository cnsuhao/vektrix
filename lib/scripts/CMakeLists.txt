# include directories
include_directories (../include) 

# output directory
set (LIBRARY_OUTPUT_PATH ../../bin)

# build
add_library (
vektrix SHARED  
../src/vtxAtlasNode.cpp
../src/vtxAtlasPacker.cpp
../src/vtxBoundingBox.cpp
../src/vtxButton.cpp
../src/vtxButtonResource.cpp
../src/vtxButtonState.cpp
../src/vtxColor.cpp
../src/vtxCreateObjectEvent.cpp
../src/vtxCXForm.cpp
../src/vtxDefaultFileContainer.cpp
../src/vtxDefaultFileContainerFactory.cpp
../src/vtxDefaultFileStream.cpp
../src/vtxDisplayObjectContainer.cpp
../src/vtxDynLib.cpp
../src/vtxEventContainer.cpp
../src/vtxFile.cpp
../src/vtxFileHelper.cpp
../src/vtxFileManager.cpp
../src/vtxFileParser.cpp
../src/vtxImageResource.cpp
../src/vtxInstance.cpp
../src/vtxInstancePool.cpp
../src/vtxInteractiveObject.cpp
../src/vtxKeyframe.cpp
../src/vtxLogManager.cpp
../src/vtxMaterial.cpp
../src/vtxMaterialFactory.cpp
../src/vtxMaterialManager.cpp
../src/vtxMaterialResource.cpp
../src/vtxMathHelper.cpp
../src/vtxMatrix.cpp
../src/vtxMovableObject.cpp
../src/vtxMoveObjectEvent.cpp
../src/vtxMovie.cpp
../src/vtxMovieClip.cpp
../src/vtxMovieClipResource.cpp
../src/vtxMovieDebugger.cpp
../src/vtxMovieFactory.cpp
../src/vtxRastarizer.cpp
../src/vtxRasterizerManager.cpp
../src/vtxRect.cpp
../src/vtxRemoveObjectEvent.cpp
../src/vtxRenderStrategy.cpp
../src/vtxResource.cpp
../src/vtxRoot.cpp
../src/vtxScriptButton.cpp
../src/vtxScriptEngine.cpp
../src/vtxScriptEngineManager.cpp
../src/vtxScriptMovieClip.cpp
../src/vtxScriptObject.cpp
../src/vtxScriptResource.cpp
../src/vtxShape.cpp
../src/vtxShapeFactory.cpp
../src/vtxShapeManager.cpp
../src/vtxShapeResource.cpp
../src/vtxStringHelper.cpp
../src/vtxSubshapeResource.cpp
../src/vtxTexture.cpp
../src/vtxTextureFactory.cpp
../src/vtxTextureManager.cpp
../src/vtxTimeline.cpp
../src/vtxTransform.cpp
../src/vtxVector2.cpp
)

# remove "lib" prefix
set_target_properties(vektrix PROPERTIES PREFIX "")

