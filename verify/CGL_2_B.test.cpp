#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B"
#include "misc/template.hpp"
#include "geometry/geometry.hpp"
#include "geometry/crosspoint.hpp"

int main() {
    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        vector<Segment> L;
        for(int j = 0; j < 2; ++j) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            L.push_back(Segment(P(a, b), P(c, d)));
        }
        cout << (intersectSS(L[0], L[1]) ? 1 : 0) << endl;
    }
    return 0;
}
