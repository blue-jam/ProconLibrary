#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_G"
#define ERROR 1e-8
#include "misc/template.hpp"
#include "geometry/geometry.hpp"
#include "geometry/tangent.hpp"

int main() {
    double x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1;
    Circle c1(x1, y1, r1);
    cin >> x2 >> y2 >> r2;
    Circle c2(x2, y2, r2);
    auto a = innertangent(c1, c2), b = outertangent(c1, c2);
    vector<P> v;
    EACH(i, a)
    v.push_back((*i)[0]);
    EACH(i, b)
    v.push_back((*i)[0]);
    sort(ALL(v), lessX);
    cout << fixed << setprecision(10);
    EACH(i, v) {
        cout << i->real() << " " << i->imag() << endl;
    }
    return 0;
}
