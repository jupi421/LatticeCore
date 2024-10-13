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
