#include <pybind11/pybind11.h>
#include <cstdio>

void show() {
	std::puts( "This is puts output" );
}

PYBIND11_MODULE( _ptest, m ) {
	m.doc() = "test";
	m.def("show", &show, "testfunction");
}
