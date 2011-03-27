#-----------------------------------------------------------------------
macro (disable_RTTI)
#{
	if(UNIX)
		set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -fno-rtti")
	endif(UNIX)
	
	if(WIN32)
		set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " /GR-")
	endif(WIN32)
#}
endmacro (disable_RTTI)
#-----------------------------------------------------------------------
macro (disable_LONGJMP)
#{
	if(WIN32)
		set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " /EHs")
	endif(WIN32)
#}
endmacro (disable_LONGJMP)
#-----------------------------------------------------------------------
macro (link_static_crt)
#{
	foreach(flag_var
			CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
			CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
#	{
		if(${flag_var} MATCHES "/MD")
			string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
		endif(${flag_var} MATCHES "/MD")
#	}
	endforeach(flag_var)
#}
endmacro (link_static_crt)
#-----------------------------------------------------------------------
macro (vtx_add_plugin plugin_name)
#{
	set (vtx_plugins_list ${vtx_plugins_list} vektrix_${plugin_name})
	set (vtx_plugins_include ${vtx_plugins_include} ${CMAKE_SOURCE_DIR}/plugins/${plugin_name}/include)
	add_subdirectory (plugins/${plugin_name}/scripts)
#}
endmacro (vtx_add_plugin)
#-----------------------------------------------------------------------
