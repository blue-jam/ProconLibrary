void dijkstra(const Graph &g, int s, vector<Weight> &dist, vector<int> &prev){
    int n = g.size();
    dist.assign(n, INF);
    dist[s] = 0;
    prev.assign(n, -1);
    priority_queue<Edge> Q;     // a < b <-> a.weight > b.weight
    Q.push(Edge(-2, s, 0));
    while(!Q.empty()){
        Edge e = Q.top(); Q.pop();
        if(prev[e.to] != -1) continue;
        prev[e.to] = e.from;
        EACH(i, g[e.to]){
        //for(Edges::const_iterator i=g[e.to].begin(); i!=g[e.to].end(); ++i){    //マクロが使えないとき
            if(dist[i -> to] > dist[i -> from] + i -> weight){
                dist[i -> to] = dist[i -> from] + i -> weight;
                Q.push(Edge(i -> from, i -> to, dist[i -> to]));
            }
        }
    }
}
vector<int> buildPath(const vector<int> &prev, int t){
    vector<int> path;
    for(int v = t; v >= 0; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}
