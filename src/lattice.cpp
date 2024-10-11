#include <array>
#include <memory>
#include <vector>

using Point = std::array<double, 3>;
using LatticeVector = std::array<double, 3>;
using BaseVector = std::array<double, 3>;

struct UnitCell {
	Point Sr{};
	//Point Ti{};
	//Point O_bottom{}, O_front{}, O_left{};

	//BasisVector a1, a2, a3, a4; // a1->Ti, a2->O_bottom, a3->O_front, a4->O_left

	//UnitCell() {
	//	Point zero = Point();
	//	Sr = Ti = O_bottom = O_front = O_left = Point();
	//}

	UnitCell() = default;
	UnitCell( const Point Sr ) : Sr{ Sr } {}

	//UnitCell(const Point Sr, const Point Ti, const Point O_bottom, const Point O_front, const Point O_left)
	//	: Sr(Sr), Ti(Ti), O_bottom(O_bottom), O_front(O_front), O_left(O_left)
	//{}
};

struct STOLattice {
	LatticeVector a_x;
	LatticeVector a_y; 
	LatticeVector c_z;
	double a;
	double c;
	size_t N_cells_rows{ 10 };
	size_t N_cells_cols{ 10 };
	size_t N_cells_layers{ 5 };
	std::vector<std::vector<std::vector<UnitCell>>> lattice;

	STOLattice( ) = default;
	STOLattice( double a, double c, size_t N_cells_rows, size_t N_cells_cols, size_t N_cells_layers )
		: N_cells_rows{ N_cells_cols } 
		, N_cells_cols{ N_cells_cols } 
		, N_cells_layers{ N_cells_layers }
		, a{ a }
		, c{ c }
		, lattice{ N_cells_layers, std::vector<std::vector<UnitCell>>(N_cells_rows, std::vector<UnitCell>(N_cells_cols)) }
	{
		LatticeVector a_x { a, 0, 0 };
		LatticeVector a_y { 0, a, 0 };
		LatticeVector c_z { 0, 0, c };
	}
};

std::unique_ptr<UnitCell> createUnitCell(size_t i, size_t j, size_t k, double a, double c) {
	
	double x = k*a;
	double y = i*a;
	double z = j*c;

	Point Sr = Point3D(x, y, z);

	
	UnitCell cell = { Sr }; //, Ti, O_bottom, O_front, O_left };
	return std::make_unique<UnitCell>(cell);
}

void populateLattice(STOLattice& lattice) {
	for(size_t i=0; i<lattice.N_cells_layers; i++) {
		for (size_t j=0; j<lattice.N_cells_rows; j++) {
			for (size_t k = 0; k<lattice.N_cells_cols; k++) {
				std::unique_ptr<UnitCell> cell = createUnitCell(i, j, k, lattice.a, lattice.c);
				lattice.lattice[i][j][k] = *cell;
			}
		}
	}
};
