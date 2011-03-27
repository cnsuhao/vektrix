# Try to find ogre
# Once done, this will define
#
#  ogre_found			- ogre has been found successfully
#  ogre_include_dirs	- the ogre include directories
#  ogre_libraries		- the ogre link libraries

set (ogre__path "<default>" CACHE STRING "You can use this option to specify an alternate path to the ogre dependency")

# unix discovery
if(WIN32)

	if(ogre__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (ogre_path ${CMAKE_SOURCE_DIR}/dependencies CACHE INTERNAL "")
		
	else(ogre__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (ogre_path ${ogre__path} CACHE INTERNAL "")
		
	endif(ogre__path STREQUAL "<default>")
	
	# try to find the ogre libraries & headers from a pre-compiled package
	find_path(ogre_include_dirs	NAMES ogre.h PATHS ${ogre_path}/include/ogre)
	
	if(BUILD_USE_STATIC_CRT)
		find_path(ogre_d3d9_dirs	NAMES OgreD3D9Plugin.h PATHS ${ogre_path}/include/ogre/RenderSystems/Direct3D9/include)
		find_path(ogre_opengl_dirs	NAMES OgreGLPlugin.h PATHS ${ogre_path}/include/ogre/RenderSystems/GL/include)
		
		set (ogre_include_dirs ${ogre_include_dirs} ${ogre_d3d9_dirs} ${ogre_opengl_dirs})

		find_library(ogre_lib	NAMES OgreMainStatic	PATHS ${ogre_path}/lib/Release)
		find_library(ogre_lib_d	NAMES OgreMainStatic_d	PATHS ${ogre_path}/lib/Debug)

		find_library(ogre_d3d9_rs_lib	NAMES RenderSystem_Direct3D9Static		PATHS ${ogre_path}/lib/Release)
		find_library(ogre_d3d9_rs_lib_d	NAMES RenderSystem_Direct3D9Static_d	PATHS ${ogre_path}/lib/Debug)

		find_library(ogre_opengl_rs_lib		NAMES RenderSystem_GLStatic		PATHS ${ogre_path}/lib/Release)
		find_library(ogre_opengl_rs_lib_d	NAMES RenderSystem_GLStatic_d	PATHS ${ogre_path}/lib/Debug)
		
		find_path(ogre_res_path OgreWin32Resources.res PATHS ${ogre_path}/res)
		set (ogre_win32_res ${ogre_res_path}/OgreWin32Resources.res)
	else(BUILD_USE_STATIC_CRT)
		find_library(ogre_lib	NAMES OgreMain		PATHS ${ogre_path}/lib/Release)
		find_library(ogre_lib_d	NAMES OgreMain_d	PATHS ${ogre_path}/lib/Debug)
	endif(BUILD_USE_STATIC_CRT)
	
	if(ogre_lib AND ogre_lib_d)
		set (ogre_libraries
			debug ${ogre_lib_d}
			debug ${ogre_d3d9_rs_lib_d}
			debug ${ogre_opengl_rs_lib_d}
			optimized ${ogre_lib}
			optimized ${ogre_d3d9_rs_lib}
			optimized ${ogre_opengl_rs_lib}
		)
	endif(ogre_lib AND ogre_lib_d)

endif(WIN32)

# unix discovery
if(UNIX)

	if(ogre__path STREQUAL "<default>")
	
		# use default path to the dependency
		set (ogre_path /usr CACHE INTERNAL "")
		
	else(ogre__path STREQUAL "<default>")
	
		# use the path that was specified by the user
		set (ogre_path ${ogre__path} CACHE INTERNAL "")
		
	endif(ogre__path STREQUAL "<default>")

	# try to find the ogre libraries & headers
	find_path(ogre_include_dirs	NAMES Ogre.h PATHS ${ogre_path}/include/OGRE ${ogre_path}/local/include/OGRE)
	
	find_library(ogre_lib		NAMES OgreMain PATHS ${ogre_path}/lib ${ogre_path}/local/lib)
	#find_library(ogre_lib_d	NAMES ogre PATHS ${ogre_path}/lib/Debug)
	
	if(ogre_lib)# AND ogre_lib_d)
		set (ogre_libraries
			#debug ${ogre_lib_d}
			optimized ${ogre_lib}
		)
	endif(ogre_lib)# AND ogre_lib_d)

endif()

# found ogre successfully
if(ogre_include_dirs AND ogre_libraries)
	set(ogre_found TRUE)
endif(ogre_include_dirs AND ogre_libraries)

# report find result
if(ogre_found)
	if(NOT ogre_FIND_QUIETLY)
		message(STATUS "Found ogre: ${ogre_path}")
	endif(NOT ogre_FIND_QUIETLY)
else(ogre_found)
	if(ogre_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find ogre")
	endif(ogre_FIND_REQUIRED)
endif(ogre_found)
