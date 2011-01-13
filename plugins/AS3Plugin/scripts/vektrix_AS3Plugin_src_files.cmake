# top-level files
set (file_root
	../include/vtxas3ScriptEngine.h
	../src/vtxas3ScriptEngine.cpp
)

# _cmake_ files
set (file_root__cmake_
	CMakeLists.txt
	vektrix_AS3Plugin_src_files.cmake
	vektrix_AS3Plugin_src_files.cmake.rule
)

# AS3 classes files
set (file_root_as3_classes
	../as3/build.py
)

# AS3 classes -> flash files
set (file_root_as3_classes_flash
)

# AS3 classes -> flash -> accessibility files
set (file_root_as3_classes_flash_accessibility
	../as3/flash/accessibility/Accessibility.as
	../as3/flash/accessibility/AccessibilityProperties.as
)

# AS3 classes -> flash -> display files
set (file_root_as3_classes_flash_display
	../as3/flash/display/BitmapData.as
	../as3/flash/display/DisplayObject.as
	../as3/flash/display/DisplayObjectContainer.as
	../as3/flash/display/Graphics.as
	../as3/flash/display/IBitmapDrawable.as
	../as3/flash/display/InteractiveObject.as
	../as3/flash/display/Loader.as
	../as3/flash/display/LoaderInfo.as
	../as3/flash/display/MovieClip.as
	../as3/flash/display/Scene.as
	../as3/flash/display/SimpleButton.as
	../as3/flash/display/Sprite.as
	../as3/flash/display/Stage.as
	../include/vtxas3DisplayObject.h
	../include/vtxas3DisplayObjectContainer.h
	../include/vtxas3InteractiveObject.h
	../include/vtxas3Loader.h
	../include/vtxas3MovieClip.h
	../include/vtxas3SimpleButton.h
	../include/vtxas3Sprite.h
	../include/vtxas3Stage.h
	../src/vtxas3DisplayObject.cpp
	../src/vtxas3DisplayObjectContainer.cpp
	../src/vtxas3InteractiveObject.cpp
	../src/vtxas3Loader.cpp
	../src/vtxas3MovieClip.cpp
	../src/vtxas3SimpleButton.cpp
	../src/vtxas3Sprite.cpp
	../src/vtxas3Stage.cpp
)

# AS3 classes -> flash -> events files
set (file_root_as3_classes_flash_events
	../as3/flash/events/Event.as
	../as3/flash/events/EventDispatcher.as
	../as3/flash/events/FocusEvent.as
	../as3/flash/events/IEventDispatcher.as
	../as3/flash/events/KeyboardEvent.as
	../as3/flash/events/MouseEvent.as
	../as3/flash/events/TimerEvent.as
	../include/vtxas3Event.h
	../include/vtxas3EventDispatcher.h
	../include/vtxas3MouseEvent.h
	../src/vtxas3Event.cpp
	../src/vtxas3EventDispatcher.cpp
	../src/vtxas3MouseEvent.cpp
)

# AS3 classes -> flash -> external files
set (file_root_as3_classes_flash_external
	../as3/flash/external/ExternalInterface.as
	../include/vtxas3ExternalInterface.h
	../src/vtxas3ExternalInterface.cpp
)

# AS3 classes -> flash -> filters files
set (file_root_as3_classes_flash_filters
	../as3/flash/filters/BitmapFilter.as
)

# AS3 classes -> flash -> geom files
set (file_root_as3_classes_flash_geom
	../as3/flash/geom/ColorTransform.as
	../as3/flash/geom/Matrix.as
	../as3/flash/geom/Point.as
	../as3/flash/geom/Rectangle.as
	../as3/flash/geom/Transform.as
)

# AS3 classes -> flash -> media files
set (file_root_as3_classes_flash_media
	../as3/flash/media/Camera.as
	../as3/flash/media/SoundTransform.as
	../as3/flash/media/Video.as
)

# AS3 classes -> flash -> net files
set (file_root_as3_classes_flash_net
	../as3/flash/net/LocalConnection.as
	../as3/flash/net/NetConnection.as
	../as3/flash/net/NetStream.as
	../as3/flash/net/SharedObject.as
	../as3/flash/net/Socket.as
	../as3/flash/net/URLRequest.as
	../include/vtxas3URLRequest.h
	../src/vtxas3URLRequest.cpp
)

# AS3 classes -> flash -> system files
set (file_root_as3_classes_flash_system
	../as3/flash/system/ApplicationDomain.as
	../as3/flash/system/LoaderContext.as
	../include/vtxas3LoaderContext.h
	../src/vtxas3LoaderContext.cpp
)

# AS3 classes -> flash -> text files
set (file_root_as3_classes_flash_text
	../as3/flash/text/StaticText.as
	../as3/flash/text/StyleSheet.as
	../as3/flash/text/TextField.as
	../as3/flash/text/TextFieldAutoSize.as
	../as3/flash/text/TextFieldType.as
	../as3/flash/text/TextFormat.as
	../as3/flash/text/TextFormatAlign.as
	../as3/flash/text/TextLineMetrics.as
	../as3/flash/text/TextSnapshot.as
	../include/vtxas3StaticText.h
	../include/vtxas3TextField.h
	../src/vtxas3StaticText.cpp
	../src/vtxas3TextField.cpp
)

# AS3 classes -> flash -> ui files
set (file_root_as3_classes_flash_ui
	../as3/flash/ui/Keyboard.as
	../as3/flash/ui/Mouse.as
	../include/vtxas3Mouse.h
	../src/vtxas3Mouse.cpp
)

# AS3 classes -> flash -> utils files
set (file_root_as3_classes_flash_utils
	../as3/flash/utils/ByteArray.as
	../as3/flash/utils/Dictionary.as
	../as3/flash/utils/Endian.as
	../as3/flash/utils/FlashUtils.as
	../as3/flash/utils/Timer.as
	../include/vtxas3Dictionary.h
	../include/vtxas3FlashUtils.h
	../include/vtxas3Timer.h
	../src/vtxas3Dictionary.cpp
	../src/vtxas3FlashUtils.cpp
	../src/vtxas3Timer.cpp
)

# AS3 classes -> vektrix files
set (file_root_as3_classes_vektrix
	../as3/vektrix/EventHandler.as
	../include/vtxas3EventHandler.h
	../src/vtxas3EventHandler.cpp
)

# Binding files
set (file_root_binding
	../include/flash_package.h
	../include/vtxas3Object.h
	../include/vtxas3ScriptInterface.h
	../src/vtxas3Object.cpp
	../src/vtxas3ScriptInterface.cpp
)

# Binding -> [exclude] files
set (file_root_binding_exclude
	../include/flash.h
	../src/flash.cpp
)

# Plugin files
set (file_root_plugin
	../include/vtxas3.h
	../include/vtxas3Plugin.h
	../src/vtxas3Plugin.cpp
)

# the source groups
source_group(""                                  FILES ${file_root})
source_group("_cmake_"                           FILES ${file_root__cmake_})
source_group("AS3 classes"                       FILES ${file_root_as3_classes})
source_group("AS3 classes\\flash"                FILES ${file_root_as3_classes_flash})
source_group("AS3 classes\\flash\\accessibility" FILES ${file_root_as3_classes_flash_accessibility})
source_group("AS3 classes\\flash\\display"       FILES ${file_root_as3_classes_flash_display})
source_group("AS3 classes\\flash\\events"        FILES ${file_root_as3_classes_flash_events})
source_group("AS3 classes\\flash\\external"      FILES ${file_root_as3_classes_flash_external})
source_group("AS3 classes\\flash\\filters"       FILES ${file_root_as3_classes_flash_filters})
source_group("AS3 classes\\flash\\geom"          FILES ${file_root_as3_classes_flash_geom})
source_group("AS3 classes\\flash\\media"         FILES ${file_root_as3_classes_flash_media})
source_group("AS3 classes\\flash\\net"           FILES ${file_root_as3_classes_flash_net})
source_group("AS3 classes\\flash\\system"        FILES ${file_root_as3_classes_flash_system})
source_group("AS3 classes\\flash\\text"          FILES ${file_root_as3_classes_flash_text})
source_group("AS3 classes\\flash\\ui"            FILES ${file_root_as3_classes_flash_ui})
source_group("AS3 classes\\flash\\utils"         FILES ${file_root_as3_classes_flash_utils})
source_group("AS3 classes\\vektrix"              FILES ${file_root_as3_classes_vektrix})
source_group("Binding"                           FILES ${file_root_binding})
source_group("Binding\\[exclude]"                FILES ${file_root_binding_exclude})
source_group("Plugin"                            FILES ${file_root_plugin})

# append all files to the file_root
set (file_root
	${file_root}
	${file_root__cmake_}
	${file_root_as3_classes}
	${file_root_as3_classes_flash}
	${file_root_as3_classes_flash_accessibility}
	${file_root_as3_classes_flash_display}
	${file_root_as3_classes_flash_events}
	${file_root_as3_classes_flash_external}
	${file_root_as3_classes_flash_filters}
	${file_root_as3_classes_flash_geom}
	${file_root_as3_classes_flash_media}
	${file_root_as3_classes_flash_net}
	${file_root_as3_classes_flash_system}
	${file_root_as3_classes_flash_text}
	${file_root_as3_classes_flash_ui}
	${file_root_as3_classes_flash_utils}
	${file_root_as3_classes_vektrix}
	${file_root_binding}
	${file_root_binding_exclude}
	${file_root_plugin}
)

# exclude certain files from all builds
set_source_files_properties (${file_root_binding_exclude} PROPERTIES HEADER_FILE_ONLY TRUE)
