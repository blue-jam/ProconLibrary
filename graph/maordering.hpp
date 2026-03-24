#pragma once
#include "datastructure/unionfind.hpp"
#include "graph/graph.hpp"
#include "misc/template.hpp"

template<typename W>
W maordering(const Graph<W>& g1, vector<int>& w) {
    int n = g1.size();
    W cut = INF;
    UnionFind uf(n);
    priority_queue<Edge<W>> Q;
    vector<int> used;
    vector<W> d;
    Graph<W> g = g1;
    w.clear();
    for (int k = 0; k < n - 1; ++k) {
        int s = uf.find(0), t = -1;
        Q.push(Edge<W>(s, s, W(0)));
        d.assign(n, 0);
        used.assign(n, 0);
        while (!Q.empty()) {
            Edge<W> e = Q.top();
            Q.pop();
            int v = uf.find(e.to);
            if (used[v]) continue;
            used[v] = true;
            s = uf.find(e.from);
            t = v;
            for (const auto& adj : g[e.to]) {
                int u = uf.find(adj.to);
                if (!used[u]) {
                    d[u] -= adj.weight;
                    Q.push(Edge<W>(v, u, d[u]));
                }
            }
        }
        if (cut > -d[t]) {
            cut = -d[t];
            w.clear();
            for (int i = 0; i < n; ++i)
                if (uf.same(t, i)) w.push_back(i);
        }
        uf.unite(s, t);
        if (uf.find(s) != s) swap(s, t);
        g[s].insert(g[s].end(), ALL(g[t]));
    }
    return cut;
}
