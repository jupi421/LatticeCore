#include <array>
#include <vector>

using Point = std::array<double, 3>;
using LatticeVector = std::array<double, 3>;
using BaseVector = std::array<double, 3>;

BaseVector operator+( const BaseVector& v1, const BaseVector& v2 ); 

struct UnitCell {
	Point Sr{};
	Point Ti{};
	Point O_bottom{};
	Point O_front{};
	Point O_left{};

	BaseVector a1{}; //Ti
	BaseVector a2{}; //O_bottom
	BaseVector a3{}; //O_front
	BaseVector a4{}; //O_left
	
	UnitCell() = default;
	UnitCell( size_t layer, size_t row, size_t col, double a, double c );
};


struct STOLattice {
	LatticeVector a_x;
	LatticeVector a_y; 
	LatticeVector c_z;
	double a;
	double c;
	size_t N_cells_rows;
	size_t N_cells_cols;
	size_t N_cells_layers;
	std::vector<std::vector<std::vector<UnitCell>>> lattice;

	STOLattice( double a, double c, size_t N_cells_rows=10, size_t N_cells_cols=10, size_t N_cells_layers=5 );
	void populateLattice();
};
