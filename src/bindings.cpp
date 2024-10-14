#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "../include/lattice_core.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(_lattice_core, m) {
	m.doc() = "SrTiO3 lattice generator";

	py::class_<UnitCell>( m, "UnitCell" )
		.def( py::init<>() )
		.def_property_readonly( "Sr", 
			[]( const UnitCell& cell ) { 
				return py::array_t<double>( 3, cell.Sr.data());
			}
		);

	py::class_<STOLattice>( m, "STOLattice" )
		.def( py::init<double, double, size_t, size_t, size_t>(), "a"_a, "c"_a, "N_rows"_a=10, "N_cols"_a=10, "N_layers"_a=5 )
		.def( "populate", &STOLattice::populateLattice, "Populate Lattice with atoms" );
		//.def_readonly( "lattice", &STOLattice::lattice );
}

