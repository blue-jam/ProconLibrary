#include "../../geometry/geometry.cpp"
#include "../../geometry/crosspoint.cpp"
#include "../../geometry/polygon.cpp"
#include "../../geometry/convexcut.cpp"

int main(){
	int n;
	cin >> n;
	Polygon p;
	for(int i = 0; i < n; ++i){
		int x, y;
		cin >> x >> y;
		p.push_back(P(x,y));
	}
	int q;
	cin >> q;
	cout << setprecision(10) << fixed;
	for(int i = 0; i < q; ++i){
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		Polygon Q = convex_cut(p, Line(P(x1, y1), P(x2, y2)));
		cout << area(Q) << endl;
	}
	return 0;
}
