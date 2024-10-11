#include "lattice.cpp"
#include <cstddef>
#include <string>

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(Lattice, m) {
	m.doc() = "SrTiO3 lattice generator";

	py::class_<Point3D>(m, "Point3D")
		.def(py::init<>(), "Default constructor")
		.def(py::init<double, double, double>(), "x"_a, "y"_a, "z"_a)
		.def_readwrite("x", &Point3D::x)
		.def_readwrite("y", &Point3D::y)
		.def_readwrite("z", &Point3D::z)
		.def("__repr__", [](const Point3D &p) {
				return 
				"Lattice.Point3D: x = " + std::to_string(p.x) +
				", y = " + std::to_string(p.y) + 
				", z = " + std::to_string(p.z);
		});

	py::class_<UnitCell>(m, "UnitCell")
		.def(py::init<>(), "Default constructor")
		.def(py::init<const Point>(), "Sr"_a)
		.def_readwrite("Sr", &UnitCell::Sr)
		.def("__repr__", [](const UnitCell &uc) {
			return "Lattice.UnitCell: Sr = ( " + 
			std::to_string(uc.Sr.x) +
			std::to_string(uc.Sr.y) +
			std::to_string(uc.Sr.z) + " )";
		});

py:class_<STOLattice>(m, "STOLattice")
		.def(py::init<double, double, size_t, size_t, size_t>(), "")
}
