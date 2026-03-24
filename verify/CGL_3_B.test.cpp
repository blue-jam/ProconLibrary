#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B"
#include "geometry/geometry.hpp"
#include "geometry/polygon.hpp"
#include "misc/template.hpp"

int main() {
    int n;
    cin >> n;
    Polygon p(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        p[i] = P(x, y);
    }
    cout << (convex(p) ? 1 : 0) << endl;
    return 0;
}
