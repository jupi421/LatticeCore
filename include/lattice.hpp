#include <array>
#include <vector>

using Point = std::array<double, 3>;
using LatticeVector = std::array<double, 3>;
using BaseVector = std::array<double, 3>;

struct UnitCell {
	Point Sr{};

	UnitCell() = default;
	UnitCell( const Point Sr ) : Sr{ Sr } {}
	//Point Ti{};
	//Point O_bottom{}, O_front{}, O_left{};

	//BasisVector a1, a2, a3, a4; // a1->Ti, a2->O_bottom, a3->O_front, a4->O_left

	//UnitCell() {
	//	Point zero = Point();
	//	Sr = Ti = O_bottom = O_front = O_left = Point();
	//}


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

	STOLattice( double a, double c, size_t N_cells_rows, size_t N_cells_cols, size_t N_cells_layers );
};
