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
