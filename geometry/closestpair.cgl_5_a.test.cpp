#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_5_A"
#define ERROR 1e-6
#include "geometry/closestpair.hpp"
#include "geometry/geometry.hpp"
#include "misc/template.hpp"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<P> v(n);
    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        v[i] = P(x, y);
    }
    cout << fixed << setprecision(10) << closestPair(v) << "\n";
    return 0;
}
