#include <Eigen/Dense>
#include <vector>

using Point = Eigen::Vector3d;
using BaseVector = Eigen::Vector3d;
using Vector = Eigen::Vector3d;

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
	UnitCell( size_t layer, size_t row, size_t col, double a, double c, double angle );
};


struct STOLattice {
	size_t N_cells_rows;
	size_t N_cells_cols;
	size_t N_cells_layers;
	std::vector<std::vector<std::vector<UnitCell>>> lattice;
	double a;
	double c;
	double angle;

	STOLattice( double a, double c, double angle, size_t N_cells_rows=10, size_t N_cells_cols=10, size_t N_cells_layers=5 );

	void populateLattice();
	void shiftLattice( const Vector shift_vector );
	//void rotateLattice( double angle );
	//void mirror();
	//void removeDuplicates();
};
