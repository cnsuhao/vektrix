# top-level files
set (file_root
	../include/vtxtests.h
)

# _cmake_ files
set (file_root__cmake_
	CMakeLists.txt
	vektrix_UnitTests_src_files.cmake
	vektrix_UnitTests_src_files.cmake.rule
)

# Application files
set (file_root_application
	../src/UnitTestsApp.cpp
)

# Testing files
set (file_root_testing
	../include/vtxtestsUnitTestList.h
)

# Testing -> Interfaces files
set (file_root_testing_interfaces
	../include/vtxtestsUnitTest.h
	../include/vtxtestsUnitTestHost.h
	../src/vtxtestsUnitTest.cpp
	../src/vtxtestsUnitTestHost.cpp
)

# Tests files
set (file_root_tests
	../generate_test_list.py
)

# Tests -> as3 files
set (file_root_tests_as3
	../tests/as3/flash_display_DisplayObject/flash_display_DisplayObject.cpp
	../tests/as3/flash_display_DisplayObject/flash_display_DisplayObject.h
	../tests/as3/flash_external_ExternalInterface/flash_external_ExternalInterface.cpp
	../tests/as3/flash_external_ExternalInterface/flash_external_ExternalInterface.h
)

# Tests -> swf files
set (file_root_tests_swf
	../tests/swf/ImageParsing/ImageParsing.cpp
	../tests/swf/ImageParsing/ImageParsing.h
)

# the source groups
source_group(""                    FILES ${file_root})
source_group("_cmake_"             FILES ${file_root__cmake_})
source_group("Application"         FILES ${file_root_application})
source_group("Testing"             FILES ${file_root_testing})
source_group("Testing\\Interfaces" FILES ${file_root_testing_interfaces})
source_group("Tests"               FILES ${file_root_tests})
source_group("Tests\\as3"          FILES ${file_root_tests_as3})
source_group("Tests\\swf"          FILES ${file_root_tests_swf})

# append all files to the file_root
set (file_root
	${file_root}
	${file_root__cmake_}
	${file_root_application}
	${file_root_testing}
	${file_root_testing_interfaces}
	${file_root_tests}
	${file_root_tests_as3}
	${file_root_tests_swf}
)
