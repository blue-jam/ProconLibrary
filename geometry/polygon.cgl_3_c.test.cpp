#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C"
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
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        int c = contains(p, P(x, y));
        if (c == OUT) cout << 0 << "\n";
        else if (c == ON) cout << 1 << "\n";
        else cout << 2 << "\n";
    }
    return 0;
}
