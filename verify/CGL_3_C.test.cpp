#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C"
#include "misc/template.hpp"
#include "geometry/geometry.hpp"
#include "geometry/polygon.hpp"

int main() {
    int n;
    cin >> n;
    Polygon p(n);
    for(int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        p[i] = P(x, y);
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        int c = contains(p, P(x, y));
        if(c == OUT) cout << 0 << endl;
        else if(c == ON) cout << 1 << endl;
        else cout << 2 << endl;
    }
    return 0;
}
