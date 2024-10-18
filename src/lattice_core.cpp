#include "../include/lattice_core.hpp"
#include <Eigen/src/Core/Matrix.h>
#include <cmath>
#include <cstddef>
#include <iostream>

#define print(x) std::cout << x << std::endl;

void rodriguesRotation( Point& point, Vector rotation_axis, const double angle ) {
	rotation_axis /= rotation_axis.norm();

	Eigen::Matrix3d I{ Eigen::Matrix3d::Identity() };
	Eigen::Matrix3d K;
	K << 0, -rotation_axis(2), rotation_axis(1),
		 rotation_axis(2), 0, -rotation_axis(0),
		 -rotation_axis(1), rotation_axis(0), 0;

	Eigen::Matrix3d R{ I + sin(angle)*K + (1-cos(angle))*K*K };

	point = R*point;
}

double tiltAmplitudeX( double x_coord, double xi ); 
double tiltAmplitudeZ( double x_coord, double xi ); 

void rotateO( UnitCell& cell, const Point relativeOrigin, const double angle ) {
	Vector rotation_axis{ cell.a1 - cell.a2 };

	cell.O_bottom -= relativeOrigin;
	cell.O_front -= relativeOrigin;
	cell.O_left -= relativeOrigin;

	rodriguesRotation( cell.O_bottom, rotation_axis, angle );
	rodriguesRotation( cell.O_front, rotation_axis, angle );
	rodriguesRotation( cell.O_left, rotation_axis, angle );

	cell.O_bottom += relativeOrigin;
	cell.O_front += relativeOrigin;
	cell.O_left += relativeOrigin;
}

UnitCell::UnitCell( size_t layer, size_t row, size_t col, double a, double c, double angle ) 
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
	
	if ( angle != 0 ) {
		size_t exp{ layer + row + col };
		short sign{ 1 };

		if ( exp%2 != 0 ) {
			sign = -1;
		}

		angle = sign*angle*M_PI/180;
		rotateO( *this, Ti, angle );
	}
}

STOLattice::STOLattice( double a, double c, double angle, size_t N_cells_rows, size_t N_cells_cols, size_t N_cells_layers )
	: N_cells_rows{ N_cells_rows } 
	, N_cells_cols{ N_cells_cols } 
	, N_cells_layers{ N_cells_layers }
	, a{ a }
	, c{ c }
	, angle{ angle }
	, lattice{ N_cells_layers, std::vector<std::vector<UnitCell>>( N_cells_rows, std::vector<UnitCell>( N_cells_cols ) ) }
{}

void STOLattice::populateLattice() {
	for( size_t i=0; i<N_cells_layers; i++ ) {
		for ( size_t j=0; j<N_cells_rows; j++ ) {
			for ( size_t k=0; k<N_cells_cols; k++ ) {
				lattice[i][j][k] = UnitCell{ i, j, k, a, c, angle };
			}
		}
	}
}

void STOLattice::shiftLattice( const Vector shift_vector ) {
	for( size_t i=0; i<N_cells_layers; i++ ) {
		for ( size_t j=0; j<N_cells_rows; j++ ) {
			for ( size_t k=0; k<N_cells_cols; k++ ) {
				lattice[i][j][k].Sr+=shift_vector; 
				lattice[i][j][k].Ti+=shift_vector; 
				lattice[i][j][k].O_bottom+=shift_vector; 
				lattice[i][j][k].O_front+=shift_vector; 
				lattice[i][j][k].O_left+=shift_vector; 
			}
		}
	}
}
