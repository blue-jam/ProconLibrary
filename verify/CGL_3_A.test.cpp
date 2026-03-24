#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A"
#include "misc/template.hpp"
#include "geometry/geometry.hpp"
#include "geometry/polygon.hpp"

int main() {
    int n;
    cin >> n;
    Polygon p(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        p[i] = P(x, y);
    }
    cout << fixed << setprecision(1);
    cout << area(p) << endl;
    return 0;
}
