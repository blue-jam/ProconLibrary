#pragma once
#include "graph/graph.hpp"
#include "misc/template.hpp"

template<typename W>
W ford_dfs(Graph<W>& g, int v, int t, W f, vector<int>& used) {
    if (v == t) return f;
    used[v] = true;
    for (auto& edge : g[v]) {
        if (!used[edge.to] && edge.weight > 0) {
            W d = ford_dfs(g, edge.to, t, min(f, edge.weight), used);
            if (d > 0) {
                edge.weight -= d;
                g[edge.to][edge.rev].weight += d;
                return d;
            }
        }
    }
    return 0;
}
template<typename W>
W ford_fulkerson(Graph<W>& g, int s, int t) {
    vector<int> used(g.size());
    W flow = 0;
    for (;;) {
        fill(ALL(used), 0);
        int f = ford_dfs(g, s, t, INF, used);
        if (f == 0) return flow;
        flow += f;
    }
    return flow;
}
