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
