// graph.cppとcrosspoint.cppが必要
// オーバーラップなしを仮定
Graph segmentArrangement(const vector<Segment> &ss, vector<P> &ps){
    for(int i = 0; i < ss.size(); ++i){
        ps.push_back(ss[i][0]);
        ps.push_back(ss[i][1]);
        for(int j=i+1;j<ss.size();++j){
            if(intersectSS(ss[i], ss[j]))
                ps.push_back(crosspointSS(ss[i], ss[j]));
        }
    }
    sort(ALL(ps), lessX); ps.erase(unique(ALL(ps), near), ps.end());
    Graph g(ps.size());
    for(int i=0;i<ss.size();++i){
        vector<pair<double, int> > lst;
        for(int j=0;j<ps.size();++j){
            if(ccw(ss[i][0], ss[i][1], ps[j]) == 0)
                lst.push_back(make_pair(norm(ss[i][0]-ps[j]), j));
        }
        sort(ALL(lst));
        for(int j=0;j+1<lst.size();++j){
            int a = lst[j].second, b = lst[j+1].second;
            addUndirectedEdge(g, a, b, abs(ps[a]-ps[b]));
        }
    }
    return g;
}
