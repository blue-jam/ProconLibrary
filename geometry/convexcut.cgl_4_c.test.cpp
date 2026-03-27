#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C"
#define ERROR 1e-6
#include "geometry/convexcut.hpp"
#include "geometry/crosspoint.hpp"
#include "geometry/geometry.hpp"
#include "geometry/polygon.hpp"
#include "misc/template.hpp"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    Polygon p;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        p.push_back(P(x, y));
    }
    int q;
    cin >> q;
    cout << setprecision(10) << fixed;
    for (int i = 0; i < q; ++i) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        Polygon Q = convex_cut(p, Line(P(x1, y1), P(x2, y2)));
        cout << area(Q) << "\n";
    }
    return 0;
}
