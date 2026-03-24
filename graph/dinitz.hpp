#pragma once
#include "graph/graph.hpp"
#include "misc/template.hpp"

template<typename W>
W blockingFlow(Graph<W>& g, vector<int>& l, int v, int t, W f) {
    if (v == t) return f;
    for (auto& edge : g[v]) {
        if (edge.weight > 0 && l[v] < l[edge.to]) {
            W d = blockingFlow(g, l, edge.to, t, min(f, edge.weight));
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
W dinitz(Graph<W>& g, int s, int t) {
    int n = g.size();
    W flow = 0;
    vector<int> l(n, -1);
    for (;;) {
        queue<int> Q;
        fill(ALL(l), -1);
        l[s] = 0;
        Q.push(s);
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            for (const auto& edge : g[v])
                if (edge.weight > 0 && l[edge.to] < 0) {
                    l[edge.to] = l[v] + 1;
                    Q.push(edge.to);
                }
        }
        if (l[t] < 0) return flow;
        W f;
        while ((f = blockingFlow(g, l, s, t, INF)) > 0) flow += f;
    }
}
