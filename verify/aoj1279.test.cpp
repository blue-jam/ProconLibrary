#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1279"
#include "misc/template.hpp"

const double INF = 1e+10;

#include "graph/graph.hpp"
#include "graph/dijkstra.hpp"
#include "geometry/geometry.hpp"
#include "geometry/crosspoint.hpp"
#include "geometry/polygon.hpp"
#include "geometry/arrangement.hpp"

int main() {
    for(;;) {
        int n;
        cin >> n;
        if(n == 0) return 0;
        P s, g;
        vector<Segment> v;
        int x, y;
        cin >> x >> y;
        s = P(x, y);
        cin >> x >> y;
        g = P(x, y);
        for(int i = 0; i < n; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            v.push_back(Segment(P(x1, y1), P(x2, y2)));
        }
        vector<Segment> road, signs;
        for(int i = 0; i < n; ++i) {
            int f = 0;
            for(int j = 0; j < n; ++j)
                if(i != j)
                    for(int k = 0; k < 2; ++k) {
                        if(ccw(v[j][0], v[j][1], v[i][k]) == 0)
                            f |= 1 << k;
                    }
            if(f == 3) road.push_back(v[i]);
            else signs.push_back(v[i]);
        }
        vector<P> ps;
        Graph<double> graph = segmentArrangement(road, ps);
        int si, gi;
        for(int i = 0; i < (int)ps.size(); ++i)
            if(abs(ps[i] - s) < eps) si = i;
        for(int i = 0; i < (int)ps.size(); ++i)
            if(abs(ps[i] - g) < eps) gi = i;

        EACH(i, signs) {
            Segment ss = *i;
            EACH(j, graph)
            EACH(k, *j) {
                int a = k->from, b = k->to;
                bool f = true;
                double d = 1;
                if(ccw(ps[a], ps[b], ss[0]) == 0) {
                    d = dot(ss[0] - ss[1], ps[b] - ps[a]);
                } else if(ccw(ps[a], ps[b], ss[1]) == 0) {
                    d = dot(ss[1] - ss[0], ps[b] - ps[a]);
                }
                if(d < eps) {
                    k->weight = INF;
                }
            }
        }

        vector<int> prev(ps.size(), -1);
        vector<double> dist(ps.size());
        dijkstra(graph, si, dist, prev);
        if(dist[gi] == INF) {
            cout << -1 << endl;
        } else {
            vector<int> path = buildPath(prev, gi);
            EACH(i, path) {
                cout << (int)ps[*i].real() << " " << (int)ps[*i].imag() << endl;
            }
            cout << 0 << endl;
        }
    }
}
