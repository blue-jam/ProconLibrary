/**
 * @file
 *
 * ## 最大流(Edmond-Karp)
 *
 * Ford-Fulkersonにおける増加パスの探索を幅優先探索によって行うアルゴリズム．
 *
 * ### 計算量
 *
 *   * O(V E^2)
 *
 * ### ソースコード
 *
 * @include edmondskarp.cpp
 *
 * ### 確認済み問題
 *
 *   * AOJ 2304
 */
Weight edmonds_karp(Graph &g, int s, int t){
    Weight flow = 0;
    int n = g.size();
    vector<int> prev(n);
    vector<int> edge(n);
    for(;;){
        queue<int> Q;
        fill(ALL(prev), -1);
        prev[s] = s;
        Q.push(s);
        while(!Q.empty() && prev[t] < 0){
            int v = Q.front(); Q.pop();
            EACH(i, g[v])if(i -> weight > 0 && prev[i -> to] < 0){
                prev[i -> to] = v;
                edge[i -> to] = i - g[v].begin();
                Q.push(i -> to);
            }
        }
        if(prev[t] < 0) return flow;
        Weight f = INF;
        for(int u = t; u != prev[u]; u = prev[u])
            f = min(f, g[prev[u]][edge[u]].weight);
        for(int u = t; u != prev[u]; u = prev[u]){
            int v = prev[u], e = edge[u], r = g[v][edge[u]].rev;
            g[v][e].weight -= f;
            g[u][r].weight += f;
        }
        flow += f;
    }
}
