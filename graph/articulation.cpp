/**
 * @file
 * ## 関節点，二連結成分分解
 *
 * 連結なグラフ \f$G=(V,E)\f$ において頂点 \f$v \in V\f$ を削除した誘導部分グラフ \f$G[V-{v}]\f$ が非連結になるとき，
 * \f$v\f$ を \f$G\f$ の関節点と呼ぶ．また，任意の頂点を削除しても連結性が保たれる部分グラフを二連結成分と呼ぶ．
 *
 * グラフの関節点を見つけるには，深さ優先探索を行えばいい．グラフの任意の点について深さ優先探索を行った時の探索木を考えると，関節点について次の性質がわかる
 *
 * - 探索木の根の頂点が関節点である \f$\iff\f$ 探索木の根の子が2つ以上
 * - 探索木の葉は関節点ではない
 * - 上記2つを除く頂点vが関節点である \f$\iff\f$ 次の条件を満たすような探索木におけるvの子wが存在する．\f$w\f$ を根とする部分木において，
 * \f$v\f$ より上に昇る辺を持つ頂点が存在しない．
 *
 * ### ソースコード
 *
 * @include articulation.cpp
 */
void artcRecur(const Graph &g, int v, int u, vector<int> &artc,
               vector<vector<int> > &comp, vector<int> &low,
               vector<bool> &open, stack<int> &S, int &cnt){
    bool isArtc = false;
    int d, c = 0;
    low[v] = d = ++cnt;
    S.push(v);
    EACH(i, g[v]) if(i->to != u){
        if(low[i->to] == 0){
            artcRecur(g, i->to, v, artc, comp, low, open, S, cnt);
            ++c;
            if(low[i->to] >= low[v]){
                isArtc = true;
                comp.push_back(vector<int>());
                while(S.top() != v){
                    comp.back().push_back(S.top()); S.pop();
                }
                comp.back().push_back(v);
            }
        }
        d = min(d, low[i->to]);
    }
    low[v] = d;
    if(u >= 0 && isArtc || u < 0 && c > 1) artc.push_back(v);
    if(u < 0) S.pop();
}

/**
 * グラフ \a g の関節点と二連結成分を \f$O(|V|+|E|)\f$ 時間で計算する．
 * @param artc 関節点が格納されるベクタ．空であることが求められる．
 * @param comp 二連結成分が格納されるベクタ．空であることが求められる．
 */
void getArticulation(const Graph &g, vector<int> &artc, vector<vector<int> > &comp){
    int n = g.size();
    vector<int> low(n);
    vector<bool> open(n);
    stack<int> S;
    int cnt = 0;
    for(int i = 0; i < n; ++i) if(low[i] == 0){
        artcRecur(g, i, -1, artc, comp, low, open, S, cnt);
    }
}
