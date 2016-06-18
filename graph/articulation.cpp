void artcRecur(const Graph &g, int v, int u, vector<int> &artc,
               vector<vector<int> > &comp, vector<int> &low,
               vector<bool> &open, stack<int> &S, int &cnt){
    bool isArtc = false;
    int d, c = 0;
    low[v] = d = ++cnt;
    S.push(v);
    EACH(i, g[v]) if(i->to != u){
        if(low[i->to] == 0){
            artcRecur(g, i->to, v, artc, comp, low, open, S, cnt);
            ++c;
            if(low[i->to] >= low[v]){
                isArtc = true;
                comp.push_back(vector<int>());
                while(S.top() != v){
                    comp.back().push_back(S.top()); S.pop();
                }
                comp.back().push_back(v);
            }
        }
        d = min(d, low[i->to]);
    }
    low[v] = d;
    if(u >= 0 && isArtc || u < 0 && c > 1) artc.push_back(v);
    if(u < 0) S.pop();
}
void getArticulation(const Graph &g, vector<int> &artc,
                     vector<vector<int> > &comp){
    int n = g.size();
    vector<int> low(n);
    vector<bool> open(n);
    stack<int> S;
    int cnt = 0;
    for(int i = 0; i < n; ++i) if(low[i] == 0){
        artcRecur(g, i, -1, artc, comp, low, open, S, cnt);
    }
}
