#pragma once
#include "graph/graph.hpp"
#include "misc/template.hpp"

/**
 * @file
 *
 * ## 単一始点最短路(Dijkstra)
 * ### 説明
 *
 * 始点の距離を0とし，近いところから順番に距離を確定していく．負の辺が存在しないグラフのある頂点からすべての頂点に対しての最短距離を求めることができる．
 *
 * 経路復元では，目的地から直前の頂点をたどることで，経路の逆順を復元している．
 *
 *
 * ### 確認済み問題
 *
 *   * POJ 3268
 *   * 経路復元は行っていない
 *
 * ### 参考
 *
 *   * [Spaghetti Source](http://www.prefield.com/algorithm/graph/dijkstra.html) 変数名以外はそのまま
 *
 */

/**
 * グラフ @a g の @a s を始点とする最短経路を @f$O(E \log V)@f$ 時間で計算する．
 * 経路の復元には，接点の直前の位置を記録した配列と目的の頂点を渡す．
 *
 * @param g グラフ
 * @param s 始点
 * @param dist 最短距離を格納．頂点数と同じ要素数．
 * @param prev 直前の頂点を格納．頂点数と同じ要素数．
 */
template<typename W>
void dijkstra(const Graph<W>& g, int s, vector<W>& dist, vector<int>& prev) {
    int n = g.size();
    dist.assign(n, INF);
    dist[s] = 0;
    prev.assign(n, -1);
    priority_queue<Edge<W>> Q; // a < b <-> a.weight > b.weight
    Q.push(Edge<W>(-2, s, 0));
    while (!Q.empty()) {
        Edge<W> e = Q.top();
        Q.pop();
        if (prev[e.to] != -1) continue;
        prev[e.to] = e.from;
        for (const auto& edge : g[e.to]) {
            if (dist[edge.to] > dist[edge.from] + edge.weight) {
                dist[edge.to] = dist[edge.from] + edge.weight;
                Q.push(Edge<W>(edge.from, edge.to, dist[edge.to]));
            }
        }
    }
}

/**
 * 頂点 @a t への最短経路を復元する．
 *
 * @param prev 直前の頂点を格納した配列
 * @param t 経路を復元したいときの目的地
 */
vector<int> buildPath(const vector<int>& prev, int t) {
    vector<int> path;
    for (int v = t; v >= 0; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}
