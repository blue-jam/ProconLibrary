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
