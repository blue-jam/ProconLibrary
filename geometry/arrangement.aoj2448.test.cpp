#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2448"
#define ERROR 1e-6
#define EPS 1e-4
#include "misc/template.hpp"

#include "geometry/arrangement.hpp"
#include "geometry/crosspoint.hpp"
#include "geometry/geometry.hpp"
#include "geometry/polygon.hpp"
#include "graph/graph.hpp"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<P> ps(N);
    for (int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        ps[i] = P(x, y);
    }
    vector<Segment> vs;
    for (int i = 0; i < N - 1; ++i) vs.push_back(Segment(ps[i], ps[i + 1]));
    merge_segments(vs);
    Graph<double> g = segmentArrangement(vs, ps);
    vector<vector<int>> pols;
    pols = getPolygon(g, ps);
    vector<double> res;
    for (const auto& pol : pols) {
        Polygon p;
        for (const auto& idx : pol)
            p.push_back(ps[idx]);
        res.push_back(area(p));
    }
    double sum = 0;
    sort(ALL(res));
    for (const auto& r : res)
        sum += r;
    cout << fixed << setprecision(5) << sum << "\n";
    return 0;
}
