// O(V^2 + VE log V)
Weight maordering(const Graph &g1, vector<int> &w){
    int n = g1.size();
    int cut = INF;
    UnionFind uf(n);
    priority_queue<Edge> Q;
    vector<int> used;
    vector<Weight> d;
    Graph g = g1;
    w.clear();
    for(int k = 0; k < n - 1; ++k){
        int s = uf.find(0), t = -1;
        Q.push(Edge(s, s, 0));
        d.assign(n, 0);
        used.assign(n, 0);
        while(!Q.empty()){
            Edge e = Q.top(); Q.pop();
            int v = uf.find(e.to);
            if(used[v]) continue;
            used[v] = true;
            s = uf.find(e.from);
            t = v;
            EACH(i, g[e.to]){
                int u = uf.find(i -> to);
                if(!used[u]){
                    d[u] -= i -> weight;
                    Q.push(Edge(v, u, d[u]));
                }
            }
        }
        if(cut > -d[t]){
            cut = -d[t];
            w.clear();
            for(int i = 0; i < n; ++i)
                if(uf.same(t, i)) w.push_back(i);
        }
        uf.unite(s, t);
        if(uf.find(s) != s) swap(s, t);
        g[s].insert(g[s].end(), ALL(g[t]));
    }
    return cut;
}
