/**
 * @file
 *
 * ## Lowest Common Ancestor(二分探索)
 *
 * 根付き木に対し，その2頂点u,vの共通の祖先で最も近いところにあるものを求める．ここではダブリングを用いて2^k個ずつさかのぼることで求めている．
 *
 * 同じ高さまで上ったのち，LCA以上まで上ってしまう場合は上らず，LCAより低い位置ならそこまで上る．最終的にLCAの1個下まで到達するはずなので，片方の親がLCAとなっている．
 *
 *
 * ### 計算量
 *
 * 初期化 O(n log n)
 * クエリへの応答 O(log n)
 *
 * ### 使用方法
 *
 * initLCAで初期化する．木の親節点の情報をparentに保存する．ancestorには出力先のvectorを渡す．また，別に深さのvectorを作っておく．dijkstraを使ったのは1例に過ぎない．頂点数がそんなに多くない場合は再帰で，多い場合はstackを使って．
 * クエリを渡すときは，2つの頂点の番号と深さの情報，初期化で使用したvectorを渡す．
 *
 * ### ソースコード
 *
 * @include lca.cpp
 *
 * ### 確認済み問題
 *
 *   * AOJ 0575
 *
 * ### 参考
 *
 *   * プログラミングコンテストチャレンジブック(p.274-p.276)
 */

/**
 * @param parent 親の節点，ない場合は-1
 * @param depth よそで計算した深さ．親が0．
 */
void calcDepth(vector<int> &parent, int root, vector<int> &depth){
	int n = parent.size();
	vector<vector<int>> child(n);
	for(int i = 0; i < n; ++i) if(parent[i] >= 0) child[parent[i]].push_back(i);
	queue<int> Q;
	depth.assign(n, -1);
	Q.push(root);
	depth[0] = 0;
	while(!Q.empty()){
		int v = Q.front(); Q.pop();
		for(int u: child[v]) {
			depth[u] = depth[v] + 1;
			Q.push(u);
		}
	}
}

/**
 * initLCAで初期化する．木の親節点の情報をparentに保存する．ancestorには出力先のvectorを渡す．
 *
 * @param parent 親の節点，ない場合は-1
 * @param ancestor ダブリングで使用するvector
 */
void initLCA(vector<int> &parent, vector<vector<int> > &ancestor){
    int n = parent.size();
    int tn = 1;
    int maxLog = 0;
    for(maxLog = 0; tn < n; ++maxLog) tn *= 2;
    ancestor.resize(maxLog, vector<int>(n, -1));
    if(maxLog == 0) return;         //頂点が1個の時の処理．急遽付け加えたため確認はされていないので注意．
    for(int i = 0; i < n; ++i)
        ancestor[0][i] = parent[i];
    for(int i = 0; i + 1 < maxLog; ++i){
        for(int j = 0; j < n; ++j){
            if(ancestor[i][j] < 0)
                ancestor[i + 1][j] = -1;
            else
                ancestor[i + 1][j] = ancestor[i][ancestor[i][j]];
        }
    }
}

/**
 * クエリを渡すときは，2つの頂点の番号と深さの情報，初期化で使用したvectorを渡す．
 *
 * @param u 頂点番号その1
 * @param v 頂点番号その2
 * @param depth よそで計算した深さ．親が0．
 * @param ancestor ダブリングで使用するvector
 */
int lca(int u, int v, vector<int> &depth, vector<vector<int> > &ancestor){
    int maxLog = ancestor.size();
    if(depth[u] > depth[v]) swap(u, v);
    for(int k = 0; k < maxLog; ++k){
        if((depth[v] - depth[u]) >> k & 1){
            v = ancestor[k][v];
        }
    }
    if(u == v) return u;
    for(int k = maxLog - 1; k >= 0; --k){
        if(ancestor[k][u] != ancestor[k][v]){
            u = ancestor[k][u];
            v = ancestor[k][v];
        }
    }
    return ancestor[0][u];
}
