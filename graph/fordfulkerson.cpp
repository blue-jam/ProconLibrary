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
 * ### ソースコード
 *
 * @include fordfulkerson.cpp
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
Weight ford_dfs(Graph &g, int v, int t, Weight f, vector<int> &used){
    if(v == t) return f;
    used[v] = true;
    EACH(i, g[v]){
        if(!used[i -> to] && i -> weight > 0){
            Weight d = ford_dfs(g, i -> to, t, min(f, i -> weight), used);
            if(d > 0){
                i -> weight -= d;
                g[i -> to][i -> rev].weight += d;
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
Weight ford_fulkerson(Graph &g, int s, int t){
    vector<int> used(g.size());
    Weight flow = 0;
    for(;;){
        fill(ALL(used), 0);
        int f = ford_dfs(g, s, t, INF, used);
        if(f == 0) return flow;
        flow += f;
    }
    return flow;
}
