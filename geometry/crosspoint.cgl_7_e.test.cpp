#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E"
#define ERROR 1e-8
#include "geometry/crosspoint.hpp"
#include "geometry/geometry.hpp"
#include "misc/template.hpp"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<Circle> v;
    for (int i = 0; i < 2; ++i) {
        int x, y, r;
        cin >> x >> y >> r;
        v.push_back(Circle(x, y, r));
    }
    pair<P, P> ps = crosspointCC(v[0], v[1]);
    if (!lessX(ps.first, ps.second)) swap(ps.first, ps.second);
    cout << fixed << setprecision(10);
    cout << real(ps.first) << " " << imag(ps.first) << " ";
    cout << real(ps.second) << " " << imag(ps.second) << "\n";
    return 0;
}
