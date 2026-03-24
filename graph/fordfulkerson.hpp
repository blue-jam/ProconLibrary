#pragma once
#include "misc/template.hpp"
#include "graph/graph.hpp"

/**
 * @file
 * ## 最大流(Ford-Fulkerson)
 * ### 説明
 *
 * 最大フローを求めるアルゴリズム.ネットワークが大きい場合はほかのアルゴリズムを使用すること.
 *
 * ### 計算量
 *
 *   * O(V E C)
 *
 * ただし，Cは最大流量
 *
 *
 * ### 確認済み問題
 *
 *   * AOJ 2304
 *
 * ### 参考
 *
 *   * グラフ・ネットワーク・組み合わせ論
 *   * 蟻本
 */
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
/**
 * グラフの @a s から @a t への最短経路を計算する．
 * 事前に逆辺をweight=0で追加しておく．また，グラフは書き換えを行うので必要な場合はコピーを取っておくこと．
 */
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
