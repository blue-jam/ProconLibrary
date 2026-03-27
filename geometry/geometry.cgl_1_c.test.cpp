#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C"
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
        int c = ccw(L[0], L[1], P(x, y));
        if (c == 0) cout << "ON_SEGMENT" << "\n";
        else if (c == 2) cout << "ONLINE_BACK" << "\n";
        else if (c == -2) cout << "ONLINE_FRONT" << "\n";
        else if (c == 1) cout << "COUNTER_CLOCKWISE" << "\n";
        else cout << "CLOCKWISE" << "\n";
    }
    return 0;
}
