/**
 * @file
 *
 * ## 強連結成分分解(Tarjan's algorithm)
 *
 * 有向グラフ @f$G=(V,E)\f$ において，任意の点から任意の点への有向道が存在するとき @f$G@f$ は強連結であるという．
 * 必ずしも強連結でないグラフにおける極大な強連結部分グラフを強連結成分と呼ぶ．
 *
 * （あくまでも僕の周辺で）強連結成分分解としてポピュラーなのはトポロジカルソートを行った後，トポロジカル順序の逆順に頂点vを選び，
 * 逆グラフに対してDFSを行うKosaraju's algorithmだが，このアルゴリズムは逆グラフを作ったうえでDFSを2回を行う必要がある．
 * 対してTarjan's algorithmは逆グラフを作成する必要もなく，DFSも一回で済む．
 *
 * ### 確認済み問題
 *
 * - AOJ 2222(Alien's Counting)
 *
 * ### 参考
 *
 * - アルゴリズムとデータ構造-基礎のツールボックス-
 */

void sccRecur(const Graph &g, int v, vector<vector<int> > &comp,
                   vector<int> &num, vector<bool> &open,
                   stack<int> &oNodes, stack<int> &oReps, int &cnt){
    if(num[v] != 0){
        if(open[v]) while(num[oReps.top()] > num[v]) oReps.pop();
        return;
    }
    num[v] = ++cnt;
    oReps.push(v); oNodes.push(v); open[v] = true;
    EACH(i, g[v])
        sccRecur(g, i->to, comp, num, open, oNodes, oReps, cnt);
    if(v == oReps.top()){
        int w;
        oReps.pop();
        comp.push_back(vector<int>());
        do{
            w = oNodes.top(); oNodes.pop();
            open[w] = false;
            comp.back().push_back(w);
        }while(v != w);
    }
}

/**
 * グラフ @a g の強連結成分を @f$O(|V|+|E|)@f$ 時間で計算する
 *
 * @param comp 強連結成分を格納するベクタ（空推奨）
 */
void getSCC(const Graph &g, vector<vector<int> > &comp){
    int n = g.size();
    vector<int> num(n);
    vector<bool> open(n);
    stack<int> oReps, oNodes;
    int cnt = 0;
    for(int i = 0; i < n; ++i) if(num[i] == 0)
        sccRecur(g, i, comp, num, open, oNodes, oReps, cnt);
}
