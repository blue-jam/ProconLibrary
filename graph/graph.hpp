#pragma once
/**
 * @file
 * ### グラフの要素
 * グラフは各頂点から出て行く辺をリストとして保持する隣接リスト表現と各頂点間に辺が存在する情報を記録する隣接行列表現がある．
 * それぞれ利点があるので状況に応じて使い分けること．
 *
 * <dl>
 *   <dt>隣接リスト</dt><dd>頂点を基準に考えればいいときに有向．重複辺も扱える．</dd>
 *   <dt>隣接行列</dt><dd>@f$O(E)@f$ が @f$O(V^2)@f$ になる．密グラフや，頂点数が少ないグラフについて効率よく扱える．重複辺を扱いにくい．</dd>
 * </dl>
 *
 * ### ソースコード
 *
 * @include graph.hpp
 *
 * Edgeのless演算子のオーバーロードで，大きいほうが左辺のときにtrueを返すようにしている．
 * これはpriority_queueで，weightの小さいほうを先に取り出すときの工夫である．
 * 気に入らない場合は，greater演算子をオーバーロードし，priority_queueを以下のように宣言する．
 *
 * @code
 * priority_queue<Edge>, vector<Edge>, greater<Edge>> Q;
 * @endcode
 */
#include "misc/template.hpp"

template<typename W>
struct Edge{
    int from, to;
    W weight;
    int rev;     // 無向グラフの対の辺
    Edge(int from, int to, W weight) :
        from(from), to(to), weight(weight) { }
    Edge(int from, int to, W weight, int rev) :
        from(from), to(to), weight(weight), rev(rev){ }
    bool operator < (const Edge &b) const {
        if(weight != b.weight) return weight > b.weight;
        if(from != b.from) return from > b.from;
        return  to > b.to;
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
void addFlowEdge(Graph<W> &g, int a, int b, type_identity_t<W> c){
    g[a].push_back(Edge<W>(a, b, c, g[b].size()));
    g[b].push_back(Edge<W>(b, a, W(0), g[a].size() - 1));
}
template<typename W>
void addUndirectedEdge(Graph<W> &g, int a, int b, type_identity_t<W> c){
    g[a].push_back(Edge<W>(a, b, c, g[b].size()));
    g[b].push_back(Edge<W>(b, a, c, g[a].size() - 1));
}

template<typename T>
struct edge {
    ll from, to;
    T weight;

    edge() : from(-1), to(-1) {}

    edge(ll from, ll to, T weight) :
            from(from), to(to), weight(weight) {}
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

