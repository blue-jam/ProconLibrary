#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B"
#include "geometry/polygon.hpp"
#include "geometry/geometry.hpp"
#include "misc/template.hpp"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    Polygon p(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        p[i] = P(x, y);
    }
    cout << (convex(p) ? 1 : 0) << "\n";
    return 0;
}
