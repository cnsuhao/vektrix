#-------------------------------------------------------------------
# This file is part of the CMake build system for Vektrix
# For the latest info, see http://www.fuse-software.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# This file prints a summary of the selected build features.

set(_features "\n")
set(_features "${_features}----------------------------------------------------------------------------\n")
set(_features "${_features}  FEATURE SUMMARY\n")
set(_features "${_features}----------------------------------------------------------------------------\n\n")

# summarise plugins
if (VEKTRIX_BUILD_PLUGIN_AS3)
	set(_plugins "${_plugins}  + Tamarin ActionScript 3 support\n")
endif ()
if (VEKTRIX_BUILD_PLUGIN_CAIRO)
	set(_plugins "${_plugins}  + Cairo vector output support\n")
endif ()
if (VEKTRIX_BUILD_PLUGIN_CURL)
	set(_plugins "${_plugins}  + cURL HTTP resource support\n")
endif ()
if (VEKTRIX_BUILD_PLUGIN_D3D9)
	set(_plugins "${_plugins}  + Direct3D9 rendering support\n")
endif ()
if (VEKTRIX_BUILD_PLUGIN_FREEIMG)
	set(_plugins "${_plugins}  + FreeImage image loading support FX\n")
endif ()
if (VEKTRIX_BUILD_PLUGIN_OGRE)
	set(_plugins "${_plugins}  + OGRE rendering support FX\n")
endif ()
if (VEKTRIX_BUILD_PLUGIN_SWF)
	set(_plugins "${_plugins}  + SWF parsing support\n")
endif ()
if (VEKTRIX_BUILD_PLUGIN_XML)
	set(_plugins "${_plugins}  + Expat XML parsing support\n")
endif ()

if (DEFINED _plugins)
	set(_features "${_features}Building plugins:\n${_plugins}")
endif ()

# summarise programs
if (VEKTRIX_BUILD_SAMPLES)
	set(_programs "${_programs}  + Demos\n")
endif ()
if (VEKTRIX_BUILD_TOOLS)
	set(_programs "${_programs}  + Tools\n")
endif ()

if (DEFINED _programs)
	set(_features "${_features}Building executables:\n${_programs}")
endif ()

# summarise core features
if (VEKTRIX_CONFIG_ENABLE_ZIP)
	set(_core "${_core}  + ZIP archives\n")
endif ()

if (DEFINED _core)
	set(_features "${_features}Building core features:\n${_core}")
endif ()


set(_features "${_features}\n")


# miscellaneous
macro(var_to_string VAR STR)
	if (${VAR})
		set(${STR} "enabled")
	else ()
		set(${STR} "disabled")
	endif ()
endmacro ()

# various true/false settings
var_to_string(VEKTRIX_CONFIG_MEMTRACK_DEBUG _memtrack_debug)
var_to_string(VEKTRIX_CONFIG_MEMTRACK_RELEASE _memtrack_release)
var_to_string(VEKTRIX_USE_BOOST _boost)

# threading settings
if (VEKTRIX_CONFIG_THREADS EQUAL 0)
	set(_threads "none")
elseif (VEKTRIX_CONFIG_THREADS EQUAL 1)
	set(_threads "full (${VEKTRIX_CONFIG_THREAD_PROVIDER})")
else ()
	set(_threads "background (${VEKTRIX_CONFIG_THREAD_PROVIDER})")
endif ()

# build type
if (VEKTRIX_STATIC)
	set(_buildtype "static")
else ()
	set(_buildtype "dynamic")
endif ()

set(_features "${_features}Build type:                      ${_buildtype}\n")
set(_features "${_features}Threading support:               ${_threads}\n")
set(_features "${_features}Memory tracker (debug):          ${_memtrack_debug}\n")
set(_features "${_features}Memory tracker (release):        ${_memtrack_release}\n")
set(_features "${_features}Use Boost:                       ${_boost}\n")

set(_features "${_features}\n----------------------------------------------------------------------------\n")
message(STATUS ${_features})
