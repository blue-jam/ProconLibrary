#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_G"
#define ERROR 1e-8
#include "geometry/tangent.hpp"
#include "geometry/geometry.hpp"
#include "misc/template.hpp"

int main() {
    double x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1;
    Circle c1(x1, y1, r1);
    cin >> x2 >> y2 >> r2;
    Circle c2(x2, y2, r2);
    auto a = innertangent(c1, c2), b = outertangent(c1, c2);
    vector<P> v;
    for (const auto& li : a)
        v.push_back(li[0]);
    for (const auto& li : b)
        v.push_back(li[0]);
    sort(ALL(v), lessX);
    cout << fixed << setprecision(10);
    for (const auto& p : v) {
        cout << p.real() << " " << p.imag() << endl;
    }
    return 0;
}
