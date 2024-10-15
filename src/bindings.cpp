#include <cstddef>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "../include/lattice_core.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(_lattice_core, m) {
	m.doc() = "SrTiO3 lattice generator";

	py::class_<STOLattice>( m, "STOLattice" )
		.def( py::init<double, double, size_t, size_t, size_t>(), "a"_a, "c"_a, "N_rows"_a=10, "N_cols"_a=10, "N_layers"_a=5 )
		.def( "populate", &STOLattice::populateLattice, "Populate Lattice with atoms" )
		.def_property_readonly( "lattice", 
			[]( const STOLattice& lattice ) {
				py::array_t<double> np_lattice{ { lattice.N_cells_layers, lattice.N_cells_rows, lattice.N_cells_cols, static_cast<size_t>(3) } };
				auto np_buffer{ np_lattice.mutable_unchecked<4>() };

				for( py::ssize_t i=0; i<lattice.N_cells_layers; i++ ) {
					for ( py::ssize_t j=0; j<lattice.N_cells_rows; j++ ) {
						for ( py::ssize_t k=0; k<lattice.N_cells_cols; k++ ) {
							Point Sr{ lattice.lattice[i][j][k].Sr };
							np_buffer( i, j, k, 0 ) = Sr[0];
							np_buffer( i, j, k, 1 ) = Sr[1];
							np_buffer( i, j, k, 2 ) = Sr[2];
						}
					}
				}

				return np_lattice;
			}
		);
}
