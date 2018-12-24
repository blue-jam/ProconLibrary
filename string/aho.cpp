/**
 * @file
 *
 * ## 複数パターンの検索(Aho-Corasick法)
 *
 * 複数の文字列パターンについていったんTrie木を構築した後，KMP法を実行しながら失敗したときのリンクを作成する．これにより，複数の文字列についてのマッチングが同時に行えるパターンマッチングオートマトンが作成できる．
 *
 * ### 計算量
 *
 *   * PMAの構築:O(m)
 *   * パターンの検索:O(n+m)
 *
 * * mはパターンの文字列の長さの総和．nは検索する文字列の長さ．
 *
 * ### ソースコード
 *
 * @include aho.cpp
 *
 * ### 確認済み問題
 *
 *   * SRM519 Div1 Medium (RequiredSubstrings)
 *
 * ### 参考
 *
 *   * [Spaghetti Source](http://www.prefield.com/algorithm/string/aho_corasick.html)
 *
 * ソースコードの参考．状態遷移の際に何回もリンク先へ飛ぶ必要がある，ほかの文字列を部分列として含んでいるときの対策がないといった点を改善した．また，DPを行いやすいように状態に一意のインデックスを割り振るようにした．
 */
struct PMA{
    int id;
    PMA *next[0x100];       //next[0] is for fail
    vector<int> accept;
    PMA() { fill(next, next + 0x100, (PMA*)NULL); }
};

/**
 * パターンマッチのオートマトンを生成する.
 *
 *   1. buildPMAを使ってPMAを構築する．
 *   2. vectorの先頭が開始状態なのでそこから検索を開始．
 *   3. 出てくる文字に応じて状態を遷移させながら読み進めていき一致するものを探す．acceptの中に一致するパターンの番号が入っている．
 *
 * パターンマッチングの状態を用いたDPがやりやすいように，各ノードにインデックスを持たせている．状態数は(パターンの数)*(文字列の長さ)でおおよそ見積もる．(必ず余裕は持たせる)
 */
//Pattern Matching AutoMaton
void buildPMA(vector<string> &words, vector<PMA*> &vp){
    int n = words.size();
    PMA *root = new PMA;    //createTrie
    root -> id = 0;
    vp.push_back(root);
    int count = 1;
    for(int i = 0; i<n; ++i){
        PMA *v = root;
        int m = words[i].size();
        for(int j = 0; j < m; ++j){
            int c = words[i][j];
            if(v -> next[c] == NULL){
                v -> next[c] = new PMA;
                v -> next[c] -> id = count++;
                vp.push_back(v -> next[c]);
            }
            v = v -> next[c];
        }
        v -> accept.push_back(i);
    }
    queue<PMA*> Q;          //make failure link
    for(int c = 1; c < 0x100; ++c){
        if(root -> next[c] != NULL){
            root -> next[c] -> next[0] = root;
            Q.push(root -> next[c]);
        } else root -> next[c] = root;
    }
    while(!Q.empty()){
        PMA *v = Q.front(); Q.pop();
        for(int c = 1; c < 0x100; ++c){
            if(v -> next[c] != NULL) 
                Q.push(v -> next[c]);
            PMA *r = v -> next[0];
            while(r -> next[c] == NULL) r = r -> next[0];
            if(v -> next[c] != NULL)
                v -> next[c] -> next[0] = r -> next[c];
            else
                v -> next[c] = r -> next[c];
        }
        v -> accept.insert(v -> accept.end(), ALL(v -> next[0] -> accept));
    }
}
