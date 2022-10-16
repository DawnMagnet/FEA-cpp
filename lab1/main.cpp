#include <NumCpp.hpp>
#include <bits/stdc++.h>


namespace PlaneTruss {
	using Mat = nc::NdArray<double>;
	using i32 = nc::int32;
	using i64 = nc::int64;
	using u64 = nc::uint64;
	using std::iterator;
	using f64 = double;
	const double pi = nc::constants::pi;
	using std::cout;
	using std::endl;
	using std::vector;

	Mat PlaneTrussAssemble(Mat K, Mat &k, i32 i, i32 j) {
		// %PlaneTrussAssemble   This function assembles the element stiffness
		// %                     matrix k of the plane truss element with nodes
		// %                     i and j into the global stiffness matrix K.
		// %                     This function returns the global stiffness
		// %                     matrix K after the element stiffness matrix
		// %                     k is assembled.
		vector<int> arr = {2 * i - 1, 2 * i, 2 * j - 1, 2 * j};
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				K(arr[i] - 1, arr[j] - 1) += k(i, j);
			}
		}
		return K;
	}
	Mat PlaneTrussElementForce(Mat E, Mat A, double L, double theta, Mat u) {
		// %PlaneTrussElementForce   This function returns the element force
		// %                         given the modulus of elasticity E, the
		// %                         cross-sectional area A, the length L,
		// %                         the angle theta (in degrees), and the
		// %                         element nodal displacement vector u.
		double x = theta * pi / 180;
		double C = cos(x);
		double S = sin(x);
		return E * A / L * Mat({-C, -S, C, S}) * u;
	}
	double PlaneTrussElementLength(double x1, double y1, double x2, double y2) {
		// %PlaneTrussElementLength   This function returns the length of the
		// %                          plane truss element whose first node has
		// %                          coordinates (x1,y1) and second node has
		// %                          coordinates (x2,y2).
		return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	}
	Mat PlaneTrussElementStiffness(double E, double A, double L, double theta) {
		// %PlaneTrussElementStiffness   This function returns the element
		// %                             stiffness matrix for a plane truss
		// %                             element with modulus of elasticity E,
		// %                             cross-sectional area A, length L, and
		// %                             angle theta (in degrees).
		// %                             The size of the element stiffness
		// %                             matrix is 4 x 4.
		double x = theta * pi / 180;
		double C = cos(x);
		double S = sin(x);
		return E * A / L * Mat({{C * C, C * S, -C * C, -C * S}, {C * S, S * S, -C * S, -S * S}, {-C * C, -C * S, C * C, C * S}, {-C * S, -S * S, C * S, S * S}});
	}
	Mat PlaneTrussElementStress(Mat E, double L, double theta, double u) {
		// % PlaneTrussElementStress This function returns the element stress % given the modulus of elasticity E, the % the length L, the angle theta(in % degrees), and the element nodal % displacement vector u.
		double x = theta * pi / 180;
		double C = cos(x);
		double S = sin(x);
		Mat y = E / L * Mat({-C, -S, C, S}) * u;
		return y;
	}
	Mat PlaneTrussInclinedSupport(Mat T, i64 i, double alpha) {
		// % PlaneTrussInclinedSupport This function calculates the % tranformation matrix T of the inclined % support at node i with angle of % inclination alpha(in degrees).
		double x = alpha * pi / 180;
		T(2 * i - 1, 2 * i - 1) = cos(x);
		T(2 * i - 1, 2 * i) = sin(x);
		T(2 * i, 2 * i - 1) = -sin(x);
		T(2 * i, 2 * i) = cos(x);
		return T;
	}


}// namespace PlaneTruss

using namespace PlaneTruss;
class TrussPoint {
public:
	double x, y;
	int64_t key = -1;
	TrussPoint(double _x, double _y) : x(_x), y(_y) {
	}
	TrussPoint(double _x, double _y, double _key) : x(_x), y(_y), key(_key) {
	}
};
class TrussEdge {
public:
	int idxa, idxb;
	vector<TrussPoint>::iterator a, b;
	// TrussPoint *a, *b;
	double length, theta;
	TrussEdge(int _a, int _b) : idxa(_a), idxb(_b) {
	}
};

class TrussSolveFramework {
	double E, A;
	vector<TrussPoint> vp;
	vector<TrussEdge> ve;
	Mat K;

public:
	TrussSolveFramework *initEA(double _e, double _a) {
		E = _e;
		A = _a;
		return this;
	}
	TrussSolveFramework *add(TrussEdge t) {
		if (t.idxa >= vp.size() && t.idxb >= vp.size() || t.idxa == t.idxb) {
			throw "Point-Index of Edge is Undefined!";
		}
		t.a = vp.begin() + t.idxa;
		t.b = vp.begin() + t.idxb;
		t.length = PlaneTrussElementLength(t.a->x, t.a->y, t.b->x, t.b->y);
		if (t.a->y == t.b->y) {
			t.theta = 0;
		} else if (t.a->x == t.b->x) {
			t.theta = pi / 2;
		} else {
			t.theta = atan(-(t.b->y - t.a->y) / (t.b->x - t.a->x)) * 180.0 / pi;
		}
		if (t.theta < 0) t.theta += 180;
		ve.push_back(t);
		return this;
	}
	TrussSolveFramework *assemble() {
		K = nc::zeros<double>(6, 6);
		for (auto &e: ve) {
			Mat t = PlaneTrussElementStiffness(E, A, e.length, e.theta);
			K = PlaneTrussAssemble(K, t, e.idxa + 1, e.idxb + 1);
		}
		return this;
	}
	TrussSolveFramework *add(TrussPoint t) {
		vp.push_back(t);
		return this;
	}
	void showK() {
		cout << K;
	}
	Mat calculateDis(Mat boundaryConditions) {
		Mat k = nc::zeros<double>(3, 3);
		[&]() {
			vector<int> v = {3, 5, 6};
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					k(i, j) = K(v[i] - 1, v[j] - 1);
				}
			}
		}();
		Mat f = boundaryConditions.transpose();
		return nc::linalg::inv(k).dot(f);
	}
};


int main() {
	TrussSolveFramework *tsf = new TrussSolveFramework();
	tsf->initEA(210e6, 1e-4)
	        ->add(TrussPoint(-2, 3))// point0
	        ->add(TrussPoint(2, 3)) // point1
	        ->add(TrussPoint(0, 0)) // point2
	        ->add(TrussEdge(0, 1))  // edge1
	        ->add(TrussEdge(0, 2))  // edge2
	        ->add(TrussEdge(1, 2))  // edge3
	        ->assemble();
	tsf->showK();

	auto solu = tsf->calculateDis({0, 5, -10});
	cout << solu;
}