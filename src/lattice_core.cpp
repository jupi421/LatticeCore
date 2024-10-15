#include "../include/lattice_core.hpp"

UnitCell::UnitCell(size_t layer, size_t row, size_t col, double a, double c) 
	: a1{ 0.5*a, 0.5*a, 0.5*c }
	, a2{ 0.5*a, 0.5*a, 0 }
	, a3{ 0.5*a, 0, 0.5*c }
	, a4{ 0, 0.5*a, 0.5*c }
{
	double x = col*a;
	double y = layer*a;
	double z = row*c;

	Sr = Point{ x, y, z };
	Ti = Sr+a1;
	O_bottom = Sr+a2;
	O_front = Sr+a3;
	O_left = Sr+a4;
}

BaseVector operator+( const BaseVector& v1, const BaseVector& v2 ) {
	return BaseVector{ v1[0]+v2[0], v1[1]+v2[1], v1[2]+v2[2] };
}

STOLattice::STOLattice(  double a, double c, size_t N_cells_rows, size_t N_cells_cols, size_t N_cells_layers )
	: N_cells_rows{ N_cells_rows } 
	, N_cells_cols{ N_cells_cols } 
	, N_cells_layers{ N_cells_layers }
	, a{ a }
	, c{ c }
	, lattice{ N_cells_layers, std::vector<std::vector<UnitCell>>( N_cells_rows, std::vector<UnitCell>( N_cells_cols ) ) }
{}

void STOLattice::populateLattice() {
	for( size_t i=0; i<N_cells_layers; i++ ) {
		for ( size_t j=0; j<N_cells_rows; j++ ) {
			for ( size_t k=0; k<N_cells_cols; k++ ) {
				lattice[i][j][k] = UnitCell{ i, j, k, a, c };
			}
		}
	}
};

void STOLattice::shiftLattice( std::array<double, 3> shift_vector ) {
	for( size_t i=0; i<N_cells_layers; i++ ) {
		for ( size_t j=0; j<N_cells_rows; j++ ) {
			for ( size_t k=0; k<N_cells_cols; k++ ) {
				lattice[i][j][k].Sr+shift_vector; 
				lattice[i][j][k].Ti+shift_vector; 
				lattice[i][j][k].O_bottom+shift_vector; 
				lattice[i][j][k].O_front+shift_vector; 
				lattice[i][j][k].O_left+shift_vector; 
			}
		}
	}
}
