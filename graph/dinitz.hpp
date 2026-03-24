#pragma once
#include "misc/template.hpp"
#include "graph/graph.hpp"

/**
 * @file
 * ## 最大流(Dinitz)
 *
 * 多くの文献で"Dinic"として紹介されているが，原論文を英訳するときに著者名がそう訳されたためそちらが広まっただけで，その後の自著では"Dinitz"と表記されている．
 *
 * ネットワークをBFSで層別ネットワークに分け，その中での極大フローを探し，増加させることを繰り返し最大流量を求める．
 *
 * ### 計算量
 *
 *   * O(V^2 E)
 *
 *
 * ### 確認済み問題
 *
 *   * AOJ 2304
 *
 * ### 参考
 *
 *   * グラフ・ネットワーク・組合せ論
 */
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
/**
 *Ford-Fulkersonと同様にネットワークとソース，シンクの頂点を渡す．グラフを構築するときに逆辺を付け忘れないように．
 */
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
