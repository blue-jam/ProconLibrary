/**
 * @file
 * ## 最小全域森(Kruskal)
 *
 * 辺のコストを小さいほうから見ていき，2つの短点がまだ連結していないときはその辺を加え，すでに連結なときは辺を加えない．同じ集合属しているか否かの判定を
 * [Union-Find木](union-find.html)を使用して調べている．
 *
 * グラフが連結な場合は最小全域木と一致する．また，N個の木からなる最小全域森を計算したい場合は，辺を1つ追加するごとに木の数が1つ減っていくことを利用して求めればよい．
 *
 * ### 計算量
 *
 *   * O(E log V) (= O(E log E))
 *
 * ### ソースコード
 *
 * @include kruskal.cpp
 *
 * ### 確認済み問題
 *
 *   * POJ 3723
 *
 * ### 参考
 *
 *   * [Spaghetti Source](http://www.prefield.com/algorithm/graph/kruskal.html)
 *   * プログラミングコンテストチャレンジブック(p101)
 */
/**
 * 辺の集合と頂点の数を受け取り，最小全域木を計算する．
 *
 * @param edges グラフに含まれる辺の集合．終了した後ソートされているので注意．
 * @param n グラフの頂点の個数
 * @return 最小全域森の重みとそれに含まれる辺の集合
 */
pair<Weight, Edges> kruskal_e(Edges &edges, int n){
    sort(ALL(edges)); reverse(ALL(edges));  //a < b <-> a.weight > b.weight
    int sz = edges.size();

    UnionFind uf(n);
    Weight total = 0;
    Edges F;
    for(int i = 0; i < sz; ++i){
        if(uf.unite(edges[i].from, edges[i].to)){
            total = total + edges[i].weight;
            F.push_back(edges[i]);
        }
    }
    return make_pair(total, F);
}
/**
 * グラフを受け取り，最小全域木を計算する．
 *
 * @param g 最小全域森を求めたいグラフ
 * @return 最小全域森の重みとそれに含まれる辺の集合
 */
pair<Weight, Edges> kruskal_g(const Graph &g){
	int n = g.size();
    vector<Edge> edges;
    for(int i = 0; i < n; ++i) edges.insert(edges.end(), ALL(g[i]));
    return kruskal_e(edges, n);
}
