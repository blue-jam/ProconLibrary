#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_A"
#include "geometry/geometry.hpp"
#include "geometry/tangent.hpp"
#include "misc/template.hpp"

int main() {
    double x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1;
    Circle c1(x1, y1, r1);
    cin >> x2 >> y2 >> r2;
    Circle c2(x2, y2, r2);
    cout << innertangent(c1, c2).size() + outertangent(c1, c2).size() << endl;
    return 0;
}
