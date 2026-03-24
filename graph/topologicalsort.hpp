#pragma once
#include "graph/graph.hpp"
#include "misc/template.hpp"

template<typename W>
bool topologicalRecur(const Graph<W>& g, int v, vector<int>& order, vector<int>& color) {
    color[v] = 1;
    for (const auto& edge : g[v]) {
        if (color[edge.to] == 1) return false;
        if (color[edge.to] == 2) continue;
        topologicalRecur(g, edge.to, order, color);
    }
    order.push_back(v);
    color[v] = 2;
    return true;
}

template<typename W>
bool topologicalSort(const Graph<W>& g, vector<int>& order) {
    int n = g.size();
    vector<int> color(n);
    bool res = true;
    for (int i = 0; i < n; ++i)
        if (color[i] == 0)
            res = res && topologicalRecur(g, i, order, color);
    reverse(ALL(order));
    return res;
}
