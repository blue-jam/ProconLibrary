/**
 * @file
 *
 * ### トポロジカルソート
 *
 * 有向グラフgについて，頂点集合Vに対して順序を付け，v[i](0<=i<|V|)と並べたとする．
 * v[i]からv[j]に向かう枝が存在するならば，i<jが成り立つ時，この順序付けをトポロジカル順序と呼ぶ．
 *
 * トポロジカル順序を求めることをトポロジカルソートと呼び，DFSの帰りがけの順に頂点に番号を振っていくことでその逆順が求められる．
 *
 * ### ソースコード
 *
 * @include topologicalsort.cpp
 *
 * ### 確認済み問題
 *
 * - AOJ 2222(Alien's Counting)
 */

bool topologicalRecur(const Graph &g, int v, vector<int> &order, vector<int> &color){
    color[v] = 1;
    EACH(i, g[v]){
        if(color[i->to] == 1) return false;
        if(color[i->to] == 2) continue;
        topologicalRecur(g, i->to, order, color);
    }
    order.push_back(v); color[v] = 2;
    return true;
}

/**
 * グラフ \a g のトポロジカル順序を\f$O(\|V\|+\|E\|)\f$ 時間で計算する．
 * @param order トポロジカル順序が格納されるベクタ．空のベクタを渡す．
 * @return DAGであれば @a true を返す．
 */
bool topologicalSort(const Graph &g, vector<int> &order){
    int n = g.size();
    vector<int> color(n);
    bool res = true;
    for(int i = 0; i < n; ++i) if(color[i] == 0)
        res = res && topologicalRecur(g, i, order, color);
    reverse(ALL(order));
    return res;
}
