cmake_minimum_required(VERSION 3.15...3.29)
project(example LANGUAGES CXX)

include(FetchContent)
FetchContent_declare(
	pybind11
	GIT_REPOSITORY https://github.com/pybind/pybind11.git
	GIT_TAG v2.11.1
)
FetchContent_MakeAvailable(pybind11)

pybind11_add_module(_ptest src/ptest.cpp)
install(TARGETS _ptest DESTINATION .)

execute_process(
	COMMAND pybind11-stubgen --help
	WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
	RESULT_VARIABLE PYBIND11_STUBGEN_FOUND
	OUTPUT_QUIET
	ERROR_QUIET
)

#if(PYBIND11_STUBGEN_FOUND EQUAL 0)
#	message(STATUS "pybind11-stubgen found -> creating STUB files")
#
#	add_custom_command(
#		TARGET _ptest POST_BUILD
#		#			pybind11-stubgen _ptest 
#		#COMMAND bash -c "mv stubs/* ."
#		#COMMAND bash -c "rmdir stubs"
#	)
#else()
#	message(STATUS "pybind11-stubgen not found -> creating STUB files skipped")
#endif()
