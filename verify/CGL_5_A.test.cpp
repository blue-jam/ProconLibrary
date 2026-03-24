#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_5_A"
#define ERROR 1e-6
#include "misc/template.hpp"
#include "geometry/geometry.hpp"
#include "geometry/closestpair.hpp"

int main() {
    int n;
    cin >> n;
    vector<P> v(n);
    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        v[i] = P(x, y);
    }
    cout << fixed << setprecision(10) << closestPair(v) << endl;
    return 0;
}
