#pragma once
#include "graph/graph.hpp"
#include "misc/template.hpp"

template<typename W>
void sccRecur(const Graph<W>& g, int v, vector<vector<int>>& comp,
              vector<int>& num, vector<bool>& open,
              stack<int>& oNodes, stack<int>& oReps, int& cnt) {
    if (num[v] != 0) {
        if (open[v])
            while (num[oReps.top()] > num[v]) oReps.pop();
        return;
    }
    num[v] = ++cnt;
    oReps.push(v);
    oNodes.push(v);
    open[v] = true;
    for (const auto& edge : g[v])
        sccRecur(g, edge.to, comp, num, open, oNodes, oReps, cnt);
    if (v == oReps.top()) {
        int w;
        oReps.pop();
        comp.push_back(vector<int>());
        do {
            w = oNodes.top();
            oNodes.pop();
            open[w] = false;
            comp.back().push_back(w);
        } while (v != w);
    }
}

template<typename W>
void getSCC(const Graph<W>& g, vector<vector<int>>& comp) {
    int n = g.size();
    vector<int> num(n);
    vector<bool> open(n);
    stack<int> oReps, oNodes;
    int cnt = 0;
    for (int i = 0; i < n; ++i)
        if (num[i] == 0)
            sccRecur(g, i, comp, num, open, oNodes, oReps, cnt);
}
