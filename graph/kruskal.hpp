#pragma once
#include "datastructure/unionfind.hpp"
#include "graph/graph.hpp"
#include "misc/template.hpp"

template<typename W>
pair<W, Edges<W>> kruskal_e(Edges<W>& edges, int n) {
    sort(ALL(edges));
    reverse(ALL(edges)); // a < b <-> a.weight > b.weight
    int sz = edges.size();

    UnionFind uf(n);
    W total = 0;
    Edges<W> F;
    for (int i = 0; i < sz; ++i) {
        if (uf.unite(edges[i].from, edges[i].to)) {
            total = total + edges[i].weight;
            F.push_back(edges[i]);
        }
    }
    return make_pair(total, F);
}
template<typename W>
pair<W, Edges<W>> kruskal_g(const Graph<W>& g) {
    int n = g.size();
    vector<Edge<W>> edges;
    for (int i = 0; i < n; ++i) edges.insert(edges.end(), ALL(g[i]));
    return kruskal_e(edges, n);
}
