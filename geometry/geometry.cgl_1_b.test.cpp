#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B"
#define ERROR 1e-8
#include "geometry/geometry.hpp"
#include "misc/template.hpp"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int x1, x2, y1, y2, q;
    cin >> x1 >> y1 >> x2 >> y2 >> q;
    Line L(P(x1, y1), P(x2, y2));
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        P p = reflection(L, P(x, y));
        cout << fixed << setprecision(10);
        cout << real(p) << " " << imag(p) << "\n";
    }
    return 0;
}
