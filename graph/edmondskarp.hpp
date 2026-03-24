#pragma once
#include "graph/graph.hpp"
#include "misc/template.hpp"

template<typename W>
W edmonds_karp(Graph<W>& g, int s, int t) {
    W flow = 0;
    int n = g.size();
    vector<int> prev(n);
    vector<int> edge(n);
    for (;;) {
        queue<int> Q;
        fill(ALL(prev), -1);
        prev[s] = s;
        Q.push(s);
        while (!Q.empty() && prev[t] < 0) {
            int v = Q.front();
            Q.pop();
            for (int idx = 0; idx < (int)g[v].size(); ++idx)
                if (g[v][idx].weight > 0 && prev[g[v][idx].to] < 0) {
                    prev[g[v][idx].to] = v;
                    edge[g[v][idx].to] = idx;
                    Q.push(g[v][idx].to);
                }
        }
        if (prev[t] < 0) return flow;
        W f = INF;
        for (int u = t; u != prev[u]; u = prev[u])
            f = min(f, g[prev[u]][edge[u]].weight);
        for (int u = t; u != prev[u]; u = prev[u]) {
            int v = prev[u], e = edge[u], r = g[v][edge[u]].rev;
            g[v][e].weight -= f;
            g[u][r].weight += f;
        }
        flow += f;
    }
}
