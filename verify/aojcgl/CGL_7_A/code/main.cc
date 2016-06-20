#include "misc/template.cpp"
#include "geometry/geometry.cpp"
#include "geometry/tangent.cpp"

int main(){
	double x1, y1, r1, x2, y2, r2;
	cin >> x1 >> y1 >> r1;
	Circle c1(x1, y1, r1);
	cin >> x2 >> y2 >> r2;
	Circle c2(x2, y2, r2);
	cout << innertangent(c1, c2).size() + outertangent(c1, c2).size() << endl;
	return 0;
}
