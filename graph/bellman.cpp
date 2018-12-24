/**
 * @file
 * ## 単一始点最短路問題(Bellman-Ford)
 *
 * ### 説明
 *
 * Bellman-Fordのアルゴリズムは，始点を距離0，そのほかを距離INFに設定したうえで，距離が求められている頂点から辺を伸ばし，
 * 既存の距離よりも短ければ距離を更新するという操作を繰り返し実行することで最短路を求めるアルゴリズムである．
 * Dijkstraが負の辺を扱えないのに対し，こちらは負の辺を扱える．
 *
 * また，負の閉路が存在しなければそれぞれの頂点を最大でも1回ずつしか通らないので，高々V-1回のループで終わることがわかっている．
 * V回目のループで更新が起こった場合は負の閉路があることがわかるので，
 * 負の閉路の検出にも利用される．\
 * しかし，負の閉路があったからといってそれが目的の頂点への最短路に影響を与えるとは限らないので注意が必要である．(例：AOJ1169)
 *
 * ### 計算量
 *
 *   * O(VE)
 *
 * ### ソースコード
 *
 * @include bellman.cpp
 *
 * ### 確認済み問題
 *
 *   * POJ 3169(Layout)
 *
 * 最短路の計算のみしか行っていない．経路の復元と，負の閉路の検出は今後．
 *
 * ### 参考
 *
 *   * [Spaghetti Source](http://www.prefield.com/algorithm/graph/bellman_ford.html)
 *   * プログラミングコンテストチャレンジブック(p95-p96)
 */
/**
 * bellmanFordでは最短路を計算する．
 *
 * bellmanFordにおいて，distに-INFと記録された頂点以外にも，負の閉路の影響を受ける頂点があることがある．-INFと記録された頂点から到達できるすべての頂点は負の閉路の影響を受ける．（要確認）
 *
 * @param g 最短路を求めたいグラフ
 * @param s 始点
 * @param dist 距離を記録する．経路がない場合はINF，そこへ到達するまでに負の閉路が含まれることがわかっていれば-1
 * @param prev 経路復元用の1つ前の位置を示す配列
 * @return 負の閉路が含まれているか
 */
bool bellmanFord(const Graph &g, int s, vector<Weight> &dist, vector<int> &prev){
    int n = g.size();
    bool nagativeRoop = false;
    dist.assign(n, INF); dist[s] = 0;
    prev.assign(n, -1);
    for(int k = 0; k < n; ++k){
        for(int v = 0; v < n; ++v){
            EACH(i, g[v]){
            //for(Edges::const_iterator i=g[v].begin(); i != g[v].end(); ++i){
                if(dist[i -> from] != INF && dist[i -> to] > dist[i -> from] + i -> weight){
                    dist[i -> to] = dist[i -> from] + i-> weight;
                    prev[i -> to] = i -> from;
                    if(k == n - 1){
                        dist[i -> to] = -INF;
                        nagativeRoop = true;
                    }
                }
            }
        }
    }
    return nagativeRoop;
}
/**
 * Graphの全域において負の閉路があるか検出する．
 *
 * @param g 最短路を求めたいグラフ
 * @return 負の閉路が含まれているか
 */
bool findNegativeRoop(const Graph &g){
    int n = g.size();
    vector<Weight> dist(n, 0);
    for(int k = 0; k < n; ++k){
        for(int v = 0; v < n; ++v){
            EACH(i, g[v]){
            //for(Edges::const_iterator i=g[v].begin(); i != g[v].end(); ++i){
                if(dist[i -> to] > dist[i -> from] + i -> weight){
                    dist[i -> to] = dist[i -> from] + i -> weight;
                    if(k == n - 1) return true;
                }
            }
        }
    }
    return false;
}
/**
 * 経路を復元する
 *
 * @param prev 経路復元用の1つ前の位置を示す配列
 * @param t 経路を復元したい時の目的地
 */
vector<int> buildPath(const vector<int> &prev, int t){
    vector<int> path;
    for(int v = t; v >= 0; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}
