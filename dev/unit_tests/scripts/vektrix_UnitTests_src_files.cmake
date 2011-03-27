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

# [$ogre_win32_res] files
set (file_root_ogre_win32_res
	${ogre_win32_res}
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

# Testing -> Interfaces -> Ogre files
set (file_root_testing_interfaces_ogre
	../include/vtxtestsOgreBase.h
	../src/vtxtestsOgreBase.cpp
)

# Testing -> Interfaces -> OIS files
set (file_root_testing_interfaces_ois
	../include/vtxtestsOISBase.h
	../src/vtxtestsOISBase.cpp
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

# Tests -> core files
set (file_root_tests_core
)

# Tests -> core -> EditText files
set (file_root_tests_core_edittext
	../tests/core/EditText/EditText.cpp
	../tests/core/EditText/EditText.h
)

# Tests -> opengl files
set (file_root_tests_opengl
)

# Tests -> opengl -> Basic files
set (file_root_tests_opengl_basic
	../tests/opengl/Basic/Basic.cpp
	../tests/opengl/Basic/Basic.h
)

# Tests -> swf files
set (file_root_tests_swf
	../tests/swf/ImageParsing/ImageParsing.cpp
	../tests/swf/ImageParsing/ImageParsing.h
)

# the source groups
source_group(""                          FILES ${file_root})
source_group("_cmake_"                   FILES ${file_root__cmake_})
source_group("Application"               FILES ${file_root_application})
source_group("[$ogre_win32_res]"         FILES ${file_root_ogre_win32_res})
source_group("Testing"                   FILES ${file_root_testing})
source_group("Testing\\Interfaces"       FILES ${file_root_testing_interfaces})
source_group("Testing\\Interfaces\\Ogre" FILES ${file_root_testing_interfaces_ogre})
source_group("Testing\\Interfaces\\OIS"  FILES ${file_root_testing_interfaces_ois})
source_group("Tests"                     FILES ${file_root_tests})
source_group("Tests\\as3"                FILES ${file_root_tests_as3})
source_group("Tests\\core"               FILES ${file_root_tests_core})
source_group("Tests\\core\\EditText"     FILES ${file_root_tests_core_edittext})
source_group("Tests\\opengl"             FILES ${file_root_tests_opengl})
source_group("Tests\\opengl\\Basic"      FILES ${file_root_tests_opengl_basic})
source_group("Tests\\swf"                FILES ${file_root_tests_swf})

# append all files to the file_root
set (file_root
	${file_root}
	${file_root__cmake_}
	${file_root_application}
	${file_root_ogre_win32_res}
	${file_root_testing}
	${file_root_testing_interfaces}
	${file_root_testing_interfaces_ogre}
	${file_root_testing_interfaces_ois}
	${file_root_tests}
	${file_root_tests_as3}
	${file_root_tests_core}
	${file_root_tests_core_edittext}
	${file_root_tests_opengl}
	${file_root_tests_opengl_basic}
	${file_root_tests_swf}
)
