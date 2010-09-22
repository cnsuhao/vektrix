# top-level files
set (file_root
	../include/vtxConfig.h
	../include/vtxPrerequisites.h
	../include/vtxThreadingConfig.h
)

# _cmake_ files
set (file_root__cmake_
	CMakeLists.txt
	vektrix_src_files.cmake
	vektrix_src_files.cmake.rule
)

# Atlas Rendering files
set (file_root_atlas_rendering
	../include/vtxAtlasElement.h
	../include/vtxAtlasNode.h
	../include/vtxAtlasPacker.h
	../include/vtxRasterizer.h
	../include/vtxRasterizerManager.h
	../src/vtxAtlasNode.cpp
	../src/vtxAtlasPacker.cpp
	../src/vtxRasterizer.cpp
	../src/vtxRasterizerManager.cpp
)

# Common files
set (file_root_common
	../include/vtxDynLib.h
	../include/vtxLogManager.h
	../include/vtxMovie.h
	../include/vtxMovieFactory.h
	../include/vtxPlugin.h
	../include/vtxRoot.h
	../src/vtxDynLib.cpp
	../src/vtxLogManager.cpp
	../src/vtxMovie.cpp
	../src/vtxMovieFactory.cpp
	../src/vtxRoot.cpp
)

# Common -> Attributes files
set (file_root_common_attributes
	../include/vtxBoundingBox.h
	../include/vtxCXForm.h
	../include/vtxColor.h
	../include/vtxGlyphStrip.h
	../include/vtxMatrix.h
	../include/vtxRect.h
	../include/vtxShapeElement.h
	../include/vtxTextLine.h
	../include/vtxTextLineElement.h
	../include/vtxTransform.h
	../include/vtxVector2.h
	../src/vtxBoundingBox.cpp
	../src/vtxCXForm.cpp
	../src/vtxColor.cpp
	../src/vtxMatrix.cpp
	../src/vtxRect.cpp
	../src/vtxTransform.cpp
	../src/vtxVector2.cpp
)

# Common -> Helpers files
set (file_root_common_helpers
	../include/vtxFileHelper.h
	../include/vtxMathHelper.h
	../include/vtxStringHelper.h
	../src/vtxFileHelper.cpp
	../src/vtxMathHelper.cpp
	../src/vtxStringHelper.cpp
)

# Common -> Helpers -> OS files
set (file_root_common_helpers_os
	../include/vtxOpSysHelper.h
	../src/vtxLinuxHelper.cpp
	../src/vtxOpSysHelper.cpp
	../src/vtxWin32Helper.cpp
)

# Common -> Templates files
set (file_root_common_templates
	../include/vtxFactory.h
	../include/vtxFactoryManager.h
	../include/vtxSingleton.h
)

# Debugging files
set (file_root_debugging
	../include/vtxAssert.h
	../include/vtxMovieDebugger.h
	../src/vtxMovieDebugger.cpp
)

# Events files
set (file_root_events
	../include/vtxEvent.h
	../include/vtxEventListener.h
	../include/vtxFocusEvent.h
	../include/vtxKeyCodes.h
	../include/vtxKeyboardEvent.h
	../include/vtxMouseEvent.h
	../src/vtxEvent.cpp
	../src/vtxFocusEvent.cpp
	../src/vtxKeyboardEvent.cpp
	../src/vtxMouseEvent.cpp
)

# Files files
set (file_root_files
)

# Files -> Default Impl files
set (file_root_files_default_impl
	../include/vtxDefaultFileContainer.h
	../include/vtxDefaultFileStream.h
	../include/vtxMemoryFileStream.h
	../src/vtxDefaultFileContainer.cpp
	../src/vtxDefaultFileStream.cpp
	../src/vtxMemoryFileStream.cpp
)

# Files -> General files
set (file_root_files_general
	../include/vtxFile.h
	../include/vtxFileManager.h
	../include/vtxFileParser.h
	../src/vtxFile.cpp
	../src/vtxFileManager.cpp
	../src/vtxFileParser.cpp
)

# Files -> Inferfaces files
set (file_root_files_inferfaces
	../include/vtxFileContainer.h
	../include/vtxFileStream.h
)

# HTML files
set (file_root_html
	../include/vtxHtmlParser.h
	../src/vtxHtmlParser.cpp
)

# HTML -> DOM files
set (file_root_html_dom
)

# HTML -> DOM -> Elements files
set (file_root_html_dom_elements
	../include/vtxHtmlElement.h
	../include/vtxHtmlFont.h
	../include/vtxHtmlImage.h
	../include/vtxHtmlParagraph.h
	../include/vtxHtmlText.h
	../src/vtxHtmlElement.cpp
	../src/vtxHtmlFont.cpp
	../src/vtxHtmlImage.cpp
	../src/vtxHtmlParagraph.cpp
	../src/vtxHtmlText.cpp
)

# HTML -> DOM -> Manipulation files
set (file_root_html_dom_manipulation
	../include/vtxHtmlOperations.h
	../src/vtxHtmlOperations.cpp
)

# HTML -> DOM -> Rendering files
set (file_root_html_dom_rendering
	../include/vtxHtmlRenderable.h
	../src/vtxHtmlRenderable.cpp
)

# HTML -> XML files
set (file_root_html_xml
	../include/vtxXmlParser.h
	../src/vtxXmlParser.cpp
)

# Instances files
set (file_root_instances
)

# Instances -> Instance Types files
set (file_root_instances_instance_types
)

# Instances -> Instance Types -> Generic files
set (file_root_instances_instance_types_generic
	../include/vtxButton.h
	../include/vtxMovieClip.h
	../src/vtxButton.cpp
	../src/vtxMovieClip.cpp
)

# Instances -> Instance Types -> Material files
set (file_root_instances_instance_types_material
	../include/vtxMaterial.h
	../include/vtxMaterialFactory.h
	../src/vtxMaterial.cpp
	../src/vtxMaterialFactory.cpp
)

# Instances -> Instance Types -> Shape files
set (file_root_instances_instance_types_shape
	../include/vtxShape.h
	../src/vtxShape.cpp
)

# Instances -> Instance Types -> Text files
set (file_root_instances_instance_types_text
	../include/vtxEditText.h
	../include/vtxStaticText.h
	../src/vtxEditText.cpp
	../src/vtxStaticText.cpp
)

# Instances -> Instance Types -> Texture files
set (file_root_instances_instance_types_texture
	../include/vtxTexture.h
	../src/vtxTexture.cpp
)

# Instances -> Interfaces files
set (file_root_instances_interfaces
	../include/vtxDisplayObject.h
	../include/vtxDisplayObjectContainer.h
	../include/vtxInstance.h
	../include/vtxInteractiveObject.h
	../include/vtxStage.h
	../src/vtxDisplayObject.cpp
	../src/vtxDisplayObjectContainer.cpp
	../src/vtxInstance.cpp
	../src/vtxInteractiveObject.cpp
	../src/vtxStage.cpp
)

# Instances -> Management files
set (file_root_instances_management
	../include/vtxInstanceManager.h
	../include/vtxInstancePool.h
	../src/vtxInstanceManager.cpp
	../src/vtxInstancePool.cpp
)

# Platforms files
set (file_root_platforms
	../include/vtxLinux.h
	../include/vtxWin32.h
)

# Resources files
set (file_root_resources
)

# Resources -> Flash Specific files
set (file_root_resources_flash_specific
	../include/vtxSymbolClassResource.h
	../src/vtxSymbolClassResource.cpp
)

# Resources -> Interfaces files
set (file_root_resources_interfaces
	../include/vtxDisplayResource.h
	../include/vtxResource.h
	../src/vtxDisplayResource.cpp
	../src/vtxResource.cpp
)

# Resources -> Resource Types files
set (file_root_resources_resource_types
)

# Resources -> Resource Types -> Button files
set (file_root_resources_resource_types_button
	../include/vtxButtonResource.h
	../src/vtxButtonResource.cpp
)

# Resources -> Resource Types -> Font files
set (file_root_resources_resource_types_font
	../include/vtxFontResource.h
	../include/vtxGlyphResource.h
	../src/vtxFontResource.cpp
	../src/vtxGlyphResource.cpp
)

# Resources -> Resource Types -> Image files
set (file_root_resources_resource_types_image
	../include/vtxImageResource.h
	../src/vtxImageResource.cpp
)

# Resources -> Resource Types -> Material files
set (file_root_resources_resource_types_material
	../include/vtxMaterialResource.h
	../src/vtxMaterialResource.cpp
)

# Resources -> Resource Types -> MovieClip files
set (file_root_resources_resource_types_movieclip
	../include/vtxMovieClipResource.h
	../src/vtxMovieClipResource.cpp
)

# Resources -> Resource Types -> Script files
set (file_root_resources_resource_types_script
	../include/vtxScriptResource.h
	../src/vtxScriptResource.cpp
)

# Resources -> Resource Types -> Shape files
set (file_root_resources_resource_types_shape
	../include/vtxShapeResource.h
	../include/vtxSubshapeResource.h
	../src/vtxShapeResource.cpp
	../src/vtxSubshapeResource.cpp
)

# Resources -> Resource Types -> Text files
set (file_root_resources_resource_types_text
	../include/vtxEditTextResource.h
	../include/vtxStaticTextResource.h
	../src/vtxEditTextResource.cpp
	../src/vtxStaticTextResource.cpp
)

# Scripting files
set (file_root_scripting
	../include/vtxScriptEngine.h
	../include/vtxScriptObject.h
	../src/vtxScriptEngine.cpp
	../src/vtxScriptObject.cpp
)

# Threading files
set (file_root_threading
	../include/vtxInterLockedType.h
	../include/vtxSemaphore.h
	../include/vtxThreadJob.h
	../include/vtxThreadJobQueue.h
	../src/vtxSemaphore.cpp
	../src/vtxThreadJobQueue.cpp
)

# Threading -> Defines files
set (file_root_threading_defines
	../include/vtxThreadingDefines.h
	../include/vtxThreadingDefinesBoost.h
	../include/vtxThreadingDefinesNone.h
)

# Threading -> File Loading files
set (file_root_threading_file_loading
	../include/vtxFileParsingJob.h
	../src/vtxFileParsingJob.cpp
)

# Threading -> Headers files
set (file_root_threading_headers
	../include/vtxThreadingHeaders.h
	../include/vtxThreadingHeadersBoost.h
)

# Timeline files
set (file_root_timeline
	../include/vtxTimeline.h
	../src/vtxTimeline.cpp
)

# Timeline -> EventContainers files
set (file_root_timeline_eventcontainers
	../include/vtxButtonState.h
	../include/vtxEventContainer.h
	../include/vtxKeyframe.h
	../src/vtxButtonState.cpp
	../src/vtxEventContainer.cpp
	../src/vtxKeyframe.cpp
)

# Timeline -> FrameEvents files
set (file_root_timeline_frameevents
	../include/vtxCreateObjectEvent.h
	../include/vtxExecuteScriptEvent.h
	../include/vtxFrameEvent.h
	../include/vtxMoveObjectEvent.h
	../include/vtxRemoveObjectEvent.h
	../src/vtxCreateObjectEvent.cpp
	../src/vtxExecuteScriptEvent.cpp
	../src/vtxFrameEvent.cpp
	../src/vtxMoveObjectEvent.cpp
	../src/vtxRemoveObjectEvent.cpp
)

# the source groups
source_group(""                                     FILES ${file_root})
source_group("_cmake_"                              FILES ${file_root__cmake_})
source_group("Atlas Rendering"                      FILES ${file_root_atlas_rendering})
source_group("Common"                               FILES ${file_root_common})
source_group("Common\\Attributes"                   FILES ${file_root_common_attributes})
source_group("Common\\Helpers"                      FILES ${file_root_common_helpers})
source_group("Common\\Helpers\\OS"                  FILES ${file_root_common_helpers_os})
source_group("Common\\Templates"                    FILES ${file_root_common_templates})
source_group("Debugging"                            FILES ${file_root_debugging})
source_group("Events"                               FILES ${file_root_events})
source_group("Files"                                FILES ${file_root_files})
source_group("Files\\Default Impl"                  FILES ${file_root_files_default_impl})
source_group("Files\\General"                       FILES ${file_root_files_general})
source_group("Files\\Inferfaces"                    FILES ${file_root_files_inferfaces})
source_group("HTML"                                 FILES ${file_root_html})
source_group("HTML\\DOM"                            FILES ${file_root_html_dom})
source_group("HTML\\DOM\\Elements"                  FILES ${file_root_html_dom_elements})
source_group("HTML\\DOM\\Manipulation"              FILES ${file_root_html_dom_manipulation})
source_group("HTML\\DOM\\Rendering"                 FILES ${file_root_html_dom_rendering})
source_group("HTML\\XML"                            FILES ${file_root_html_xml})
source_group("Instances"                            FILES ${file_root_instances})
source_group("Instances\\Instance Types"            FILES ${file_root_instances_instance_types})
source_group("Instances\\Instance Types\\Generic"   FILES ${file_root_instances_instance_types_generic})
source_group("Instances\\Instance Types\\Material"  FILES ${file_root_instances_instance_types_material})
source_group("Instances\\Instance Types\\Shape"     FILES ${file_root_instances_instance_types_shape})
source_group("Instances\\Instance Types\\Text"      FILES ${file_root_instances_instance_types_text})
source_group("Instances\\Instance Types\\Texture"   FILES ${file_root_instances_instance_types_texture})
source_group("Instances\\Interfaces"                FILES ${file_root_instances_interfaces})
source_group("Instances\\Management"                FILES ${file_root_instances_management})
source_group("Platforms"                            FILES ${file_root_platforms})
source_group("Resources"                            FILES ${file_root_resources})
source_group("Resources\\Flash Specific"            FILES ${file_root_resources_flash_specific})
source_group("Resources\\Interfaces"                FILES ${file_root_resources_interfaces})
source_group("Resources\\Resource Types"            FILES ${file_root_resources_resource_types})
source_group("Resources\\Resource Types\\Button"    FILES ${file_root_resources_resource_types_button})
source_group("Resources\\Resource Types\\Font"      FILES ${file_root_resources_resource_types_font})
source_group("Resources\\Resource Types\\Image"     FILES ${file_root_resources_resource_types_image})
source_group("Resources\\Resource Types\\Material"  FILES ${file_root_resources_resource_types_material})
source_group("Resources\\Resource Types\\MovieClip" FILES ${file_root_resources_resource_types_movieclip})
source_group("Resources\\Resource Types\\Script"    FILES ${file_root_resources_resource_types_script})
source_group("Resources\\Resource Types\\Shape"     FILES ${file_root_resources_resource_types_shape})
source_group("Resources\\Resource Types\\Text"      FILES ${file_root_resources_resource_types_text})
source_group("Scripting"                            FILES ${file_root_scripting})
source_group("Threading"                            FILES ${file_root_threading})
source_group("Threading\\Defines"                   FILES ${file_root_threading_defines})
source_group("Threading\\File Loading"              FILES ${file_root_threading_file_loading})
source_group("Threading\\Headers"                   FILES ${file_root_threading_headers})
source_group("Timeline"                             FILES ${file_root_timeline})
source_group("Timeline\\EventContainers"            FILES ${file_root_timeline_eventcontainers})
source_group("Timeline\\FrameEvents"                FILES ${file_root_timeline_frameevents})

# append all files to the file_root
set (file_root
	${file_root}
	${file_root__cmake_}
	${file_root_atlas_rendering}
	${file_root_common}
	${file_root_common_attributes}
	${file_root_common_helpers}
	${file_root_common_helpers_os}
	${file_root_common_templates}
	${file_root_debugging}
	${file_root_events}
	${file_root_files}
	${file_root_files_default_impl}
	${file_root_files_general}
	${file_root_files_inferfaces}
	${file_root_html}
	${file_root_html_dom}
	${file_root_html_dom_elements}
	${file_root_html_dom_manipulation}
	${file_root_html_dom_rendering}
	${file_root_html_xml}
	${file_root_instances}
	${file_root_instances_instance_types}
	${file_root_instances_instance_types_generic}
	${file_root_instances_instance_types_material}
	${file_root_instances_instance_types_shape}
	${file_root_instances_instance_types_text}
	${file_root_instances_instance_types_texture}
	${file_root_instances_interfaces}
	${file_root_instances_management}
	${file_root_platforms}
	${file_root_resources}
	${file_root_resources_flash_specific}
	${file_root_resources_interfaces}
	${file_root_resources_resource_types}
	${file_root_resources_resource_types_button}
	${file_root_resources_resource_types_font}
	${file_root_resources_resource_types_image}
	${file_root_resources_resource_types_material}
	${file_root_resources_resource_types_movieclip}
	${file_root_resources_resource_types_script}
	${file_root_resources_resource_types_shape}
	${file_root_resources_resource_types_text}
	${file_root_scripting}
	${file_root_threading}
	${file_root_threading_defines}
	${file_root_threading_file_loading}
	${file_root_threading_headers}
	${file_root_timeline}
	${file_root_timeline_eventcontainers}
	${file_root_timeline_frameevents}
)
