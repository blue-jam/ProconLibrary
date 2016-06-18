bool topologicalRecur(const Graph &g, int v, vector<int> &order,
                      vector<int> &color){
    color[v] = 1;
    EACH(i, g[v]){
        if(color[i->to] == 1) return false;
        if(color[i->to] == 2) continue;
        topologicalRecur(g, i->to, order, color);
    }
    order.push_back(v); color[v] = 2;
    return true;
}
bool topologicalSort(const Graph &g, vector<int> &order){
    int n = g.size();
    vector<int> color(n);
    bool res = true;
    for(int i = 0; i < n; ++i) if(color[i] == 0)
        res = res && topologicalRecur(g, i, order, color);
    reverse(ALL(order));
    return res;
}
