#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A"
#include "geometry/convexhull.hpp"
#include "geometry/geometry.hpp"
#include "misc/template.hpp"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<P> v(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        v[i] = P(x, y);
    }
    Polygon p = convex_hull(v, 0);
    int m = p.size();
    int idx = 0;
    for (int i = 0; i < m; ++i) {
        if (lessY(p[i], p[idx]))
            idx = i;
    }
    cout << m << "\n";
    for (int i = 0; i < m; ++i) {
        cout << (int)p[(idx + i) % m].real() << " " << (int)p[(idx + i) % m].imag() << "\n";
    }
    return 0;
}
