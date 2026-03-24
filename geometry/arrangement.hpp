#pragma once
#include "geometry/crosspoint.hpp"
#include "geometry/geometry.hpp"
#include "geometry/polygon.hpp"
#include "graph/graph.hpp"
#include "misc/template.hpp"
bool merge_if_able(Segment& s, Segment t) {
    if (!parallel(s, t)) return false;
    bool f = true;
    for (const auto& si : s)
        for (const auto& tj : t)
            f = f && !near(si, tj);
    if (f) {
        if (abs(ccw(s[0], t[0], s[1])) == 1) return false;
        if (ccw(s[0], s[1], t[0]) == -2 || ccw(t[0], t[1], s[0]) == -2) return false;
    }
    s = Segment(min(s[0], t[0], lessX), max(s[1], t[1], lessX));
    return true;
}
// オーバーラップをマージする．（破壊的）
void merge_segments(vector<Segment>& ss) {
    for (int i = 0; i < ss.size(); ++i)
        if (lessX(ss[i][1], ss[i][0])) swap(ss[i][1], ss[i][0]);
    for (int i = 0; i < ss.size(); ++i)
        for (int j = i + 1; j < ss.size(); ++j)
            if (merge_if_able(ss[i], ss[j]))
                ss[j--] = ss.back(), ss.pop_back();
}
Graph<double> segmentArrangement(const vector<Segment>& ss, vector<P>& ps) {
    for (int i = 0; i < ss.size(); ++i) {
        ps.push_back(ss[i][0]);
        ps.push_back(ss[i][1]);
        for (int j = i + 1; j < ss.size(); ++j) {
            if (intersectSS(ss[i], ss[j]))
                ps.push_back(crosspointSS(ss[i], ss[j]));
        }
    }
    sort(ALL(ps), lessX);
    ps.erase(unique(ALL(ps), near), ps.end());
    Graph<double> g(ps.size());
    for (int i = 0; i < ss.size(); ++i) {
        vector<pair<double, int>> lst;
        for (int j = 0; j < ps.size(); ++j) {
            if (ccw(ss[i][0], ss[i][1], ps[j]) == 0)
                lst.push_back(make_pair(norm(ss[i][0] - ps[j]), j));
        }
        sort(ALL(lst));
        for (int j = 0; j + 1 < lst.size(); ++j) {
            int a = lst[j].second, b = lst[j + 1].second;
            addUndirectedEdge(g, a, b, abs(ps[a] - ps[b]));
        }
    }
    return g;
}
bool walkCW(const Graph<double>& g, int v, int u, vector<int>& lst, const vector<P>& ps, vector<vector<int>>& used, vector<vector<int>>& res) {
    for (int j = 0; j + 1 < lst.size(); ++j)
        if (lst[j] == u && lst[j + 1] == v) {
            Polygon pol;
            for (int i = j; i < lst.size() - 1; ++i) pol.push_back(ps[lst[i]]);
            double s = area(pol);
            if (s > eps) {
                vector<int> v;
                for (int i = j; i < lst.size() - 1; ++i) {
                    used[lst[i]][lst[(i + 1) % lst.size()]] = true;
                    v.push_back(lst[i]);
                }
                res.push_back(v);
                return true;
            } else {
                return false;
            }
        }
    vector<pair<double, int>> es;
    P e = (ps[v] - ps[u]) / abs(ps[v] - ps[u]);
    P n = e * P(0, 1);
    for (const auto& adj : g[v])
        if (adj.to != u && !used[v][adj.to]) {
            es.push_back(make_pair(atan2(dot(n, ps[adj.to] - ps[v]), dot(e, ps[adj.to] - ps[v])), adj.to));
        }
    sort(ALL(es));
    reverse(ALL(es));
    lst.push_back(v);
    for (const auto& ei : es) {
        bool r = walkCW(g, ei.second, v, lst, ps, used, res);
        if (r) {
            lst.pop_back();
            return r;
        }
    }
    lst.pop_back();
    return false;
}
// 線分アレンジメントによってできる閉領域を求める
vector<vector<int>> getPolygon(const Graph<double>& g, const vector<P>& ps) {
    vector<vector<int>> res;
    int n = g.size();
    vector<vector<int>> used(n, vector<int>(n));

    res.clear();
    for (int i = 0; i < n; ++i)
        for (const auto& edge : g[i])
            if (!used[i][edge.to]) {
                vector<int> v;
                walkCW(g, edge.to, i, v, ps, used, res);
                used[i][edge.to] = true;
            }
    return res;
}
