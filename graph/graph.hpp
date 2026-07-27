#pragma once
#include "misc/template.hpp"

template<typename W>
struct Edge {
    int from, to;
    W weight;
    int rev; // 残余グラフの逆辺
    int id;
    Edge(int from, int to, W weight) : from(from), to(to), weight(weight), rev(-1), id(-1) {}
    Edge(int from, int to, W weight, int rev) : from(from), to(to), weight(weight), rev(rev), id(-1) {}
    Edge(int from, int to, W weight, int rev, int id) : from(from), to(to), weight(weight), rev(rev), id(id) {}
    bool operator<(const Edge& b) const {
        if (weight != b.weight) return weight < b.weight;
        if (from != b.from) return from < b.from;
        if (to != b.to) return to < b.to;
        return id < b.id;
    }
    bool operator>(const Edge& b) const { return b < *this; }
};
template<typename W = ll>
using Edges = vector<Edge<W>>;
enum class IndexBase {
    Zero = 0,
    One = 1,
};
template<typename W = ll>
struct Graph {
    int n;
    vector<Edges<W>> edges;
    Edges<W> edge_list;

    explicit Graph(int n = 0) : n(n), edges(n) {}

    int size() const { return n; }
    bool empty() const { return n == 0; }

    auto begin() { return edges.begin(); }
    auto end() { return edges.end(); }
    auto begin() const { return edges.begin(); }
    auto end() const { return edges.end(); }

    Edges<W>& operator[](int v) { return edges[v]; }
    const Edges<W>& operator[](int v) const { return edges[v]; }

    int add_directed(int from, int to, type_identity_t<W> weight = W(1)) {
        int id = edge_list.size();
        Edge<W> e(from, to, weight, -1, id);
        edges[from].push_back(e);
        edge_list.push_back(e);
        return id;
    }

    int add_undirected(int a, int b, type_identity_t<W> weight = W(1)) {
        int id = edge_list.size();
        int ai = edges[a].size();
        int bi = edges[b].size();
        edges[a].push_back(Edge<W>(a, b, weight, bi, id));
        edges[b].push_back(Edge<W>(b, a, weight, ai, id));
        edge_list.push_back(Edge<W>(a, b, weight, -1, id));
        return id;
    }

    const Edges<W>& all_edges() const { return edge_list; }

    template<typename A, typename B>
    static Graph directed(int n, const A& a, const B& b, IndexBase base = IndexBase::One) {
        assert(a.size() == b.size());
        Graph g(n);
        int shift = static_cast<int>(base);
        for (int i = 0; i < (int)a.size(); ++i)
            g.add_directed(a[i] - shift, b[i] - shift);
        return g;
    }

    template<typename A, typename B>
    static Graph undirected(int n, const A& a, const B& b, IndexBase base = IndexBase::One) {
        assert(a.size() == b.size());
        Graph g(n);
        int shift = static_cast<int>(base);
        for (int i = 0; i < (int)a.size(); ++i)
            g.add_undirected(a[i] - shift, b[i] - shift);
        return g;
    }

    template<typename A, typename B, typename C>
        requires(!same_as<remove_cvref_t<C>, IndexBase>)
    static Graph directed(int n, const A& a, const B& b, const C& w, IndexBase base = IndexBase::One) {
        assert(a.size() == b.size());
        assert(a.size() == w.size());
        Graph g(n);
        int shift = static_cast<int>(base);
        for (int i = 0; i < (int)a.size(); ++i)
            g.add_directed(a[i] - shift, b[i] - shift, w[i]);
        return g;
    }

    template<typename A, typename B, typename C>
        requires(!same_as<remove_cvref_t<C>, IndexBase>)
    static Graph undirected(int n, const A& a, const B& b, const C& w, IndexBase base = IndexBase::One) {
        assert(a.size() == b.size());
        assert(a.size() == w.size());
        Graph g(n);
        int shift = static_cast<int>(base);
        for (int i = 0; i < (int)a.size(); ++i)
            g.add_undirected(a[i] - shift, b[i] - shift, w[i]);
        return g;
    }
};
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
    g.add_undirected(a, b, c);
}
