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
pair<Weight, Edges> kruskal_g(const Graph &g){
	int n = g.size();
    vector<Edge> edges;
    for(int i = 0; i < n; ++i) edges.insert(edges.end(), ALL(g[i]));
    return kruskal_e(edges, n);
}
