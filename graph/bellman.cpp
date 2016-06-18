bool bellmanFord(const Graph &g, int s, vector<Weight> &dist, vector<int> &prev){
    int n = g.size();
    bool nagativeRoop = false;
    dist.assign(n, INF); dist[s] = 0;
    prev.assign(n, -1);
    for(int k = 0; k < n; ++k){
        for(int v = 0; v < n; ++v){
            EACH(i, g[v]){
            //for(Edges::const_iterator i=g[v].begin(); i != g[v].end(); ++i){
                if(dist[i -> from] != INF && dist[i -> to] > dist[i -> from] + i -> weight){
                    dist[i -> to] = dist[i -> from] + i-> weight;
                    prev[i -> to] = i -> from;
                    if(k == n - 1){
                        dist[i -> to] = -INF;
                        nagativeRoop = true;
                    }
                }
            }
        }
    }
    return nagativeRoop;
}
bool findNegativeRoop(const Graph &g){
    int n = g.size();
    vector<Weight> dist(n, 0);
    for(int k = 0; k < n; ++k){
        for(int v = 0; v < n; ++v){
            EACH(i, g[v]){
            //for(Edges::const_iterator i=g[v].begin(); i != g[v].end(); ++i){
                if(dist[i -> to] > dist[i -> from] + i -> weight){
                    dist[i -> to] = dist[i -> from] + i -> weight;
                    if(k == n - 1) return true;
                }
            }
        }
    }
    return false;
}
vector<int> buildPath(const vector<int> &prev, int t){
    vector<int> path;
    for(int v = t; v >= 0; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}
