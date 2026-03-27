#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D"
#define ERROR 1e-8
#include "geometry/crosspoint.hpp"
#include "geometry/geometry.hpp"
#include "misc/template.hpp"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        vector<Segment> L;
        for (int j = 0; j < 2; ++j) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            L.push_back(Segment(P(a, b), P(c, d)));
        }
        cout << fixed << setprecision(11);
        cout << distanceSS(L[0], L[1]) << "\n";
    }
    return 0;
}
