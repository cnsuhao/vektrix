# top-level files
set (file_root
)

# _cmake_ files
set (file_root__cmake_
	CMakeLists.txt
	vektrix_SwfPlugin_src_files.cmake
	vektrix_SwfPlugin_src_files.cmake.rule
)

# Parser files
set (file_root_parser
	../include/vtxswfParser.h
	../include/vtxswfParserTypes.h
	../src/vtxswfParser.cpp
)

# Plugin files
set (file_root_plugin
	../include/vtxswf.h
	../include/vtxswfPlugin.h
	../src/vtxswfPlugin.cpp
)

# TagParsers files
set (file_root_tagparsers
	../include/vtxswfFontParser.h
	../include/vtxswfImageParser.h
	../include/vtxswfScriptParser.h
	../include/vtxswfShapeParser.h
	../include/vtxswfStructureParser.h
	../include/vtxswfTextParser.h
	../src/vtxswfFontParser.cpp
	../src/vtxswfImageParser.cpp
	../src/vtxswfScriptParser.cpp
	../src/vtxswfShapeParser.cpp
	../src/vtxswfStructureParser.cpp
	../src/vtxswfTextParser.cpp
)

# TagParsers -> Shape files
set (file_root_tagparsers_shape
	../include/vtxswfContourElement.h
	../include/vtxswfContourPoint.h
	../include/vtxswfSubLine.h
	../include/vtxswfSubShape.h
	../src/vtxswfContourElement.cpp
	../src/vtxswfContourPoint.cpp
)

# the source groups
source_group(""                  FILES ${file_root})
source_group("_cmake_"           FILES ${file_root__cmake_})
source_group("Parser"            FILES ${file_root_parser})
source_group("Plugin"            FILES ${file_root_plugin})
source_group("TagParsers"        FILES ${file_root_tagparsers})
source_group("TagParsers\\Shape" FILES ${file_root_tagparsers_shape})

# append all files to the file_root
set (file_root
	${file_root}
	${file_root__cmake_}
	${file_root_parser}
	${file_root_plugin}
	${file_root_tagparsers}
	${file_root_tagparsers_shape}
)
