# Try to find tamarin
# Once done, this will define
#
#  tamarin_found			- tamarin has been found successfully
#  tamarin_include_dirs		- the tamarin include directories
#  tamarin_libs				- the tamarin link libraries
#  tamarin_debugger_libs	- the tamarin debugger link libraries

set (tamarin__path "<default>" CACHE STRING "You can use this option to specify an alternate path to the tamarin dependency")

# win32 discovery
if(WIN32)

	if(tamarin__path STREQUAL "<default>")

		# use default path to the dependency
		set (tamarin_path ${CMAKE_SOURCE_DIR}/dependencies CACHE INTERNAL "")

	else(tamarin__path STREQUAL "<default>")

		# use the path that was specified by the user
		set (tamarin_path ${tamarin__path} CACHE INTERNAL "")

	endif(tamarin__path STREQUAL "<default>")

	# find the tamarin headers
	find_path(tamarin_include_base NAMES core/avmplus.h PATHS ${tamarin_path}/include/caspin/tamarin)

	if(MSVC90)
	
		set (tamarin_output_dir ${tamarin_path}/lib)
		
		# tamarin debug libraries
		find_library(tamarin_avmplus_lib_d	NAMES avmplus	PATHS ${tamarin_output_dir}/Debug)
		find_library(tamarin_eval_lib_d		NAMES eval		PATHS ${tamarin_output_dir}/Debug)
		find_library(tamarin_mmgc_lib_d		NAMES MMgc		PATHS ${tamarin_output_dir}/Debug)
		find_library(tamarin_nanojit_lib_d	NAMES nanojit	PATHS ${tamarin_output_dir}/Debug)
		
		# tamarin release libraries
		find_library(tamarin_avmplus_lib	NAMES avmplus	PATHS ${tamarin_output_dir}/Release)
		find_library(tamarin_eval_lib		NAMES eval		PATHS ${tamarin_output_dir}/Release)
		find_library(tamarin_mmgc_lib		NAMES MMgc		PATHS ${tamarin_output_dir}/Release)
		find_library(tamarin_nanojit_lib	NAMES nanojit	PATHS ${tamarin_output_dir}/Release)
		
		# tamarin debugger debug libraries
		find_library(tamarin_avmplus_debugger_lib_d	NAMES avmplus_debugger	PATHS ${tamarin_output_dir}/Debug)
		find_library(tamarin_eval_debugger_lib_d	NAMES eval_debugger		PATHS ${tamarin_output_dir}/Debug)
		find_library(tamarin_mmgc_debugger_lib_d	NAMES MMgc_debugger		PATHS ${tamarin_output_dir}/Debug)
		find_library(tamarin_nanojit_debugger_lib_d	NAMES nanojit_debugger	PATHS ${tamarin_output_dir}/Debug)
		
		# tamarin debugger release libraries
		find_library(tamarin_avmplus_debugger_lib	NAMES avmplus_debugger	PATHS ${tamarin_output_dir}/Release)
		find_library(tamarin_eval_debugger_lib		NAMES eval_debugger		PATHS ${tamarin_output_dir}/Release)
		find_library(tamarin_mmgc_debugger_lib		NAMES MMgc_debugger		PATHS ${tamarin_output_dir}/Release)
		find_library(tamarin_nanojit_debugger_lib	NAMES nanojit_debugger	PATHS ${tamarin_output_dir}/Release)
		
		set (tamarin_libs
			# debug
			debug ${tamarin_avmplus_lib_d}
			debug ${tamarin_eval_lib_d}
			debug ${tamarin_mmgc_lib_d}
			debug ${tamarin_nanojit_lib_d}

			# release
			optimized ${tamarin_avmplus_lib}
			optimized ${tamarin_eval_lib}
			optimized ${tamarin_mmgc_lib}
			optimized ${tamarin_nanojit_lib}
		)
		
		set (tamarin_debugger_libs
			# debug
			debug ${tamarin_avmplus_debugger_lib_d}
			debug ${tamarin_eval_debugger_lib_d}
			debug ${tamarin_mmgc_debugger_lib_d}
			debug ${tamarin_nanojit_debugger_lib_d}

			# release
			optimized ${tamarin_avmplus_debugger_lib}
			optimized ${tamarin_eval_debugger_lib}
			optimized ${tamarin_mmgc_debugger_lib}
			optimized ${tamarin_nanojit_debugger_lib}
		)
	endif(MSVC90)
	
	if(MSVC10)
	
		set (tamarin_output_dir ${tamarin_path}/lib)
		
		# tamarin debug libraries
		find_library(tamarin_avm_lib_d NAMES avm PATHS ${tamarin_output_dir}/Debug)

		# tamarin release libraries
		find_library(tamarin_avm_lib NAMES avm PATHS ${tamarin_output_dir}/Release)

		# tamarin debugger debug libraries
		find_library(tamarin_avm_debugger_lib_d NAMES avm_debugger PATHS ${tamarin_output_dir}/Debug)

		# tamarin debugger release libraries
		find_library(tamarin_avm_debugger_lib NAMES avm_debugger PATHS ${tamarin_output_dir}/Release)

		set (tamarin_libs
			# debug
			debug ${tamarin_avm_lib_d}

			# release
			optimized ${tamarin_avm_lib}
		)

		set (tamarin_debugger_libs
			# debug
			debug ${tamarin_avm_debugger_lib_d}

			# release
			optimized ${tamarin_avm_debugger_lib}
		)
	endif(MSVC10)
	
	# additional win32 libraries
	set (tamarin_libs
		${tamarin_libs}
		winmm.lib
	)
	
	set (tamarin_debugger_libs
		${tamarin_debugger_libs}
		winmm.lib
	)

endif(WIN32)

if(UNIX)

	if(tamarin__path STREQUAL "<default>")

		# use default path to the dependency
		set (tamarin_path ${caspin_path}/tamarin CACHE INTERNAL "")

	else(tamarin__path STREQUAL "<default>")

		# use the path that was specified by the user
		set (tamarin_path ${tamarin__path} CACHE INTERNAL "")

	endif(tamarin__path STREQUAL "<default>")

	# find the tamarin headers
	find_path(tamarin_include_base NAMES core/avmplus.h PATHS ${tamarin_path})

	# tamarin default libraries
	find_library(tamarin_avmplus_lib	NAMES avmplus	PATHS ${tamarin_path}/bin)
	find_library(tamarin_mmgc_lib		NAMES MMgc		PATHS ${tamarin_path}/bin)

	# tamarin debugger libraries
	find_library(tamarin_avmplus_debugger_lib	NAMES avmplus_debugger	PATHS ${tamarin_path}/bin)
	find_library(tamarin_mmgc_debugger_lib		NAMES MMgc_debugger		PATHS ${tamarin_path}/bin)
	
	set (tamarin_libs
		${tamarin_avmplus_lib}
		${tamarin_mmgc_lib}
		pthread
	)
	
	set (tamarin_debugger_libs
		${tamarin_avmplus_debugger_lib}
		${tamarin_mmgc_debugger_lib}
		pthread
	)
	
endif()

# the tamarin include directories
set (tamarin_include_dirs
	${tamarin_include_base}/core
	${tamarin_include_base}/VMPI
	${tamarin_include_base}/platform
	${tamarin_include_base}/MMgc
	${tamarin_include_base}/eval
	${tamarin_include_base}/other-licenses/zlib
	${tamarin_include_base}/shell
	${tamarin_include_base}/extensions
)

# found tamarin successfully
if(tamarin_include_base AND tamarin_libs AND tamarin_debugger_libs)
	set(tamarin_found TRUE)
endif(tamarin_include_base AND tamarin_libs AND tamarin_debugger_libs)

# report find result
if(tamarin_found)
	if(NOT tamarin_FIND_QUIETLY)
		message(STATUS "Found tamarin: ${tamarin_path}")
	endif(NOT tamarin_FIND_QUIETLY)
else(tamarin_found)
	if(tamarin_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find tamarin")
	endif(tamarin_FIND_REQUIRED)
endif(tamarin_found)
