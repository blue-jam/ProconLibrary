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
void dijkstra(const Graph &g, int s, vector<Weight> &dist, vector<int> &prev){
    int n = g.size();
    dist.assign(n, INF);
    dist[s] = 0;
    prev.assign(n, -1);
    priority_queue<Edge> Q;     // a < b <-> a.weight > b.weight
    Q.push(Edge(-2, s, 0));
    while(!Q.empty()){
        Edge e = Q.top(); Q.pop();
        if(prev[e.to] != -1) continue;
        prev[e.to] = e.from;
        EACH(i, g[e.to]){
        //for(Edges::const_iterator i=g[e.to].begin(); i!=g[e.to].end(); ++i){    //マクロが使えないとき
            if(dist[i -> to] > dist[i -> from] + i -> weight){
                dist[i -> to] = dist[i -> from] + i -> weight;
                Q.push(Edge(i -> from, i -> to, dist[i -> to]));
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
vector<int> buildPath(const vector<int> &prev, int t){
    vector<int> path;
    for(int v = t; v >= 0; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}
