#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A"
#define ERROR 1e-8
#include "misc/template.hpp"
#include "geometry/geometry.hpp"

int main() {
    int x1, x2, y1, y2, q;
    cin >> x1 >> y1 >> x2 >> y2 >> q;
    Line L(P(x1, y1), P(x2, y2));
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        P p = projection(L, P(x, y));
        cout << fixed << setprecision(10);
        cout << real(p) << " " << imag(p) << endl;
    }
    return 0;
}
