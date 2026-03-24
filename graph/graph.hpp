#pragma once
#include "misc/template.hpp"

template<typename W>
struct Edge {
    int from, to;
    W weight;
    int rev; // 無向グラフの対の辺
    Edge(int from, int to, W weight) : from(from), to(to), weight(weight) {}
    Edge(int from, int to, W weight, int rev) : from(from), to(to), weight(weight), rev(rev) {}
    bool operator<(const Edge& b) const {
        if (weight != b.weight) return weight > b.weight;
        if (from != b.from) return from > b.from;
        return to > b.to;
    }
};
template<typename W = ll>
using Edges = vector<Edge<W>>;
template<typename W = ll>
using Graph = vector<Edges<W>>;
template<typename W = ll>
using Array = vector<W>;
template<typename W = ll>
using Matrix = vector<Array<W>>;

template<typename W>
void addFlowEdge(Graph<W>& g, int a, int b, type_identity_t<W> c) {
    g[a].push_back(Edge<W>(a, b, c, g[b].size()));
    g[b].push_back(Edge<W>(b, a, W(0), g[a].size() - 1));
}
template<typename W>
void addUndirectedEdge(Graph<W>& g, int a, int b, type_identity_t<W> c) {
    g[a].push_back(Edge<W>(a, b, c, g[b].size()));
    g[b].push_back(Edge<W>(b, a, c, g[a].size() - 1));
}

template<typename T>
struct edge {
    ll from, to;
    T weight;

    edge() : from(-1), to(-1) {}

    edge(ll from, ll to, T weight) : from(from), to(to), weight(weight) {}
};

template<typename T>
struct graph {
    ll n;
    vector<vector<edge<T>>> edges;

    explicit graph(ll n) : n(n), edges(n) {}

    void add(ll from, ll to, T weight) {
        edges[from].emplace_back(from, to, weight);
    }
};
