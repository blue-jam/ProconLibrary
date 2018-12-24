/**
 * @file
 *
 * ## 橋，二辺連結成分分解
 *
 * グラフ \f$G=(V,E)\f$ において，辺 \f$e \in E\f$ を除いたグラフ \f$G^\prime=(V,E-{e})\f$ が連結でないとき，
 * \f$e\f$ を \f$G\f$ の橋と呼ぶ．また，任意の辺を1つ削除しても連結性が保たれる \f$G\f$ の極大な部分グラフを二辺連結成分と呼ぶ．
 *
 * 二辺連結成分であるかどうかを調べるには，連結成分1つにつき深さ優先探索を1回行えばよい．
 * 強連結成分分解のコードを少し変えると二辺連結成分分解のコードになる．詳しい説明は文献を参照．
 *
 * ### ソースコード
 *
 * @include bridge.cpp
 *
 * ### 確認済み問題
 *
 * - AOJ Courses Library Graph Connected Components Problem B
 *
 * ### 参考
 * - アルゴリズムとデータ構造-基礎のツールボックス-
 */

void bridgeRecur(const Graph &g, int v, int u,
                 Edges &bridge, vector<vector<int> > &comp,
                 vector<int> &num, vector<bool> &open,
                 stack<int> &oNodes, stack<int> &oReps, int &cnt){
    if(num[v] != 0){
        if(open[v]) while(num[oReps.top()] > num[v]) oReps.pop();
        return;
    }
    num[v] = ++cnt;
    oReps.push(v); oNodes.push(v); open[v] = true;
    EACH(i, g[v]) if(i->to != u)
        bridgeRecur(g, i->to, i->from, bridge, comp, num, open, oNodes, oReps, cnt);
    if(v == oReps.top()){
        int w;
        oReps.pop();
        comp.push_back(vector<int>());
        do{
            w = oNodes.top(); oNodes.pop();
            open[w] = false;
            comp.back().push_back(w);
        }while(v != w);
        bridge.push_back(Edge(min(u, v), max(u,v), 0));
    }
}

/**
 * グラフ @a g の橋と二辺連結成分を @f$O(|V|+|E|)@f$ 時間で計算する．
 * @param bridge 橋が格納されるベクタ(空推奨)
 * @param comp 二辺連結成分が格納されるベクタ(空推奨)
 */
void getBridge(const Graph &g, Edges &bridge, vector<vector<int> > &comp){
    int n = g.size();
    vector<int> num(n);
    vector<bool> open(n);
    stack<int> oReps, oNodes;
    int cnt = 0;
    for(int i = 0; i < n; ++i) if(num[i] == 0){
        bridgeRecur(g, i, n, bridge, comp, num, open, oNodes, oReps, cnt);
        bridge.pop_back();
    }
}
