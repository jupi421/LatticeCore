#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <cstddef>
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
				py::array_t<double> np_lattice{ { lattice.N_cells_layers, lattice.N_cells_rows, lattice.N_cells_cols, static_cast<size_t>(5), static_cast<size_t>(3) } };
				auto np_buffer{ np_lattice.mutable_unchecked<5>() };

				for( py::ssize_t i=0; i<lattice.N_cells_layers; i++ ) {
					for ( py::ssize_t j=0; j<lattice.N_cells_rows; j++ ) {
						for ( py::ssize_t k=0; k<lattice.N_cells_cols; k++ ) {
							Point Sr{ lattice.lattice[i][j][k].Sr };
							Point Ti{ lattice.lattice[i][j][k].Ti };
							Point O_bottom{ lattice.lattice[i][j][k].O_bottom };
							Point O_front{ lattice.lattice[i][j][k].O_front };
							Point O_left{ lattice.lattice[i][j][k].O_left };
							
							np_buffer( i, j, k, 0, 0 ) = Sr[0];
							np_buffer( i, j, k, 0, 1 ) = Sr[1];
							np_buffer( i, j, k, 0, 2 ) = Sr[2];

							np_buffer( i, j, k, 1, 0 ) = Ti[0];
							np_buffer( i, j, k, 1, 1 ) = Ti[1];
							np_buffer( i, j, k, 1, 2 ) = Ti[2];

							np_buffer( i, j, k, 2, 0 ) = O_bottom[0];
							np_buffer( i, j, k, 2, 1 ) = O_bottom[1];
							np_buffer( i, j, k, 2, 2 ) = O_bottom[2];

							np_buffer( i, j, k, 3, 0 ) = O_front[0];
							np_buffer( i, j, k, 3, 1 ) = O_front[1];
							np_buffer( i, j, k, 3, 2 ) = O_front[2];
						
							np_buffer( i, j, k, 4, 0 ) = O_left[0];
							np_buffer( i, j, k, 4, 1 ) = O_left[1];
							np_buffer( i, j, k, 4, 2 ) = O_left[2];
						}
					}
				}

				return np_lattice;
			},
			"Returns a np.ndarray of shape (Nlayers, Nrows, Ncols, 2, 3); The slice [:,:,:,i,:] returns the position of Sr, Ti, bottom O, front O and left O of each unit cell respectively"
		);
}
